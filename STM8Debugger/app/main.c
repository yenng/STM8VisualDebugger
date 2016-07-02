/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Timer.h"
//#include "misc.h"
#include <stdint.h>

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
void TIM1_UP_IRQHandler(void);
//void TIM1_CC_IRQHandler(void);
void delay(int counter);

int main(void)
{

  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;
  counter = 0;


  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();

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

  TIM_Cmd(TIM1, DISABLE);
  // TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

  TimerPeriod = (SystemCoreClock / 30000 ) - 1;

  Channel1Pulse = (uint16_t) (((uint32_t) 1 * (TimerPeriod - 1)) / 100);
	// Prescaler = 0, 60kHz
	// OCmode2, Inactive Before CNT < CCRx.
	// 96% Off = 16u Sec

  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE,
	 		  	  	TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
			  	  	TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);

  //  NVIC_EnableIRQ(TIM1_CC_IRQn);
  NVIC_EnableIRQ(TIM1_UP_IRQn);

  //  TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE); //Have to put after GPIO
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //Have to put after GPIO

  //  TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);



  while (1)
  {
	   if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))
		   PWMcounter++;



  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, DISABLE);
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
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitTypeDef gpio; //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
  gpio.GPIO_Pin = GPIO_Pin_13;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  gpio.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOC, &gpio);
  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

/**
  * @brief  This function handles TIM1 interrupt request.
  * @param  None
  * @retval None
  */
//void TIM1_CC_IRQHandler(void)
void TIM1_UP_IRQHandler()
{
	uint32_t TimerPeriod = 0;
	uint16_t Channel1Pulse = 0;

    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {

//    	TIM_Cmd(TIM1, DISABLE);
//    	TIM_CtrlPWMOutputs(TIM1, DISABLE);
    	counter ++;
//      TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);

    	if(counter == 1)
	    {
    	  TimerPeriod = (SystemCoreClock / 2000 ) - 1;
    	  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
    	  //Prescaler = 1, 1kHz
    	  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE,
    	  				TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
    	  				TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
//    		counter = 0;
	    }
	    else if(counter == 5) //Toggle
	   {
		  TimerPeriod = (SystemCoreClock / 4000 ) - 1;
		  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
		  //Prescaler = 1, 1kHz
		  TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE,
						TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
						TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
//			counter = 0;
	   }
	    else if(counter == 9)
    			  {
    				TimerPeriod = (SystemCoreClock / 30000 ) - 1;
    				Channel1Pulse = (uint16_t) (((uint32_t) 1 * (TimerPeriod - 1)) / 100);
    				TM_TIMER_Init(TIM1, 1, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1, DISABLE,
    							  TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
    							  TIM_OCPolarity_High, TIM_OCIdleState_Set, DISABLE);
    				counter = 0;

    			  }

     /* else if(counter == 5)
  	  {
    	TimerPeriod = (SystemCoreClock / 2000 ) - 1;
    	Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
    	//Prescaler = 0, 2kHz
    	TM_TIMER_Init(TIM1, 0, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1,
    	 		  	  	TIM_OCMode_PWM1, Channel1Pulse, TIM_OutputState_Enable,
    			  	  	TIM_OCPolarity_High, TIM_OCIdleState_Set, ENABLE);
//		counter = 0;
  	  }
  	  else if(counter == 9)
  	  {
        TimerPeriod = (SystemCoreClock / 60000 ) - 1;
        Channel1Pulse = (uint16_t) (((uint32_t) 97 * (TimerPeriod - 1)) / 100);
        TM_TIMER_Init(TIM1, 0, TIM_CounterMode_Up, TimerPeriod, TIM_CKD_DIV1,
        		      TIM_OCMode_PWM2, Channel1Pulse, TIM_OutputState_Enable,
        		  	  TIM_OCPolarity_High, TIM_OCIdleState_Set, ENABLE);
        counter = 0;

  	  }
*/

/*
 	  if(!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))
  		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
  	  else
  		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);*/

//  	  TIM_Cmd(TIM1, ENABLE);
//  	  TIM_CtrlPWMOutputs(TIM1, ENABLE);

	    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 10000; i++) {}
}

