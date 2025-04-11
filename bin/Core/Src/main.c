/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"
#include <stdbool.h>
#include "../../icode/motor/motor.h"
#include "../../icode/tjc_usart/tjc_usart.h"
#include "../../icode/delay/delay.h"
#include "../../icode/rubbish/rubbish.h"
#include "../../icode/infrared/infrared.h"
#include "../../icode/direct_m/direct_m.h"
#include "../../icode/ele/ele.h"
#include "../../icode/ring_buffer/ring_buffer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define FRAME_LENGTH 7

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char box[1] = {0};
char rab[1] = {0};
char tr[1] = {'9'};
char str[100];
uint16_t Red[4] = {0};
uint16_t bin[1] = {0};
uint8_t motor1_forward_flag = 1;
uint8_t motor2_forward_flag = 1;
uint8_t motor1_stop_flag = 0;
uint8_t motor2_stop_flag = 0;
int flag = 0;
volatile uint8_t send_flag = 0;
float angle;
// ����ȥ������صı���
static volatile uint32_t last_debounce_time = 0;
const uint32_t debounce_delay = 10; // ȥ������ʱʱ�䣬��λ������
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {// �ⲿ�жϻص�����
	// ���ؼ��
//	if (GPIO_Pin == GPIO_PIN_2) {
//	    // ����ʼ�ź�
//	    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == GPIO_PIN_RESET) {
//	        // �ӳ� 2 �루�ɸ�����Ҫ����ʱ�䣩
//	        delay_us(2000000);
//
//	        // �ٴ�ȷ�Ϻ����ź�
//	        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == GPIO_PIN_RESET) {
//	            Red[0] = 1;               // �������ر�־
//	            Infrared(1);              // ����״̬��Ч����
//	        }
//	    }
//	    // ����жϱ�־λ
//	    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
//	} else {
//	    Red[0] = 0;  // δ��⵽���أ������־
//	}
//
	if (GPIO_Pin == GPIO_PIN_3) {
	    // ����ʼ�ź�
	    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET) {
	        // �ӳ� 2 �루�ɸ�����Ҫ����ʱ�䣩
	        delay_us(2000000);

	        // �ٴ�ȷ�Ϻ����ź�
	        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET) {
	            Red[1] = 1;               // �������ر�־
	            Infrared(1);              // ����״̬��Ч����
	        }
	    }
	    // ����жϱ�־λ
	    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
	} else {
	    Red[1] = 0;  // δ��⵽���أ������־
	}
//
//	if (GPIO_Pin == GPIO_PIN_4) {
//	    // ����ʼ�ź�
//	    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_RESET) {
//	        // �ӳ� 2 �루�ɸ�����Ҫ����ʱ�䣩
//	        delay_us(2000000);
//
//	        // �ٴ�ȷ�Ϻ����ź�
//	        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_RESET) {
//	            Red[2] = 1;               // �������ر�־
//	            Infrared(1);              // ����״̬��Ч����
//	        }
//	    }
//	    // ����жϱ�־λ
//	    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
//	} else {
//	    Red[2] = 0;  // δ��⵽���أ������־
//	}
//
//	if (GPIO_Pin == GPIO_PIN_8) {
//	    // ����ʼ�ź�
//	    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) {
//	        // �ӳ� 2 �루�ɸ�����Ҫ����ʱ�䣩
//	        delay_us(2000000);
//
//	        // �ٴ�ȷ�Ϻ����ź�
//	        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) {
//	            Red[3] = 1;               // �������ر�־
//	            Infrared(1);              // ����״̬��Ч����
//	        }
//	    }
//	    // ����жϱ�־λ
//	    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
//	} else {
//	    Red[3] = 0;  // δ��⵽���أ������־
//	}

    // ���ʹ�������
    if (GPIO_Pin == GPIO_PIN_1) {  // ��⵽һ����դ�ź�
        // ��ȡ��ǰʱ��
        uint32_t current_time = HAL_GetTick();

        // ����Ƿ񳬹���ȥ������ʱʱ��
        if ((current_time - last_debounce_time) >= debounce_delay) {
            // ��¼��ǰʱ��
            last_debounce_time = current_time;

            // �ٴμ������״̬
            if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1) == GPIO_PIN_RESET) {
                // ִ����Ӧ�Ķ���
            	dj1_stop();
            	motor1_forward_flag = 0;
                // ����жϱ�־
                __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
            }
        }
    }

    if (GPIO_Pin == GPIO_PIN_0) {  // ��⵽������դ�ź�
        // ��ȡ��ǰʱ��
        uint32_t current_time = HAL_GetTick();

        // ����Ƿ񳬹���ȥ������ʱʱ��
        if ((current_time - last_debounce_time) >= debounce_delay) {
            // ��¼��ǰʱ��
            last_debounce_time = current_time;

            // �ٴμ������״̬
            if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0) == GPIO_PIN_RESET) {
                // ִ����Ӧ�Ķ���
            	dj2_stop();
            	dj3_stop();
            	motor2_stop_flag = 1;
            	motor2_forward_flag = 0;
            	motor1_forward_flag = 0;
                send_flag = 1; // ���÷��ͱ�־
                // ����жϱ�־
                __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
            }
        }
    }
}


