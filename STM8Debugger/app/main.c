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
  timerConfigurePWM(TIM1, channel1, 30000, 4, TIM_OCMode_Inactive);
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
  *         Handle SWIM Activation Sequence.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler()
{
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
    switch(swimState.state)
    {
      case SWIM_ACTIVATION:
          swimActivation();
          break;
      case SWIM_READY_TO_SEND:
      
      case SWIM_COMMAND_SRST:
          swimCommandSRST();
          break;

      case SWIM_COMMAND_ACK:
          break;
      // case SWIM_LISTEN_SYNCHRONIZATION:
          // TIM_Cmd(TIM1, DISABLE);
          // TIM_CtrlPWMOutputs(TIM1, DISABLE);
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
        swimListenSynchronization();
        break;
      default:
        swimState.state = SWIM_ACTIVATION;
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

      configurePin(SWIM_OUT_PORT, SWIM_OUT_PIN, GPIO_Mode_IN_FLOATING);
      TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active);
//       timerConfigurePWM(TIM1, channel1, 50000, 0, TIM_OCMode_Active);
      swimState.state = SWIM_LISTEN_SYNCHRONIZATION;
      NVIC_DisableIRQ(TIM1_UP_IRQn);
      TIM4_init();
      
      /* TIM4 configuration: PWM Input mode ------------------------
         The external signal is connected to TIM4 CH2 pin (PB.07),
         The Falling edge is used as active edge,
      ------------------------------------------------------------ */
      TM_PWM_IC_Init(TIM4, TIM_Channel_2, TIM_ICPolarity_Falling, TIM_ICSelection_DirectTI,
    		          TIM_ICPSC_DIV1, 0x0);
//             TI2_Config(TIM4, TIM_ICPolarity_Falling, TIM_ICSelection_DirectTI, 0x0);
      TIM_Cmd(TIM4, ENABLE);
      swimState.counter = 0;
    }
  }

}

void swimListenSynchronization(void)
{
  uint16_t counterValue = 0;
  uint16_t period = 0;

  swimState.counter++;

  if(swimState.counter == 1)
  {
    TIM_SetCounter(TIM4, 0);
  }
  else
  {
    counterValue = TIM_GetCounter(TIM4);
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);

    /*  16uSecs = 62500 Hz */
    frequency = RCC_Clocks.PCLK1_Frequency / counterValue;
    
    if(frequency < 62500)
      swimState.state = SWIM_COMMAND_WOTF;
    else
      swimState.state = SWIM_ACTIVATION;
    
    swimState.counter = 0;
    swimState.cmdBitCounter = 0;
    NVIC_DisableIRQ(TIM4_IRQn);
    TIM1_init();
    timerConfigurePWM(TIM1, channel1, 3000000, 0, TIM_OCMode_Active));
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
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
