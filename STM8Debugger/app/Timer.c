#include "Timer.h"
#include <stdint.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

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
				   uint16_t OCPreload_Enable)
{

	  TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
	  TIM_TimeBaseStructure.TIM_CounterMode = CounterMode;
	  TIM_TimeBaseStructure.TIM_Period = Period;
	  TIM_TimeBaseStructure.TIM_ClockDivision = ClockDivision;
	  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	  TIM_ARRPreloadConfig(TIMx, ARRPreloadConfig);

	   outputChannelInit.TIM_OCMode = OCMode;
	   outputChannelInit.TIM_Pulse = Pulse;
	   outputChannelInit.TIM_OutputState = OutputState;
	   outputChannelInit.TIM_OCPolarity = OCPolarity;
	   outputChannelInit.TIM_OCIdleState = OCIdleState;
	   TIM_OC1Init(TIMx, &outputChannelInit);
	   TIM_OC1PreloadConfig(TIM1, OCPreload_Enable);
}

//  /* Time Base configuration */
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//
//  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//
////  TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);
////  TIM_UpdateDisableConfig(TIM1, DISABLE);
//  outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
//  outputChannelInit.TIM_Pulse = Channel1Pulse;
//  outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
//  outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
//  outputChannelInit.TIM_OCIdleState = TIM_OCIdleState_Set;
//
//  TIM_OC1Init(TIM1, &outputChannelInit);
//  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

