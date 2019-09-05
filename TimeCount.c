/*
 * TimeCount.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


#include "TimeCount.h"
#include "Data.h"
#include "Random.h"
#include "Led.h"
#include "wav.h"
#include "uart.h"
#include "IOPort.h"
#include <stdlib.h>


///////////////////////////////////////////////////////////////////////////////////////////////
void MeasureTime(void)
{
	char str[64];

	if(Settings.Sound == Normal || Settings.Sound == Random)			//count down time only if not from File !
	{
		if(Settings.TurnOff == None || (Settings.TurnOff == ForNight && NightFlag == DayNow) || (Settings.TurnOff == ForDay && NightFlag == NightNow))
		{
			if(LowPowerFlag == 0 && CardMountedFlag == Mounted && BlockFlag == 0)							//count down time
			{
				if(BreakTime > 0)
				{
					BreakTime --;
				}
				else																						//if time == 0
				{
					PlayMusic();																		//play proper music file

					if(Settings.BreakTime == Normal)													//if normal count
					{
						BreakTime = Settings.BreakMinute*60 + Settings.BreakSecond;							//set normal time again
					}
					else if(Settings.BreakTime == Random)													//if random count
					{
						BreakTime = ChooseRandom(Settings.BreakMinute*60 + Settings.BreakSecond);			//random time
					}
				}
			}
		}
		else
		{
			BreakTime = Settings.BreakMinute*60 + Settings.BreakSecond;									//po powrocie z nocnego
		}

		USART_String("\n\r BreakTime = ");
		USART_String(itoa(BreakTime, str, 10));
	}
	else if(Settings.Sound == FromFile)											//if time loaded from file
	{
		uint8_t Temp_DayOfWeek;
		uint8_t Temp_Hour;
		uint8_t Temp_Minute;

		RTCReciveTimeEnable();					//read time from RTC
		RTCSendReciveTime(1);

		RTCShowTime();							//show time from RTC

		//readRTC time if seconds == 0 (only once at beginning of every minute)

		if(Time.ActualSecond == 0)
		{
			LoadOnTimesFile();					//read every line of file ontimes.txt and compare with RTC
		}



	}
}
