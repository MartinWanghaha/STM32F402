#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f0xx.h"

void SysTick_Init(void);
void TimingDelay_Decrement(void);
void Delay_us(__IO u32 nTime);         // ��λ10us
#define Delay_ms(x) Delay_us(100*x)	 //��λms


#endif /* __ISO_SYSTICK_H */
