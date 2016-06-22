#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Timer.h"
#include <stdint.h>

void initializeLEDs()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,DISABLE);

    GPIO_InitTypeDef gpio;         //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOC,&gpio);

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

	//  TM_Init(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t CounterMode, uint16_t Period, uint16_t ClockDivision)
	//  TM_Timer_Init(TIM1, 0, TIM_CounterMode_Up, 18009, TIM_CKD_DIV1);
	//  TM_Init(TIM1, 0, TIM_CounterMode_Up, 0xFFFF, TIM_CKD_DIV1);

	TIM_TimeBaseInitTypeDef timer;
	//
	timer.TIM_Prescaler = 0;
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 18009;
	timer.TIM_ClockDivision = TIM_CKD_DIV1;
	timer.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &timer);

	//  void TM_PWM_Init(TIM_TypeDef* TIMx, uint16_t OCMode, uint16_t OutputState, uint16_t OCPolarity, uint16_t Period, uint16_t DutyCycle, uint16_t OCPreload_Enable)
	//  TM_PWM_Init(TIM1, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High, 18009, 50, TIM_OCPreload_Enable);
}

void InitializePWMChannel()
{
	//    TIM_OCInitTypeDef TIM_OCStruct;
	//
	//    /* Common settings */
	//
	//    /* PWM mode 2 = Clear on compare match */
	//    /* PWM mode 1 = Set on compare match */
	//    TIM_OCStruct.TIM_OCMode = OCMode;
	//    TIM_OCStruct.TIM_OutputState = OutputState;
	//    TIM_OCStruct.TIM_OCPolarity = OCPolarity;
	//
	///*
	//    To get proper duty cycle, you have simple equation
	//
	//    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1
	//
	//    where DutyCycle is in percent, between 0 and 100%
	//
	//    25% duty cycle:     pulse_length = ((18009 + 1) * 25) / 100 - 1 = 4502
	//    50% duty cycle:     pulse_length = ((18009 + 1) * 50) / 100 - 1 = 9004
	//    75% duty cycle:     pulse_length = ((18009 + 1) * 75) / 100 - 1 = 13507
	//    100% duty cycle:    pulse_length = ((18009 + 1) * 100) / 100 - 1 = 18009
	//
	//    Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
	//*/
	//    TIM_OCStruct.TIM_Pulse = ((Period + 1) * DutyCycle) / 100 - 1 ; /* % duty cycle */
	//    TIM_OC1Init(TIMx, &TIM_OCStruct);
	//    TIM_OC1PreloadConfig(TIMx, OCPreload_Enable);
	//    // TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	//
	//    // GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN ,ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2ENR_AFIOEN ,DISABLE);
    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 9000;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
}

int main(void)
{
  uint32_t timerValue = 0;
  initializeLEDs();
  initializeTimer();
  InitializePWMChannel();

  timerValue = TIM_GetCounter(TIM1);
  TIM_Cmd(TIM1, ENABLE);

//Please check the clock for alternate function
  while(1)
  {

	  timerValue = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8) & 1;
	  if(timerValue) //(timerValue > 9000)
	  {
//		  GPIO_SetBits(GPIOC, GPIO_Pin_13);
		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		  delay(100);
	  }
	  else
	  {
//		  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		  delay(1000);
	  }

  }
}


/*
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

