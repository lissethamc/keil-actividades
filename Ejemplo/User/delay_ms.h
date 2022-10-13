/**
  ******************************************************************************
  * @file    delay_ms.h 
  * @author  Luis Carlos Reynoso López
  * @version V1.0.0
  * @date    29-09-2021
  * @brief   Hardware delay
  ******************************************************************************

  */
#include "stm32f4xx.h"
void delay_ms(uint32_t delayTicks);
void SysTickSet(void);
