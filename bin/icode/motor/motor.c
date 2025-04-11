/*
 * motor.c
 *
 *  Created on: Sep 20, 2024
 *      Author: zyc
 */
#include "motor.h"
#include "../../icode/delay/delay.h"

void Servo_Control_up(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//占空比值 = 1/9 * 角度 + 5
   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint16_t )temp);
}

void Servo_Control_down(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//占空比值 = 1/9 * 角度 + 5
   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint16_t )temp);
}

void Servo_Control_a(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//占空比值 = 1/9 * 角度 + 5
   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint16_t )temp);
}

void Servo_Control_b(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//占空比值 = 1/9 * 角度 + 5
   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (uint16_t )temp);
}

void Servo_Control_c(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//占空比值 = 1/9 * 角度 + 5
   __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (uint16_t )temp);
}

void Servo_Control_d(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//占空比值 = 1/9 * 角度 + 5
   __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (uint16_t )temp);
}

//45中间，75/15最外面
void off()
{
	Servo_Control_d(60);
	delay_us(100000);
	Servo_Control_c(70);
	delay_us(100000);
	Servo_Control_b(40);
	delay_us(100000);
	Servo_Control_a(70);
	delay_us(300000);
}

void on()
{
	Servo_Control_a(35);
	delay_us(100000);
	Servo_Control_b(70);
	delay_us(100000);
	Servo_Control_c(40);
	delay_us(100000);
	Servo_Control_d(30);
	delay_us(300000);
}
