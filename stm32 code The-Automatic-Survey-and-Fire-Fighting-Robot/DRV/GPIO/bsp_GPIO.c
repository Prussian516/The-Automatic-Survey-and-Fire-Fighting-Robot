/*
********************************************************************************************************
文件名：bsp_GPIO.c
功  能：配置需要的普通IO
备  注：最好把所有的IO在这里配置，方便管理
*********************************************************************************************************
*/



#include "bsp_GPIO.h"   

/*
********************************************************************************************************
函数名称：void LED_GPIO_Config(void)
函数功能：初始化LED1的GPIO功能
硬件连接：LED1----PC13
*********************************************************************************************************
*/
void LED_GPIO_Config(void) //led gpio配置
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LED1_CLK, ENABLE); 	/*开启GPIO的外设时钟*/																   
		GPIO_InitStructure.GPIO_Pin = LED1_Pin;	/*选择要控制的GPIO引脚*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*设置引脚模式为通用推挽输出*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*设置引脚速率为50MHz */ 
		GPIO_Init(LED1_PORT, &GPIO_InitStructure);/*调用库函数，初始化GPIOC13*/	
}
void USART1_GPIO_Config(void)  //USART1 gpio 配置
{
   GPIO_InitTypeDef GPIO_InitStructure;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能GPIOA
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //使能USART1
	 
	 //设置GPIO工作模式-PA9 PA10复用为串口1
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
  
 
}




//------------------End of File----------------------------
