/*
 * FreeRTOS Kernel V10.3.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#include "FreeRTOS.h"
#include <stdlib.h>
#include <string.h>
#include <communication_uart.h>
#include <firmware_package.pb-c.h>
#include <protobuf-c.h>

/* Delay between cycles of the 'check' task. */
#define mainUART_DELAY						( ( TickType_t ) 10000 / portTICK_PERIOD_MS )

/* UART configuration - note this does not use the FIFO so is not very
efficient. */
#define mainBAUD_RATE				( 19200 )
#define mainFIFO_SET				( 0x10 )
#define MAX_MSG_SIZE				( 500 )

static void prvSetupHardware( void );

extern char _shared_data_start;
extern uint32_t _new_image_start;


uint32_t *pImage;
uint32_t recievingByte;

/*-----------------------------------------------------------*/


static void *custom_alloc(void *allocator_data, size_t size)
{
	print_string("hi custom malloc\n");
	return malloc(size);
}

static void custom_free(void *allocator_data, void *data)
{
	print_string("hi custom free\n");
	return;
}
static ProtobufCAllocator custom_c__allocator = {
	.alloc = &custom_alloc,
	.free = &custom_free,
	.allocator_data = NULL,
};

int main(void)
{
	/* Configure the clocks, UART and GPIO. */
	char *bootenv = &_shared_data_start;
	pImage = &_new_image_start;
	int i, j = 0;
	uint32_t imagesize;
	char recievingChar;
	FirmwareUpgrade__FirmwarePacket *packet;
	FirmwareUpgrade__SrecLine *srec_line;
	uint8_t packet_size;
	char message_buffer[MAX_MSG_SIZE];
	prvSetupHardware();

	/* Start the Tx of the message on the UART. */
	print_string(bootenv);

	if(*bootenv == 'R'){
		memcpy(bootenv,"UTask recovery sent hi\n", 24);
		SysCtlReset();
	}
	memcpy(bootenv,"UTask recovery sent hi\n", 24);
	
	while (1)
	{
		read_packet(message_buffer, &packet_size);
		char *test = malloc(sizeof(FirmwareUpgrade__SrecLine));

		print_uint8(&packet_size);

		custom_c__allocator.alloc(custom_c__allocator.allocator_data, sizeof(char));

		print_string("packet1\n");

		(&custom_c__allocator)->alloc((&custom_c__allocator)->allocator_data, sizeof(char));

		print_string("packet21\n");

		srec_line = firmware_upgrade__srec_line__unpack(&custom_c__allocator, sizeof(char), message_buffer);

		print_string("packet2\n");
		
		if(!strcmp(srec_line->record_type, "S5")) break;

		print_string("packet3\n");
		
		pImage = pImage + srec_line->address;

		print_string("packet4\n");

		memcpy(pImage, srec_line->data.data, srec_line->data.len);

		print_string("packet5\n");
	}
	
	
	
	// FlashUsecSet(SysCtlClockGet() / 1000000);

	// read_uint32(&imagesize);

	// j=1;



	// for (i = 1; i <= imagesize; i++)
	// {

	// 	if (j == 4)
	// 	{
	// 		read_uint8(&recievingChar);
	// 		recievingByte += ((uint32_t) recievingChar) << 24;
	// 		// if(FlashProtectSet(0xC000, FlashReadWrite)){
	// 		// 	if(FlashProtectGet(0xC000) == 0)
	// 		// 		printUART("Failed at set protect, protection set FlashReadWrite\n");
	// 		// 	if(FlashProtectGet(0xC000) == 1)
	// 		// 		printUART("Failed at set protect, protection set FlashReadOnly\n");
	// 		// 	if(FlashProtectGet(0xC000) == 2)
	// 		// 		printUART("Failed at set protect, protection set FlashExecuteOnly\n");
	// 		// 	continue;
	// 		// }
			
	// 		// if(FlashErase(pImage)){
	// 		// 	printUART("Falied at erase");
	// 		// 	continue;
	// 		// }

			
	// 		// if(FlashProgram(&recievingByte, pImage, sizeof(recievingByte))){
	// 		// 	printUART("Falied at program\n");
	// 		// 	continue;
	// 		// }
	// 		memcpy(pImage,&recievingByte,sizeof(recievingByte));
	// 		print_string("Bytes written\n");
	// 		pImage++;
	// 		j=1;
	// 	}
	// 	else if (j == 3)
	// 	{
	// 		read_uint8(&recievingChar);
	// 		recievingByte += ((uint32_t) recievingChar) << 16;
	// 		j=4;
	// 		print_string("Byte recieved\n");
	// 	}
	// 	else if (j == 2)
	// 	{
	// 		read_uint8(&recievingChar);
	// 		recievingByte += ((uint32_t) recievingChar) << 8;
	// 		j=3;
	// 		print_string("Byte recieved\n");
	// 	}
	// 	else
	// 	{
	// 		read_uint8(&recievingChar);
	// 		recievingByte =  ((uint32_t) recievingChar);
	// 		j=2;
	// 		print_string("Byte recieved\n");
	// 	}
	// }

	print_string("Done\n");
	SysCtlReset();
	
	return 0;
}
/*-----------------------------------------------------------*/
static void prvSetupHardware( void )
{
	init_uart_communication();
}

