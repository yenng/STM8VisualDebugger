#include "Timer.h"
#include <stdint.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
	/*   The Timer pulse is calculated as follows:
	   - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
		 -----------------------------------------------------------------------
	 * Compute the value to be set in ARR regiter to generate signal frequency at 1 Khz
	 * SystemCoreClock is too fast to generate 1Khz
	 * So, we put a prescale = 1 (1+1=2)
	 * (72M /2) / (frequency )
     */
  //  TimerPeriod = (SystemCoreClock / 2000 ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  //  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
// Prescaler = 0, 60kHz
	// OCmode2, Inactive Before CNT < CCRx.
	// 96% Off = 16u Sec

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
	  TIM_OC1Init(TIMx, &outputChannelInit);
	  TIM_OC1PreloadConfig(TIM1, OCPreload_Enable);
}

void TM_PWM_IC_Init(TIM_TypeDef* TIMx,
                    uint16_t Channel,
                    uint16_t ICPolarity,
                    uint16_t ICSelection,
                    uint16_t ICPrescaler,
                    uint16_t ICFilter,
                    uint16_t InputTriggerSource,
                    uint16_t SlaveMode,
                    uint16_t MasterSlaveMode)
{
  TIM_ICInitStructure.TIM_Channel = Channel;
  TIM_ICInitStructure.TIM_ICPolarity = ICPolarity;
  TIM_ICInitStructure.TIM_ICSelection =ICSelection;
  TIM_ICInitStructure.TIM_ICPrescaler =ICPrescaler;
  TIM_ICInitStructure.TIM_ICFilter = ICFilter;

  TIM_PWMIConfig(TIMx, &TIM_ICInitStructure);

  /* Select the TIM3 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(TIMx, InputTriggerSource);

  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM3, SlaveMode);

  /* Enable the Master/Slave Mode */
  TIM_SelectMasterSlaveMode(TIM3, MasterSlaveMode);
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

