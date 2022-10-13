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
#include <stdio.h>

/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

GPIO_InitTypeDef	GPIO_InitStructure;	//Inicializaci�n de Terminales/Velocidad/Modo

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Delay(__IO uint32_t nCount);

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
	
	/*Inicializar el LCD*/
	LCD_Init();
	
	/*Configurar LCD: Condigurar 2 capas w/ Blending and CLUT cargado para capa 1*/
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	
	LTDC_LayerCmd(LTDC_Layer2, ENABLE); //ltdc controlador de display
	
	/*Recarga configuracion LTDC*/
	LTDC_ReloadConfig(LTDC_IMReload); //carga las caracteristicas mas comunes de configuracion pra activar el controlador
	
	/*Habilita el LCD*/
	LTDC_Cmd(ENABLE);
	
	/*Configuracion de LCD*/
	LCD_LayerInit();//inicializa la capa, la prepara para que reciba info
	
	/*Habilitacion del Display del LCD*/
	LCD_DisplayOn();
	
	/*Set foreground layer*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	
	LCD_Clear(LCD_COLOR_BLACK);
	
	LCD_SetBackColor(LCD_COLOR_BLACK);
	
	LCD_SetTextColor(LCD_COLOR_WHITE);
	
	LCD_SetFont(&Font12x12);
	
//	LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *)"ABCDEFGHIJ0123456789");
	
//	LCD_DrawRect(5,5,100,100);
	
	LCD_WriteData(2);
	
	
	
	
	
  while (1)
  {

  }
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
