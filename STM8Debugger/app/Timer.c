#include "Timer.h"
#include <stdint.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void TIM1_init(void)
{
  TIM_Cmd(TIM1, DISABLE);
  configRccTIM1();

  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  TIM_SetCounter(TIM1, 0);
  TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);
  NVIC_EnableIRQ(TIM1_UP_IRQn);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //Have to put after GPIO

}
/** @brief Configure the TIM4 channel2 as PWM input capture
  *
  */
void TIM4_init(void)
{
  TIM_Cmd(TIM4, DISABLE);
  configRccTIM4();

  TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
  TIM_SetCounter(TIM4, 0);
  NVIC_EnableIRQ(TIM4_IRQn);

  TIM_Cmd(TIM4, ENABLE);

  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE); //Have to put after GPIO
}

void configRccTIM1(void)
{
  /* TIM1 clocks enable , reset disable*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 , DISABLE);
}

void configRccTIM4(void)
{
  /* TIM4 clocks enable , reset disable*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE);
}

void timerConfigurePeriod(TIM_TypeDef* TIMx, uint32_t frequency)
{
  uint16_t timerPeriod = 0;
  uint16_t prescaler = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  
  prescaler = (RCC_Clocks.PCLK2_Frequency / (frequency * 65535));

  timerPeriod = (RCC_Clocks.PCLK2_Frequency / (frequency * (prescaler + 1))) - 1;

  TM_TIMER_Init(TIM1, prescaler, TIM_CounterMode_Up, timerPeriod, TIM_CKD_DIV1, DISABLE);

}

void timerConfigurePWM(TIM_TypeDef* TIMx,  uint16_t channelx, uint32_t frequency, int dutyCycle, uint16_t TIM_OCMode)
{
  uint16_t timerPeriod = 0;
  uint16_t channel1Pulse = 0;
  uint16_t prescaler = 0;

  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  prescaler = (RCC_Clocks.PCLK2_Frequency / (frequency * 65535));

  timerPeriod = (RCC_Clocks.PCLK2_Frequency / (frequency * (prescaler + 1))) - 1;
  channel1Pulse = (uint16_t) (((uint32_t) dutyCycle * (timerPeriod - 1)) / 100);

  TM_TIMER_Init(TIM1, prescaler, TIM_CounterMode_Up, timerPeriod, TIM_CKD_DIV1, DISABLE);

  TM_PWM_OC_Init(TIM1, channelx, TIM_OCMode, channel1Pulse, TIM_OutputState_Enable,
                 TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
//  TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
}

void TM_TIMER_Init(TIM_TypeDef* TIMx,
                  uint16_t Prescaler,
                  uint16_t CounterMode,
                  uint16_t Period,
                  uint16_t ClockDivision,
                  uint16_t ARRPreloadConfig)
{
  TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
  TIM_TimeBaseStructure.TIM_CounterMode = CounterMode;
  TIM_TimeBaseStructure.TIM_Period = Period;
  TIM_TimeBaseStructure.TIM_ClockDivision = ClockDivision;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIMx, ARRPreloadConfig);
}

void TM_PWM_OC_Init(TIM_TypeDef* TIMx,
                    uint16_t channelx,
                    uint16_t OCMode,
                    uint16_t Pulse,
                    uint16_t OutputState,
                    uint16_t OCPolarity,
                    uint16_t OCIdleState,
                    uint16_t OCPreload_Enable)
{
  outputChannelInit.TIM_OCMode = OCMode;
  outputChannelInit.TIM_Pulse = Pulse;
  outputChannelInit.TIM_OutputState = OutputState;
  outputChannelInit.TIM_OCPolarity = OCPolarity;
  outputChannelInit.TIM_OCIdleState = OCIdleState;
  if(channelx == channel1)
  {
    TIM_OC1Init(TIMx, &outputChannelInit);
    TIM_OC1PreloadConfig(TIMx, OCPreload_Enable);
  }
  else if(channelx == channel2)
  {
    TIM_OC2Init(TIMx, &outputChannelInit);
    TIM_OC2PreloadConfig(TIMx, OCPreload_Enable);
  }
  else if(channelx == channel3)
  {
    TIM_OC3Init(TIMx, &outputChannelInit);
    TIM_OC3PreloadConfig(TIMx, OCPreload_Enable);
  }
  else
  {
    if(channelx == channel4)
    {
      TIM_OC4Init(TIMx, &outputChannelInit);
      TIM_OC4PreloadConfig(TIMx, OCPreload_Enable);
    }
  }
}

void TM_PWM_IC_Init(TIM_TypeDef* TIMx,
                    uint16_t TIM_Channel,
                    uint16_t ICPolarity,
                    uint16_t ICSelection,
                    uint16_t ICPrescaler,
                    uint16_t ICFilter)
{
  TIM_ICInitStructure.TIM_Channel =  TIM_Channel;
  TIM_ICInitStructure.TIM_ICPolarity = ICPolarity;
  TIM_ICInitStructure.TIM_ICSelection = ICSelection;
  TIM_ICInitStructure.TIM_ICPrescaler = ICPrescaler;
  TIM_ICInitStructure.TIM_ICFilter = ICFilter;

  TIM_PWMIConfig(TIMx, &TIM_ICInitStructure);
  
  // /* Select the TIM4 Input Trigger: TI1FP1 */
  // TIM_SelectInputTrigger(TIMx, TIM_TS_TI1FP1);

  // /* Select the slave Mode: Reset Mode */
  // TIM_SelectSlaveMode(TIMx, TIM_SlaveMode_Reset);

  // /* Enable the Master/Slave Mode */
  // TIM_SelectMasterSlaveMode(TIMx, TIM_MasterSlaveMode_Enable);

}

uint32_t getTimerARR(TIM_TypeDef* TIMx)
{
	uint32_t arrValue = 0;
	arrValue = TIMx->ARR;
	return arrValue;
}
