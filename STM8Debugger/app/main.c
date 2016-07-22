/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Timer.h"
//#include "misc.h"
#include <stdint.h>
#include "Interrupt.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_7PWM_Output
  * @{
  */


uint16_t counter = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM1_init(void);
void TIM4_IC_init(void);
void TIM1_UP_IRQHandler(void);
//void TIM1_CC_IRQHandler(void);
void TIM4_IRQHandler(void);
void delay(int counter);

int main(void)
{

  counter = 0;
  RCC_Configuration();
  GPIO_Configuration();

  /* Reset SWIM */
//  GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
//  GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
//  delay(100);
  GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
//  delay(100);
//  delay(100);

  TIM1_init();

  while (1)
  {

  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* TIM1, GPIOA, and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, DISABLE);

  /* TIM3 clock enable */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//  RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);

}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: reset SWIM pin*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* GPIOB Configuration: SWIM_IN pin*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // reset state;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // reset state;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  GPIO_InitTypeDef gpio; //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
//  gpio.GPIO_Pin = GPIO_Pin_13;
//  gpio.GPIO_Speed = GPIO_Speed_50MHz;
//  gpio.GPIO_Mode = GPIO_Mode_Out_OD;
//  GPIO_Init(GPIOC, &gpio);
//  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void TIM1_init(void)
{
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;

  TIM_Cmd(TIM1, DISABLE);

  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  TIM_SetCounter(TIM1, 0);
  TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);
  NVIC_EnableIRQ(TIM1_UP_IRQn);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //Have to put after GPIO
//  TIM_UpdateDisableConfig(TIM1, DISABLE);

  TimerPeriod = (SystemCoreClock / 4000 ) - 1;
  Channel1Pulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);

  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE);

  TM_PWM_OC_Init(TIM1, TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
                 TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
//  TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_InActive);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

}

/*
void TIM4_IC_init(void)
{

  TIM_Cmd(TIM4, DISABLE);

  TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
  TIM_SetCounter(TIM4, 0);
  NVIC_EnableIRQ(TIM4_IRQn);

  TM_PWM_IC_Init(TIM4,
                 TIM_Channel_2,
                 TIM_ICPolarity_Rising,
                 TIM_ICSelection_DirectTI,
                 TIM_ICPSC_DIV1,
                 0x0,
                 TIM_TS_TI2FP2, //what?
                 TIM_SlaveMode_Reset,
                 TIM_MasterSlaveMode_Enable);

   TIM4 counter enable
  TIM_Cmd(TIM4, ENABLE);
  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE); //Have to put after GPIO

}

*/

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 1000; i++) {}
}


/**
  * @brief  This function handles TIM1 interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler()
{
	uint32_t TimerPeriod = 0;
	uint16_t Channel1Pulse = 0;

    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {

      counter ++;

      if(counter == 1)
      {
        TimerPeriod = (SystemCoreClock / 2000 ) - 1;
        Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
        //Prescaler = 1, 1kHz
        TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE);

        TM_PWM_OC_Init(TIM1, TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
                      TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
      }
      else if(counter == 5)
      {
        TimerPeriod = (SystemCoreClock / 4000 ) - 1;
        Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
        //Prescaler = 1, 2kHz
        TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE);

        TM_PWM_OC_Init(TIM1, TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
                       TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
      }
      else if(counter == 9)
      {
//    	  TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
    	  TM_PWM_OC_Init(TIM1, TIM_ForcedAction_Active, Channel1Pulse, TIM_OutputState_Enable,
    	                 TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
//    	  counter = 0;
//    	  TIM_Cmd(TIM1, DISABLE);
//    	  TIM_CtrlPWMOutputs(TIM1, DISABLE);
      }

      TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

void TIM4_IRQHandler(void)
{

}
