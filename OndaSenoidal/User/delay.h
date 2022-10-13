/**
  ******************************************************************************
  * @file    delay.h 
  * @author  Lisseth Abigail Martinez Castillo
  * @version V1.0.0
  * @date    02-10-2022
  * @brief   Hardware delay
  ******************************************************************************

  */
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "misc.h"
void delay_ms(uint32_t dlyTicks);
void SysTickSet(void);
