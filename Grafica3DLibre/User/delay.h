/**
  ******************************************************************************
  * @file    delay_ms.h 
  * @author  Lisseth Abigail Martinez Castillo
  * @version V1.0.0
  * @date    02-10-2022
  * @brief   Hardware delay
  ******************************************************************************

  */
#include "stm32f4xx.h"
void delay_ms(uint32_t dlyTicks);
void SysTickSet(void);
