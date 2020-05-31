
#include <firmware_package.pb-c.h>
#include <protobuf-c.h>
#include <stdint.h>
#include <communication.h>
#include <stm32f4xx_crc.h>

int check_data_packet_checksum(const void *packet)
{
	uint32_t checksum32_data[500] = {0};
	FirmwareUpgrade__FirmwarePacket *_packet = (FirmwareUpgrade__FirmwarePacket *)packet;
	uint32_t helper_mask[4] = {0xff, 0xff00, 0xff0000, 0xff000000};
	uint32_t checksum;

	if(_packet->line->data.len == _packet->line->address && _packet->line->data.len == _packet->line->byte_count )
		return 0;

	checksum32_data[0] = (0xff00 & (_packet->line->record_type[0] << 8)) | (0xff & _packet->line->record_type[1]);
	checksum32_data[1] = _packet->line->byte_count;
	checksum32_data[2] = _packet->line->address;
	checksum32_data[3] = _packet->line->checksum;

	for (int i = 0; i < _packet->line->data.len; i++)
	{
		int helper = 3 - i % 4;
		checksum32_data[4 + i / 4] = checksum32_data[4 + i / 4] | (helper_mask[helper] & (_packet->line->data.data[i] << (8 * helper)));
	}

	CRC_ResetDR();
	checksum = CRC_CalcBlockCRC(checksum32_data, _packet->line->byte_count / 4 + 4);

	return checksum == _packet->checksum;
}

int check_srec_line_checksum(const void *packet)
{
	FirmwareUpgrade__FirmwarePacket *_packet = (FirmwareUpgrade__FirmwarePacket *)packet;
	uint32_t helper_mask[4] = {0xff, 0xff00, 0xff0000, 0xff000000};
	uint32_t checksum;

	checksum = 0;
	checksum += (_packet->line->address & helper_mask[0]);
	checksum += (_packet->line->address & helper_mask[1]) >> 8;
	checksum += (_packet->line->address & helper_mask[2]) >> 16;
	checksum += (_packet->line->address & helper_mask[3]) >> 24;
	checksum += (_packet->line->byte_count & helper_mask[0]);
	checksum += (_packet->line->byte_count & helper_mask[1]) >> 8;
	checksum += (_packet->line->byte_count & helper_mask[2]) >> 16;
	checksum += (_packet->line->byte_count & helper_mask[3]) >> 24;
	for (int i = 0; i < _packet->line->data.len; i++)
	{
		checksum += _packet->line->data.data[i];
	}

	checksum = checksum & 0xff;

	checksum = checksum ^ 0xff;

	return checksum == _packet->line->checksum;
}