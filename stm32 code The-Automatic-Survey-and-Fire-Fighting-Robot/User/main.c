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
	   if(res==0xAA && state==0)  //帧头1
	   {
	    state=1;
	   }else if(res==0xAB && state==1)
	   {
	    direction=1;  //1为右转
	    state=0;    //重置为0
	   }else if(res==0xAC && state==1)
	   {
	    direction=2;   //2为左转
		state=0;    //重置为0
	   }else if(res==0xAD&&state==1)
	   {
	    direction=0;  //0为停止
	    state=0;
	   }  
	   else if(res==0xAE&&state==1)
	   {
	    direction=3;  //3为前进
	    state=0;
	   }
	   else if(res==0xAF&&state==1)
	   {
	    direction=4;  //4为后退
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
//***************************设置局部变量***************************//
	
//*****************************************************************//
	
//*****************************系统初始*****************************//
	
	STM32_System_Init();//所有系统配置在这个函数里完成
  
//*****************************************************************//

	
//*****************************************************************//
	//注意先初始化后轮PWM，再设置前轮PWM
    MOTO_H_PWM_Out(80, 80);	//后轮70%PWM 
    MOTO_Q_PWM_Out(80, 80);	//前轮70%PWM

	
	
	while (1)
	{
	
     if(direction==1)
     {
		 MOTO_H_PWM_Out(75, 75);	//后轮75%PWM
		 MOTO_Q_PWM_Out(75, 75);	//前轮75%PWM
		 Car_Turn_Right();
	 }
	 else if(direction==2)
	 {	 
		 MOTO_H_PWM_Out(75, 75);	//后轮75%PWM
		 MOTO_Q_PWM_Out(75, 75);	//前轮75%PWM
		 Car_Turn_Left();

	 }	 
	 else if(direction==0)
	 {	 
		 MOTO_H_PWM_Out(75, 75);	//后轮75%PWM
		 MOTO_Q_PWM_Out(75, 75);	//前轮75%PWM
		 Car_Stop();
	 }
	 else if(direction==3)
	 {
       MOTO_H_PWM_Out(75, 75);	//后轮75%PWM
	   MOTO_Q_PWM_Out(75, 75);	//前轮75%PWM		 
	   Car_Go();
	 }
	 else if(direction==4)
	 {
      MOTO_H_PWM_Out(75, 75);	//后轮75%PWM
	  MOTO_Q_PWM_Out(75, 75);	//前轮75%PWM	
	 Car_Back();
     }
    }



}

/*********************************************END OF FILE**********************/
