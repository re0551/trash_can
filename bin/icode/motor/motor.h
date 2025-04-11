/*
 * motor.h
 *
 *  Created on: Sep 20, 2024
 *      Author: huawei
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#include "stm32f4xx_hal.h" //HAL¿âÎÄ¼þÉùÃ÷
#include "main.h"
#include "tim.h"

void Servo_Control_up(uint16_t angle);
void Servo_Control_down(uint16_t angle);
void Servo_Control_next_a(uint16_t angle);
void Servo_Control_next_b(uint16_t angle);
void Servo_Control_next_c(uint16_t angle);
void Servo_Control_next_d(uint16_t angle);
void on(void);
void off(void);
#endif /* MOTOR_MOTOR_H_ */
