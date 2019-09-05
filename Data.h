/*
 * Data.h
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

#ifndef DATA_H_
#define DATA_H_

/**********************************************************************************************/
/*							             USTAWIENIA                                           */
/**********************************************************************************************/

#include <avr/io.h>
#include "Type.h"

/**********************************************************************************************/
/*							                DEFINICJE                                         */
/**********************************************************************************************/

#define None 		0			//TurnOff
#define ForNight   	1
#define ForDay		2

#define Normal		0
#define Random		1
#define FromFile	2

#define Off			0
#define	WithSound	2

#define DayNow		1
#define NightNow	0

#define Mounted 	1
#define NotMounted	0

#define Szpak		0
#define Dzik		1

/**********************************************************************************************/
/*							             STRUKTURA USTAWIEN                                   */
/**********************************************************************************************/

struct CONF
{
	char 		Folder[10];				//Szpak / Dzik
	uint8_t 	LowPower;				//70 (7V) do 140 (14V)
	uint8_t 	Volume;					//1 do 10
	uint8_t 	TurnOff;				//0 - None, 1 - Night_Off, 2 - Day_off
	uint8_t 	BreakMinute;			//0 do 60
	uint8_t		BreakSecond;			//0 do 60
	uint8_t		Sound;					//0 - Normal, 1 - Random, 2 - FromFile
	uint8_t		BreakTime;				//0 - Normal, 1 - Random
	uint8_t		Relay;					//0 - Off, 1 - Random, 2 - WithSound
//	uint8_t		RelayTime;				//1 do 30
	uint8_t		Led;					//0 - Off, 1 - Random, 2 - WithSound
//	uint8_t		LedTime;				//1 do 30
}Settings;

/**********************************************************************************************/
/*							                  RTC		     	                             */
/**********************************************************************************************/

struct RTC
{
	BYTE ActualSecond;
	BYTE ActualMinute;
	BYTE ActualHour;
	BYTE ActualDayOfWeek;

	BYTE SaveSecond;
	BYTE SaveMinute;
	BYTE SaveHour;
	BYTE SaveDayOfWeek;
}Time;

/**********************************************************************************************/
/*							             ZMIENNE GLOBALNE                                     */
/**********************************************************************************************/

BYTE Timer2Flag_ADC;			//co 50ms - czujniki
BYTE Timer2Flag_COUNT;			//co 1s - odliczanie
BYTE MoveSensorFlag;			//1- wykryto ruch
BYTE LowPowerFlag;				//1- za niskie zasilanie
BYTE Times;						//licznik ile zapisano czasów w pliku
WORD BreakTime; 				//czas przerwy
BYTE RGBLedFlag;				//kontrola zachowania diod LED
BYTE MosfetLedFlag;				//kontrola zachowania stroboskopu LED na mosfecie -> 1 - w³¹czony, 0 - wy³aczony
BYTE RelayFlag;					//jesli 1 relay w³¹czony
BYTE NightFlag;					//jesli 1 to wykryto noc, 0 to dzieñ
BYTE ADCFlag;					//czy ju¿ pobrano dane z czujnika - przerwanie
BYTE CardMountedFlag;			//jesli 0 to nie ma karty
uint8_t ActualSongCount;				//policzonych utworów w wybranym folderze
BYTE BlockFlag;					//jesli 1 nie dziala nic


#endif /* DATA_H_ */
