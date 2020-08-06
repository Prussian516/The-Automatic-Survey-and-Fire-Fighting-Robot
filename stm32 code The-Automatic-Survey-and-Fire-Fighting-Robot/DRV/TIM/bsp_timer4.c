/*
********************************************************************************************************
文件名：bsp_timer3.c
功  能：adc的配置
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/


#include "bsp_timer4.h"

//***************************定时器初始化***************************//
// TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71  
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
 
void Timer4_Init(u32 arr,int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;//自动重新装载寄存器周期的值澹ㄥ计数值澹)
	TIM_TimeBaseStructure.TIM_Prescaler = psc;//时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//对外部时钟进行采样的时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//参数初始化

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	//TIM_Cmd(TIM4, ENABLE);//启动定时器 
	
}



//***************************PWM频率及占空比初始化***************************//
//=====初始化PWM 20KHZ 高频可以防止电机低频时的尖叫声

//TIM4 输出PWM控制四个电机
//CH1--PB6，CH2--PB7，CH3--PB8，CH4--PB9
//PB6控制PWMA--left moto，PB7控制PWMB--right moto  前部两个电机
//PB8控制PWMA--right moto，PB9控制PWMB--left moto  后部两个电机

// ARR= 3599 时频率为20Khz
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
//************************************************************************//
void MOTO_PWM_Init(u32 arr, int psc)
{
	TIM_OCInitTypeDef TIM_OCInitSructure;
	GPIO_InitTypeDef    GPIO_InitStructure;
	//配置pwm输出端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	//初始化定时器
	Timer4_Init(arr,psc);//Init timer4
	//设置通道1 pwm参数
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//占空比= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC1Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC1PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm

	//设置通道2 pwm参数
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//占空比= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC2Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC2PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm
	
		//设置通道3 pwm参数
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//占空比= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC3Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC3PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm

	//设置通道4 pwm参数
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//占空比= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC4Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC4PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm

	TIM_ARRPreloadConfig(TIM4, ENABLE);//启动自动重装
	TIM_Cmd(TIM4, ENABLE);//启动定时	
}

//***************************占空比调节***************************//
//占空比 = TIMx_CCRx / TIMx_ARR
//moto_lq：左前轮电机，moto_rq：右前轮电机.   数值 0-100
//***************************占空比调节***************************//
void MOTO_Q_PWM_Out(u16 moto_lq, u16 moto_rq)
{
	
	TIM_OCInitTypeDef TIM_OCInitSructure;
	
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	//CH1 左前电机
	TIM_OCInitSructure.TIM_Pulse = moto_lq;//占空比= ccr/100
	TIM_OC1Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC1PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm
	
	//CH2 右前电机
	TIM_OCInitSructure.TIM_Pulse = moto_rq;//占空比= ccr /100
	TIM_OC2Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC2PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);//启动自动重装
	 
}	

//***************************占空比调节***************************//
//占空比 = TIMx_CCRx / TIMx_ARR
//moto_rh：右后轮电机，moto_rq：右前轮电机.   数值 0-100
//***************************占空比调节***************************//
void MOTO_H_PWM_Out(u16 moto_lh, u16 moto_rh)
{
	
	TIM_OCInitTypeDef TIM_OCInitSructure;
	
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	//CH3 右后电机
	TIM_OCInitSructure.TIM_Pulse = moto_lh;//占空比= ccr/100
	TIM_OC3Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC3PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm
	
	//CH4 右前电机
	TIM_OCInitSructure.TIM_Pulse = moto_rh;//占空比= ccr /100
	TIM_OC4Init(TIM4, &TIM_OCInitSructure);//参数初始化
	TIM_OC4PolarityConfig(TIM4, TIM_OCPreload_Enable);//开始输出pwm
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);//启动自动重装
	 
}	



