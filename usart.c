#include "sys.h"
#include "usart.h"
#include "led.h"	  
#include "stdio.h"
#include "string.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////// 	 
////���ʹ��ucos,����������ͷ�ļ�����.
//#if SYSTEM_SUPPORT_UCOS
//#include "includes.h"					//ucos ʹ��	  
//#endif
////#define SEND_SIZE 28    //sizeof(tSendTXoneData)
////#define AUTOP_SIZE 17   //sizeof(tReceXToneTData)
//uint8_t auto_send[50];

////////////////////////////////////////////////////////////////////
////�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
uint8_t auto_send[50];
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

///*ʹ��microLib�ķ���*/
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
//#if EN_USART2_RX   //���ʹ���˽���
////����1�жϷ������
////ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
////����״̬
////bit15��	������ɱ�־
////bit14��	���յ�0x0d
////bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART_RX_STA=0;       //����״̬���	  
//extern tReceTXoneData ReceData;
void usart2_init(u32 bound)
{
    //GPIO�˿�����
   GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
     //USART2_TX   PB.10
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART2_RX	  PB.11
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
   GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

   USART_Init(USART2, &USART_InitStructure); //��ʼ������
   USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}
void usart3_init(u32 bound)
{
    //GPIO�˿�����
   GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART1��GPIOAʱ��
     //USART2_TX   PB.10
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART2_RX	  PB.11
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
   GPIO_Init(GPIOB, &GPIO_InitStructure);  

   //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

   USART_Init(USART3, &USART_InitStructure); //��ʼ������
   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
   USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

}
const char sof = 0xA4;
const char end = 0xF1;
char RECIVE_start=0;
volatile char rec_buff[30];
volatile int rec_count=0;
char temp_buf[14]={0};
extern tReceTXoneData ReceData;

void USART2_IRQHandler(void)                	//����1�жϷ������
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
void USART3_IRQHandler(void)                	//����1�жϷ������
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART3, USART_IT_RXNE); 
		}
	}
