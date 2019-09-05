/*
 * uart.h
 *
 *  Created on: 03-07-2015
 *      Author: someone
 */

#ifndef UART_H_
#define UART_H_

void USART_Init(void);
void USART_Write_Number(long number);
void USART_Write(char data);
void USART_String(const char* str);


#endif /* UART_H_ */
