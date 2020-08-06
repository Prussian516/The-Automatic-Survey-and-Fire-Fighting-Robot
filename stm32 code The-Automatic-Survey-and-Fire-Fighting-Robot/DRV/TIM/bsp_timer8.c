/*
********************************************************************************************************
文件名：bsp_timer8.c
功  能：adc的配置
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/


#include "bsp_timer8.h"

//***************************定时器初始化***************************//
// TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71  
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
 


//***************************PWM频率及占空比初始化***************************//
//=====初始化PWM 20KHZ 高频可以防止电机低频时的尖叫声

//TIM8 输出PWM控制四个电机
//四驱底盘及四轮麦克纳姆轮底盘
//硬件连接说明：
//
//PC6---ENA，控制小车左前电机速度
//PC7---ENB，控制小车右前电机速度

//后部电机驱动L298N
//PC9---ENB，控制小车左后电机速度
//PC8---ENA，控制小车右后电机速度

// ARR= 3599 时频率为20Khz
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
//************************************************************************//


//***************************占空比调节***************************//
//占空比 = TIMx_CCRx / TIMx_ARR
//moto_lq：左前轮电机，moto_rq：右前轮电机.   数值 0-100
//***************************占空比调节***************************//
void MOTO_Q_PWM_Out(u16 moto_lq, u16 moto_rq)
{
	
	TIM_OCInitTypeDef TIM_OCInitSructure;
	
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	
  //PC6--CH1 左前电机
	TIM_OCInitSructure.TIM_Pulse = moto_lq;//占空比= ccr /100
	TIM_OC1Init(TIM8, &TIM_OCInitSructure);//参数初始化
	TIM_OC1PolarityConfig(TIM8, TIM_OCPreload_Enable);//开始输出pwm
	TIM_ARRPreloadConfig(TIM8, ENABLE);//启动自动重装
	TIM_CtrlPWMOutputs(TIM8, ENABLE);//主输出使能 
	//PC7--CH2 左前电机
	TIM_OCInitSructure.TIM_Pulse = moto_rq;//占空比= ccr/100
	TIM_OC2Init(TIM8, &TIM_OCInitSructure);//参数初始化
	TIM_OC2PolarityConfig(TIM8, TIM_OCPreload_Enable);//开始输出pwm
	

	
	//TIM_ARRPreloadConfig(TIM8, ENABLE);//启动自动重装
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
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
	
  //PC8---CH3 右后电机
	TIM_OCInitSructure.TIM_Pulse = moto_rh;//占空比= ccr /100
	TIM_OC3Init(TIM8, &TIM_OCInitSructure);//参数初始化
	TIM_OC3PolarityConfig(TIM8, TIM_OCPreload_Enable);//开始输出pwm
	TIM_ARRPreloadConfig(TIM8, ENABLE);//启动自动重装
	TIM_CtrlPWMOutputs(TIM8, ENABLE);//主输出使能 
	
	//PC9--CH4 左后电机
	TIM_OCInitSructure.TIM_Pulse = moto_lh;//占空比= ccr/100
	TIM_OC4Init(TIM8, &TIM_OCInitSructure);//参数初始化
	TIM_OC4PolarityConfig(TIM8, TIM_OCPreload_Enable);//开始输出pwm
		
	TIM_ARRPreloadConfig(TIM8, ENABLE);//启动自动重装
	TIM_CtrlPWMOutputs(TIM8, ENABLE);//主输出使能 
}	

void TIM8_PWM(u16 arr,u16 psc)
{  
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  //使能GPIO外设时钟使能      

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM8_CH1-4
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
       
        TIM_TimeBaseStructure.TIM_Period = arr-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值         80K
        TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //设置用来作为TIMx时钟频率除数的预分频值  不分频
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
        TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //设置待装入捕获比较寄存器的脉冲值
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
        TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能       
       
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //设置待装入捕获比较寄存器的脉冲值
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
        TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2预装载使能       
       
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //设置待装入捕获比较寄存器的脉冲值
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
        TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3预装载使能       
       
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //设置待装入捕获比较寄存器的脉冲值
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
        TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4预装载使能       
       
        TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器

        TIM_Cmd(TIM8, ENABLE);  //使能TIM8
        TIM_CtrlPWMOutputs(TIM8,ENABLE);        //MOE 主输出使能       

}



