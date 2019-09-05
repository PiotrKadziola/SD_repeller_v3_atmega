/*
 * Led.h
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

#ifndef LED_H_
#define LED_H_

/**********************************************************************************************/
/*							          GENEROWANIE DZWIEKU                                     */
/**********************************************************************************************/

#include <avr/delay.h>
#include "Type.h"

#define LED_OFF 			0		//wszystkie wy³¹czone
#define LED_POWER_ON		1		//zielona wieci
#define LED_PLAY			2		//czerwona swieci
#define LED_NO_SDCARD		3		//niebieska miga 300 ms
#define LED_LOCK			4		//zielona miga 300 ms
#define LED_LOW_POWER		5		//czerwona miga 300 ms

/**********************************************************************************************/
/*							            GENEROWANIE DZWIEKOW                                  */
/**********************************************************************************************/

void Led(void);



#endif /* LED_H_ */
