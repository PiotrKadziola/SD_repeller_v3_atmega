/*
 * DS1340.c
 *
 *  Created on: 23-09-2015
 *      Author: DESAR
 */


#include "i2c.h"
#include "DS1340.h"
#include "Data.h"
#include "uart.h"
#include <stdlib.h>
#include "SDTimes.h"


/**********************************************************************************************/
/*							           I2C EXTERNAL BUFFER 	                                  */
/**********************************************************************************************/

extern  BYTE I2CReadBuffer;

/**********************************************************************************************/
/*							                 RTC FLAG	                                      */
/**********************************************************************************************/

		BYTE RTCFlag;				//4-odczytuje, 3 - zapisuje, 2- odczytaj, 1-zapisz

/**********************************************************************************************/
/*							              RTC ADDRESS DATA	                                  */
/**********************************************************************************************/

#define RTCSecondAddress 		0x02
#define RTCMinuteAddress	    0x03
#define RTCHourAddress			0x04
#define RTCDayOfWeekAddress		0x06

/**********************************************************************************************/
/*							         	    DecToBCDCode	                                  */
/**********************************************************************************************/

BYTE DecToBCDCode(BYTE Dec)
{
	return ((Dec/10)<<4)+(Dec%10);
}

/**********************************************************************************************/
/*							         	    BCDToDecCode	                                  */
/**********************************************************************************************/

BYTE BCDToDecCode(BYTE BCD)
{
	return ((BCD>>4)*10)+(0x0F & BCD);
}

/**********************************************************************************************/
/*							         	 RTCSendTimeEnable  		                          */
/**********************************************************************************************/

void RTCReciveTimeEnable(void)
{
	RTCFlag |= 0x02;
}

/**********************************************************************************************/
/*							         	 RTCSendTimeEnable  		                          */
/**********************************************************************************************/

void RTCSendTimeEnable(void)
{
	RTCFlag |= 0x01;
}

/**********************************************************************************************/
/*							         	 RTCSendTimeEnable  		                          */
/**********************************************************************************************/

void RTCSendReciveStart(void)
{
	if(((RTCFlag>>2) == 0) && ((RTCFlag & 0x03) != 0))
		I2CSendStart();
}

/**********************************************************************************************/
/*							         	    RTCReciveTime 	                                  */
/**********************************************************************************************/

