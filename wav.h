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
 *   jeœli chcemy uzyskaæ mo¿liwoœæ odtwarzania plików WAV 16-bit z samplerate = 44,1kHz
 *   nale¿y koniecznie zmieniæ:
 *
 *   1. zmieniæ zewnêtrzny rezonator kwarcowy na 24MHz lub wiêkszy (nie zapomnieæ o Fusebicie CKOPT!!!)
 *   2. zmieniæ poni¿szy parametr z 0 na 1
 *   3. przekompilowaæ ca³oœæ z opcj¹ CLEAN
 *
 *   wy³¹czona zostanie obs³uga informacji na LCD w trakcie odtwarzania a tak¿e efekty dŸwiêkowe
 */
#define USE44KHZ 	0			// 0 = pliki max 22,050kHz,    1 = pliki max 44,1kHz
//--------------------------------------------------------------------------------------------------------


//*************** makra i zmienne na potrzeby obs³ugi PetitFAT
// proszê pamiêtaæ tak¿e o zmianie tych wartoœci w pliku mmc.c !!!!
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

//int8_t sk1=-1, sk2=4;	// zmienne pomocnicze do efektów dŸwiêkowych
#define BUF_SIZE 512			// maksymalny rozmiar pojedynczego bufora
uint8_t  buf[2][BUF_SIZE];		// podwójny bufor do odczytu z karty SD
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
