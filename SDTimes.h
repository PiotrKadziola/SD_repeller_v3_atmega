/*
 * SDTimes.h
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

#ifndef SDTIMES_H_
#define SDTIMES_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>
#include <string.h>


#include "diskio.h"
#include "pff.h"
#include "Timer.h"
#include "Data.h"
#include "Type.h"


char char_upr(char a);
char str_cmp_upr(char *a, char *b, char no_length_check);
double set_get_param(char *param, char *val);
double get_time_param(char *param, char *val);
void ShowErrors(uint8_t error);
void LoadConfigFile(void);
void LoadTimeFile(void);
void LoadOnTimesFile(void);
void CheckCardMount(void);


#endif /* SDTIMES_H_ */
