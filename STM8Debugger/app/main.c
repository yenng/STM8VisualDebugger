/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
//#include "Timer.h"
//#include "misc.h"
#include <stdint.h>

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_7PWM_Output
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_OCInitTypeDef outputChannelInit;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
uint16_t counter = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM1_UP_IRQHandler(void);
void delay(int counter);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{


//  NVIC_EnableIRQ(TIM1_UP_IRQn);
//	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();



/*   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 1 Khz
   * 72M / (frequency * 2)
   * /
*/
  TimerPeriod = (SystemCoreClock / (1000 *2) ) - 1;

  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
//  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
//  Channel2Pulse = (uint16_t) (((uint32_t) 375 * (TimerPeriod - 1)) / 1000);
//  /* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 and 3N */
//  Channel3Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);
//  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
//  Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod- 1)) / 1000);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

//  TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);
//  TIM_UpdateDisableConfig(TIM1, DISABLE);


  outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
  outputChannelInit.TIM_Pulse = Channel1Pulse;
  outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
  outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
  outputChannelInit.TIM_OCIdleState = TIM_OCIdleState_Set;

  TIM_OC1Init(TIM1, &outputChannelInit);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);


  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  uint32_t checkbit = 0;


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
  /* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE|
		  	  	  	  	 RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE|
		  	  	  	  	 RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, DISABLE);
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
}

/**
  * @brief  This function handles TIM1 interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler()
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
      TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
      counter ++;
  	  if(!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))
  	  {
  		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
  	  }
  	  else
  	  {
  		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
  	  }

  	  if(counter == 8)
  	  {

  		TIM_Cmd(TIM1, DISABLE);
  		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  		TimerPeriod = (SystemCoreClock / (2000 *2) ) - 1;

  		TIM_TimeBaseStructure.TIM_Prescaler = 0;
  		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  		TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  		TIM_Cmd(TIM1, ENABLE);
  		counter = 0;
  	  }
    }
}

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 10000; i++) {}
}

