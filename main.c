/* main.c */
#include "main.h"
#include <firmware_package.pb-c.h>
#include <protobuf-c.h>
#include <string.h>

#define MAX_MSG_SIZE (500)

static void prvSetupHardware(void);

int main(void)
{
	FirmwareUpgrade__FirmwarePacket *packet;
	FirmwareUpgrade__SrecLine *srec_line;
	uint8_t packet_size;
	uint8_t message_buffer[MAX_MSG_SIZE];
	uint8_t *pImage = &_firmware_upgrade;
	uint32_t *bootenv = &_shared;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000);
	prvSetupHardware();

	/* Start the Tx of the message on the UART. */

	if (*bootenv == 2)
	{
		print_string("booted task and restarting\n");
		*bootenv = 3;
		NVIC_SystemReset();
	}
	print_string("booted task and upgrading\n");
	bootenv[55] = 0;
	while (1)
	{
		print_string("hi\n");
		while (read_packet(message_buffer, &packet_size))
			;


		srec_line = firmware_upgrade__srec_line__unpack(NULL, packet_size * sizeof(char), message_buffer);

		if(srec_line == NULL){
			continue;
		}

		if (!strcmp(srec_line->record_type, "S5")){
			print_string("Got S5\n");
			break;
		}
		if (!strcmp(srec_line->record_type, "S0"))
			continue;

		memcpy(&pImage[srec_line->address], srec_line->data.data, srec_line->data.len);
		bootenv[50] = (uint32_t) &pImage[srec_line->address + srec_line->data.len];
  		firmware_upgrade__srec_line__free_unpacked(srec_line, NULL);
	}
	bootenv[55] = 1;
	*bootenv = 2;

	NVIC_SystemReset();
}

static void prvSetupHardware(void)
{
	gpio_init();
	init_communication();
}