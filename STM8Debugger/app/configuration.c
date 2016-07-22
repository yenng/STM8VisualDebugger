#include "configuration.h"

void configurePin(GPIO_TypeDef* port, uint16_t pinNum, GPIOMode_TypeDef mode)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  if (port == GPIOA)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //| RCC_APB2Periph_AFIO
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
  }
  else if (port == GPIOB)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, DISABLE);
  }
  else if (port == GPIOC)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);
  }
  else if (port == GPIOD)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, DISABLE);
  }
  else if (port == GPIOE)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, DISABLE);
  }
  else if (port == GPIOF)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, DISABLE);
  }
  else
  {
    if (port == GPIOG)
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); 
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, DISABLE);
    }
  }

  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = pinNum;
  GPIO_InitStructure.GPIO_Mode = mode;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(port, &GPIO_InitStructure);
}

void configurationTIM1_Channel1(void)
{
  /* TIM1, GPIOA, and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, DISABLE);
  
  //Channel_1 == SWIM_OUT_PIN
  configurePin(GPIOA, GPIO_Pin_8, GPIO_Mode_AF_OD);
}
