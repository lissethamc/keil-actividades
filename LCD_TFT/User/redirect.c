
/**
  ******************************************************************************
  * @file    Redirec.c 
  * @author  MC Jos� Miguel Mor�n Loza
  * @version V1.0.0
  * @date    13/02/2011
  * @brief   Redirecci�n de funciones de Bajo Nivel.
  ******************************************************************************
*/ 
#include <stdint.h>		//*
#include <stdio.h>
#include <rt_misc.h>
#include <rtl.h>
#include "stm32f429i_discovery_lcd.h" //*

#pragma import(__use_no_semihosting_swi)


extern int Enviar_Mensaje(char c);	//Env�a Mensaje al LCD
//int Enviar_Mensaje(char c);	//Env�a Mensaje al LCD

struct __FILE { int handle;};
FILE __stdout;


int fputc(int c, FILE *f) 
{
  return (Enviar_Mensaje(c));		//Env�a Mensaje al LCD
}


void _sys_exit(int return_code) 
{

  for(;;);

//label:  goto label;  /* endless loop */
}


