#ifndef __Timer_setting_H__
#define __Timer_setting_H__

#include "stm32f10x_tim.h"
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_OCInitTypeDef outputChannelInit;

void TM_TIMER_Init(TIM_TypeDef* TIMx,
        		   uint16_t Prescaler,
        		   uint16_t CounterMode,
        		   uint16_t Period,
        		   uint16_t ClockDivision,
        		   uint16_t ARRPreloadConfig,
        		   uint16_t OCMode,
        		   uint16_t Pulse,
				   uint16_t OutputState,
				   uint16_t OCPolarity,
				   uint16_t OCIdleState,
				   uint16_t OCPreload_Enable);

#endif //__Timer_setting_H__

