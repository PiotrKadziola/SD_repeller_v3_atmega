/*
 * LightMeasure.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


/**********************************************************************************************/
/*							     POMIAR NATEZENIA SWIATLA                                     */
/**********************************************************************************************/

#include "LightMeasure.h"
#include "Data.h"
#include "IOPort.h"
#include "ADC.h"

/**********************************************************************************************/
/*							       MIERZY NATERZENIE SWIATLA           		                  */
/**********************************************************************************************/

void MeasureLight(void)
{

		   WORD Brightness = 0;
	static DWORD Average = 0;
	static BYTE Counter = 0;

	if(ADCFlag == 1 && LowPowerFlag == 0)
	{
		Brightness = ADCValue();
		Average += Brightness;
		Brightness = 0;

		if(Counter >= 10)
		{
			Average = Average / Counter;

			if(Average > 980)
			{
				NightFlag = NightNow;				//noc
			}

			if(Average < 850)
			{
				NightFlag = DayNow;					//dzien
			}

			Average = 0;
			Counter = 0;


		}

		ADCFlag = 0;
		Counter++;
		ADCStart();
	}

}
