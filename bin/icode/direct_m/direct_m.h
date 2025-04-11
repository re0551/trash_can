/*
 * l298n..h
 *
 *  Created on: Oct 4, 2024
 *      Author: huawei
 */

#ifndef DIRECT_M_DIRECT_M_H_
#define DIRECT_M_DIRECT_M_H_

#include "stm32f4xx_hal.h" //HAL¿âÎÄ¼þÉùÃ÷
#include "main.h"
#include "tim.h"


#include <stdint.h>

void Forward(void);
void Back(void);
void Stop(void);


#endif /* DIRECT_M_DIRECT_M_H_ */
