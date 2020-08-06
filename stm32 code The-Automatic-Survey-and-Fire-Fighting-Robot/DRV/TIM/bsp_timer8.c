/*
********************************************************************************************************
�ļ�����bsp_timer8.c
��  �ܣ�adc������
��  ע��
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/


#include "bsp_timer8.h"

//***************************��ʱ����ʼ��***************************//
// TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71  
//arr���Զ���װ�Ĵ�����psc��Ƶϵ��
//PWM��Ƶ�� = 72MHz/ARR/PCS ����  20K = 72M/3600/1 =  20K
 


//***************************PWMƵ�ʼ�ռ�ձȳ�ʼ��***************************//
//=====��ʼ��PWM 20KHZ ��Ƶ���Է�ֹ�����Ƶʱ�ļ����

//TIM8 ���PWM�����ĸ����
//�������̼����������ķ�ֵ���
//Ӳ������˵����
//
//PC6---ENA������С����ǰ����ٶ�
//PC7---ENB������С����ǰ����ٶ�

//�󲿵������L298N
//PC9---ENB������С��������ٶ�
//PC8---ENA������С���Һ����ٶ�

// ARR= 3599 ʱƵ��Ϊ20Khz
//arr���Զ���װ�Ĵ�����psc��Ƶϵ��
//PWM��Ƶ�� = 72MHz/ARR/PCS ����  20K = 72M/3600/1 =  20K
//************************************************************************//


//***************************ռ�ձȵ���***************************//
//ռ�ձ� = TIMx_CCRx / TIMx_ARR
//moto_lq����ǰ�ֵ����moto_rq����ǰ�ֵ��.   ��ֵ 0-100
//***************************ռ�ձȵ���***************************//
void MOTO_Q_PWM_Out(u16 moto_lq, u16 moto_rq)
{
	
	TIM_OCInitTypeDef TIM_OCInitSructure;
	
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	
  //PC6--CH1 ��ǰ���
	TIM_OCInitSructure.TIM_Pulse = moto_lq;//ռ�ձ�= ccr /100
	TIM_OC1Init(TIM8, &TIM_OCInitSructure);//������ʼ��
	TIM_OC1PolarityConfig(TIM8, TIM_OCPreload_Enable);//��ʼ���pwm
	TIM_ARRPreloadConfig(TIM8, ENABLE);//�����Զ���װ
	TIM_CtrlPWMOutputs(TIM8, ENABLE);//�����ʹ�� 
	//PC7--CH2 ��ǰ���
	TIM_OCInitSructure.TIM_Pulse = moto_rq;//ռ�ձ�= ccr/100
	TIM_OC2Init(TIM8, &TIM_OCInitSructure);//������ʼ��
	TIM_OC2PolarityConfig(TIM8, TIM_OCPreload_Enable);//��ʼ���pwm
	

	
	//TIM_ARRPreloadConfig(TIM8, ENABLE);//�����Զ���װ
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}	

//***************************ռ�ձȵ���***************************//
//ռ�ձ� = TIMx_CCRx / TIMx_ARR
//moto_rh���Һ��ֵ����moto_rq����ǰ�ֵ��.   ��ֵ 0-100
//***************************ռ�ձȵ���***************************//
void MOTO_H_PWM_Out(u16 moto_lh, u16 moto_rh)
{
	
	TIM_OCInitTypeDef TIM_OCInitSructure;
	
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	
  //PC8---CH3 �Һ���
	TIM_OCInitSructure.TIM_Pulse = moto_rh;//ռ�ձ�= ccr /100
	TIM_OC3Init(TIM8, &TIM_OCInitSructure);//������ʼ��
	TIM_OC3PolarityConfig(TIM8, TIM_OCPreload_Enable);//��ʼ���pwm
	TIM_ARRPreloadConfig(TIM8, ENABLE);//�����Զ���װ
	TIM_CtrlPWMOutputs(TIM8, ENABLE);//�����ʹ�� 
	
	//PC9--CH4 �����
	TIM_OCInitSructure.TIM_Pulse = moto_lh;//ռ�ձ�= ccr/100
	TIM_OC4Init(TIM8, &TIM_OCInitSructure);//������ʼ��
	TIM_OC4PolarityConfig(TIM8, TIM_OCPreload_Enable);//��ʼ���pwm
		
	TIM_ARRPreloadConfig(TIM8, ENABLE);//�����Զ���װ
	TIM_CtrlPWMOutputs(TIM8, ENABLE);//�����ʹ�� 
}	

void TIM8_PWM(u16 arr,u16 psc)
{  
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  //ʹ��GPIO����ʱ��ʹ��      

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM8_CH1-4
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
       
        TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ         80K
        TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
        TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //���ô�װ�벶��ȽϼĴ���������ֵ
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
        TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��       
       
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //���ô�װ�벶��ȽϼĴ���������ֵ
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
        TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��       
       
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //���ô�װ�벶��ȽϼĴ���������ֵ
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
        TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��       
       
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
        TIM_OCInitStructure.TIM_Pulse = 50; //���ô�װ�벶��ȽϼĴ���������ֵ
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
        TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��       
       
        TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

        TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM8
        TIM_CtrlPWMOutputs(TIM8,ENABLE);        //MOE �����ʹ��       

}



