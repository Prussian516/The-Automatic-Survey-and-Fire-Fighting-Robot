#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "stm32f10x.h"
#include "stdio.h"
/*
2020-4-16重构
编辑日志：添加USART_Init()函数
*/
#define USART_REC_LEN 200  //定义最大接收字节数
#define EN_USART1_RX 1   //使能1 禁止 0 串口1接收

extern u8 USART_RX_BUF[USART_REC_LEN];  //定义最大接收字节数 (200)
extern u8 USART_RX_STA;   //接收状态标记


void my_usart_init(u32 bound); //串口初始化函数定义



#endif
	
