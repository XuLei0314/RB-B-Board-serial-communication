#include "sys.h"
#include "usart.h"
#include "led.h"	  
#include "stdio.h"
#include "string.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////// 	 
////如果使用ucos,则包括下面的头文件即可.
//#if SYSTEM_SUPPORT_UCOS
//#include "includes.h"					//ucos 使用	  
//#endif
////#define SEND_SIZE 28    //sizeof(tSendTXoneData)
////#define AUTOP_SIZE 17   //sizeof(tReceXToneTData)
//uint8_t auto_send[50];

////////////////////////////////////////////////////////////////////
////加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
uint8_t auto_send[50];
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

///*使用microLib的方法*/
// /* 
//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART1, (uint8_t) ch);

//	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
//   
//    return ch;
//}
//int GetKey (void)  { 

//    while (!(USART1->SR & USART_FLAG_RXNE));

//    return ((int)(USART1->DR & 0x1FF));
//}
//*/
//#if EN_USART2_RX   //如果使能了接收
////串口1中断服务程序
////注意,读取USARTx->SR能避免莫名其妙的错误   	
//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
////接收状态
////bit15，	接收完成标志
////bit14，	接收到0x0d
////bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	  
//extern tReceTXoneData ReceData;
void usart2_init(u32 bound)
{
    //GPIO端口设置
   GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
     //USART2_TX   PB.10
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART2_RX	  PB.11
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
   GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

   USART_Init(USART2, &USART_InitStructure); //初始化串口
   USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
   USART_Cmd(USART2, ENABLE);                    //使能串口 

}
void usart3_init(u32 bound)
{
    //GPIO端口设置
   GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能USART1，GPIOA时钟
     //USART2_TX   PB.10
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART2_RX	  PB.11
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
   GPIO_Init(GPIOB, &GPIO_InitStructure);  

   //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

   USART_Init(USART3, &USART_InitStructure); //初始化串口
   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
   USART_Cmd(USART3, ENABLE);                    //使能串口 

}
const char sof = 0xA4;
const char end = 0xF1;
char RECIVE_start=0;
volatile char rec_buff[30];
volatile int rec_count=0;
char temp_buf[14]={0};
extern tReceTXoneData ReceData;

void USART2_IRQHandler(void)                	//串口1中断服务程序
{

if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
		{
//			GREEN_ON;
			//LED_ON;
			temp_buf[rec_count] = USART_ReceiveData(USART2);
			if(temp_buf[rec_count] == sof)
			{
				RECIVE_start = 1;
				rec_count = 1;
				return;
			}
			if(RECIVE_start)
			{
				temp_buf[rec_count++] = USART_ReceiveData(USART2);
				
				if(temp_buf[rec_count-1] == end)
				{
					RECIVE_start = 0;
					rec_count = 0;
				 memcpy(&ReceData,temp_buf,sizeof(tReceTXoneData));
				}
			}
		}
}
void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART3, USART_IT_RXNE); 
		}
	}
