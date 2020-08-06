#ifndef __BSP_TIMER3_H
#define __BSP_TIMER3_H


#include "stm32f10x.h"
void Timer4_Init(u32 arr,int psc);
void MOTO_PWM_Init(u32 arr, int psc);
void MOTO_Q_PWM_Out(u16 moto_lq, u16 moto_rq);
void MOTO_H_PWM_Out(u16 moto_lh, u16 moto_rh);


#endif

