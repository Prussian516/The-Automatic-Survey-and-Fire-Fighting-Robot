/*
********************************************************************************************************
�ļ�����bsp_GPIO.c
��  �ܣ�������Ҫ����ͨIO
��  ע����ð����е�IO���������ã��������
*********************************************************************************************************
*/



#include "bsp_GPIO.h"   

/*
********************************************************************************************************
�������ƣ�void LED_GPIO_Config(void)
�������ܣ���ʼ��LED1��GPIO����
Ӳ�����ӣ�LED1----PC13
*********************************************************************************************************
*/
void LED_GPIO_Config(void) //led gpio����
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LED1_CLK, ENABLE); 	/*����GPIO������ʱ��*/																   
		GPIO_InitStructure.GPIO_Pin = LED1_Pin;	/*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*��������ģʽΪͨ���������*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*������������Ϊ50MHz */ 
		GPIO_Init(LED1_PORT, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC13*/	
}
void USART1_GPIO_Config(void)  //USART1 gpio ����
{
   GPIO_InitTypeDef GPIO_InitStructure;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //ʹ��GPIOA
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //ʹ��USART1
	 
	 //����GPIO����ģʽ-PA9 PA10����Ϊ����1
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
  
 
}




//------------------End of File----------------------------
