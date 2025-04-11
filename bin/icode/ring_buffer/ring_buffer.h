/*
 * ring_buffer.h
 *
 *  Created on: Mar 5, 2025
 *      Author: zyc
 */

#ifndef RING_BUFFER_RING_BUFFER_H_
#define RING_BUFFER_RING_BUFFER_H_

#include <stdint.h>

#define BUFFER_SIZE 128

typedef struct {
    uint8_t data[BUFFER_SIZE];  // 数据存储数组
    volatile uint16_t head;     // 写指针
    volatile uint16_t tail;     // 读指针
} RingBuffer;

void RingBuffer_Init(RingBuffer *buf);
void RingBuffer_Clear(RingBuffer *buf);
uint8_t RingBuffer_Write(RingBuffer *buf, uint8_t data);
uint8_t RingBuffer_Read(RingBuffer *buf, uint8_t *data);

#endif /* RING_BUFFER_RING_BUFFER_H_ */
