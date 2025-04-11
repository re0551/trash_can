/*
 * infrared.c
 *
 *  Created on: Sep 12, 2024
 *      Author: huawei
 */


#include "Infrared.h"
#include "../../icode/tjc_usart/tjc_usart.h"

void Infrared(uint8_t a)
{
	    if(Red[0] == 1)  //��⵽�����ź�2
	        {
		            bin[0]=2; //�к�����Ͱ2���������ź�
			      }

		else if(Red[1] == 1)  //��⵽�����ź�3
		    {
			        bin[0]=3; //��������Ͱ3���������ź�
		          }

		else if(Red[2] == 1)//��⵽�����ź�4
			{
					bin[0]=4; //��������Ͱ4���������ź�
		          }

		else if (Red[3] == 1)  //��⵽�����ź�5
			{
					bin[0]=5; //�ɻ�������Ͱ5���������ź�
				  }
}

// �������غ���
void full(void) {
    switch (bin[0]) {
        case 5:
            sprintf(str, "t5.txt=\"������\"");
            tjc_send_string(str);
            sprintf(str, "click m4,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        case 2:
            sprintf(str, "t6.txt=\"������\"");
            tjc_send_string(str);
            sprintf(str, "click m5,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        case 3:
            sprintf(str, "t7.txt=\"������\"");
            tjc_send_string(str);
            sprintf(str, "click m6,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        case 4:
            sprintf(str, "t8.txt=\"������\"");
            tjc_send_string(str);
            sprintf(str, "click m7,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        default:
            break;
    }
}
