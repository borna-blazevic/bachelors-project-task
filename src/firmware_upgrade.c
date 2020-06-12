
#include <firmware_package.pb-c.h>
#include <protobuf-c.h>
#include <stdint.h>
#include <communication.h>
#include <string.h>

void send_status_packet(int status_type)
{
	FirmwareUpgrade__Status status = FIRMWARE_UPGRADE__STATUS__INIT;
	uint8_t packet_size;
	uint8_t message_buffer[MAX_MSG_SIZE];
	switch (status_type)
	{
	case 1:
		status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__READY;
		break;
	case 2:
		status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__ACK;
		break;
	case 3:
		status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__REJECT;
		break;

	default:
		status.status = FIRMWARE_UPGRADE__STATUS__STATUS_ENUM__REJECT;
		break;
	}
	packet_size = firmware_upgrade__status__get_packed_size(&status);
	firmware_upgrade__status__pack(&status, message_buffer);
	message_buffer[packet_size] = '\0';
	print_string((char *)message_buffer);
	print_string("\n");
}
int recieve_data_packet(void **ret_packet)
{
	FirmwareUpgrade__FirmwarePacket *packet;
	uint8_t packet_size;
	uint8_t message_buffer[MAX_MSG_SIZE];
	if (read_packet(message_buffer, &packet_size))
		return -1;

	packet = firmware_upgrade__firmware_packet__unpack(NULL, packet_size * sizeof(char), message_buffer);

	if (packet == NULL)
		return 0;

	*ret_packet = packet;

	return sizeof(packet);
}

int check_data_packet_type(const void *packet, char *package_type)
{
	return strcmp(((FirmwareUpgrade__FirmwarePacket *)packet)->line->record_type, package_type);
}
void free_data_packet(const void *packet)
{
	firmware_upgrade__firmware_packet__free_unpacked((FirmwareUpgrade__FirmwarePacket *)packet, NULL);
}

uint32_t write_data(uint8_t *address, const void *packet)
{
	FirmwareUpgrade__FirmwarePacket *_packet = (FirmwareUpgrade__FirmwarePacket *)packet;
	memcpy(&address[_packet->line->address], _packet->line->data.data, _packet->line->data.len);
	return (uint32_t)&address[_packet->line->address + _packet->line->data.len];
}