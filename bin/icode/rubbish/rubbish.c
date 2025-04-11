/*
 * rubbish.c
 *
 *  Created on: Oct 3, 2024
 *      Author: zyc
 */
#include "rubbish.h"


void rubbish(void)
{
    switch (rab[0])
    {
        case '5':
            sprintf(str, "page 1");
            tjc_send_string(str);
            sprintf(str, "click m0,1");
            tjc_send_string(str);
            flag++;
            break;
        case '6':
            sprintf(str, "page 1");
            tjc_send_string(str);
            sprintf(str, "click m1,1");
            tjc_send_string(str);
            flag++;
            break;
        case '3':
            sprintf(str, "page 1");
            tjc_send_string(str);
            sprintf(str, "click m2,1");
            tjc_send_string(str);
            flag++;
            break;
        case '4':
            sprintf(str, "page 1");
            tjc_send_string(str);
            sprintf(str, "click m3,1");
            tjc_send_string(str);
            flag++;
            break;
        case '8'://≤•∑≈ ”∆µ
            sprintf(str, "page 2");
            tjc_send_string(str);
			sprintf(str, "click m20,1");
			tjc_send_string(str);
            break;
        default:
            break;
    }
}

