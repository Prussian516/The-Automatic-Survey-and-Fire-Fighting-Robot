#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "stm32f10x.h"
#include "stdio.h"
/*
2020-4-16�ع�
�༭��־�����USART_Init()����
*/
#define USART_REC_LEN 200  //�����������ֽ���
#define EN_USART1_RX 1   //ʹ��1 ��ֹ 0 ����1����

extern u8 USART_RX_BUF[USART_REC_LEN];  //�����������ֽ��� (200)
extern u8 USART_RX_STA;   //����״̬���


void my_usart_init(u32 bound); //���ڳ�ʼ����������



#endif
	
