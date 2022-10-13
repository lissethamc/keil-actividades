#include "stm32f4xx.h"

extern volatile uint32_t msTicks;
void delay_ms(uint32_t delayTicks)
{
	uint32_t curTicks;
	curTicks = msTicks;
	while ((msTicks - curTicks) < delayTicks);
}

void SysTickSet(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SystemCoreClockUpdate();
	if(SysTick_Config(SystemCoreClock / 8000))
	{
		while(1);
	}
}
