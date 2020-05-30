#include <stdint.h>

void send_status_packet(int status_type);
int recieve_data_packet(void **ret_packet);
int check_data_packet_type(const void *packet, char *package_type);
void free_data_packet(const void *packet);
uint32_t write_data(uint8_t *address, const void *packet);