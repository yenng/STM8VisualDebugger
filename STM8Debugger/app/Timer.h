#ifndef __Timer_setting_H__
#define __Timer_setting_H__

#include "stm32f10x_tim.h"

#define Timer_Enable ((uint16_t)0x0001)
#define TImer_Disable ((uint16_t)0xFFFE)


void Timer_conf(TIM_TypeDef* TIMx,
                uint16_t Prescaler,
                uint16_t CounterMode,
                uint16_t Period,
                uint16_t ClockDivision
              );
              
              
void enableTimer(TIM_TypeDef* TIM,FunctionalState NewState);


uint16_t getTime(TIM_TypeDef* TIMx);

#endif //__Timer_setting_H__

