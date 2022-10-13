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

/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef	GPIO_InitStructure;
/* Private define ------------------------------------------------------------*/
#define VRES 318
#define HRES 238
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern uint8_t Linea;


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{

	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	 

  /* Configurar PG13 y PG14 como Push Pull*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	// Inicializar el lcd
	LCD_Init();
	
	// Habilitar capa 1
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	
	/* Habilitar capa 2 */
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);
	
	/* Recarga de configuraci�n LTDC */
	LTDC_ReloadConfig(LTDC_IMReload);
	
	/* Habilitar el LCD */
	LTDC_Cmd(ENABLE);
	
	/* Configuraci�n de LCD */
	LCD_LayerInit();
	/* Habilitaci�n del Display del LCD */
	LCD_DisplayOn();
	/* Set foreground layer */
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	/* Clear the LCD */
	LCD_Clear(LCD_COLOR_BLACK);
	/* Set the LCD Back Color */
	LCD_SetBackColor(LCD_COLOR_BLACK);
	/* Set the LCD text color */
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12x12);
	
	LCD_Clear(LCD_COLOR_BLACK);
	SysTickSet();
	while(1){
		
		for(int i=0;i!=9999;i++){
			GPIOG->BSRRL=GPIO_Pin_13;
			Linea = 10;
			printf("      Conteo: %d    \n",i);
			delay_ms(200);
			GPIOG->BSRRH=GPIO_Pin_13;
			delay_ms(200);
	
		
		}
	}
	
	

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
