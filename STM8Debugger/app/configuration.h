#ifndef __configuration_H__
#define __configuration_H__

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void configurePin(GPIO_TypeDef* port, uint16_t pinNum, GPIOMode_TypeDef mode);
void configurationTIM1_Channel1(void);
#endif // __configuration_H__

