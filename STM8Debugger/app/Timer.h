#ifndef __Timer_H__
#define __Timer_H__

#include "stm32f10x_tim.h"
#include "configuration.h"


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_OCInitTypeDef outputChannelInit;
TIM_ICInitTypeDef TIM_ICInitStructure;

#define channel1 1
#define channel2 2
#define channel3 3
#define channel4 4

void TIM1_init(void);
void TIM4_init(void);
void configRccTIM1(void);
void configRccTIM4(void);
void timerConfigurePeriod(TIM_TypeDef* TIMx, uint32_t frequency);
void timerConfigurePWM(TIM_TypeDef* TIMx,  uint16_t channelx, uint32_t frequency, int dutyCycle, uint16_t TIM_OCMode);
void TM_TIMER_Init(TIM_TypeDef* TIMx,
                  uint16_t Prescaler,
                  uint16_t CounterMode,
                  uint16_t Period,
                  uint16_t ClockDivision,
                  uint16_t ARRPreloadConfig);
                  // uint16_t OCMode,
                  // uint16_t Pulse,
                  // uint16_t OutputState,
                  // uint16_t OCPolarity,
                  // uint16_t OCIdleState,
                  // uint16_t OCPreload_Enable);
                  
void TM_PWM_OC_Init(TIM_TypeDef* TIMx,
					uint16_t channelx,
                    uint16_t OCMode,
                    uint16_t Pulse,
                    uint16_t OutputState,
                    uint16_t OCPolarity,
                    uint16_t OCIdleState,
                    uint16_t OCPreload_Enable);

void TM_PWM_IC_Init(TIM_TypeDef* TIMx,
                    uint16_t TIM_Channel,
                    uint16_t ICPolarity,
                    uint16_t ICSelection,
                    uint16_t ICPrescaler,
                    uint16_t ICFilter);
                    /*uint16_t InputTriggerSource,
                    uint16_t SlaveMode,
                    uint16_t MasterSlaveMode);*/

uint32_t getTimerARR(TIM_TypeDef* TIMx);

#endif //__Timer_H__

