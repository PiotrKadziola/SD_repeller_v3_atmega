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
	static uint8_t v1, v2;			// zmienne do przechowywania próbek
	buf_idx++;						// pomijamy m³odszy bajt 16-bitowej próbki kana³ L
	v1 = buf[nr_buf][buf_idx++]-128;// -128 korekcja konwerji próbki 16-bitowej do 8-bitowej
	buf_idx++;						// pomijamy m³odszy bajt 16-bitowej próbki kana³ R
	v2 = buf[nr_buf][buf_idx++]-128;// -128 korekcja konwerji próbki 16-bitowej do 8-bitowej
	OCR1A = v1;						// próbka na wyjœcie PWM1, kana³ L
	OCR1B = v2;						// próbka na wyjœcie PWM2, kana³ R

	buf_idx &= 0x01ff;
	if( !buf_idx ) {
		can_read = 1;
		nr_buf ^= 0x01;
	}
#endif

#if USE44KHZ == 0
	static uint16_t buf_idx;		// indeks w pojedynczym buforze
	static uint8_t v1, v2;			// zmienne do przechowywania próbek
	static uint8_t efekt_cnt;		// zmienna pomocnicza dla uzyskiwania prostych efektów

	if( !efekt_cnt ) {

		if( 16 == FLAGS.resolution ) {				// jeœli rozdzielczoœæ 16-bitów
			if( FLAGS.stereo ) {					// jeœli próbki stereofoniczne
				buf_idx++;							// pomijamy m³odszy bajt 16-bitowej próbki kana³ L
				v1 = buf[nr_buf][buf_idx++]-128;	// -128 korekcja konwerji próbki 16-bitowej do 8-bitowej
				buf_idx++;							// pomijamy m³odszy bajt 16-bitowej próbki kana³ R
				v2 = buf[nr_buf][buf_idx++]-128;	// -128 korekcja konwerji próbki 16-bitowej do 8-bitowej
			} else {								// jeœli próbki monofoniczne
				buf_idx++;							// pomijamy m³odszy bajt 16-bitowej próbki MONO
				v1 = ((buf[nr_buf][buf_idx++]-128));	// -128 korekcja konwerji próbki 16-bitowej do 8-bitowej
				v2 = v1;							// to samo na dwa kana³y/wyjœcia
			}
		} else {									// jeœli rozdzielczoœæ 8-bitów
			if( !FLAGS.stereo ) {					// jeœli próbki monofoniczne
				v1 = buf[nr_buf][buf_idx++];		// pobieramy próbkê MONO do zmiennej v1
				v2 = v1;							// to samo na dwa kana³y/wyjœcia
			} else {								// jeœli próbki stereofoniczne
				v1 = buf[nr_buf][buf_idx++];		// pobieramy próbkê kana³ L
				v2 = buf[nr_buf][buf_idx++];		// pobieramy próbkê kana³ R

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

			OCR1A = x2;									// próbka na wyjœcie PWM1, kana³ L
			OCR1B = y2;									//25%
		break;

		case 2:

			OCR1A = x1;									// próbka na wyjœcie PWM1, kana³ L
			OCR1B = y1;									//50%
		break;

		case 3:

			OCR1A = x1+x2;								// próbka na wyjœcie PWM1, kana³ L
			OCR1B = y1+y2;								//75%
		break;

		case 4:

			OCR1A = v1;									// próbka na wyjœcie PWM1, kana³ L
			OCR1B = v2;									//100%
		break;
	}

										// próbka na wyjœcie PWM2, kana³ R

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

