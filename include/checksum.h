#include <stdint.h>

int check_data_packet_checksum(const void *packet, uint32_t secret);
int check_srec_line_checksum(const void *packet);