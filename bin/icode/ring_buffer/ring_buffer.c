/*
 * ring_buffer.c
 *
 *  Created on: Mar 5, 2025
 *      Author: zyc
 */

#include "ring_buffer.h"

// 初始化缓冲区
void RingBuffer_Init(RingBuffer *buf) {
    buf->head = 0;
    buf->tail = 0;
}

// 清空缓冲区
void RingBuffer_Clear(RingBuffer *buf) {
    buf->head = 0;
    buf->tail = 0;
}

// 向缓冲区写入数据
uint8_t RingBuffer_Write(RingBuffer *buf, uint8_t data) {
    uint16_t next_head = (buf->head + 1) % BUFFER_SIZE;
    if (next_head != buf->tail) {  // 检查缓冲区是否已满
        buf->data[buf->head] = data;
        buf->head = next_head;
        return 1;  // 写入成功
    }
    return 0;  // 缓冲区已满，写入失败
}

// 从缓冲区读取数据
uint8_t RingBuffer_Read(RingBuffer *buf, uint8_t *data) {
    if (buf->tail != buf->head) {  // 检查缓冲区是否有数据
        *data = buf->data[buf->tail];
        buf->tail = (buf->tail + 1) % BUFFER_SIZE;
        return 1;  // 读取成功
    }
    return 0;  // 缓冲区为空，读取失败
}
