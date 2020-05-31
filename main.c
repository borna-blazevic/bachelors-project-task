/* main.c */
#include "main.h"
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>

static void prvSetupHardware(void);
static void blinky_task(void *pvParameters);
static void firmware_upgrade_task(void *pvParameters);

int main(void)
{
	uint32_t *bootenv = &_shared;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000);
	prvSetupHardware();

	/* Start the Tx of the message on the UART. */

	if (*bootenv == 2)
	{
		print_string("\nbooted task and restarting\n");
		*bootenv = 3;
		NVIC_SystemReset();
	}
	print_string("\nbooted task and upgrading\n");

	xTaskCreate(firmware_upgrade_task, "firmware_upgrade_task", 10000, NULL, 5, NULL);
	xTaskCreate(blinky_task, "blinky_task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

static void blinky_task(void *pvParameters)
{
	uint32_t led_state;
	led_state = 1; // ON
	while (1)
	{
		gpio_led_state(LED4_GREEN_ID, led_state);
		led_state = (led_state == 1) ? 0 : 1;
		vTaskDelay(100 / portTICK_RATE_MS); // LED blinking frequency
	}
}

static void firmware_upgrade_task(void *pvParameters)
{
	void *packet;
	int r;
	uint32_t *bootenv = &_shared;
	uint8_t *pImage = &_firmware_upgrade;
	bootenv[55] = 0;
	uint32_t led_state = 1; // ON
	send_status_packet(1);
	while (1)
	{
		do
		{
			vTaskDelay(10 / portTICK_RATE_MS); // LED blinking frequency
			r = recieve_data_packet(&packet);
			if (r == -1)
				send_status_packet(1);
			else
				break;
		} while (1);

		if (r == 0)
		{
			send_status_packet(3);
			continue;
		}

		if (!check_data_packet_checksum(packet))
		{
			free_data_packet(packet);
			send_status_packet(3);
			continue;
		}

		if (!check_srec_line_checksum(packet))
		{
			free_data_packet(packet);
			send_status_packet(3);
			continue;
		}

		if (!check_data_packet_type(packet, "S5"))
		{
			free_data_packet(packet);
			send_status_packet(2);
			break;
		}

		if (!check_data_packet_type(packet, "S0"))
		{
			free_data_packet(packet);
			send_status_packet(2);
			continue;
		}
		free_data_packet(packet);
		bootenv[50] = write_data(pImage, packet);
		send_status_packet(2);
	}
	bootenv[55] = 1;
	*bootenv = 2;
	NVIC_SystemReset();
}

static void prvSetupHardware(void)
{
	gpio_init();
	init_communication();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
}

void HardFault_Handler(void)
{
	NVIC_SystemReset();
}
