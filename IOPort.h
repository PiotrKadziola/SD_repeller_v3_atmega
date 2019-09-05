/*
 * IOPort.h
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

#ifndef IOPORT_H_
#define IOPORT_H_

/**********************************************************************************************/
/*							         DEFINICJA WEJSC I WYJSC                                  */
/**********************************************************************************************/


#include "Type.h"
#include <avr/io.h>

/**********************************************************************************************/
/*                                 DEFINICJA BITOW PORTU A                                    */
/**********************************************************************************************/

typedef struct bit_struct_A
{
	BYTE 					:		1;		//Light Sensor
	BYTE 	 				:		1;		//Vcc Measure
	BYTE		 			:		1;
	BYTE SW_Test			:		1;
	BYTE IO_Standby			:		1;
	BYTE IO_Mute			:		1;
	BYTE 					:		1;
	BYTE 			 		:		1;
}bitA;


/**********************************************************************************************/
/*                                 DEFINICJA BITOW PORTU B                                    */
/**********************************************************************************************/

typedef struct bit_struct_B
{
	BYTE 					:		1;
	BYTE IO_LED_Mosfet 		:		1;
	BYTE IO_Move	 		:		1;
	BYTE IO_SD_CD			:		1;
	BYTE IO_SD_CS			:		1;
	BYTE IO_MOSI			:		1;
	BYTE IO_MISO	   	    :    	1;
	BYTE IO_SCK				:		1;
}bitB;

/**********************************************************************************************/
/*                                 DEFINICJA BITOW PORTU C                                    */
/**********************************************************************************************/

typedef struct bit_struct_C
{
	BYTE    				:		1;		//SCL
	BYTE    				:		1;		//SDA
	BYTE IO_LED_Blue		:		1;
	BYTE IO_LED_Red			:		1;
	BYTE IO_LED_Green		:		1;
	BYTE IO_Relay			:		1;
	BYTE 					:		1;
	BYTE 					:		1;
}bitC;

/**********************************************************************************************/
/*                                 DEFINICJA BITOW PORTU D                                    */
/**********************************************************************************************/

typedef struct bit_struct_D
{
	BYTE IO_WiFi1			:		1;
	BYTE 					:		1;		//TRACE (TXD)
	BYTE IO_WiFi2			:		1;
	BYTE IO_WiFi3			:		1;
	BYTE 					:		1;		//Right Speaker(PWM)
	BYTE 					:		1;		//Left Speaker(PWM)
	BYTE IO_WiFi4	 		:		1;
	BYTE 					:		1;
}bitD;

/**********************************************************************************************/
/*                                 	 OPIS PINOW PORTU A	                                      */
/**********************************************************************************************/

#define bitA(adr) (*((volatile bitA*) (adr)))

#define PIN_SW_Test				bitA(&PINA).SW_Test
#define PIN_Standby				bitA(&PINA).IO_Standby
#define PIN_Mute				bitA(&PINA).IO_Mute

#define UP_SW_Test				 bitA(&PORTA).SW_Test
#define UP_Standby				 bitA(&PORTA).IO_Standby
#define UP_Mute					 bitA(&PORTA).IO_Mute

/**********************************************************************************************/
/*                                DEFINICJA KIERUNKU PORTU A                                  */
/**********************************************************************************************/

#define bitA(adr) (*((volatile bitA*) (adr)))

#define DIR_SW_Test				bitA(&DDRA).SW_Test
#define DIR_Standby				bitA(&DDRA).IO_Standby
#define DIR_Mute				bitA(&DDRA).IO_Mute

/**********************************************************************************************/
/*                                 	 OPIS PINOW PORTU B                                       */
/**********************************************************************************************/

#define bitB(adr) (*((volatile bitB*) (adr)))

#define PIN_LED_Mosfet			bitB(&PINB).IO_LED_Mosfet
#define PIN_Move				bitB(&PINB).IO_Move
#define PIN_SD_CD		 		bitB(&PINB).IO_SD_CD
#define PIN_SD_CS		 		bitB(&PINB).IO_SD_CS
#define PIN_MOSI		 		bitB(&PINB).IO_MOSI
#define PIN_MISO		 		bitB(&PINB).IO_MISO
#define PIN_SCK			 		bitB(&PINB).IO_SCK

