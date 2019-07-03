#ifndef __POWER_H
#define __POWER_H	 
#include "sys.h"
#include "main.h"

#define SV5_OFF		GPIOA->BRR = GPIO_Pin_4
#define SV5_ON		GPIOA->BSRR = GPIO_Pin_4

#define SV6_OFF		GPIOA->BRR = GPIO_Pin_5
#define SV6_ON		GPIOA->BSRR = GPIO_Pin_5

#define SV7_OFF		GPIOA->BRR = GPIO_Pin_6
#define SV7_ON		GPIOA->BSRR = GPIO_Pin_6

#define SV8_OFF		GPIOA->BRR = GPIO_Pin_7
#define SV8_ON		GPIOA->BSRR = GPIO_Pin_7
void POWER_Init(void);

#endif

