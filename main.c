/* main.c */
#include "main.h"
#include <firmware_package.pb-c.h>
#include <protobuf-c.h>
#include <string.h>
#include <stm32f4xx_crc.h>

#define MAX_MSG_SIZE (500)

static void prvSetupHardware(void);

int main(void)
{
	FirmwareUpgrade__FirmwarePacket *packet;
	FirmwareUpgrade__Status status = FIRMWARE_UPGRADE__STATUS__INIT;
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
	status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__READY;
	packet_size = firmware_upgrade__status__get_packed_size(&status);
	firmware_upgrade__status__pack(&status, message_buffer);
	message_buffer[packet_size] = '\0';
	print_string(message_buffer);
	print_string("\n");

	while (1)
	{
		while (read_packet(message_buffer, &packet_size))
			;

		packet = firmware_upgrade__firmware_packet__unpack(NULL, packet_size * sizeof(char), message_buffer);

		if (packet == NULL)
		{
			print_string("packet null\n");
			status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__REJECT;
			packet_size = firmware_upgrade__status__get_packed_size(&status);
			firmware_upgrade__status__pack(&status, message_buffer);
			message_buffer[packet_size] = '\0';
			print_string(message_buffer);
			print_string("\n");
			continue;
		}

		uint32_t checksum32_data[500] = {0};

		checksum32_data[0] = (0xff00 & (packet->line->record_type[0] << 8)) | (0xff & packet->line->record_type[1]);
		checksum32_data[1] = packet->line->byte_count;
		checksum32_data[2] = packet->line->address;
		checksum32_data[3] = packet->line->checksum;

		uint32_t helper_mask[4] = {0xff, 0xff00, 0xff0000, 0xff000000};

		for (int i = 0; i < packet->line->data.len; i++)
		{
			int helper = 3 - i % 4;
			checksum32_data[4 + i / 4] = checksum32_data[4 + i / 4] | (helper_mask[helper] & (packet->line->data.data[i] << (8 * helper)));
		}

		uint32_t checksum;
		CRC_ResetDR();
		checksum = CRC_CalcBlockCRC(checksum32_data, packet->line->byte_count / 4 + 4);

		if (checksum != packet->checksum)
		{
			print_string("packet bad 1\n");
			status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__REJECT;
			packet_size = firmware_upgrade__status__get_packed_size(&status);
			firmware_upgrade__status__pack(&status, message_buffer);
			message_buffer[packet_size] = '\0';
			print_string(message_buffer);
			print_string("\n");
		}

		checksum = 0;
		checksum += (packet->line->address & helper_mask[0]);
		checksum += (packet->line->address & helper_mask[1]) >> 8;
		checksum += (packet->line->address & helper_mask[2]) >> 16;
		checksum += (packet->line->address & helper_mask[3]) >> 24;
		checksum += (packet->line->byte_count & helper_mask[0]);
		checksum += (packet->line->byte_count & helper_mask[1]) >> 8;
		checksum += (packet->line->byte_count & helper_mask[2]) >> 16;
		checksum += (packet->line->byte_count & helper_mask[3]) >> 24;
		for (int i = 0; i < packet->line->data.len; i++)
		{
			checksum += packet->line->data.data[i];
		}

		checksum = checksum & 0xff;

		checksum = checksum ^ 0xff;

		if (checksum != packet->line->checksum)
		{
			status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__REJECT;
			packet_size = firmware_upgrade__status__get_packed_size(&status);
			firmware_upgrade__status__pack(&status, message_buffer);
			message_buffer[packet_size] = '\0';
			print_string(message_buffer);
			print_string("\n");
		}

		if (!strcmp(packet->line->record_type, "S5"))
		{
			status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__ACK;
			packet_size = firmware_upgrade__status__get_packed_size(&status);
			firmware_upgrade__status__pack(&status, message_buffer);
			message_buffer[packet_size] = '\0';
			print_string(message_buffer);
			print_string("\n");
			break;
		}
		if (!strcmp(packet->line->record_type, "S0"))
		{
			status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__ACK;
			packet_size = firmware_upgrade__status__get_packed_size(&status);
			firmware_upgrade__status__pack(&status, message_buffer);
			message_buffer[packet_size] = '\0';
			print_string(message_buffer);
			print_string("\n");
			continue;
		}
		memcpy(&pImage[packet->line->address], packet->line->data.data, packet->line->data.len);
		bootenv[50] = (uint32_t)&pImage[packet->line->address + packet->line->data.len];
		firmware_upgrade__firmware_packet__free_unpacked(packet, NULL);

		status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__ACK;
		packet_size = firmware_upgrade__status__get_packed_size(&status);
		firmware_upgrade__status__pack(&status, message_buffer);
		message_buffer[packet_size] = '\0';
		print_string(message_buffer);
		print_string("\n");
	}
	bootenv[55] = 1;
	*bootenv = 2;

	memcpy(&pImage[800000], "hello", 5);

	print_string("wrong\n");
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