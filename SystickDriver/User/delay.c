/**
  ******************************************************************************
  * @file    delay.c 
  * @author  Lisseth Abigail Martinez Castillo
  * @version V1.0.0
  * @date    02-10-2022
  * @brief   Hardware delay
  ******************************************************************************

  */
#include "delay.h"
extern volatile uint32_t msTicks;

void delay_ms(uint32_t dlyTicks)
{
	uint32_t curTicks;
	curTicks = msTicks;
	while((msTicks-curTicks)<dlyTicks);
}

void SysTickSet(void)
{

	SystemCoreClockUpdate();
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); 
	SysTick_Config(16000-1);
	
	if(SysTick_Config(SystemCoreClock/1000)){
		while(1);
	}
}
