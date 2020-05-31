/* usart.h */
#ifndef USART_H
#define USART_H

#define BUFSIZE 256
#define BAUDRATE 115200

void USART1_Init(void);       // init USART1 peripheral
void USART1_SendChar(char c); // blocking send character
int USART1_Dequeue(char *c);  // pop character from receive FIFO

#endif