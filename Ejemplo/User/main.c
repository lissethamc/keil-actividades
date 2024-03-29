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

#include <stdint.h>
#include <stdio.h>
#include "delay_ms.h"
#include "LCD_TFT.h"
#include "RTL.h"

/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

GPIO_InitTypeDef	GPIO_InitStructure;	//Inicializaci�n de Terminales/Velocidad/Modo

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


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
	SysTickSet();

	extern uint8_t Linea;
	
	LCD_Init();
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	LTDC_ReloadConfig(LTDC_IMReload);
	LTDC_Cmd(ENABLE);
	
	LCD_LayerInit();
	LCD_DisplayOn();
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetBackColor(LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	//LCD_SetFont(&Font12x12);
	//LCD_SetFont(&Font12x12);

	//LCD_DrawCircle(10,10,10);
	delay_ms(3000);

	while(1)
	{
		for(int j = 0; j!=9999; j++)
		{
			Linea=0;
			printf("Conteo: %d\n",j);
			delay_ms(1000);
		}
		
	}
	
	
} //Fin de main()
    



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
