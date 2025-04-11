/*
 * ring_buffer.c
 *
 *  Created on: Mar 5, 2025
 *      Author: zyc
 */

#include "ring_buffer.h"

// ��ʼ��������
void RingBuffer_Init(RingBuffer *buf) {
    buf->head = 0;
    buf->tail = 0;
}

// ��ջ�����
void RingBuffer_Clear(RingBuffer *buf) {
    buf->head = 0;
    buf->tail = 0;
}

// �򻺳���д������
uint8_t RingBuffer_Write(RingBuffer *buf, uint8_t data) {
    uint16_t next_head = (buf->head + 1) % BUFFER_SIZE;
    if (next_head != buf->tail) {  // ��黺�����Ƿ�����
        buf->data[buf->head] = data;
        buf->head = next_head;
        return 1;  // д��ɹ�
    }
    return 0;  // ������������д��ʧ��
}

// �ӻ�������ȡ����
uint8_t RingBuffer_Read(RingBuffer *buf, uint8_t *data) {
    if (buf->tail != buf->head) {  // ��黺�����Ƿ�������
        *data = buf->data[buf->tail];
        buf->tail = (buf->tail + 1) % BUFFER_SIZE;
        return 1;  // ��ȡ�ɹ�
    }
    return 0;  // ������Ϊ�գ���ȡʧ��
}
