/*
 * LEDMosfet.c
 *
 *  Created on: 24-09-2015
 *      Author: DESAR
 */

#include "LEDMosfet.h"
#include "IOPort.h"
#include "Data.h"

void TurnOnLedMosfet(void)
{
	if(MosfetLedFlag == 1)
	{
		if(PIN_LED_Mosfet == 1)			//Blink LED
		{
			UP_LED_Mosfet = 0;
		}
		else
		{
			UP_LED_Mosfet = 1;
		}
	}
	else
	{
		UP_LED_Mosfet = 0;				//turn off LED
	}
}
