/*
 * main.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


/*
 * main.c			F_CPU = 20MHz
 *
 */

//#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <string.h>
#include <stdlib.h>

#include "Type.h"
#include "Data.h"
#include "Timer.h"
#include "Switch.h"
#include "Led.h"
#include "TimeCount.h"
#include "ADC.h"
#include "LightMeasure.h"
#include "MoveSensor.h"
#include "wav.h"
#include "IOPort.h"
#include "SDTimes.h"
#include "uart.h"
#include "DS1340.h"


int main(void)
{
	InitSPI();
	InitPort();							//inicjalizacja portów
	InitTimer0();						//audio
	InitTimer1();						//audio
	InitTimer2();						//count
	InitADC();							//inicjalizacja ADC
	ADCChannel(0);						//wybór kana³u ADC
	ADCStart();
	USART_Init();

	I2CConfig();

	sei();								// globalne zezwolenie na przerwania

	LowPowerFlag = 0;
	BlockFlag = 0;						//domyslnie sterownik odblokowany
	MosfetLedFlag = 0;
	CardMountedFlag = NotMounted;		//at start SD card must be mounted
	RGBLedFlag = LED_NO_SDCARD;			//LEDFlag -> no sd card
	Led();								//set proper LED

	_delay_ms(500);					//wait one second

	while(1)
	{
		CheckSwitch();					//Odczytaj stan przyciskow

		if(Timer2Flag_ADC == 1)						//50 ms
		{
			Led();									//sterowanie ledami

//			MoveSensorCheck();
			TurnOnLedMosfet();						//blibking mosfet LED
			MeasureLight();

			Timer2Flag_ADC = 0;
		}

		if(Timer2Flag_COUNT == 1)					//1s - odliczanie
		{
			CheckCardMount();						//check pin card detect and mount the SD card
			MeasureTime();							//BreakTime odliczanie -> do w³¹czenia dŸwiêku, lub odczyt z pliku

			Timer2Flag_COUNT = 0;
		}
	}

	return 0;

}
