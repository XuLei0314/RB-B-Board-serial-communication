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

//extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//extern u16 USART_RX_STA;         		//接收状态标记	
////如果想串口中断接收，请不要注释以下宏定义
//	  	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记
extern u8  USART2_RX_FLAG;	

void usart2_init(u32 bound);
void usart3_init(u32 bound);
#endif


