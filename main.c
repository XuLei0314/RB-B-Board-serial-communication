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
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIM3_Int_Init(20000-1,7200-1); //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	usart2_init(115200);//����1��ʼ��
	usart3_init(115200);//����1��ʼ��
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
