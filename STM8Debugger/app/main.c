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

uint16_t counter = 0;

/* Private function prototypes -----------------------------------------------*/

// void TIM4_IC_init(void);
void TIM1_UP_IRQHandler(void);
//void TIM1_CC_IRQHandler(void);
// void TIM4_IRQHandler(void);
void delay(int counter);

int main(void)
{

  counter = 0;

/*   Reset SWIM*/
//  SWIM_Reset();
//  delay(1);
//  SWIM_RESET_DEASSERT();
//  configurePin(SWIM_OUT_PORT, SWIM_OUT_PIN, GPIO_Mode_Out_PP);
//  GPIO_SetBits(SWIM_OUT_PORT, SWIM_OUT_PIN);
//  configurePin(SWIM_OUT_PORT, SWIM_OUT_PIN, GPIO_Mode_AF_OD);
//  swimInInit();


//  SWIM_RESET_Init();
//  SWIM_RESET();
  //  delay(1);
//  delay(18);
//  SWIM_RESET_DEASSERT();
/*  swimOutInit();
  swimInInit();
  TIM1_init();

  timerConfigurePWM(TIM1, channel1, 500);
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  delay(20);
  SWIM_RESET_Init();
  SWIM_RESET();
  delay(20);*/

  SWIM_RESET_Init();

  swimOutInit();
  swimInInit();
  TIM1_init();

  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  uint16_t timerPeriod = 0;
  uint16_t channel1Pulse = 0;
  timerPeriod = (RCC_Clocks.PCLK2_Frequency / ( 30000 )) - 1;
  channel1Pulse = (uint16_t) (((uint32_t) 4 * (timerPeriod - 1)) / 100);

  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, timerPeriod, TIM_CKD_DIV1, DISABLE);

  TM_PWM_OC_Init(TIM1, channel1, TIM_OCMode_PWM1, channel1Pulse, TIM_OutputState_Enable,
                 TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
//  timerConfigurePWM(TIM1, channel1, 30000);
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
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
	uint16_t Channel1Pulse = 0;

  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {

    counter ++;

    if(counter == 1)
    {
      timerConfigurePWM(TIM1, channel1, 1000);
    }
    else if(counter == 5)
    {
      timerConfigurePWM(TIM1, channel1, 2000);
    }
    else if(counter == 9)
    {
  	  TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
//  	  TIM_Cmd(TIM1, DISABLE);  //Cannot disable
//  	  TIM_CtrlPWMOutputs(TIM1, DISABLE); //Cannot disable
    }

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  }
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

//
//void TIM4_IRQHandler(void)
//{
//
//}


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
