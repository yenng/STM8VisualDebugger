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
int SWRST[5] = {0, 0, 0, 0, 0};
int highBitFormat[22] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int lowBitFormat[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
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

  swimState.state = SWIM_ACTIVATION;
  swimState.counter = 0;
  SWIM_RESET_Init();

  swimOutInit();
  swimInInit();
  TIM1_init();
  timerConfigurePWM(TIM1, channel1, 30000, 4);
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

    switch(swimState.state)
    {
      case SWIM_ACTIVATION:
          swimState.counter++;
          if(swimState.counter == 1)
          {
            timerConfigurePWM(TIM1, channel1, 1000, 50);
          }
          else if(swimState.counter == 5)
          {
            timerConfigurePWM(TIM1, channel1, 2000, 50);
          }
          else
          {
            
            if(swimState.counter == 9)
            {
              TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
              timerConfigurePeriod(TIM1, 17000);
              swimState.state = SWIM_COMMAND;
              swimState.bitFormatCounter = 22;
              swimState.cmdBitCounter = 0;
              swimState.cmd[0] = SWRST[0];
            }
          
          }
          break;
          
      case SWIM_COMMAND:
          timerConfigurePeriod(TIM1, 125);

          if(swimState.bitFormatCounter > 21)
          {
            if(swimState.cmdBitCounter == 5)
              break;
            
            if(swimState.cmd[swimState.cmdBitCounter])
              swimState.bitFormat[0] = highBitFormat[0];
            else
              swimState.bitFormat[0] = lowBitFormat[0];
            swimState.bitFormatCounter = 0;
          }
          else
          {
            if(swimState.bitFormat[swimState.bitFormatCounter] == 1)
              TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
            else
              TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_InActive);
            
            swimState.bitFormatCounter++;
          }
          
          break;
      default:
        swimState.state = SWIM_ACTIVATION;
      break;
    }
//    counter ++;




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
