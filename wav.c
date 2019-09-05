/*
 * wav.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */



#include "wav.h"
#include "IOPort.h"
#include "Random.h"
#include "Switch.h"
#include "uart.h"
#include "stdlib.h"
#include "SDTimes.h"
#include "LED.h"


char SelectedDir[10];				//ca³a cie¿ka do utworu
char SelectedFile[13];				//konkretny utwór do w³¹czenia

/**********************************************************************************************/
/*                                GLOBALNA STRUKTURA KLAWISZY                                 */
/**********************************************************************************************/

	/* 0:Invalid format, 1:I/O error, >1:Number of samples */
	DWORD load_header (void) {
		DWORD sz;
		uint8_t *wsk_buf = &buf[0][0];
		uint16_t ocrx;
//		char str[64];

		if (pf_read(wsk_buf, 12, &rb)) return 1;	/* Load file header (12 bytes) */

		if (rb != 12 || LD_DWORD(wsk_buf+8) != FCC('W','A','V','E')) return 0;

		for (;;) {
			pf_read(wsk_buf, 8, &rb);					/* Get Chunk ID and size */
			if (rb != 8) return 0;
			sz = LD_DWORD(&wsk_buf[4]);					/* Chunk size */

			switch (LD_DWORD(&wsk_buf[0])) {			/* FCC */
			case FCC('f','m','t',' ') :					/* 'fmt ' chunk */

				if (sz > 100 || sz < 16) return 0;		/* Check chunk size */

				pf_read(wsk_buf, sz, &rb);				/* Get content */

				if (rb != sz) return 0;

				if (wsk_buf[0] != 1) return 0;			/* Check coding type (1) */

				if (wsk_buf[2] != 1 && wsk_buf[2] != 2) /* Check channels (1/2) */
					return 0;

				FLAGS.stereo = wsk_buf[2]==2;				/* Get channel flag */
				if (wsk_buf[14] != 8 && wsk_buf[14] != 16)	/* Check resolution (8/16) */
					return 0;

				FLAGS.resolution = wsk_buf[14];			// ustalamy jaka rozdzielczoœæ 16/8 - bitów
				FLAGS.prescaler = 0;

				// obliczmy preskaler Timera0 w zale¿noœci od czêstotliwoœci samplowania
				FLAGS.khz = LD_WORD(&wsk_buf[4]);
				ocrx = (uint16_t)(F_CPU/8/LD_WORD(&wsk_buf[4]))-1;
				if( ocrx > 255 ) {
					ocrx = (uint16_t)(F_CPU/64/LD_WORD(&wsk_buf[4]))-1;
					FLAGS.prescaler = 1;
				}
				OCR0A = (uint8_t)ocrx;					// obliczona wartoœæ OCR0

				break;

			case FCC('d','a','t','a') :				/* 'data' chunk (start to PLAY) */

				return sz;

			case FCC('L','I','S','T') :				/* 'LIST' chunk (skip) */
			case FCC('f','a','c','t') :				/* 'fact' chunk (skip) */
				pf_lseek(Fs.fptr + sz);
				break;

			default :								/* Unknown chunk (error) */
				return 0;
		}
	}

	return 0;
}


// ******************  funkcja  P L A Y  ********************************
BYTE play ( const char *fn ) {

	DWORD sz;
	FRESULT res;
	char str[64];				//define zrobiæ w wersji RELEASE

	res = pf_mount(&Fs);

	if ((res = pf_open(fn)) == 0) {

		sz = load_header();						/* Load file header */
		if (sz < 256) return (WORD)sz;

		pf_lseek(0);

		pf_read(&buf[0][0], BUF_SIZE , &rb);	// za³aduj pierwsz¹ czêœæ bufora
		pf_read(&buf[1][0], BUF_SIZE , &rb);	// za³aduj drug¹ czêœæ bufora

		if( !FLAGS.prescaler )
		{
			USART_String("\n\r ////////////////////////////////////////////");
			USART_String("\n\r FLAGS.khz: ");
			USART_String(itoa(FLAGS.khz, str, 10));
			USART_String("\n\r FLAGS.prescaler: ");
			USART_String(itoa(FLAGS.prescaler , str, 10));
			USART_String("\n\r FLAGS.resolution: ");
			USART_String(itoa(FLAGS.resolution , str, 10));
			USART_String("\n\r FLAGS.stereo: ");
			USART_String(itoa(FLAGS.stereo, str, 10));
			USART_String("\n\r ////////////////////////////////////////////");

			TMR_START;		// start Timera0 (samplowanie)
		}
		else
		{
			USART_String("\n\r ////////////////////////////////////////////");
			USART_String("\n\r FLAGS.khz: ");
			USART_String(itoa(FLAGS.khz, str, 10));
			USART_String("\n\r FLAGS.prescaler: ");
			USART_String(itoa(FLAGS.prescaler , str, 10));
			USART_String("\n\r FLAGS.resolution: ");
			USART_String(itoa(FLAGS.resolution , str, 10));
			USART_String("\n\r FLAGS.stereo: ");
			USART_String(itoa(FLAGS.stereo, str, 10));
			USART_String("\n\r ////////////////////////////////////////////");
			TMR64_START;						// preskalerem zale¿nym od czêstotliwoœci
		}

		DDRD  |= (1<<PD5)|(1<<PD4);				// ustaw piny PWM1 (OC1A) oraz PWM2 (OC1B) jako wyjœcia WA¯NE !!!

		while(1) {
			if( can_read ) {				// jeœli flaga ustawiona w obs³udze przerwania

			  	res =	pf_read(&buf[ nr_buf ^ 0x01 ][0], BUF_SIZE , &rb);	// odczytaj kolejny bufor

//				if(Switch.Pressed == 0 && (PIN_SW_UP == CLR || PIN_SW_DOWN == CLR || PIN_SW_RIGHT == CLR || PIN_SW_LEFT == CLR)) break;

				if(rb < BUF_SIZE) break;
				can_read = 0;
			}
		}

		DDRD  &= ~((1<<PD5)|(1<<PD4));		// ustaw piny PWM1 (OC1A) oraz PWM2 (OC1B) jako wejœcia WA¯NE !!!

		if( !FLAGS.prescaler ) TMR_STOP;	// wy³¹czenie Timera0 (samplowania)
		else TMR64_STOP;

		_delay_ms(500);						// przerwa 0,5s
	}

	ShowErrors(res);

	return res;
}

