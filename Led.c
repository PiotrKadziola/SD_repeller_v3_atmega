/*
 * Led.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

/**********************************************************************************************/
/*							          GENEROWANIE DZWIEKU                                     */
/**********************************************************************************************/

#include <avr\io.h>
#include "Led.h"
#include "Data.h"
#include "IOPort.h"

/**********************************************************************************************/
/*							              DEFINICJE CZASU                                     */
/**********************************************************************************************/

//#define AlarmTime		500

/**********************************************************************************************/
/*							            GENEROWANIE DZWIEKOW                                  */
/**********************************************************************************************/

void Led(void)
{
	static BYTE counter = 0;

	switch(RGBLedFlag)										//wlacza sie co 50 ms
	{
		case LED_OFF:
			UP_LED_Red 		= OFF;
			UP_LED_Green 	= OFF;
			UP_LED_Blue 	= OFF;
			break;

		case LED_POWER_ON:
			UP_LED_Red 		= OFF;
			UP_LED_Green 	= ON;
			UP_LED_Blue 	= OFF;
			break;

		case LED_PLAY:
			UP_LED_Red 		= ON;
			UP_LED_Green 	= OFF;
			UP_LED_Blue 	= OFF;
			break;

		case LED_NO_SDCARD:									//miga niebieska 200ms
			UP_LED_Red 		= OFF;
			UP_LED_Green 	= OFF;

			if(counter >= 4)								//jesli przekroczono 200 ms
			{
				if(PIN_LED_Blue == OFF)						//miganie ledem
				{
					UP_LED_Blue 	= ON;
				}
				else
				{
					UP_LED_Blue 	= OFF;
				}

				counter = 0;
			}
			break;
	}

	if(counter >= 255)
	{
		counter = 0;
	}
	counter++;
}

