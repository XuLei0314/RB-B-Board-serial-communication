#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
//#define LED0 PBout(5)// PB5
//#define LED1 PEout(5)// PE5	
//#define LED2 PEout(4)// PE5
//#define LED3 PEout(3)// PE5
//#define LED4 PEout(2)// PE5
#define RED_ON  	GPIOB->BRR = GPIO_Pin_1
#define RED_OFF 	GPIOB->BSRR = GPIO_Pin_1

#define GREEN_ON 	GPIOB->BRR = GPIO_Pin_0
#define GREEN_OFF GPIOB->BSRR = GPIO_Pin_0

void LED_Init(void);//��ʼ��

		 				    
#endif
