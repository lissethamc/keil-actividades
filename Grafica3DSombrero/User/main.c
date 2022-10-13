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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "core_cm4.h"
#include "misc.h"
#include "delay.h"
/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

GPIO_InitTypeDef	GPIO_InitStructure;	//Inicialización de Terminales/Velocidad/Modo

/* Private define ------------------------------------------------------------*/
#define X0 10
#define Y0 10
#define NODES 20
#define SIDE 10
#define STEP 1 
#define PI 3.1416
#define HRES 240

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
typedef struct{
	int x;
	int y;
}point;

point edge[NODES], prev;
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
	//SysTickSet();
	
	int i, j, x, y, z;
	float xf, yf, zf, sf;
	int px, py;
	int xoff, scale;
	
	xoff = 100;
	scale = 2;
		
		LCD_DrawUniLine(X0, 10, X0, 10);
		LCD_DrawUniLine(X0-5, Y0, HRES-10, Y0);
		LCD_DrawUniLine(X0-2, Y0-2, X0+120, Y0+120);


		for(j=0; j<NODES; j++){ 
			edge[j].x = X0+j*SIDE/2;
			edge[j].y = Y0+j*SIDE/2;
		}

		for(i=0; i<NODES; i++){
			x = i*SIDE; 
			xf = (6*PI/200)*(float)(x-xoff); 
			prev.y = Y0;
			prev.x = X0 + x;

			for(j=0; j<NODES; j++){
				y = j*SIDE; 
				yf = (6*PI/200)*(float)(y-100); 

				//sf = sqrt(xf*xf+yf*yf); 
				//zf = 1/(1+sf)*cos(sf); 
				//zf=xf*xf-yf*yf; //scale 1 dividir entre escala
				
				//zf = sin(xf+yf); //escala 20 
				zf = xf*xf + xf*yf + yf*yf;
				zf = 1/2*x+y*cos(y);
				
				z = zf/scale; //scale=75

				
				px = X0 + x + y/2; 
				py = Y0 + z +y/2;

				//plot(px, py);
				LCD_DrawLine(py, px, 1, LCD_DIR_HORIZONTAL);
			
				
				LCD_DrawUniLine(py, px, prev.y, prev.x);
				LCD_DrawUniLine(py, px, edge[j].y, edge[j].x); 

				prev.x = px;
				prev.y = py;
				edge[j].x = px;	
				edge[j].y = py;
			}
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
