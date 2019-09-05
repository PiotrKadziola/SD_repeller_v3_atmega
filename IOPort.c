/*
 * IOPort.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


/**********************************************************************************************/
/*							         DEFINICJA WEJSC I WYJSC                                  */
/**********************************************************************************************/

#include "IOPort.h"

/**********************************************************************************************/
/*							        USTAWIENIE KIERUNKU POTROW                                */
/**********************************************************************************************/

void PINDirection(void)
{
	DIR_SD_CD		= 	IN;
	DIR_LED_Green	=	OUT;
	DIR_LED_Red		=	OUT;
	DIR_LED_Blue	=	OUT;
	DIR_LED_Mosfet	=	OUT;
	DIR_SW_Test		=	IN;
	DIR_Relay		=	OUT;
	DIR_Standby		=	OUT;
	DIR_Mute		=	OUT;
	DIR_WiFi1		=	IN;
	DIR_WiFi2		=	IN;
	DIR_WiFi3		=	IN;
	DIR_WiFi4		=	IN;
	DIR_Move		=	IN;
}

/**********************************************************************************************/
/*							         USTAWIENIE STANU PORTOW                                  */
/**********************************************************************************************/

void PINState(void)
{

	PIN_LED_Green	= 	CLR;
	PIN_LED_Red		= 	CLR;
	PIN_LED_Blue	= 	CLR;
	PIN_WiFi1		=	CLR;			//rezystor do masy - podci¹gniêcie
	PIN_WiFi2		=	CLR;
	PIN_WiFi3		=	CLR;
	PIN_WiFi4		=	CLR;
}

/**********************************************************************************************/
/*							        USTAWIENIE PODCIAGANIA PORTOW                             */
/**********************************************************************************************/

void UPResistanse(void)
{

	UP_SD_CD		= 	OFF;
	UP_SD_CS		= 	ON;
	UP_MOSI			=	ON;
	UP_MISO			=	ON;
	UP_SCK			=	ON;
	UP_LED_Green	=	ON;
	UP_LED_Red		=	ON;
	UP_LED_Blue		=	ON;
	UP_LED_Mosfet	= 	ON;				//turn off at start !!
	UP_Relay		=	ON;
	UP_Standby		=	OFF;
	UP_Mute			=	OFF;
	UP_SW_Test		= 	OFF;
	UP_Move			=	OFF;
}

/**********************************************************************************************/
/*							            KONFIGURACJA PORTOW                                   */
/**********************************************************************************************/

void InitPort(void)
{
	PINDirection();
	UPResistanse();
	PINState();
}
