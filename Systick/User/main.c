/**
  ******************************************************************************
  * @file    main.c 
  * @author  MC Jos� Miguel Mor�n Loza
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main program body
  ******************************************************************************

  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"	//Archivo encabezado para el acceso a los 
												//dispositivos Perif�ricos del CMSIS Cortex-M4
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "core_cm4.h"
#include "misc.h"

/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

GPIO_InitTypeDef	GPIO_InitStructure;	//Inicializaci�n de Terminales/Velocidad/Modo

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern volatile uint32_t msTicks;
/* Private function prototypes -----------------------------------------------*/

void Delay(__IO uint32_t nCount);
void delay_ms(uint32_t dlyTicks);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< 	En este punto los ajustes del reloj del microcontrolador est�n 
				configurados, a trav�s de la funci�n SystemInit() la cual se llama
				desde el archivo startup (startup_stm32f429_439xx.s) antes de saltar
				a la aplicaci�n principal.
				Para reconfigurar los ajustes predeterminados de la funci�n SystemInit,
				refierase al documento system_stm32f4xx.c
  */  
  
  /* Agregue el c�digo de su aplicaci�n aqu� */
	
	  /* Habilitaci�n de reloj del perif�rico GPIOG */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	/* Habilitaci�n de reloj del perif�rico GPIOB */
	

  /* Configurar PG13 y PG14 como Push Pull*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	SystemCoreClockUpdate();
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); 
	SysTick_Config(16000-1);
	
	if(SysTick_Config(SystemCoreClock/2000)){
		while(1);
	}
	
  while (1)
  {
		
		GPIOG->BSRRL=GPIO_Pin_13;	//LED Verde On
		
		delay_ms(800);

		GPIOG->BSRRH=GPIO_Pin_13; //LED Verde Off
		
		delay_ms(300);
		
  }
}
  

void delay_ms(uint32_t dlyTicks){
	uint32_t curTicks;
	curTicks = msTicks;
	while((msTicks-curTicks)<dlyTicks);
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reportar del nombre del archivo fuente y el n�mero de l�nea
  *			donde se "declara o mantiene" alg�n par�metro con error.
  * @param  file: Apunta al nombre del archivo fuente
  * @param  line: N�mero de l�ne que contiene el error.
  * @retval Ninguno
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* El usuario podr� agregar su propia implementaci�n para reportar el nombre
  	 del archivo y el n�mero de l�nea,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) 
	*/

  /* lazo infinito */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT 2011 Moran Technologies *****END OF FILE****/
