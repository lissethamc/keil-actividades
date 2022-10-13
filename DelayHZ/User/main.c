/**
  ******************************************************************************
  * @file    main.c 
  * @author  MC José Miguel Morán Loza
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main program body
  ******************************************************************************

  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"	//Archivo encabezado para el acceso a los 
												//dispositivos Periféricos del CMSIS Cortex-M4
#include "delay_ms.h"
#include <math.h>
#include "stm32f429i_discovery_lcd.h"

#define PI 3.1415
#define X0 10
#define Y0 120

/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

GPIO_InitTypeDef	GPIO_InitStructure;	//Inicialización de Terminales/Velocidad/Modo

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DrawRandLines();
void DrawSinWave();



/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< 	En este punto los ajustes del reloj del microcontrolador están 
				configurados, a través de la función SystemInit() la cual se llama
				desde el archivo startup (startup_stm32f429_439xx.s) antes de saltar
				a la aplicación principal.
				Para reconfigurar los ajustes predeterminados de la función SystemInit,
				refierase al documento system_stm32f4xx.c
  */  
  
  /* Agregue el código de su aplicación aquí */
	
	  /* Habilitación de reloj del periférico GPIOG */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	 

  /* Configurar PG13 y PG14 como Push Pull*/
	
	LCD_Init();
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);
	LTDC_ReloadConfig(LTDC_IMReload);
	LTDC_Cmd(ENABLE);
	
	LCD_LayerInit();
	LCD_DisplayOn();
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetBackColor(LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12x12);
	
	//LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *) "ABCDEFGHIJ0123456789");
	//LCD_DisplayStringLine(LCD_LINE_2, (uint8_t *) "abcdefghij0123456789");
	//LCD_DisplayStringLine(LCD_LINE_3, (uint8_t *) " El CARLOS ");
	//LCD_DrawRect(100, 50, 100, 100);
	

	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	SysTickSet();
	RNG_Cmd(ENABLE);
	//DrawRandLines();
	DrawSinWave();
	
	
} //Fin de main()
    
void DrawRandLines()
{
	LCD_DrawLine(0, 0, 319,LCD_DIR_VERTICAL);
	LCD_DrawLine(238, 0, 319, LCD_DIR_VERTICAL);
	LCD_DrawLine(238, 318, 239, LCD_DIR_HORIZONTAL);
	LCD_DrawLine(0, 0, 239, LCD_DIR_HORIZONTAL);
	
	for(int i = 0; i < 100; i++)
	{
		RNG_GetFlagStatus(1);
		LCD_DrawUniLine(RNG_GetRandomNumber()%239,RNG_GetRandomNumber()%319,RNG_GetRandomNumber()%239,RNG_GetRandomNumber()%319);
		RNG_GetFlagStatus(0);
		delay_ms(100);
	}
}	

void DrawSinWave()
{
	int16_t x;
	float xf, yf;
	LCD_DrawLine(120, 0, 319,LCD_DIR_VERTICAL);
	LCD_DrawLine(0, 0, 239, LCD_DIR_HORIZONTAL);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	for(x = 0; x < 300; x++)
	{
		xf = (2 *  PI / 50) * (float)x;
		yf = 75.0 / (8 * PI) * xf * sin(xf);
		LCD_DrawLine(yf + Y0, x + X0, 1, LCD_DIR_HORIZONTAL);
		delay_ms(100);
	}
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reportar del nombre del archivo fuente y el número de línea
  *			donde se "declara o mantiene" algún parámetro con error.
  * @param  file: Apunta al nombre del archivo fuente
  * @param  line: Número de líne que contiene el error.
  * @retval Ninguno
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* El usuario podrá agregar su propia implementación para reportar el nombre
  	 del archivo y el número de línea,
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
