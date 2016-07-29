#include "Timer.h"
#include <stdint.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void TIM1_init(void)
{
//  uint16_t TimerPeriod = 0;
//  uint16_t Channel1Pulse = 0;
  TIM_Cmd(TIM1, DISABLE);
  configurationTIM1_Channel1();


  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  TIM_SetCounter(TIM1, 0);
  TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);
  NVIC_EnableIRQ(TIM1_UP_IRQn);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //Have to put after GPIO
//  TIM_UpdateDisableConfig(TIM1, DISABLE);

/*  TimerPeriod = (SystemCoreClock / 8000 ) - 1;
  Channel1Pulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);

  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE);

  TM_PWM_OC_Init(TIM1, TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
                 TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);


  TIM_Cmd(TIM1, ENABLE);*/

//  TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
//  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void configurationTIM1_Channel1(void)
{
  /* TIM1, GPIOA, and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 , DISABLE);

  //Channel_1 == SWIM_OUT_PIN
//  configurePin(GPIOA, GPIO_Pin_8, GPIO_Mode_AF_OD);
}

void timerConfigurePWM(TIM_TypeDef* TIMx,  uint16_t channelx, uint16_t frequency)
{
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;


  TimerPeriod = (SystemCoreClock / (frequency * 2)) - 1;
  Channel1Pulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);

  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE);

  TM_PWM_OC_Init(TIM1, channelx, TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
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
  TIM_ICInitStructure.TIM_ICSelection = ICSelection;
  TIM_ICInitStructure.TIM_ICPrescaler = ICPrescaler;
  TIM_ICInitStructure.TIM_ICFilter = ICFilter;

  TIM_PWMIConfig(TIMx, &TIM_ICInitStructure);

  /* Select the TIM3 Input Trigger: TI2FP2 */
//  TIM_SelectInputTrigger(TIMx, InputTriggerSource);

  /* Select the slave Mode: Reset Mode */
//  TIM_SelectSlaveMode(TIM3, SlaveMode);

  /* Enable the Master/Slave Mode */
//  TIM_SelectMasterSlaveMode(TIM3, MasterSlaveMode);
}

