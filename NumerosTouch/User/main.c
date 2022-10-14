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
#include "stm32f4xx.h"	
#define RADIO 25
#define OFFSETX 77 //desplazamiento entre radios para x para los botones
#define OFFSETY 61 //desplazamiento entre radios para y para los botones
#define FIRSTX 43 //coordenada x para el primer circulo 
#define FIRSTY 107 // coordenada y para el primer circulo 
#define LASTX 197 //coordenada en x para el ultimo circulo
#define LASTY 229 //cordenada en y para el ultimo circulo

/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef	GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
void displayConfig();
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void drawCircles();


/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	extern uint8_t Linea;
	static TP_STATE* TP_State;
	SysTickSet();
	displayConfig();
	
	
	while(IOE_Config() != IOE_OK)
	{
		LCD_Clear(LCD_COLOR_RED);
		LCD_SetTextColor(LCD_COLOR_WHITE);
		LCD_DisplayStringLine(LCD_LINE_6, (uint8_t*)" IOE NO ESTA BIEN");
		LCD_DisplayStringLine(LCD_LINE_7, (uint8_t*)"REINICIE LA TARJETA");
		LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)"E INTENTE DE NUEVO");
	}
	LCD_SetFont(&Font16x24);
	
	
	drawCircles();
	

	while(1){
		TP_State = IOE_TP_GetState();
		TP_State-> Y = 320 - TP_State-> Y;
		LCD_SetFont(&Font12x12);
		Linea = 0;
		LCD_SetTextColor(LCD_COLOR_WHITE);
		printf("Y: %d  X: %d \n",TP_State->Y, TP_State->X);
		
		if(TP_State->TouchDetected){
		LCD_SetFont(&Font16x24);
		Linea = 2;
		LCD_SetTextColor(LCD_COLOR_WHITE);
			
			}
		}
		
	}    

void displayConfig(){
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
}

void drawCircles(){
	LCD_SetTextColor(LCD_COLOR_WHITE);
	extern uint8_t Linea;
	uint8_t counter = 1;
	
	Linea = 4;
	for (int j=FIRSTY; j<=LASTY;j+=OFFSETY){
		Linea=(counter==7)?9:counter+3;
		printf("  %d    %d    %d\n",counter, counter+1, counter+2);
		for(int i=FIRSTX; i<=LASTX; i+=OFFSETX){
			LCD_DrawCircle(i,j,RADIO);
		}
		counter+=3;
	}
	Linea = 12 ;
	printf("       0    \n");
	LCD_DrawCircle(FIRSTX+OFFSETX,FIRSTY+OFFSETY*3,RADIO); 
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
