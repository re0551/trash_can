/*
 * sevor.c
 *
 *  Created on: Apr 2, 2024
 *      Author: 29257
 */
#include "../../BSP/sevor/sevor.h"

#include <stdio.h>
#include<math.h>

uint16_t  Sevor_ccr = 500 ; //�ٶ�����
uint32_t pulse;
void Dir (uint8_t dir)
{
	if(dir == 1)
	{
		delay_us(2000);
		HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_SET);
	}
	else if(dir == 0)
	{
		delay_us(2000);
		HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_RESET);
	}
}
void En (uint8_t en)
{
	if(en == 1)
	{
		delay_us(2000);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
	}
	else if(en == 0)
	{
		delay_us(2000);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
	}
}


void Sevor_Init(void)
{
	 HAL_TIM_OC_Start_IT(&Sevor_motor_tim, Secor_motor_Channle);

	 En(0);
	 Dir(1);
}

void Sevor_Speed_Improve(uint16_t num)
{
	Sevor_ccr -= num;
}

void Sevor_Speed_Reduce(uint16_t num)
{
	Sevor_ccr += num;
}

void Sevor_Angle2Pulse(int angle) {
	if (angle > 0) {
		Dir(1);
	} else {
		Dir(0);
	}
	pulse = angle / 0.225;
	if (pulse == 0) {
		HAL_TIM_OC_Stop_IT(&Sevor_motor_tim, Secor_motor_Channle);
	} else
		HAL_TIM_OC_Start_IT(&Sevor_motor_tim, Secor_motor_Channle);

}
/********************************************���μӼ���***********************************************/
Sevor_Motor g_srd               = {STOP,CW,0,0,0,0,0};  /* �Ӽ��ٱ��� */
__IO int32_t  g_step_position     = 0;                    /* ��ǰλ�� */
__IO uint8_t  g_motion_sta        = 0;                    /* �Ƿ����˶���0��ֹͣ��1���˶� */
__IO uint32_t g_add_pulse_count   = 0;                    /* ��������ۼ� */

