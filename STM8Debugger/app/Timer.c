//#include "Timer.h"
//#include <stdint.h>
//#include "stm32f10x_tim.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
///*typedef struct
//{
//  uint16_t TIM_Prescaler;         !< Specifies the prescaler value used to divide the TIM clock.
//                                       This parameter can be a number between 0x0000 and 0xFFFF
//
//  uint16_t TIM_CounterMode;       !< Specifies the counter mode.
//                                       This parameter can be a value of @ref TIM_Counter_Mode
//
//  uint16_t TIM_Period;            !< Specifies the period value to be loaded into the active
//                                       Auto-Reload Register at the next update event.
//                                       This parameter must be a number between 0x0000 and 0xFFFF.
//
//  uint16_t TIM_ClockDivision;     *!< Specifies the clock division.
//                                      This parameter can be a value of @ref TIM_Clock_Division_CKD
//
//  uint8_t TIM_RepetitionCounter;  *!< Specifies the repetition counter value. Each time the RCR downcounter
//                                       reaches zero, an update event is generated and counting restarts
//                                       from the RCR value (N).
//                                       This means in PWM mode that (N+1) corresponds to:
//                                          - the number of PWM periods in edge-aligned mode
//                                          - the number of half PWM period in center-aligned mode
//                                       This parameter must be a number between 0x00 and 0xFF.
//                                       @note This parameter is valid only for TIM1 and TIM8.
//} TIM_TimeBaseInitTypeDef;
//*/
///*
//void TM_TIMER_Init(void) {
//    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
//
//    /* Enable clock for TIM4
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2 ,DISABLE);
///*
//    TIM4 is connected to APB1 bus, which has on F1 device 36MHz clock
//    But, timer has internal PLL, which double this frequency for timer, up to 72MHz
//    Remember: Not each timer is connected to APB1, there are also timers connected
//    on APB2, which works at 72MHz by default, and internal PLL increase
//    this to up to 144MHz
//
//    Set timer prescaller
//    Timer count frequency is set with
//
//    timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
//
//    In our case, we want a max frequency for timer, so we set prescaller to 0
//    And our timer will have tick frequency
//
//    timer_tick_frequency = 72000000 / (0 + 1) = 72000000
//
//    TIM_BaseStruct.TIM_Prescaler = 0;
//    /* Count up
//    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
///*
//    Set timer period when it have reset
//    First you have to know max value for timer
//    In our case it is 16bit = 65535
//    To get your frequency for PWM, equation is simple
//
//    PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
//
//    If you know your PWM frequency you want to have timer period set correct
//
//    TIM_Period = timer_tick_frequency / PWM_frequency - 1
//
//    In our case, for 2Khz PWM_frequency, set Period to
//
//    TIM_Period = 72000000 / 2000 - 1 = 18009
//
//    If you get TIM_Period larger than max timer value (in our case 65535),
//    you have to choose larger prescaler and slow down timer tick frequency
//
//    TIM_BaseStruct.TIM_Period = 18009; /* 2kHz PWM
//    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_BaseStruct.TIM_RepetitionCounter = 0;
//    /* Initialize TIM2
//    TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
//    /* Start count on TIM2
//    TIM_Cmd(TIM2, ENABLE);
//}
//
//*/
//
//void TM_Init(TIM_TypeDef* TIMx,
//                uint16_t Prescaler,
//                uint16_t CounterMode,
//                uint16_t Period,
//                uint16_t ClockDivision
//              )
//{
//  TIM_TimeBaseInitTypeDef timer;
//
//  timer.TIM_Prescaler = Prescaler;
//  timer.TIM_CounterMode = CounterMode;
//  timer.TIM_Period = Period;
//  timer.TIM_ClockDivision = ClockDivision;
////  timer.TIM_RepetitionCounter = 0;
//
//  TIM_TimeBaseInit(TIMx, &timer);
//}
//
//
//  uint16_t getTime(TIM_TypeDef* TIMx){
//  return (TIMx->CNT);
//}
//void enableTimer(TIM_TypeDef* TIMx,FunctionalState NewState){
//    if(NewState != DISABLE){
//    TIMx->CR1 |= Timer_Enable;
//    }else{
//    TIMx->CR1 &= TImer_Disable;
//    }
//
//  }
//
///**
//  * @brief  TIM Output Compare Init structure definition
//  */
///* PWM1 Mode configuration: Channel1
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//
//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
//
//  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
//*/
//void TM_PWM_Init(TIM_TypeDef* TIMx,
//                uint16_t OCMode,
//                uint16_t OutputState,
//                uint16_t OCPolarity,
//                uint16_t Period,
//                uint16_t DutyCycle,
//                uint16_t OCPreload_Enable)
//{
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
//
//}
//
////PA8 and PA11
//void TM1_CHANNEL_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
//
//// #ifdef STM32F10X_CL
//  /*GPIOB Configuration: TIM1 channel1 and 4 */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);	//Don't need remap, default function
//
//}
