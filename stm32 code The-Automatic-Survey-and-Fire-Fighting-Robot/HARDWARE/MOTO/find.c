/*
�ļ���:find.c
Ӳ�����ӣ�

��д���ϿƼ�
�Ա����꣺http://shop60670850.taobao.com/
*/
#include "find.h"
#include "bsp_timer8.h"
#include "bsp_sys.h"
#include "delay.h"

//ѭ��IO��ʼ��
//Ѱ�����������ҵ����Դ�O1 O2 O3 O4 
//Ӳ������ O1-PA4��O2-PA5��O3-PA6��O4-PA7��
//Ҫ��ʼ��Ϊ����ģʽ
void Find_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7;//ѡ��IO�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//����Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//����GPIO_InitStructure��ָ���Ĳ�����ʼ������GPIOD�Ĵ���

} 


//ѭ������ѭ��ģ�� ��������ߵ�ƽ1  ���ߵ͵�ƽ0
//С���������O4----���Ҷ���O1
//ѭ��·�棺��ɫ·���ɫ�����ߣ���Ѱ���ߡ�
//���� ���������1���������0
void Find(void)
{
	//ȫ�ǰ��ߣ�ǰ��
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// ���ߣ�ǰ��
	{
			Car_Go();
	}
	////O2�ں���  �ұ��к��� С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2Ѱ������
	{
			
			Car_Turn_Right();
	}

	////O2�ں��� O1����  �ұ��к��� С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1Ѱ������
	{
			Car_Turn_Right();
	}
	////O1�ں���  �ұ��к��� С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))// O1Ѱ������
	{
		Car_Turn_Right();
	}
	////O3�ں���  ��߱��к��� С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3Ѱ������
	{
		Car_Turn_Left();
	}
	////O3��O4�ں���  ��߱��к��� С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O3 O4Ѱ������
	{
		Car_Turn_Left();
	}
	
	////O4�ں���  ��߱��к��� С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4Ѱ������
	{
		Car_Turn_Left();
			
	}
	
	
	
	//ͣ��
	if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))// ���Դ��������ں���
	{
		 Car_Stop();
	}
	
	
}












