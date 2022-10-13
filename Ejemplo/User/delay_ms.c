/**
  ******************************************************************************
  * @file    delay_ms.c 
  * @author  Luis Carlos Reynoso López
  * @version V1.0.0
  * @date    29-09-2021
  * @brief   Hardware delay
  ******************************************************************************

  */
#include "stm32f4xx.h"
extern volatile uint32_t msTicks;
void delay_ms(uint32_t delayTicks)
{
	uint32_t curTicks;
	curTicks = msTicks;
	int ADJ = 2.33*delayTicks/100;
	while ((msTicks - curTicks) < delayTicks + ADJ);
}

void SysTickSet(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SystemCoreClockUpdate();
	if(SysTick_Config(SystemCoreClock / 3200))
	{
		while(1);
	}
}
