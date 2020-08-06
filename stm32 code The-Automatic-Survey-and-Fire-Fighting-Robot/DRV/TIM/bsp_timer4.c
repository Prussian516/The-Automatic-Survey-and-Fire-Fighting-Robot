/*
********************************************************************************************************
�ļ�����bsp_timer3.c
��  �ܣ�adc������
��  ע��
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/


#include "bsp_timer4.h"

//***************************��ʱ����ʼ��***************************//
// TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71  
//arr���Զ���װ�Ĵ�����psc��Ƶϵ��
//PWM��Ƶ�� = 72MHz/ARR/PCS ����  20K = 72M/3600/1 =  20K
 
void Timer4_Init(u32 arr,int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;//�Զ�����װ�ؼĴ������ڵ�ֵ壨����ֵ�)
	TIM_TimeBaseStructure.TIM_Prescaler = psc;//ʱ�ӷ�Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//������ʼ��

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	//TIM_Cmd(TIM4, ENABLE);//������ʱ�� 
	
}



//***************************PWMƵ�ʼ�ռ�ձȳ�ʼ��***************************//
//=====��ʼ��PWM 20KHZ ��Ƶ���Է�ֹ�����Ƶʱ�ļ����

//TIM4 ���PWM�����ĸ����
//CH1--PB6��CH2--PB7��CH3--PB8��CH4--PB9
//PB6����PWMA--left moto��PB7����PWMB--right moto  ǰ���������
//PB8����PWMA--right moto��PB9����PWMB--left moto  ���������

// ARR= 3599 ʱƵ��Ϊ20Khz
//arr���Զ���װ�Ĵ�����psc��Ƶϵ��
//PWM��Ƶ�� = 72MHz/ARR/PCS ����  20K = 72M/3600/1 =  20K
//************************************************************************//
void MOTO_PWM_Init(u32 arr, int psc)
{
	TIM_OCInitTypeDef TIM_OCInitSructure;
	GPIO_InitTypeDef    GPIO_InitStructure;
	//����pwm����˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	//��ʼ����ʱ��
	Timer4_Init(arr,psc);//Init timer4
	//����ͨ��1 pwm����
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//ռ�ձ�= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC1Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC1PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm

	//����ͨ��2 pwm����
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//ռ�ձ�= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC2Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC2PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm
	
		//����ͨ��3 pwm����
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//ռ�ձ�= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC3Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC3PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm

	//����ͨ��4 pwm����
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;//ռ�ձ�= 0/100
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC4Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC4PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm

	TIM_ARRPreloadConfig(TIM4, ENABLE);//�����Զ���װ
	TIM_Cmd(TIM4, ENABLE);//������ʱ	
}

//***************************ռ�ձȵ���***************************//
//ռ�ձ� = TIMx_CCRx / TIMx_ARR
//moto_lq����ǰ�ֵ����moto_rq����ǰ�ֵ��.   ��ֵ 0-100
//***************************ռ�ձȵ���***************************//
void MOTO_Q_PWM_Out(u16 moto_lq, u16 moto_rq)
{
	
	TIM_OCInitTypeDef TIM_OCInitSructure;
	
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	//CH1 ��ǰ���
	TIM_OCInitSructure.TIM_Pulse = moto_lq;//ռ�ձ�= ccr/100
	TIM_OC1Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC1PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm
	
	//CH2 ��ǰ���
	TIM_OCInitSructure.TIM_Pulse = moto_rq;//ռ�ձ�= ccr /100
	TIM_OC2Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC2PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);//�����Զ���װ
	 
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
	//CH3 �Һ���
	TIM_OCInitSructure.TIM_Pulse = moto_lh;//ռ�ձ�= ccr/100
	TIM_OC3Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC3PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm
	
	//CH4 ��ǰ���
	TIM_OCInitSructure.TIM_Pulse = moto_rh;//ռ�ձ�= ccr /100
	TIM_OC4Init(TIM4, &TIM_OCInitSructure);//������ʼ��
	TIM_OC4PolarityConfig(TIM4, TIM_OCPreload_Enable);//��ʼ���pwm
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);//�����Զ���װ
	 
}	



