/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "timer.h"
//#include "misc.h"
#include <stdint.h>
#include "interrupt.h"
#include "swim.h"
#include "configuration.h"
#include "malloc.h"

uint16_t counter = 0;
SwimState swimState;
/* Private function prototypes -----------------------------------------------*/

void delay(int counter);
void TIM1_UP_IRQHandler(void);
void TIM4_IRQHandler(void);
void swimActivation(void);
void swimCommandSRST(void);

int main(void)
{

  counter = 0;

  swimState.state = SWIM_ACTIVATION;
  swimState.counter = 0;
//  SWIM_RESET_Init();

  SWIM_RESET_Init();
  swimInInit();
  swimOutInit();
  TIM1_init();
//  timerConfigurePWM(TIM1, channel1, 30000, 4, TIM_OCMode_PWM1);
  timerConfigurePWM(TIM1, channel1, 30000, 4, TIM_OCMode_Inactive);
//  timerConfigurePWM(TIM1, channel1, 30000);
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  delay(20);
  SWIM_RESET();


  while (1)
  {
//	  delay(100);
  }
}

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 100; i++) {}
}

/**
  * @brief  This function handles TIM1 interrupt request.
  * 		Handle SWIM Activation Sequence.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler()
{
//	uint32_t TimerPeriod = 0;
//	uint16_t Channel1Pulse = 0;

  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {

    switch(swimState.state)
    {
      case SWIM_ACTIVATION:
          swimActivation();
          break;

      case SWIM_COMMAND_SRST:
          swimCommandSRST();
          break;

      case SWIM_COMMAND_ACK:
//        TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
          break;
      case SWIM_DO_NOTHING:
//    	  TIM_Cmd(TIM1, DISABLE);
          TIM_CtrlPWMOutputs(TIM1, DISABLE);
    	  break;
      default:
        swimState.state = SWIM_ACTIVATION;
      break;
    }
//    counter ++;


    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  }
}

void TIM4_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
  {
    switch(swimState.state)
	{
      case SWIM_LISTEN_SYNCHRONIZATION:

    	  swimState.counter = 0;
	      swimState.state = SWIM_ACTIVATION;
	      NVIC_EnableIRQ(TIM1_UP_IRQn);

      break;

      default:
          swimState.state = SWIM_DO_NOTHING;

      break;
	}
  }
      TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
}

void swimActivation(void)
{
	uint32_t ARRvalue = 0;
	uint16_t CRRvalue = 0;

	swimState.counter++;

    if(swimState.counter == 1)
    {
      timerConfigurePWM(TIM1, channel1, 1000, 50, TIM_OCMode_PWM1);
    }
    else if(swimState.counter == 5)
    {
        /* from 1k Hz ARR */
    	ARRvalue = getTimerARR(TIM1);

    	/* divide it into 2kHZ */
    	ARRvalue = ARRvalue / 2;

    	/* Pwm duty = 50 % */
    	CRRvalue = ARRvalue / 2;

    	TIM_SetAutoreload(TIM1, ARRvalue);
    	TIM_SetCompare1(TIM1, CRRvalue);
    }
    else
    {

      if(swimState.counter == 9)
      {
        /* from 2k Hz ARR */
    	ARRvalue = getTimerARR(TIM1);

        /* divide it into 50kHZ */
        ARRvalue = ARRvalue / 50;

        TIM_SetAutoreload(TIM1, ARRvalue);

//        TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
        configurePin(SWIM_OUT_PORT, SWIM_OUT_PIN, GPIO_Mode_IN_FLOATING);
//              timerConfigurePeriod(TIM1, 60000);

//        timerConfigurePWM(TIM1, channel1, 50000, 0, TIM_OCMode_Active);
//        NVIC_DisableIRQ(TIM1_UP_IRQn);
//        swimState.state = SWIM_LISTEN_SYNCHRONIZATION;
//        swimState.state = SWIM_COMMAND_SRST;
        swimState.cmdBitCounter = 0;

//        TIM4_init();
        /* brief  Configure the TI2 as Input. */
//        TM_PWM_IC_Init(TIM4, TIM_Channel_2, TIM_ICPolarity_Falling, TIM_ICSelection_DirectTI,
//      		          TIM_ICPSC_DIV1, 0x0);
//              TI2_Config(TIM4, TIM_ICPolarity_Falling, TIM_ICSelection_DirectTI, 0x0);
      }
    }

}

void swimCommandSRST(void)
{
    if(swimState.cmdBitCounter == 0)
    {
//      timerConfigurePWM(TIM1, channel1, 60000, 1, TIM_OCMode_Active);

//        	if(GPIO_ReadInputDataBit(SWIM_IN_PORT, SWIM_IN_PIN))
//        	  TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_InActive);
//        	else
//              TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);

      timerConfigurePWM(TIM1, channel1, 363636, 91, TIM_OCMode_PWM2);

    }
    else if(swimState.cmdBitCounter == 5)
    {
      TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_InActive);
//    	swimState.state = SWIM_DO_NOTHING;
//         TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
    }
    swimState.cmdBitCounter++;

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




///**
//  * @brief  Configures the different system clocks.
//  * @param  None
//  * @retval None
//  */
//void RCC_Configuration(void)
//{
//  /* TIM1, GPIOA, and AFIO clocks enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //| RCC_APB2Periph_AFIO
//  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, DISABLE);
//
//  /* TIM3 clock enable */
////  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
////  RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
//
//}
//
//
//void GPIO_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//
////  /* GPIOB Configuration: reset SWIM pin*/
////  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////  GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//  /* GPIOB Configuration: SWIM_IN pin*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // reset state;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // reset state;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//}
