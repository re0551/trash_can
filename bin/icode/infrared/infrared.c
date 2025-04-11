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
	    if(Red[0] == 1)  //检测到红外信号2
	        {
		            bin[0]=2; //有害垃圾桶2发送满载信号
			      }

		else if(Red[1] == 1)  //检测到红外信号3
		    {
			        bin[0]=3; //厨余垃圾桶3发送满载信号
		          }

		else if(Red[2] == 1)//检测到红外信号4
			{
					bin[0]=4; //其他垃圾桶4发送满载信号
		          }

		else if (Red[3] == 1)  //检测到红外信号5
			{
					bin[0]=5; //可回收垃圾桶5发送满载信号
				  }
}

// 发送满载函数
void full(void) {
    switch (bin[0]) {
        case 5:
            sprintf(str, "t5.txt=\"已满载\"");
            tjc_send_string(str);
            sprintf(str, "click m4,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        case 2:
            sprintf(str, "t6.txt=\"已满载\"");
            tjc_send_string(str);
            sprintf(str, "click m5,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        case 3:
            sprintf(str, "t7.txt=\"已满载\"");
            tjc_send_string(str);
            sprintf(str, "click m6,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        case 4:
            sprintf(str, "t8.txt=\"已满载\"");
            tjc_send_string(str);
            sprintf(str, "click m7,1");
            tjc_send_string(str);
            bin[0]=0;
            break;
        default:
            break;
    }
}
