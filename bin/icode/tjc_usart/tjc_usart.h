/*
 * tjc_usart.h
 *
 *  Created on: Sep 16, 2024
 *      Author: zyc
 */

#ifndef TJC_USART_TJC_USART_H_
#define TJC_USART_TJC_USART_H_
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
/**
	��ӡ����Ļ����
*/



#define TJC_UART huart1
#define TJC_UART_INS USART1
extern UART_HandleTypeDef huart1;



void tjc_send_string(char* str);
void tjc_send_txt(char* objname, char* attribute, char* txt);
void tjc_send_val(char* objname, char* attribute, int val);
void tjc_send_nstring(char* str, unsigned char str_length);
void initRingBuffer(void);
void write1ByteToRingBuffer(uint8_t data);
void deleteRingBuffer(uint16_t size);
uint16_t getRingBufferLength(void);
uint8_t read1ByteFromRingBuffer(uint16_t position);




#define RINGBUFFER_LEN	(500)     //�����������ֽ��� 500

#define usize getRingBufferLength()
#define code_c() initRingBuffer()
#define udelete(x) deleteRingBuffer(x)
#define u(x) read1ByteFromRingBuffer(x)

extern uint8_t RxBuffer[1];
extern uint32_t msTicks;


#endif
