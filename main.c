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


/* Environment includes. */
#include "DriverLib.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart.h"
#include "flash.h"

/* Delay between cycles of the 'check' task. */
#define mainUART_DELAY						( ( TickType_t ) 10000 / portTICK_PERIOD_MS )

/* UART configuration - note this does not use the FIFO so is not very
efficient. */
#define mainBAUD_RATE				( 19200 )
#define mainFIFO_SET				( 0x10 )
/*
 * Configure the processor and peripherals for this demo.
 */


static void prvSetupHardware( void );
static void vUARTTask( void *pvParameter );



char uart_buffer[50];

extern char _shared_data_start;
extern uint32_t _new_image_start;


uint32_t *pImage;
uint32_t recievingByte;
static volatile char *pcNextChar;

void printUART(char *mes);

/*-----------------------------------------------------------*/

int main(void)
{
	/* Configure the clocks, UART and GPIO. */
	char *bootenv = &_shared_data_start;
	pImage = &_new_image_start;
	int i;
	uint32_t imagesize;
	char check[5];
	prvSetupHardware();

	/* Start the Tx of the message on the UART. */
	UARTIntDisable(UART0_BASE, UART_INT_TX);
	{
		pcNextChar = bootenv;
		/* Send the first character. */
		if (!(HWREG(UART0_BASE + UART_O_FR) & UART_FR_TXFF))
		{
			HWREG(UART0_BASE + UART_O_DR) = *pcNextChar;
		}

		pcNextChar++;
	}
	UARTIntEnable(UART0_BASE, UART_INT_TX);
	memcpy(bootenv,"UTask sent hi\n", 15);

	
	imagesize = UARTCharGet(UART0_BASE);
	imagesize |= UARTCharGet(UART0_BASE)<<8;
	imagesize |= UARTCharGet(UART0_BASE)<<16;
	imagesize |= UARTCharGet(UART0_BASE)<<24;

	for (i = 1; i <= imagesize; i++)
	{
		if (i % 4 == 0)
		{
			recievingByte += UARTCharGet(UART0_BASE) << 24;
			if(FlashProtectSet(pImage, FlashReadWrite)){
				if(FlashProtectGet(pImage) == 0)
					printUART("Failed at set protect, protection set FlashReadWrite");
				if(FlashProtectGet(pImage) == 1)
					printUART("Failed at set protect, protection set FlashReadOnly");
				if(FlashProtectGet(pImage) == 2)
					printUART("Failed at set protect, protection set FlashExecuteOnly");
			}
			
			if(FlashErase(pImage))
				printUART("Falied at erase");

			
			if(FlashProgram(&recievingByte, pImage, sizeof(recievingByte)))
				printUART("Falied at program");
		}
		else if (i % 3 == 0)
		{
			recievingByte += UARTCharGet(UART0_BASE) << 16;
			printUART("hi");
		}
		else if (i % 2 == 0)
		{
			recievingByte += UARTCharGet(UART0_BASE) << 8;
			printUART("hi");
		}
		else
		{
			recievingByte = UARTCharGet(UART0_BASE);
			printUART("hi");
		}
	}
	printUART("Done");
	return 0;
}
/*-----------------------------------------------------------*/

void printUART(char *mes){
	
	while (*mes != '\0')
	{
		UARTCharPut(UART0_BASE, *mes);
		mes++;
	}
	UARTCharPut(UART0_BASE, '\n');
	
}

static void prvSetupHardware( void )
{
	/* Setup the PLL. */
	SysCtlClockSet( SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ );

	/* Enable the UART.  */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	/* Set GPIO A0 and A1 as peripheral function.  They are used to output the
	UART signals. */
	GPIODirModeSet( GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_DIR_MODE_HW );

	/* Configure the UART for 8-N-1 operation. */
	UARTConfigSet( UART0_BASE, mainBAUD_RATE, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE );

	/* We don't want to use the fifo.  This is for test purposes to generate
	as many interrupts as possible. */
	HWREG( UART0_BASE + UART_O_LCR_H ) &= ~mainFIFO_SET;

	/* Enable Tx interrupts. */
	HWREG( UART0_BASE + UART_O_IM ) |= UART_INT_RX;
	IntPrioritySet( INT_UART0, configKERNEL_INTERRUPT_PRIORITY );
	IntEnable( INT_UART0 );
}

static void vUARTTask( void *pvParameters )
{


}

/*-----------------------------------------------------------*/

void vUART_ISR(void)
{
unsigned long ulStatus;

	/* What caused the interrupt. */
	ulStatus = UARTIntStatus( UART0_BASE, pdTRUE );

	/* Clear the interrupt. */
	UARTIntClear( UART0_BASE, ulStatus );

	/* Was a Tx interrupt pending? */
	if( ulStatus & UART_INT_TX )
	{
		/* Send the next character in the string.  We are not using the FIFO. */
		if( *pcNextChar != 0 )
		{
			if( !( HWREG( UART0_BASE + UART_O_FR ) & UART_FR_TXFF ) )
			{
				HWREG( UART0_BASE + UART_O_DR ) = *pcNextChar;
			}
			pcNextChar++;
		}
	}
}