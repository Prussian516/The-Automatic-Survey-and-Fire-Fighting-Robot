#include "bsp_sys.h"
#include "stdio.h"

static u8 direction=0;
void USART1_IRQHandler(void)
{
    static u8 res;
	static u8 state=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==!RESET)
	{
	   res = USART_ReceiveData(USART1);
	   if(res==0xAA && state==0)  //֡ͷ1
	   {
	    state=1;
	   }else if(res==0xAB && state==1)
	   {
	    direction=1;  //1Ϊ��ת
	    state=0;    //����Ϊ0
	   }else if(res==0xAC && state==1)
	   {
	    direction=2;   //2Ϊ��ת
		state=0;    //����Ϊ0
	   }else if(res==0xAD&&state==1)
	   {
	    direction=0;  //0Ϊֹͣ
	    state=0;
	   }  
	   else if(res==0xAE&&state==1)
	   {
	    direction=3;  //3Ϊǰ��
	    state=0;
	   }
	   else if(res==0xAF&&state==1)
	   {
	    direction=4;  //4Ϊ����
	    state=0;
	   }
	   else
       {
	    state=0;
	   }
	   USART_SendData(USART1,res);

		
	}
   

}	

int main(void)
{	
//***************************���þֲ�����***************************//
	
//*****************************************************************//
	
//*****************************ϵͳ��ʼ*****************************//
	
	STM32_System_Init();//����ϵͳ������������������
  
//*****************************************************************//

	
//*****************************************************************//
	//ע���ȳ�ʼ������PWM��������ǰ��PWM
    MOTO_H_PWM_Out(80, 80);	//����70%PWM 
    MOTO_Q_PWM_Out(80, 80);	//ǰ��70%PWM

	
	
	while (1)
	{
	
     if(direction==1)
     {
		 MOTO_H_PWM_Out(75, 75);	//����75%PWM
		 MOTO_Q_PWM_Out(75, 75);	//ǰ��75%PWM
		 Car_Turn_Right();
	 }
	 else if(direction==2)
	 {	 
		 MOTO_H_PWM_Out(75, 75);	//����75%PWM
		 MOTO_Q_PWM_Out(75, 75);	//ǰ��75%PWM
		 Car_Turn_Left();

	 }	 
	 else if(direction==0)
	 {	 
		 MOTO_H_PWM_Out(75, 75);	//����75%PWM
		 MOTO_Q_PWM_Out(75, 75);	//ǰ��75%PWM
		 Car_Stop();
	 }
	 else if(direction==3)
	 {
       MOTO_H_PWM_Out(75, 75);	//����75%PWM
	   MOTO_Q_PWM_Out(75, 75);	//ǰ��75%PWM		 
	   Car_Go();
	 }
	 else if(direction==4)
	 {
      MOTO_H_PWM_Out(75, 75);	//����75%PWM
	  MOTO_Q_PWM_Out(75, 75);	//ǰ��75%PWM	
	 Car_Back();
     }
    }



}

/*********************************************END OF FILE**********************/
