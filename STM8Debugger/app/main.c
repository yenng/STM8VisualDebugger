

#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 10000; i++) {}
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

    while (1)
   {
    	GPIO_SetBits(GPIOC, GPIO_Pin_13); // LED ON
        delay(100);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // LED OFF
        delay(100);
    }
}
