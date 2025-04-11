/*
 * ele.c
 *
 *  Created on: Oct 13, 2024
 *      Author: zyc
 */

#include "ele.h"

void dj1()
{
	HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, DIR1_Pin, GPIO_PIN_SET);

    for(int i=0;i<10;i++){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,i);
		delay_us(10);
            }
   HAL_Delay(100);
}

void dj2()
{
	HAL_GPIO_WritePin(GPIOC, EN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, DIR2_Pin, GPIO_PIN_RESET);

    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
    HAL_Delay(400);

    for(int i=0;i<10;i++){
     	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i);
    	delay_us(10);
    }
      HAL_Delay(100);
}

void dj3()
{
	HAL_GPIO_WritePin(GPIOB, EN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, DIR3_Pin, GPIO_PIN_RESET);

	for(int i=0;i<10;i++){
	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,i);
	     delay_us(10);
	}
}

void dj1_stop()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,0);
}

void dj2_stop()
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
}

void dj3_stop()
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,0);
}




