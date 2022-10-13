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



/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

GPIO_InitTypeDef	GPIO_InitStructure;	//Inicialización de Terminales/Velocidad/Modo

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
	SysTickSet();
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

	extern uint8_t Linea;
	static TP_STATE* TP_State;
	LCD_Init();
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);
	LTDC_ReloadConfig(LTDC_IMReload);
	LTDC_Cmd(ENABLE);
	
	LCD_LayerInit();
	LCD_DisplayOn();
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	LCD_SetBackColor(LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_Clear(LCD_COLOR_BLACK);
	
	while(IOE_Config() != IOE_OK)
	{
		LCD_Clear(LCD_COLOR_RED);
		LCD_SetTextColor(LCD_COLOR_WHITE);
		LCD_DisplayStringLine(LCD_LINE_6, (uint8_t*)" IOE NO ESTA BIEN");
		LCD_DisplayStringLine(LCD_LINE_7, (uint8_t*)"REINICIE LA TARJETA");
		LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)"E INTENTE DE NUEVO");
	}
	
	LCD_SetFont(&Font12x12);

	LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	
	Linea = 17;
	printf("      LED ROJO    \n");
	LCD_DrawRect(20, 180, 55, 200);
	
	Linea = 23;
	printf("      LED VERDE    \n");
	LCD_DrawRect(20, 255, 55, 200);

	while(1)
	{
		TP_State = IOE_TP_GetState();
		// TP_State->Y=TP_State->Y-320;
		TP_State-> Y = 320 - TP_State-> Y;
		Linea = 0;
		LCD_SetTextColor(LCD_COLOR_WHITE);
		printf("Y: %d  X: %d \n",TP_State->Y, TP_State->X);
		
		if((TP_State -> TouchDetected) && (TP_State ->Y <= 310) && (TP_State->Y >= 255) && (TP_State ->X >= 20) && (TP_State->X <= 220))
		{
			//enciende led verde
			GPIOG->BSRRL = GPIO_Pin_13;
			GPIOG->BSRRH = GPIO_Pin_14;
			
			LCD_SetTextColor(LCD_COLOR_GREEN);
			Linea = 23;
			printf("      LED VERDE    \n");
			LCD_SetTextColor(LCD_COLOR_WHITE);
			LCD_DrawRect(20, 255, 55, 200);
			
			Linea = 17;
			printf("      LED ROJO    \n");
			LCD_DrawRect(20, 180, 55, 200);
		}	
		
		if((TP_State -> TouchDetected) && (TP_State ->Y <= 235) && (TP_State->Y >= 180) && (TP_State ->X >= 20) && (TP_State->X <= 220))
		{
			//enciende led rojo
			GPIOG->BSRRH = GPIO_Pin_13;
			GPIOG->BSRRL = GPIO_Pin_14;
			
			LCD_SetTextColor(LCD_COLOR_RED);
			Linea = 17;
			printf("      LED ROJO    \n");
			LCD_SetTextColor(LCD_COLOR_WHITE);
			LCD_DrawRect(20, 180, 55, 200);
			
			Linea = 23;
			printf("      LED VERDE    \n");
			LCD_DrawRect(20, 255, 55, 200);
		}
	}
	
	
} //Fin de main()
    



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