void InitSPI(void)
{
	// init SPI
	DDRB |= (1<<CS)|(1<<MOSI)|(1<<SCK)|(1<<CS);
	PORTB |= (1<<CS);
	SPCR |= (1<<SPE)|(1<<MSTR);
	SPSR |= (1<<SPI2X);				// masymalny zegar SCK
}

void CountSongs(void)
{
	char str[64];
	uint8_t res = 0;

	ActualSongCount = 0;												//reset SongCount

	if(CardMountedFlag == Mounted)
	{
		USART_String("\n\r CountSongs -> pf_opendir: ");				//open folder with WAV files
		res = pf_opendir(&Dir, SelectedDir);
		ShowErrors(res);

		while (!(pf_readdir(&Dir, &Fno)) && Fno.fname[0]) {				//count all WAV files
			if (!(Fno.fattrib & (AM_HID))
				&& strstr(Fno.fname, ".WAV") ) {
				ActualSongCount++;
			}
		}

		USART_String("\n\r SongCount = ");
		USART_String(itoa(ActualSongCount, str, 10));
	}

}

void ChooseFolder(void)
{
	if(Settings.Sound == Random || Settings.Sound == Normal)		//if random, random song
	{
		strcpy(SelectedDir, Settings.Folder);							//set proper folder to play from config file
	}
	else if(Settings.Sound == FromFile)
	{
																//set proper folder to play from ONTIMES.txt
	}
}

void ChooseSong(void)				//before this function folder should be selected and song if playing from ontimes.txt
{
	static BYTE count = 0;
	static BYTE ActualSong = 0;										//number of song to be played
	char str[64];
	uint8_t res = 0;

	ChooseFolder();													//choose folder to play
	CountSongs();													//count songs in selected folder -> actualSongcount

	if(CardMountedFlag == Mounted)
	{
		if(Settings.Sound == Random)								//if random, random song
		{
			ActualSong = ChooseRandom(ActualSongCount)+1;				//od 1 do SongCount
		}
		else if(Settings.Sound == Normal)							//if normal, song ++
		{
			if(ActualSong < ActualSongCount)
			{
				ActualSong ++;
			}
			else
			{
				ActualSong = 1;
			}
		}
		else if(Settings.Sound == FromFile)							//if played from file
		{
			strcpy(SelectedFile, Fno.fname);						//proper song is selected from file
		}

		USART_String("\n\r MaxSong = ");
		USART_String(itoa(ActualSongCount, str, 10));

		USART_String("\n\r Choosen Song = ");
		USART_String(itoa(ActualSong, str, 10));

		if(Settings.Sound == Normal || Settings.Sound == Random)				//if random or normal, count proper song
		{
			USART_String("\n\r ChooseSong -> pf_opendir: ");				//open folder with WAV files
			res = pf_opendir(&Dir, SelectedDir);
			ShowErrors(res);

			while (!(pf_readdir(&Dir, &Fno)) && Fno.fname[0]) 					//liczenie po kolei a¿ do znalezienia wybranej piosenki
			{
				if (!(Fno.fattrib & (AM_HID)) && strstr(Fno.fname, ".WAV") )
				{
					count++;

					if(count >= ActualSong)
					{
						strcpy(SelectedFile, Fno.fname);									//wybrana piosenka
						USART_String("\n\r Selected song name :  ");
						USART_String(SelectedFile);

						count = 0;
						break;
					}
				}
			}
		}

	}
}


void PlayMusic(void)
{
//	char str[64];						//zakomentowaæ w wersji RELEASE

	RGBLedFlag = LED_PLAY;
	Led();

	if(Settings.Led == WithSound)		//turn on LEDMosfet if necessary
	{
		MosfetLedFlag = 1;
	}

	if(Settings.Relay == WithSound)		//turn on Relay if necessary
	{
		RelayFlag = 1;
	}

	UP_Standby		=	ON;				//turn on
	UP_Mute			=	ON;

	if(Settings.TurnOff == None || (Settings.TurnOff == ForNight && NightFlag == DayNow) || (Settings.TurnOff == ForDay && NightFlag == NightNow))
	{
		ChooseSong();													//choose song, random or normal or from file

		_delay_ms(500);													//time to turn on amplifier

		strcat(SelectedDir, "/");
		strcat(SelectedDir, SelectedFile);

		USART_String("\n\r strcat SelectedDir: ");
		USART_String(SelectedDir);

		play(SelectedDir);												//play selected dir and song
	}

	UP_Standby		=	ON;			//turn off
	UP_Mute			=	ON;

	if(Settings.Led == WithSound)		//turn off LEDMosfet if necessary
	{
		MosfetLedFlag = 0;
	}

	if(Settings.Relay == WithSound)		//turn off Relay if necessary
	{
		RelayFlag = 0;
	}

	RGBLedFlag = LED_POWER_ON;
	Led();
}


