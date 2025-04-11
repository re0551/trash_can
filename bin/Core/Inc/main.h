/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern char box[1];
extern char rab[1];
extern uint16_t Red[4];
extern uint16_t bin[1];
extern  char str[100];
extern  int flag;

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Sensor1_Pin GPIO_PIN_2
#define Sensor1_GPIO_Port GPIOE
#define Sensor1_EXTI_IRQn EXTI2_IRQn
#define Sensor2_Pin GPIO_PIN_3
#define Sensor2_GPIO_Port GPIOE
#define Sensor2_EXTI_IRQn EXTI3_IRQn
#define Sensor3_Pin GPIO_PIN_4
#define Sensor3_GPIO_Port GPIOE
#define Sensor3_EXTI_IRQn EXTI4_IRQn
#define EN1_Pin GPIO_PIN_4
#define EN1_GPIO_Port GPIOA
#define STEP1_Pin GPIO_PIN_5
#define STEP1_GPIO_Port GPIOA
#define DIR1_Pin GPIO_PIN_6
#define DIR1_GPIO_Port GPIOA
#define DIR2_Pin GPIO_PIN_7
#define DIR2_GPIO_Port GPIOA
#define EN2_Pin GPIO_PIN_4
#define EN2_GPIO_Port GPIOC
#define EN3_Pin GPIO_PIN_0
#define EN3_GPIO_Port GPIOB
#define STEP3_Pin GPIO_PIN_1
#define STEP3_GPIO_Port GPIOB
#define DIR3_Pin GPIO_PIN_7
#define DIR3_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_12
#define IN1_GPIO_Port GPIOD
#define IN2_Pin GPIO_PIN_13
#define IN2_GPIO_Port GPIOD
#define EN_Pin GPIO_PIN_14
#define EN_GPIO_Port GPIOD
#define STEP2_Pin GPIO_PIN_6
#define STEP2_GPIO_Port GPIOC
#define KEY_Pin GPIO_PIN_6
#define KEY_GPIO_Port GPIOD
#define Sensor4_Pin GPIO_PIN_8
#define Sensor4_GPIO_Port GPIOB
#define Sensor4_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
