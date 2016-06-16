#include "Timer.h"
#include <stdint.h>
#include "stm32f10x_tim.h"

void Timer_conf(TIM_TypeDef* TIMx,
                uint16_t Prescaler,
                uint16_t CounterMode,
                uint16_t Period,
                uint16_t ClockDivision
              ){
                
  TIM_TimeBaseInitTypeDef timer;
  
  timer.TIM_Prescaler = Prescaler;
  timer.TIM_CounterMode = CounterMode;
  timer.TIM_Period = Period;
  timer.TIM_ClockDivision = ClockDivision;  

  TIM_TimeBaseInit(TIMx,&timer);
}

void enableTimer(TIM_TypeDef* TIMx,FunctionalState NewState){
  if(NewState != DISABLE){
  TIMx->CR1 |= Timer_Enable;
  }else{
  TIMx->CR1 &= TImer_Disable;
  }
  
}

uint16_t getTime(TIM_TypeDef* TIMx){
  return (TIMx->CNT);
}
