/*
 * wav.h
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

#ifndef WAV_H_
#define WAV_H_


#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>
//#include <avr/interrupt.h>
#include <string.h>
//#include <stdlib.h>


#include "diskio.h"
#include "pff.h"
#include "Timer.h"
#include "Data.h"
#include "Type.h"


//--------------------------------------------------------------------------------------------------------
/*
 *   je�li chcemy uzyska� mo�liwo�� odtwarzania plik�w WAV 16-bit z samplerate = 44,1kHz
 *   nale�y koniecznie zmieni�:
 *
 *   1. zmieni� zewn�trzny rezonator kwarcowy na 24MHz lub wi�kszy (nie zapomnie� o Fusebicie CKOPT!!!)
 *   2. zmieni� poni�szy parametr z 0 na 1
 *   3. przekompilowa� ca�o�� z opcj� CLEAN
 *
 *   wy��czona zostanie obs�uga informacji na LCD w trakcie odtwarzania a tak�e efekty d�wi�kowe
 */
#define USE44KHZ 	0			// 0 = pliki max 22,050kHz,    1 = pliki max 44,1kHz
//--------------------------------------------------------------------------------------------------------


//*************** makra i zmienne na potrzeby obs�ugi PetitFAT
// prosz� pami�ta� tak�e o zmianie tych warto�ci w pliku mmc.c !!!!
#define SCK 	PB7
#define MOSI 	PB5
#define MISO 	PB6
#define CS 		PB4

#define FCC(c1,c2,c3,c4)	(((DWORD)c4<<24)+((DWORD)c3<<16)+((WORD)c2<<8)+(BYTE)c1)	/* FourCC */

// definicja struktury z parametrami WAV
typedef struct {
	uint8_t stereo:1;
	uint8_t prescaler:1;
	uint8_t resolution;
	uint16_t khz;
} _FLAGS;


FATFS Fs;			/* File system object */
DIR Dir;			/* Directory object */
FILINFO Fno;		/* File information */


WORD rb;

//int8_t sk1=-1, sk2=4;	// zmienne pomocnicze do efekt�w d�wi�kowych
#define BUF_SIZE 512			// maksymalny rozmiar pojedynczego bufora
uint8_t  buf[2][BUF_SIZE];		// podw�jny bufor do odczytu z karty SD
uint8_t nr_buf;		// indeks aktywnego buforu
_FLAGS FLAGS;	// definicja struktury
volatile uint8_t can_read;

/* 0:Invalid format, 1:I/O error, >1:Number of samples */
DWORD load_header (void);
BYTE play ( const char *fn );
void InitSPI(void);
void CountSongs(void);
void ChooseFolder(void);
void ChooseSong(void);
void PlayMusic(void);


#endif /* WAV_H_ */
