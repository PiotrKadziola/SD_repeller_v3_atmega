/*
 * Switch.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


/**********************************************************************************************/
/*						             ODCZYT PRZYCISKOW                                        */
/**********************************************************************************************/

#include "Switch.h"
#include "IOPort.h"
#include "Data.h"
#include "LED.h"
#include "Random.h"
#include "Random.h"
#include "wav.h"
#include "uart.h"
#include <stdlib.h>

/**********************************************************************************************/
/*						     DEFINICJA CZASU ZMIANY TRYBU PRZYCISKU                           */
/**********************************************************************************************/

#define PressedTime				2

/**********************************************************************************************/
/*                                GLOBALNA STRUKTURA KLAWISZY                                 */
/**********************************************************************************************/

struct SwitchStructure
{
  uint8_t Up;
  uint8_t Down;
  uint8_t Right;
  uint8_t Left;
  uint8_t Pressed;
  uint8_t Blocked;
}Switch;

/**********************************************************************************************/
/*						             SPRAWDZANIE PRZYCISKU                                    */
/**********************************************************************************************/

unsigned char CheckSwitch(void)
{
	uint8_t SwitchType = 0;
	uint8_t Time       = 0;
	char str[64];

	if(PIN_SW_Test == CLR || PIN_WiFi1 == CLR || PIN_WiFi2 == CLR || PIN_WiFi3 == CLR || PIN_WiFi4 == CLR)
	{
		if(PIN_SW_Test == CLR && PIN_WiFi1 == CLR && PIN_WiFi2 == CLR && PIN_WiFi3 == CLR && PIN_WiFi4 == CLR)
		{
			if(Switch.Pressed == 0x00)
			{
				while(Time < 10*PressedTime && PIN_SW_Test == CLR)
				{
					Time++;
					for(int i = 0; i< 2; i++)
						_delay_ms(10);
				}

				if(Time >= 10*PressedTime)
				{
					USART_String("\n\r T pressed");
					Switch.Pressed 	= 0x01;
					Switch.Blocked 	= 1;
					SwitchType 	   	= 'T';
					Time 			= 0;
				}
			}

			if(Switch.Pressed == 0x00)
			{
				USART_String("\n\r T");
				SwitchType = 'T';

				if(BlockFlag == 0)
				{
					if(Settings.BreakTime == Normal)													//normalnie
					{
						RGBLedFlag = LED_PLAY;
						Led();
						PlayMusic();														//wlaczenie wybranego utworu
						RGBLedFlag = LED_POWER_ON;
						BreakTime = Settings.BreakMinute*60 + Settings.BreakSecond;							//w sekundach
					}
					else if(Settings.BreakTime == Random)													//losowo
					{
						RGBLedFlag = LED_PLAY;
						Led();
						PlayMusic();														//wlaczenie wybranego utworu
						RGBLedFlag = LED_POWER_ON;
						BreakTime = ChooseRandom(Settings.BreakMinute*60 + Settings.BreakSecond);				//od 1 do SetBreakSecond
					}
				}
			}
		}

	}

	if(PIN_SW_Test == SET && PIN_WiFi1 == SET && PIN_WiFi2 == CLR && PIN_WiFi3 == CLR && PIN_WiFi4 == CLR)
	{
		if(Switch.Pressed == 0x00)
		{
			while(Time < 10*PressedTime && PIN_WiFi1 == SET)
			{

				Time++;
				for(int i = 0; i< 2; i++)
					_delay_ms(10);
			}

			if(Time >= 10*PressedTime)
			{
				USART_String("\n\r P Pressed");
				Switch.Pressed 	= 0x01;
				Switch.Blocked 	= 1;
				SwitchType 	   	= 'P';
				Time 			= 0;
			}
		}

		if(Switch.Pressed == 0x00)
		{
			USART_String("\n\r P");
			SwitchType = 'P';

			if(BlockFlag == 0)
			{
				if(Settings.BreakTime == Normal)													//normalnie
				{
					RGBLedFlag = LED_PLAY;
					Led();
					PlayMusic();														//wlaczenie wybranego utworu
					RGBLedFlag = LED_POWER_ON;
					BreakTime = Settings.BreakMinute*60 + Settings.BreakSecond;							//w sekundach
				}
				else if(Settings.BreakTime == Random)													//losowo
				{
					RGBLedFlag = LED_PLAY;
					Led();
					PlayMusic();														//wlaczenie wybranego utworu
					RGBLedFlag = LED_POWER_ON;
					BreakTime = ChooseRandom(Settings.BreakMinute*60 + Settings.BreakSecond);				//od 1 do SetBreakSecond
				}
			}
		}
	}

	if(PIN_SW_Test == SET && PIN_WiFi1 == CLR && PIN_WiFi2 == SET && PIN_WiFi3 == CLR && PIN_WiFi4 == CLR)
	{
		if(Switch.Pressed == 0x00)
		{
			while(Time < 10*PressedTime && PIN_WiFi2 == SET)
			{

				Time++;
				for(int i = 0; i< 2; i++)
					_delay_ms(10);
			}

			if(Time >= 10*PressedTime)
			{
				USART_String("\n\r L Pressed");
				Switch.Pressed 	= 0x01;
				Switch.Blocked 	= 1;
				SwitchType 	   	= 'L';
				Time 			= 0;
			}
		}

		if(Switch.Pressed == 0x00)
		{
			USART_String("\n\r L");
			SwitchType = 'L';

			if(BlockFlag == 0)
			{
				BlockFlag = 1;
			}
			else
			{
				BlockFlag = 0;
			}

			USART_String("\n\r BlockFlag = ");
			USART_String(itoa(BlockFlag, str, 10));
		}
	}

	if(PIN_SW_Test == SET && PIN_WiFi1 == CLR && PIN_WiFi2 == CLR && PIN_WiFi3 == SET && PIN_WiFi4 == CLR)
	{
		if(Switch.Pressed == 0x00)
		{
			while(Time < 10*PressedTime && PIN_WiFi3 == SET)
			{

				Time++;
				for(int i = 0; i< 2; i++)
					_delay_ms(10);
			}

			if(Time >= 10*PressedTime)
			{
				USART_String("\n\r + Pressed");
				Switch.Pressed 	= 0x01;
				Switch.Blocked 	= 1;
				SwitchType 	   	= '+';
				Time 			= 0;
			}
		}

		if(Switch.Pressed == 0x00)
		{
			USART_String("\n\r +");
			SwitchType = '+';

			if(Settings.Volume < 4)								//dorobic parametr maxvolume
			{
				Settings.Volume ++;
			}

			USART_String("\n\r Volume = ");
			USART_String(itoa(Settings.Volume, str, 10));
		}
	}

	if(PIN_SW_Test == SET && PIN_WiFi1 == CLR && PIN_WiFi2 == CLR && PIN_WiFi3 == CLR && PIN_WiFi4 == SET)
	{
		if(Switch.Pressed == 0x00)
		{
			while(Time < 10*PressedTime && PIN_WiFi4 == SET)
			{

				Time++;
				for(int i = 0; i< 2; i++)
					_delay_ms(10);
			}

			if(Time >= 10*PressedTime)
			{
				USART_String("\n\r - pressed");
				Switch.Pressed 	= 0x01;
				Switch.Blocked 	= 1;
				SwitchType 	   	= '-';
				Time 			= 0;
			}
		}

		if(Switch.Pressed == 0x00)
		{
			USART_String("\n\r -");
			SwitchType = '-';

			if(Settings.Volume > 1)								//dorobic parametr maxvolume
			{
				Settings.Volume --;
			}

			USART_String("\n\r Volume = ");
			USART_String(itoa(Settings.Volume, str, 10));
		}
	}

	Time           = 0;

	if(PIN_SW_Test == SET)
	{
		Switch.Pressed = 0;
	}

	return SwitchType;

}

