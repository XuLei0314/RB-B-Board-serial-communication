#include "main.h"

extern char temp_buf[14];
extern char RECIVE_start;
//uint16_t buffer[8];
extern uint8_t auto_send[50];
tReceTXoneData ReceData = {0};
extern int count;
u8 SV5_State = 0x0000;
u8 SV6_State = 0x0000;
u8 SV7_State = 0x0000;
u8 SV8_State = 0x0000 ;
int main(void)
{	
	u16 t;  
//	u16 len;
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM3_Int_Init(20000-1,7200-1); //10Khz的计数频率，计数到5000为500ms
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	usart2_init(115200);//串口1初始化
	usart3_init(115200);//串口1初始化
	POWER_Init();
	while(1)
	{ 
		SV5_State=ReceData.temp1_1;
		SV6_State=ReceData.temp2_1;
		SV7_State=ReceData.temp3_1;
		SV8_State=ReceData.temp4_1;	
		 memcpy(auto_send, &ReceData, sizeof(tReceTXoneData));
		for(t=0;t<sizeof(tReceTXoneData);t++)
	{
				USART_SendData(USART3,auto_send[t]);
				while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);
	}
		if(SV5_State==0x0001)
		{
			RED_ON;
			SV5_ON;
		}
		else
		{
			RED_OFF;
			SV5_OFF;
		}
		if(SV6_State==0x0001)
		{
			RED_ON;
			SV6_ON;
		}
		else
		{
			RED_OFF;
			SV6_OFF;
		}
		if(SV7_State==0x0001)
		{
			RED_ON;
			SV7_ON;
		}
		else
		{
			RED_OFF;
			SV7_OFF;
		}
		if(SV8_State==0x0001)
		{
			RED_ON;
			SV8_ON;
		}
		else
		{
			RED_OFF;
			SV8_OFF;
		}
}
}