#define UP_LED_Mosfet			bitB(&PORTB).IO_LED_Mosfet
#define UP_Move					bitB(&PORTB).IO_Move
#define UP_SD_CD			 	bitB(&PORTB).IO_SD_CD
#define UP_SD_CS			 	bitB(&PORTB).IO_SD_CS
#define UP_MOSI				 	bitB(&PORTB).IO_MOSI
#define UP_MISO				 	bitB(&PORTB).IO_MISO
#define UP_SCK				 	bitB(&PORTB).IO_SCK


/**********************************************************************************************/
/*                                DEFINICJA KIERUNKU PORTU B                                  */
/**********************************************************************************************/

#define bitB(adr) (*((volatile bitB*) (adr)))

#define DIR_LED_Mosfet			bitB(&DDRB).IO_LED_Mosfet
#define DIR_Move				bitB(&DDRB).IO_Move
#define DIR_SD_CD		 		bitB(&DDRB).IO_SD_CD
#define DIR_SD_CS		 		bitB(&DDRB).IO_SD_CS
#define DIR_MOSI		 		bitB(&DDRB).IO_MOSI
#define DIR_MISO		 		bitB(&DDRB).IO_MISO
#define DIR_SCK			 		bitB(&DDRB).IO_SCK

/**********************************************************************************************/
/*                                 	 OPIS PINOW PORTU C                                       */
/**********************************************************************************************/

#define bitC(adr) (*((volatile bitC*) (adr)))

#define PIN_LED_Green	 		bitC(&PINC).IO_LED_Green
#define PIN_LED_Red	 			bitC(&PINC).IO_LED_Red
#define PIN_LED_Blue	 		bitC(&PINC).IO_LED_Blue
#define PIN_Relay		 		bitC(&PINC).IO_Relay

#define UP_LED_Green		 	bitC(&PORTC).IO_LED_Green
#define UP_LED_Red			 	bitC(&PORTC).IO_LED_Red
#define UP_LED_Blue			 	bitC(&PORTC).IO_LED_Blue
#define UP_Relay			 	bitC(&PORTC).IO_Relay

/**********************************************************************************************/
/*                                DEFINICJA KIERUNKU PORTU C                                  */
/**********************************************************************************************/

#define bitC(adr) (*((volatile bitC*) (adr)))

#define DIR_LED_Green 			bitC(&DDRC).IO_LED_Green
#define DIR_LED_Red	 			bitC(&DDRC).IO_LED_Red
#define DIR_LED_Blue 			bitC(&DDRC).IO_LED_Blue
#define DIR_Relay	 			bitC(&DDRC).IO_Relay

/**********************************************************************************************/
/*                                 	 OPIS PINOW PORTU D                                       */
/**********************************************************************************************/

#define bitD(adr) (*((volatile bitD*) (adr)))

#define PIN_WiFi1		 		bitD(&PIND).IO_WiFi1
#define PIN_WiFi2		 		bitD(&PIND).IO_WiFi2
#define PIN_WiFi3		 		bitD(&PIND).IO_WiFi3
#define PIN_WiFi4		 		bitD(&PIND).IO_WiFi4


#define UP_WiFi1		 		bitD(&PORTD).IO_WiFi1
#define UP_WiFi2			 	bitD(&PORTD).IO_WiFi2
#define UP_WiFi3		 		bitD(&PORTD).IO_WiFi3
#define UP_WiFi4			 	bitD(&PORTD).IO_WiFi4

/**********************************************************************************************/
/*                                DEFINICJA KIERUNKU PORTU D                                  */
/**********************************************************************************************/

#define bitD(adr) (*((volatile bitD*) (adr)))

#define DIR_WiFi1			 	bitD(&DDRD).IO_WiFi1
#define DIR_WiFi2			 	bitD(&DDRD).IO_WiFi2
#define DIR_WiFi3			 	bitD(&DDRD).IO_WiFi3
#define DIR_WiFi4			 	bitD(&DDRD).IO_WiFi4

/**********************************************************************************************/
/*                                   DEFINICJA STALYCH           	                          */
/**********************************************************************************************/

#define SET 1		//SET
#define CLR 0

#define IN  0		//DIR
#define OUT	1

#define ON  0
#define OFF 1

/**********************************************************************************************/
/*							            KONFIGURACJA PORTOW                                   */
/**********************************************************************************************/

void InitPort(void);


#endif /* IOPORT_H_ */
