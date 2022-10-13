#include "LCD_TFT.h"
#include <stdint.h>		//*
#include <stdio.h>
#include <rt_misc.h>
#include <rtl.h>
#include "stm32f429i_discovery_lcd.h" //*


/* Impresión de los caracteres del LCD */

	uint8_t LCD_String[20]= {0,0,0}; //{"ABCDEFGHIJ012345678"};		//Texto que aparecerá en el LCD

	uint8_t i;
	uint8_t Linea;

int Enviar_Mensaje(char c)
{
	//Envía Mensaje usando printf	

	while (c!='\n')
	{
		
		LCD_String[i]=c;
		i++;
		
    	return 0;
	}
	
		/* Impresión de los caracteres del LCD */
	//LCD_GLASS_DisplayString(LCD_String);
	//LCD_DisplayStringLine(uint16_t Line, uint8_t *ptr)
	
	if (Linea==26)	//FONT 12x12
		{
			Linea=0;
		}
	LCD_DisplayStringLine(LINE(Linea), LCD_String);
		
	for (i=0;i!=20;i++)		//Limpiar Arreglo despúes
		{										//de imprimir texto
		LCD_String[i]=' ';
		}	
		
		Linea++;
		

	//LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c);
	//LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii);
	i=0;
	return 0;
	
}
