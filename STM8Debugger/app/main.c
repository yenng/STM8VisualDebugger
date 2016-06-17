#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

//void delay(int counter)
//{
//    int i;
//    for (i = 0; i < counter * 1000; i++) {}
//}
//
//int main(void)
//{
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,DISABLE);
//    GPIO_InitTypeDef gpio;         //The GPIO_InitTypeDef structure can be referred by stm32f10x_gpio.h.
//    gpio.GPIO_Pin = GPIO_Pin_6;
//    gpio.GPIO_Speed = GPIO_Speed_50MHz;
//    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
//    GPIO_Init(GPIOB,&gpio);
//
////    GPIO_SetBits(GPIOC, GPIO_Pin_13); // LED ON
//    while (1)
//   {
//    	GPIO_SetBits(GPIOB, GPIO_Pin_6); // LED ON
//        delay(10);
//        GPIO_ResetBits(GPIOB, GPIO_Pin_6); // LED OFF
//        delay(1);
//    }
//}

int main(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2 ,DISABLE);
    
    Timer_conf(TIM2,0,TIM_CounterMode_Up,0xFFFF,TIM_CKD_DIV1);
    uint16_t time;
    enableTimer(TIM2,ENABLE);
    uint32_t checkTimCR1 = TIM2->CR1;
    uint32_t checkTimCR2 = TIM2->CR2;
    uint32_t checkTimCNT = TIM2->CNT;
    uint32_t checkTimPSC = TIM2->PSC;
    uint32_t checkTimARR = TIM2->ARR;
    while(1)
    {
      time = getTime(TIM2);
    }
}