BYTE RTCReciveTime(void)
{
	static BYTE Index   = 0;
	       BYTE RTCBusy = 0;
		   BYTE Read;

	if((RTCFlag & 0x02) == 0x02 && (RTCFlag & 0x04) == 0x00)
	{
		RTCFlag |= 0x08;

		switch(Index)
		{
			case 0:
					RTCBusy = I2CByteRead(RTCSecondAddress);

					if(RTCBusy == 0x01)							//OK
					{
						Read = BCDToDecCode(0x7F & I2CReadBuffer);

						if(Read <= 59)
							Time.ActualSecond = Read;

						I2CSendStart();
						RTCBusy = 0x00;
						Index++;
					}

					if(RTCBusy == 0x02)							//Err
					{
						RTCFlag &= ~0x02;
						RTCFlag &= ~0x08;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;

			case 1:
					RTCBusy = I2CByteRead(RTCMinuteAddress);

					if(RTCBusy == 0x01)							//OK
					{
						Read = BCDToDecCode(0x7F & I2CReadBuffer);

						if(Read <= 59)
							Time.ActualMinute = Read;

						I2CSendStart();
						RTCBusy = 0x00;
						Index++;
					}

					if(RTCBusy == 0x02)							//Err
					{
						RTCFlag &= ~0x02;
						RTCFlag &= ~0x08;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;

			case 2:
					RTCBusy = I2CByteRead(RTCHourAddress);

					if(RTCBusy == 0x01)							//OK
					{
						Read = BCDToDecCode(0x3F & I2CReadBuffer);

						if(Read <= 23)
							Time.ActualHour = Read;

						I2CSendStart();
						RTCBusy = 0x00;
						Index++;
					}

					if(RTCBusy == 0x02)							//Err
					{
						RTCFlag &= ~0x02;
						RTCFlag &= ~0x08;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;

			case 3:
					RTCBusy = I2CByteRead(RTCDayOfWeekAddress);

					if(RTCBusy == 0x01)							//OK
					{
						Read = 0x07 & I2CReadBuffer;

						if(Read <= 6)
							Time.ActualDayOfWeek = Read;

						RTCFlag &= ~0x02;
						RTCFlag &= ~0x08;

						RTCBusy = 0x01;
						Index = 0;
					}

					if(RTCBusy == 0x02)							//Err
					{
						RTCFlag &= ~0x02;
						RTCFlag &= ~0x08;

						RTCBusy = 0x01;
						Index = 0;
					}


					break;
		}
	}

	return RTCBusy;
}

/**********************************************************************************************/
/*							         	    RTCSendTime 	                                  */
/**********************************************************************************************/

BYTE RTCSendTime(void)
{
	static BYTE Index   = 0;
		   BYTE RTCBusy = 0;

	if((RTCFlag & 0x01) == 0x01 && (RTCFlag & 0x08) == 0x00)
	{
		RTCFlag |= 0x04;

		switch(Index)
		{
			case 0:
					RTCBusy = I2CByteWrite(RTCSecondAddress, ( DecToBCDCode(Time.SaveSecond)));

					if(RTCBusy == 0x01)				//OK
					{
						I2CSendStart();
						RTCBusy = 0x00;
						Index++;
					}

					if(RTCBusy == 0x02)				//Err
					{
						RTCFlag &= ~0x01;
						RTCFlag &= ~0x04;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;

			case 1:
					RTCBusy = I2CByteWrite(RTCMinuteAddress, ( DecToBCDCode(Time.SaveMinute)));

					if(RTCBusy == 0x01)				//OK
					{
						I2CSendStart();
						RTCBusy = 0x00;
						Index++;
					}

					if(RTCBusy == 0x02)				//Err
					{
						RTCFlag &= ~0x01;
						RTCFlag &= ~0x04;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;

			case 2:
					RTCBusy = I2CByteWrite(RTCHourAddress, ( DecToBCDCode(Time.SaveHour)));

					if(RTCBusy == 0x01)				//OK
					{
						I2CSendStart();
						RTCBusy = 0x00;
						Index++;
					}

					if(RTCBusy == 0x02)				//Err
					{
						RTCFlag &= ~0x01;
						RTCFlag &= ~0x04;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;

			case 3:
					RTCBusy = I2CByteWrite(RTCDayOfWeekAddress, (0x07 & Time.SaveDayOfWeek));

					if(RTCBusy == 0x01)				//OK
					{
						RTCFlag &= ~0x01;
						RTCFlag &= ~0x04;

						RTCBusy = 0x01;
						Index = 0;
					}

					if(RTCBusy == 0x02)				//Err
					{
						RTCFlag &= ~0x01;
						RTCFlag &= ~0x04;

						RTCBusy = 0x01;
						Index = 0;
					}

					break;
		}
	}

	return RTCBusy;
}

/**********************************************************************************************/
/*							           RTCSendReciveTime	                                  */
/**********************************************************************************************/

void RTCSendReciveTime(BYTE StartEnable)
{
	if(StartEnable == 0)
	{
		RTCReciveTime();
		RTCSendTime();
	}

	RTCSendReciveStart();
}

/**********************************************************************************************/
/*							           		RTCShowTime	   		                               */
/**********************************************************************************************/
void RTCShowTime(void)
{
	char str[64];

	USART_String("\n\r");
	USART_String("\n\r ////////////////RTC Time////////////////");
	USART_String("\n\r DayOfWeek: ");						//0 to 6
	switch(Time.ActualDayOfWeek)
	{
		case 0:
		{
			USART_String(" Sunday");
			break;
		}

		case 1:
		{
			USART_String(" Monday");
			break;
		}

		case 2:
		{
			USART_String(" Tuesday");
			break;
		}

		case 3:
		{
			USART_String(" Wednesday");
			break;
		}

		case 4:
		{
			USART_String(" Thursday");
			break;
		}
		case 5:
		{
			USART_String(" Friday");
			break;
		}

		case 6:
		{
			USART_String(" Saturday");
			break;
		}
	}
	USART_String("\n\r Second: ");
	USART_String(itoa(Time.ActualSecond, str, 10));
	USART_String("\n\r Minute: ");
	USART_String(itoa(Time.ActualMinute, str, 10));
	USART_String("\n\r Hour: ");
	USART_String(itoa(Time.ActualHour, str, 10));

}
