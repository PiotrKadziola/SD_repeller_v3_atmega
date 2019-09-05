/*
 * Timer.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


/**********************************************************************************************/
/*							                TIMER                                             */
/**********************************************************************************************/

#include <avr\io.h>
#include "Timer.h"

/**********************************************************************************************/
/*							      DEFINICJA CZESTOTLIWOSCI TIMERA                             */
/**********************************************************************************************/

#define CPUFreq 	20000000				//czestotliwosc taktowania uP
#define Time2    	1000					//czestotliwosc przerwania timera
#define Div2		128						//podzial czestotliwosci kwarcu
#define TimerValue0 CPUFreq/Time2/Div2		//wyliczanie czasu do przepelnienia

/**********************************************************************************************/
/*							           INICJALIZACJA TIMER 0                                  */
/**********************************************************************************************/

void InitTimer0(void)		// konfiguracja Timer0 (samplowanie)
{
			// tryb CTC					//normal port operation
	TCCR0A = (0<<WGM00) | (1<<WGM01) | (0<<COM0A1) | (0<<COM0A0)| (0<<COM0B1) | (0<<COM0B0);
			// CTC				// no prescaler ?
	TCCR0B = (0<<CS02) | (0<<CS01)  | (0<<CS00) | (0<<WGM02);		// zezwolenie na przerwanie CompareMatch

	TIMSK0 = (1<<OCIE0A);

//	TIFR0 = (1<<OCF0A);
}

/**********************************************************************************************/
/*							           INICJALIZACJA TIMER 1                                  */
/**********************************************************************************************/

void InitTimer1(void)
{
	// konfiguracja PWM 8 bit (Timer1) noœna
	TCCR1A = (1<<WGM10) | (0<<WGM11) | (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1) |(0<<COM1B0);

	TCCR1B = (1<<CS10) | (0<<WGM12) | (0<<WGM13);
}

/**********************************************************************************************/
/*							           INICJALIZACJA TIMER 2                                  */
/**********************************************************************************************/

void InitTimer2(void)
{
	//CTC mode			    		// normal port operation
	TCCR2A |= (1<<WGM21) | (0<<WGM20) | (0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0);

			//CDC				//prescaler 64
	TCCR2B |= (0<<WGM22) | (1<<CS22) | (0<<CS21) | (1<<CS20);

	TCNT2 = (256-TimerValue0);			//wartosc poczatkowa

	TIMSK2 |= (1<<TOIE2) | (0<<OCIE2A);				//wlacz przerwanie od przepe³nienia Timer2

}

/**********************************************************************************************/
/*							         REINICAJALIZACJA WARTOSCI 2                              */
/**********************************************************************************************/

void ReloadTimer2(void)
{
	TCNT2=(256-TimerValue0);			//wartosc poczatkowa
}


