/*
#include "stm32f10x_gpio.h"p[]
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Timer.h"
#include "misc.h"
#include <stdint.h>

void initializeLEDs()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);

    GPIO_InitTypeDef gpio; //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOC, &gpio);

//    GPIO_PinAFConfig
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
    GPIO_InitTypeDef gpioa;
    gpioa.GPIO_Pin = GPIO_Pin_8;
    gpioa.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa);

//    GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13, Bit_RESET);
}

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 1000; i++) {}
}

void initializeTimer()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 ,ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 ,DISABLE);

	TIM1_DeInit();

	TIM_TimeBaseInitTypeDef timer;
	timer.TIM_Prescaler = 0;
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 18009;
	timer.TIM_ClockDivision = TIM_CKD_DIV1;
	timer.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &timer);
	TIM_Cmd(TIM1, ENABLE);
}


void EnableTimerInterrupt()
{
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM1_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}


void initializePWMChannel()
{
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN ,ENABLE); // Don't sure
    RCC_APB2PeriphResetCmd(RCC_APB2ENR_AFIOEN ,DISABLE); // Don't sure
    TIM_OCInitTypeDef outputChannelInit;
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 9000;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
}

int main(void)
{
  uint32_t timerValue = 0;
  uint32_t checkBit = 0;
  initializeLEDs();
  initializeTimer();
  initializePWMChannel();
  EnableTimerInterrupt();
  timerValue = TIM_GetCounter(TIM1);
  TIM_Cmd(TIM1, ENABLE);

//Please check the clock for alternate function
  while(1)
  {

//	  checkBit = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8);
//	  delay(100);
//	  checkBit = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8);
//	  delay(100);
//	  checkBit = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8);
//	  delay(100);


	 if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
     {
	         TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	         GPIO_ToggleBits(GPIOC, GPIO_Pin_13);
     }



	  timerValue = TIM_GetCounter(TIM1);
	  if(timerValue > 10000)//(checkBit)//(timerValue > 10000)//(!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))// (timerValue > 10000)
	  {
//		  GPIO_SetBits(GPIOC, GPIO_Pin_13);
		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		  delay(100);
	  }
	  else
	  {
//		  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		  delay(100);
	  }

  }
}



void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 1000; i++) {}
}

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,DISABLE);
    GPIO_InitTypeDef gpio;         //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOC,&gpio);

//    GPIO_SetBits(GPIOC, GPIO_Pin_13); // LED ON
    while (1)
   {
    	GPIO_SetBits(GPIOC, GPIO_Pin_13); // LED ON
        delay(1000);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // LED OFF
        delay(1000);
    }
}


*/

/**
  ******************************************************************************
  * @file    TIM/7PWM_Output/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

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
//  		  delay(100);
  	  }
  	  else
  	  {
  		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
//  		  delay(100);
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

/* Private functions ---------------------------------------------------------*/
void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 10000; i++) {}
}

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{


  NVIC_EnableIRQ(TIM1_UP_IRQn);

  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */

  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);


/*   The objective is to generate 7 PWM signal at 1 KHz:
     - TIM1_Period = (SystemCoreClock / 2000) - 1

   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 1 Khz
   * 72M / (frequency * 2)
   * /
*/
  TimerPeriod = (SystemCoreClock / (1000 *2) ) - 1;

//  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
//  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
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


//  outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
//  outputChannelInit.TIM_Pulse = Channel1Pulse;
//  outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
//  outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
//  outputChannelInit.TIM_OCIdleState = TIM_OCIdleState_Set;
//
//  TIM_OC1Init(TIM1, &outputChannelInit);
//  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  /*
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
  */





  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
//  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  uint32_t checkbit = 0;


  while (1)
  {
//	  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
//	  checkbit = TIM_GetFlagStatus(TIM1, TIM_FLAG_Update);
//
///*	  Toggle LED
// *
// *
// */
//	  if(!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))//(checkbit)//(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8))
//	  {
////		  GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
//		  delay(100);
//	  }
//	  else
//	  {
////		  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
//		  delay(100);
//	  }
//
//	  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
//	  checkbit = TIM_GetFlagStatus(TIM1, TIM_FLAG_Update);
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
//void GPIO_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//
//#ifdef STM32F10X_CL
//  /* GPIOE Configuration: Channel 1/1N, 2/2N, 3/3N and 4 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|
//                                GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//
//  GPIO_Init(GPIOE, &GPIO_InitStructure);
//
//  /* TIM1 Full remapping pins */
////  GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
//
//  GPIO_InitTypeDef gpio; //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
//  gpio.GPIO_Pin = GPIO_Pin_13;
//  gpio.GPIO_Speed = GPIO_Speed_50MHz;
//  gpio.GPIO_Mode = GPIO_Mode_Out_OD;
//  GPIO_Init(GPIOC, &gpio);
//
//
//#else
//  /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//  /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//  GPIO_InitTypeDef gpio; //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
//  gpio.GPIO_Pin = GPIO_Pin_13;
//  gpio.GPIO_Speed = GPIO_Speed_50MHz;
//  gpio.GPIO_Mode = GPIO_Mode_Out_OD;
//  GPIO_Init(GPIOC, &gpio);
//
//
//#endif
//}

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


//#ifdef  USE_FULL_ASSERT
//
///**
//  * @brief  Reports the name of the source file and the source line number
//  *         where the assert_param error has occurred.
//  * @param  file: pointer to the source file name
//  * @param  line: assert_param error line source number
//  * @retval None
//  */
//void assert_failed(uint8_t* file, uint32_t line)
//{
//  /* User can add his own implementation to report the file name and line number,
//     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//
//  while (1)
//  {}
//}
//
//#endif


/**
  * @}
  */

/**
  * @}
  */



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