void create_t_ctrl_param(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    __IO uint16_t tim_count;        /* �ﵽ����ٶ�ʱ�Ĳ���*/
    __IO uint32_t max_s_lim;        /* ����Ҫ��ʼ���ٵĲ������������û�дﵽ����ٶȣ�*/
    __IO uint32_t accel_lim;
    if(g_motion_sta != STOP)        /* ֻ�����������ֹͣ��ʱ��ż���*/
        return;
    if(step < 0)                    /* ����Ϊ���� */
    {
        g_srd.dir = CCW;            /* ��ʱ�뷽����ת */
        Dir(CCW);
        step =-step;                /* ��ȡ��������ֵ */
    }
    else
    {
        g_srd.dir = CW;             /* ˳ʱ�뷽����ת */
        Dir(CW);
    }

    if(step == 1)                   /* ����Ϊ1 */
    {
        g_srd.accel_count = -1;     /* ֻ�ƶ�һ�� */
        g_srd.run_state = DECEL;    /* ����״̬. */
        g_srd.step_delay = 1000;    /* Ĭ���ٶ� */
    }
    else if(step != 0)              /* ���Ŀ���˶�������Ϊ0*/
    {
        /*��������ٶȼ���, ����õ�min_delay���ڶ�ʱ���ļ�������ֵ min_delay = (alpha / t)/ w*/
        g_srd.min_delay = (int32_t)(A_T_x10 /speed); //��������ʱ�ļ���ֵ

        /* ͨ�������һ��(c0) �Ĳ�����ʱ���趨���ٶȣ�����accel��λΪ0.1rad/sec^2
         step_delay = 1/tt * sqrt(2*alpha/accel)
         step_delay = ( tfreq*0.676/10 )*10 * sqrt( (2*alpha*100000) / (accel*10) )/100 */

        g_srd.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10); /* c0 */

        max_s_lim = (uint32_t)(speed*speed/(A_x200*accel/10));  /* ������ٲ�֮��ﵽ����ٶȵ����� max_s_lim = speed^2 / (2*alpha*accel) */

        if(max_s_lim == 0)                                      /* ����ﵽ����ٶ�С��0.5�������ǽ���������Ϊ0,��ʵ�����Ǳ����ƶ�����һ�����ܴﵽ��Ҫ���ٶ� */
        {
            max_s_lim = 1;
        }
        accel_lim = (uint32_t)(step*decel/(accel+decel));       /* ���ﲻ��������ٶ� ������ٲ�֮�����Ǳ��뿪ʼ���� n1 = (n1+n2)decel / (accel + decel) */

        if(accel_lim == 0)                                      /* ����һ�� ��һ������*/
        {
            accel_lim = 1;
        }
        if(accel_lim <= max_s_lim)                              /* ���ٽ׶ε���������ٶȾ͵ü��١�����ʹ�������������ǿ��Լ�������ٽ׶β��� */
        {
            g_srd.decel_val = accel_lim - step;                 /* ���ٶεĲ��� */
        }
        else
        {
            g_srd.decel_val = -(max_s_lim*accel/decel);         /* ���ٶεĲ��� */
        }
        if(g_srd.decel_val == 0)                                /* ����һ�� ��һ������ */
        {
            g_srd.decel_val = -1;
        }
        g_srd.decel_start = step + g_srd.decel_val;             /* ���㿪ʼ����ʱ�Ĳ��� */


        if(g_srd.step_delay <= g_srd.min_delay)                 /* ���һ��ʼc0���ٶȱ����ٶ��ٶȻ��󣬾Ͳ���Ҫ���м����˶���ֱ�ӽ������� */
        {
            g_srd.step_delay = g_srd.min_delay;
            g_srd.run_state = RUN;
        }
        else
        {
            g_srd.run_state = ACCEL;
        }
        g_srd.accel_count = 0;                                  /* ��λ�Ӽ��ټ���ֵ */
    }
    g_motion_sta = 1;                                           /* ���Ϊ�˶�״̬ */
    En(EN_ON);
    tim_count=__HAL_TIM_GET_COUNTER(&Sevor_motor_tim);
    __HAL_TIM_SET_COMPARE(&Sevor_motor_tim,Secor_motor_Channle,tim_count+g_srd.step_delay/2);  /* ���ö�ʱ���Ƚ�ֵ */
    HAL_TIM_OC_Start_IT(&Sevor_motor_tim,TIM_CHANNEL_1);                                 /* ʹ�ܶ�ʱ��ͨ�� */
}
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
//	uint16_t VAL = 0;
	__IO uint32_t tim_count = 0;
	__IO uint32_t tmp = 0;
	uint16_t new_step_delay = 0; /* �����£��£�һ����ʱ���� */
	__IO static uint16_t last_accel_delay = 0; /* ���ٹ��������һ����ʱ���������ڣ� */
	__IO static uint32_t step_count = 0; /* ���ƶ�����������*/
	__IO static int32_t rest = 0; /* ��¼new_step_delay�е������������һ������ľ��� */
	__IO static uint8_t i = 0; /* ��ʱ��ʹ�÷�תģʽ����Ҫ���������жϲ����һ���������� */
	if(htim->Instance == TIM2)
	{
//		i++;
//		if(i%2 == 0)
//		{
//			pulse -- ;
//			if(pulse == 0) HAL_TIM_OC_Stop_IT(&htim2, TIM_CHANNEL_1);
//		}
//		VAL = __HAL_TIM_GET_COMPARE(&htim2,TIM_CHANNEL_1);
//		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,(VAL+Sevor_ccr)%0xFFFF); //�޸ıȽ�ֵ
		tim_count = __HAL_TIM_GET_COUNTER(&Sevor_motor_tim);
		tmp = tim_count + g_srd.step_delay / 2; /* ����Cֵ�������Ҫ��ת���ε�������Ҫ����2 */
		__HAL_TIM_SET_COMPARE(&Sevor_motor_tim, Secor_motor_Channle, tmp);

		i++; /* ��ʱ���жϴ�������ֵ */
		if (i == 2) /* 2�Σ�˵���Ѿ����һ���������� */
		{
			i = 0; /* ���㶨ʱ���жϴ�������ֵ */
			switch (g_srd.run_state) /* �Ӽ������߽׶� */
			{
			case STOP:
				step_count = 0; /* ���㲽�������� */
				rest = 0; /* ������ֵ */
				/* �ر�ͨ��*/
				HAL_TIM_OC_Stop_IT(&Sevor_motor_tim, Secor_motor_Channle);
				En(EN_OFF);
				g_motion_sta = 0; /* ���Ϊֹͣ״̬  */
				break;

			case ACCEL:
				g_add_pulse_count++; /* ֻ���ڼ�¼���λ��ת���˶��ٶ� */
				step_count++; /* ������1*/
				if (g_srd.dir == CW) {
					g_step_position++; /* ����λ�ü�1  ��¼����λ��ת�����ٶ�*/
				} else {
					g_step_position--; /* ����λ�ü�1*/
				}
				g_srd.accel_count++; /* ���ټ���ֵ��1*/
				new_step_delay = g_srd.step_delay
						- (((2 * g_srd.step_delay) + rest)
								/ (4 * g_srd.accel_count + 1));/* ������(��)һ����������(ʱ����) */
				rest = ((2 * g_srd.step_delay) + rest)
						% (4 * g_srd.accel_count + 1); /* �����������´μ��㲹��������������� */
				if (step_count >= g_srd.decel_start) /* ����Ƿ�����Ҫ���ٵĲ��� */
				{
					g_srd.accel_count = g_srd.decel_val; /* ���ټ���ֵΪ���ٽ׶μ���ֵ�ĳ�ʼֵ */
					g_srd.run_state = DECEL; /* �¸����������ٽ׶� */
				} else if (new_step_delay <= g_srd.min_delay) /* ����Ƿ񵽴�����������ٶ� ����ֵԽС�ٶ�Խ�죬������ٶȺ�����ٶ���Ȼ����ͽ�������*/
				{
					last_accel_delay = new_step_delay; /* ������ٹ��������һ����ʱ���������ڣ�*/
					new_step_delay = g_srd.min_delay; /* ʹ��min_delay����Ӧ����ٶ�speed��*/
					rest = 0; /* ������ֵ */
					g_srd.run_state = RUN; /* ����Ϊ��������״̬ */
				}
				break;

			case RUN:
				g_add_pulse_count++;
				step_count++; /* ������1 */
				if (g_srd.dir == CW) {
					g_step_position++; /* ����λ�ü�1 */
				} else {
					g_step_position--; /* ����λ�ü�1*/
				}
				new_step_delay = g_srd.min_delay; /* ʹ��min_delay����Ӧ����ٶ�speed��*/
				if (step_count >= g_srd.decel_start) /* ��Ҫ��ʼ���� */
				{
					g_srd.accel_count = g_srd.decel_val; /* ���ٲ�����Ϊ���ټ���ֵ */
					new_step_delay = last_accel_delay; /* �ӽ׶�������ʱ��Ϊ���ٽ׶ε���ʼ��ʱ(��������) */
					g_srd.run_state = DECEL; /* ״̬�ı�Ϊ���� */
				}
				break;

			case DECEL:
				step_count++; /* ������1 */
				g_add_pulse_count++;
				if (g_srd.dir == CW) {
					g_step_position++; /* ����λ�ü�1 */
				} else {
					g_step_position--; /* ����λ�ü�1 */
				}
				g_srd.accel_count++;
				new_step_delay = g_srd.step_delay
						- (((2 * g_srd.step_delay) + rest)
								/ (4 * g_srd.accel_count + 1)); /* ������(��)һ����������(ʱ����) */
				rest = ((2 * g_srd.step_delay) + rest)
						% (4 * g_srd.accel_count + 1); /* �����������´μ��㲹��������������� */

				/* ����Ƿ�Ϊ���һ�� */
				if (g_srd.accel_count >= 0) /* �жϼ��ٲ����Ƿ�Ӹ�ֵ�ӵ�0�ǵĻ� ������� */
				{
					g_srd.run_state = STOP;
				}
				break;
			}
			g_srd.step_delay = new_step_delay; /* Ϊ�¸�(�µ�)��ʱ(��������)��ֵ */
		}
	}
}

