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
#include <math.h> 			//dispositivos Perif�ricos del CMSIS Cortex-M4
												
#define PI 3.1416
#define YOFFSET 120
#define VRES 318
#define HRES 238


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
	
	float x,y;
	
	displayConfig();
	LCD_DrawLine(0,0,HRES,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(YOFFSET,0,VRES,LCD_DIR_VERTICAL);
	
	for (int i=0;i<280;i++){
		x =(2*PI/70) * (float)i; 
		y=4*x*sin(x);
		LCD_DrawLine(y+YOFFSET,i,1,LCD_DIR_HORIZONTAL);
	} 
}

void displayConfig(){
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
	LCD_SetFont(&Font12x12);
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
