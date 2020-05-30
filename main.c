/* main.c */
#include "main.h"
#include <string.h>


static void prvSetupHardware(void);

int main(void)
{
	uint8_t *pImage = &_firmware_upgrade;
	uint32_t *bootenv = &_shared;
	void *packet;

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

	bootenv[55] = 0;
	send_status_packet(1);

	while (1)
	{
		if (!recieve_data_packet(&packet))
		{
			send_status_packet(3);
			continue;
		}

		if (!check_data_packet_checksum(packet))
		{
			send_status_packet(3);
			continue;
		}

		if (!check_srec_line_checksum(packet))
		{
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


