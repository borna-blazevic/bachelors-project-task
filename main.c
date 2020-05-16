/* main.c */
#include "main.h"
#include "memory_config.h"


static void prvSetupHardware( void );

int main(void)
{
	int i;
	char c;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000);
	prvSetupHardware();
	gpio_led_state(LED6_BLUE_ID, 1);
	char *bootenv = &_shared_data_start;

	/* Start the Tx of the message on the UART. */
	print_string(bootenv);

	gpio_led_state(LED5_RED_ID, 1);

	if(*bootenv == 'R'){
		memcpy(bootenv,"UTask recovery sent hi\n", 24);
		NVIC_SystemReset();
	}
	memcpy(bootenv,"UTask recovery sent hi\n", 24);
	NVIC_SystemReset();
}


static void prvSetupHardware( void )
{
	gpio_init();
	init_communication();
}