// ����ȫ�ֻ�����
RingBuffer rx_buffer;

// ����У�麯��
uint8_t is_valid_data(uint8_t data) {
    return (data == '1' || data == '6' || data == '3' || data == '4' || data == '5' || data == '8');
}

// USART2�����жϻص�����
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart2) {
        HAL_UART_Receive_IT(&huart2, (uint8_t*)box, 1);
        uint8_t received_data = box[0];  // ��ȡ���յ�������
        // ��������Ƿ�Ϸ�
        if (is_valid_data(received_data)) {
            // ���Ϸ����ݴ��뻺����
            if (!RingBuffer_Write(&rx_buffer, received_data)) {
                // ������������������Ӵ������߼�
                printf("Buffer is full!\n");
            }
        }
    } else if (huart->Instance == TJC_UART_INS) {
        write1ByteToRingBuffer(RxBuffer[0]);
        HAL_UART_Receive_IT(&TJC_UART, RxBuffer, 1);  // ����ʹ�ܴ���1�����ж�
    }
}

// ������������
void ProcessBufferData(void) {
    uint8_t data;
    while (RingBuffer_Read(&rx_buffer, &data)) {  // �ӻ�������ȡ����
        printf("Received data: %c, is_valid: %d\n", data, is_valid_data(data));  // ��ӡ������Ϣ
        if (is_valid_data(data)) {  // ��������Ƿ�Ϸ�
            switch (data) {  // ��������ִ�ж������
                case '1':
                    HAL_UART_Transmit(&huart2, (uint8_t*)tr, 1, 1000);
                    break;
                case '8':
                    rab[0] = box[0];
                    rubbish();
                    break;
                case '4':
                    off();
                    Servo_Control_down(9);
                    delay_us(20000);
                    Servo_Control_up(3);
                    delay_us(500000);
                    Servo_Control_up(45);
                    delay_us(20000);
                    Servo_Control_down(53);
                    delay_us(300000);
                    on();
                	motor1_forward_flag = 1;
                	motor2_forward_flag = 1;
                    rab[0] = box[0];
                    rubbish();
                    break;
                case '6':
                    off();
                    Servo_Control_down(90);
                    delay_us(20000);
                    Servo_Control_up(90);
                    delay_us(500000);
                    Servo_Control_up(45);
                    delay_us(20000);
                    Servo_Control_down(53);
                    delay_us(300000);
                    on();
                	motor1_forward_flag = 1;
                	motor2_forward_flag = 1;
                    rab[0] = box[0];
                    rubbish();
                    break;
                case '5':
                    off();
                    Servo_Control_down(10);
                    delay_us(20000);
                    Servo_Control_up(75);
                    delay_us(500000);
                    Servo_Control_up(45);
                    delay_us(20000);
                    Servo_Control_down(53);
                    delay_us(300000);
                    on();
                	motor1_forward_flag = 1;
                	motor2_forward_flag = 1;
                    rab[0] = box[0];
                    rubbish();
                    break;
                case '3':
                    off();
                    Servo_Control_down(115);
                    delay_us(20000);
                    Servo_Control_up(5);
                    delay_us(500000);
                    Servo_Control_up(45);
                    delay_us(20000);
                    Servo_Control_down(53);
                    delay_us(300000);
                    on();
                	motor1_forward_flag = 1;
                	motor2_forward_flag = 1;
                    rab[0] = box[0];
                    rubbish();
                    break;
                default:
                    break;
            }
        }
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM9_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
    HAL_UART_Receive_IT(&huart2, (uint8_t*)box, 1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

    initRingBuffer();  // ��ʼ�����λ�����
    HAL_UART_Receive_IT(&TJC_UART, RxBuffer, 1);  // �򿪴��ڽ����ж�

    // ��ʼ��������
    RingBuffer_Init(&rx_buffer);
    // ����USART2�����ж�
    HAL_UART_Receive_IT(&huart2, (uint8_t*)box, 1);

    //����
    off();
    Servo_Control_up(45);
    delay_us(20000);
    Servo_Control_down(53);
    delay_us(1000000);
    on();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
            // ����USART2����������
            ProcessBufferData();

            if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6) == GPIO_PIN_RESET) { // ��������

                if (send_flag) {
                    HAL_UART_Transmit(&huart2, (uint8_t*)tr, 1, 1000);
                    send_flag = 0;
                }

                // ���ʹ�����
                if (motor1_forward_flag) {
                    dj1();
                }

                if (motor2_forward_flag) {
                	dj2();
                	dj3();
                }

                if (motor2_stop_flag) {
                    dj2_stop();
                    dj3_stop();
                    motor2_stop_flag = 0;
                }

                //���ؼ��
                full();

                // �Ƹ�ѹ������
                if (flag == 10) {
                    Forward();
                    delay_us(2200000);
                    Stop();
                    delay_us(1000000);
                    Back();
                    delay_us(2200000);
                    Stop();
                    flag = 0;
                }
            }
        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

