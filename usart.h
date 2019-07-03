#ifndef __USART_H
#define __USART_H
//#include <stm32f10x_lib.h>
#include "stdio.h"	
#include "sys.h" 

	  	
typedef __packed struct
{
	uint8_t sof1;      //0xA5
	uint16_t temp1_1;      //chassis angluar rate  deg/s
	uint16_t temp2_1;      //x velocity  mm/s
	uint16_t temp3_1;      //y velocity  mm/s
  uint16_t temp4_1;
	uint16_t temp5_1;
	uint16_t temp6_1;
	uint16_t temp7_1;
	uint16_t temp8_1;
	uint8_t end1;      //0xFE
} tReceTXoneData;

//extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u16 USART_RX_STA;         		//����״̬���	
////����봮���жϽ��գ��벻Ҫע�����º궨��
//	  	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		//����״̬���
extern u8  USART2_RX_FLAG;	

void usart2_init(u32 bound);
void usart3_init(u32 bound);
#endif


