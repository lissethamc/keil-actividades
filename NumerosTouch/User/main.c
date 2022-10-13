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
#define YOFFSET	55 //los valores de offset son para mover todo el teclado en conjunto											
#define XOFFSET 7
#define VALX 36
#define VALY 52
#define RADIO 25


/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef	GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
void displayConfig();
void clearCharArray();
void drawButtons(); 
int isInsideCircle(int posX, int posY);
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t cad[16];
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
	clearCharArray();
	
	
	while(IOE_Config() != IOE_OK)
	{
		LCD_Clear(LCD_COLOR_RED);
		LCD_SetTextColor(LCD_COLOR_WHITE);
		LCD_DisplayStringLine(LCD_LINE_6, (uint8_t*)" IOE NO ESTA BIEN");
		LCD_DisplayStringLine(LCD_LINE_7, (uint8_t*)"REINICIE LA TARJETA");
		LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)"E INTENTE DE NUEVO");
	}
	LCD_SetFont(&Font16x24);
	drawButtons();
	
	/*LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	
	Linea = 1;
	for (int i=0;i<16;i++){
		printf("%c", cad[i]);
	}*/
	

	while(1){
		TP_State = IOE_TP_GetState();
		TP_State-> Y = 320 - TP_State-> Y;
		LCD_SetFont(&Font12x12);
		Linea = 0;
		LCD_SetTextColor(LCD_COLOR_WHITE);
		printf("Y: %d  X: %d \n",TP_State->Y, TP_State->X);
		
		
		//if(TP_State->TouchDetected)&&(isInsideCicle(x,y)) //retorna 1 si si o 0 sino, si igual es entero, es conveniente que me retorne un valor de acuerdo con el numero presionado? 
		if(TP_State->TouchDetected){
		LCD_SetFont(&Font16x24);
		Linea = 2;
		LCD_SetTextColor(LCD_COLOR_WHITE);
		printf("%d\n",isInsideCircle(TP_State->X,TP_State->Y));
			
/*			switch(isInsideCircle(TP_State->X,TP_State->Y)){
				case -1:
					GPIOG->BSRRH = GPIO_Pin_13;
					GPIOG->BSRRL = GPIO_Pin_14;
					break;
				case 0:
					GPIOG->BSRRL = GPIO_Pin_13;
					GPIOG->BSRRH = GPIO_Pin_14;
					break;
				case 1:
					GPIOG->BSRRL = GPIO_Pin_13;
					GPIOG->BSRRH = GPIO_Pin_14;
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;*/
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

void clearCharArray(){
	for (int i=0;i<15;i++){
		cad[i]=' ';
	}
	cad[15]='\n';
}

void drawButtons(){
	LCD_SetTextColor(LCD_COLOR_WHITE);
	extern uint8_t Linea;
	Linea = 4;
	printf("  1    2    3\n");
	
	LCD_DrawCircle(VALX+XOFFSET,VALY+YOFFSET,RADIO);
	LCD_DrawCircle(VALX+77+XOFFSET,VALY+YOFFSET,RADIO);
	LCD_DrawCircle(VALX+154+XOFFSET,VALY+YOFFSET,RADIO);
	
	Linea = 7;
	printf("  4    5    6\n");
	LCD_DrawCircle(VALX+XOFFSET,VALY+61+YOFFSET,RADIO);
	LCD_DrawCircle(VALX+77+XOFFSET,VALY+61+YOFFSET,RADIO);
	LCD_DrawCircle(VALX+154+XOFFSET,VALY+61+YOFFSET,RADIO);
	
	Linea = 9;
	printf("  7    8    9\n");;
	LCD_DrawCircle(VALX+XOFFSET,VALY+122+YOFFSET,RADIO);
	LCD_DrawCircle(VALX+77+XOFFSET,VALY+122+YOFFSET,RADIO);
	LCD_DrawCircle(VALX+154+XOFFSET,VALY+122+YOFFSET,RADIO);
	
	Linea = 12 ;
	printf("       0    \n");
	LCD_DrawCircle(113+XOFFSET,235+YOFFSET,25); //x, y, radio1,  radio2
}

int isInsideCircle(int posX, int posY){ // retorna valor del 0-9 si fue presionado un boton, que les corresponda, retorna -1 sino
	int distance;
	int count=1;
	
	distance = sqrt((posX-120)*(posX-120)+(posY-290)*(posY-290)); //boton digito 0
	/*if(distance <= 25){//25 es el valor de los radios
		return 0;
	}*/
	for(int j=VALY+OFFSET;j<=VALY+122+YOFFSET;j=j+61){ // y = filas diferencia en radios en y es de 61
			for(int i=VALX+XOFFSET;i<=VALX+154+XOFFSET;i=i+77){ //x =columnas  diferencia en radios en x es de 77
					distance = sqrt((posX-i)*(posX-i)+(posY-j)*(posY-j));
					if(distance <= 25){//25 es el valor de los radios
						return count;
					}
					else{
						count++;
					}
			}
	}
	return -1;
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
