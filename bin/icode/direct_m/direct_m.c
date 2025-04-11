/*
 * l298n.c
 *
 *  Created on: Oct 4, 2024
 *      Author: huawei
 */

#include "direct_m.h"

void Forward()
{
	HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, IN2_Pin, GPIO_PIN_RESET);
}

void Back()
{
	HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, IN2_Pin, GPIO_PIN_SET);
	}

void Stop()
{
	HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, IN2_Pin, GPIO_PIN_SET);
}


