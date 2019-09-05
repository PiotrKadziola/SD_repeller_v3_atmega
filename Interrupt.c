/*
 * Interrupt.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */


/**********************************************************************************************/
/*							               PRZERWANIA                                         */
/**********************************************************************************************/

#include <avr\interrupt.h>
#include <avr\signal.h>
#include "wav.h"
#include "Data.h"
#include "Timer.h"
#include "Type.h"


//***************** przerwanie TIMER0 - samplowanie ******************************************
ISR(TIMER0_COMPA_vect) {

	char str[64];

#if USE44KHZ == 1

	static uint16_t buf_idx;		// indeks w pojedynczym buforze
	static uint8_t v1, v2;			// zmienne do przechowywania pr�bek
	buf_idx++;						// pomijamy m�odszy bajt 16-bitowej pr�bki kana� L
	v1 = buf[nr_buf][buf_idx++]-128;// -128 korekcja konwerji pr�bki 16-bitowej do 8-bitowej
	buf_idx++;						// pomijamy m�odszy bajt 16-bitowej pr�bki kana� R
	v2 = buf[nr_buf][buf_idx++]-128;// -128 korekcja konwerji pr�bki 16-bitowej do 8-bitowej
	OCR1A = v1;						// pr�bka na wyj�cie PWM1, kana� L
	OCR1B = v2;						// pr�bka na wyj�cie PWM2, kana� R

	buf_idx &= 0x01ff;
	if( !buf_idx ) {
		can_read = 1;
		nr_buf ^= 0x01;
	}
#endif

#if USE44KHZ == 0
	static uint16_t buf_idx;		// indeks w pojedynczym buforze
	static uint8_t v1, v2;			// zmienne do przechowywania pr�bek
	static uint8_t efekt_cnt;		// zmienna pomocnicza dla uzyskiwania prostych efekt�w

	if( !efekt_cnt ) {

		if( 16 == FLAGS.resolution ) {				// je�li rozdzielczo�� 16-bit�w
			if( FLAGS.stereo ) {					// je�li pr�bki stereofoniczne
				buf_idx++;							// pomijamy m�odszy bajt 16-bitowej pr�bki kana� L
				v1 = buf[nr_buf][buf_idx++]-128;	// -128 korekcja konwerji pr�bki 16-bitowej do 8-bitowej
				buf_idx++;							// pomijamy m�odszy bajt 16-bitowej pr�bki kana� R
				v2 = buf[nr_buf][buf_idx++]-128;	// -128 korekcja konwerji pr�bki 16-bitowej do 8-bitowej
			} else {								// je�li pr�bki monofoniczne
				buf_idx++;							// pomijamy m�odszy bajt 16-bitowej pr�bki MONO
				v1 = ((buf[nr_buf][buf_idx++]-128));	// -128 korekcja konwerji pr�bki 16-bitowej do 8-bitowej
				v2 = v1;							// to samo na dwa kana�y/wyj�cia
			}
		} else {									// je�li rozdzielczo�� 8-bit�w
			if( !FLAGS.stereo ) {					// je�li pr�bki monofoniczne
				v1 = buf[nr_buf][buf_idx++];		// pobieramy pr�bk� MONO do zmiennej v1
				v2 = v1;							// to samo na dwa kana�y/wyj�cia
			} else {								// je�li pr�bki stereofoniczne
				v1 = buf[nr_buf][buf_idx++];		// pobieramy pr�bk� kana� L
				v2 = buf[nr_buf][buf_idx++];		// pobieramy pr�bk� kana� R

			}
		}

	}
	BYTE x1,y1,x2,y2;

	x1 = v1/2;			//polowa
	y1 = v2/2;			//polowa
	x2 = v1/4;			//cwiartka
	y2 = v2/4;			//cwiartka

	switch(Settings.Volume)
	{
		case 1:

			OCR1A = x2;									// pr�bka na wyj�cie PWM1, kana� L
			OCR1B = y2;									//25%
		break;

		case 2:

			OCR1A = x1;									// pr�bka na wyj�cie PWM1, kana� L
			OCR1B = y1;									//50%
		break;

		case 3:

			OCR1A = x1+x2;								// pr�bka na wyj�cie PWM1, kana� L
			OCR1B = y1+y2;								//75%
		break;

		case 4:

			OCR1A = v1;									// pr�bka na wyj�cie PWM1, kana� L
			OCR1B = v2;									//100%
		break;
	}

										// pr�bka na wyj�cie PWM2, kana� R

	if( buf_idx > BUF_SIZE-1 ){

		buf_idx=0;								// reset indeksu bufora
		can_read = 1;							// flaga = 1
		nr_buf ^= 0x01;							// zmiana bufora na kolejny
	}

#endif

}
// *************************** koniec przerwania ****************************************


/**********************************************************************************************/
/*							            PRZERWANIE TIMERA 2                                   */
/**********************************************************************************************/

SIGNAL(TIMER2_OVF_vect)																//1ms
{
	static WORD Divider = 0;
	static WORD Divider1 = 0;

	if(Divider >= 50)																//50ms - czujniki
	{
		Divider = 0;
		Timer2Flag_ADC = 1;
	}

	if(Divider1 >= 1000)															//1s - odliczanie
	{
		Divider1 = 0;
		Timer2Flag_COUNT = 1;
	}

	Divider++;
	Divider1++;

	ReloadTimer2();
}

/**********************************************************************************************/
/*							              PRZERWANIE ADC                                      */
/**********************************************************************************************/

SIGNAL(ADC_vect)
{
	ADCFlag = 1;
}

/**********************************************************************************************/
/*							              		RTC		                                      */
/**********************************************************************************************/

SIGNAL(TWI_vect)
{
	RTCSendReciveTime(0);
}

