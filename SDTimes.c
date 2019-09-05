/*
 * SDTimes.c
 *
 *  Created on: 28-06-2015
 *      Author: someone
 */

#include "SDTimes.h"
#include "IOPort.h"
#include "Led.h"
#include "uart.h"
#include "data.h"
#include "stdlib.h"
#include "wav.h"
#include <avr/pgmspace.h>


extern char SelectedDir[10];				//ca³a cie¿ka do utworu

char char_upr(char a)
{
	if ((a >= 'a') && (a <= 'z'))
	{
		return(a - 32);
	}
	else
	{
		return(a);
	}
}
/////////////////////////////////////////////////////////////////////////
char str_cmp_upr(char *a, char *b, char no_length_check)
{
	if (no_length_check)
	{
		// don't care about common string length
		while ((*a) && (*b))
		{
			if (char_upr(*a++) != char_upr(*b++))
			{
				return(0);
			}
		}
	}
	else
	{
		// check if strings are of common length
		while ((*a) || (*b))
		{
			if (char_upr(*a++) != char_upr(*b++))
			{
				return(0);
			}
		}
	}

	return(1);
}
/////////////////////////////////////////////////////////////////////////////////
double set_get_param(char *param, char *val)
{
	char str[64];
	double ret = 0;
	uint8_t res;


	if (str_cmp_upr(param, (char *)"Folder", 0))
	{

		USART_String("\n\r Selected folder :");
		USART_String(val);

		for(uint8_t i = 0; i<sizeof(Settings.Folder); i++)					//reset Settings.folder bufor
		{
			Settings.Folder[i]	=	0;
		}
		memcpy(Settings.Folder, val, 10);				//copy val to Settings.Folder

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"LowPower", 0))
	{
		Settings.LowPower = atoi((char *)val);
		USART_String("\n\r LowPower = ");
		USART_String(itoa(Settings.LowPower, str, 10));

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"Volume", 0))
	{
		Settings.Volume = atoi((char *)val);
		USART_String("\n\r Volume = ");
		USART_String(itoa(Settings.Volume, str, 10));

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"BreakSecond", 0))
	{
		Settings.BreakSecond = atoi((char *)val);
		USART_String("\n\r BreakSecond = ");
		USART_String(itoa(Settings.BreakSecond, str, 10));

		ret = 1;
	}


	if (str_cmp_upr(param, (char *)"BreakMinute", 0))
	{
		Settings.BreakMinute = atoi((char *)val);
		USART_String("\n\r BreakMinute = ");
		USART_String(itoa(Settings.BreakMinute, str, 10));

		ret = 1;
	}


	if (str_cmp_upr(param, (char *)"TurnOff", 0))
	{
		if (str_cmp_upr(val, (char *)"None", 0))
		{
			Settings.TurnOff = None;
			USART_String("\n\r TurnOff : None");
		}
		else if (str_cmp_upr(val, (char *)"ForNight", 0))
		{
			Settings.TurnOff = ForNight;
			USART_String("\n\r TurnOff : ForNight");
		}
		else if (str_cmp_upr(val, (char *)"ForDay", 0))
		{
			Settings.TurnOff = ForDay;
			USART_String("\n\r TurnOff : ForDay");
		}

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"Sound", 0))
	{
		if (str_cmp_upr(val, (char *)"Normal", 0))
		{
			Settings.Sound = Normal;
			USART_String("\n\r Sound : Normal");
		}
		else if (str_cmp_upr(val, (char *)"Random", 0))
		{
			Settings.Sound = Random;
			USART_String("\n\r Sound : Random");
		}
		else if (str_cmp_upr(val, (char *)"FromFile", 0))
		{
			Settings.Sound = FromFile;
			USART_String("\n\r Sound : Fromfile");
		}

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"BreakTime", 0))
	{
		if (str_cmp_upr(val, (char *)"Normal", 0))
		{
			Settings.BreakTime = Normal;
			USART_String("\n\r BreakTime : Normal");
		}
		else if (str_cmp_upr(val, (char *)"Random", 0))
		{
			Settings.BreakTime = Random;
			USART_String("\n\r BreakTime : Random");
		}

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"Relay", 0))
	{
		if (str_cmp_upr(val, (char *)"Off", 0))
		{
			Settings.Relay = Off;
			USART_String("\n\r Relay : Off");
		}
//		else if (str_cmp_upr(val, (char *)"Random", 0))
//		{
//			Settings.Relay = Random;
//			USART_String("\n\r Relay : Random");
//		}
		else if (str_cmp_upr(val, (char *)"WithSound", 0))
		{
			Settings.Relay = WithSound;
			USART_String("\n\r Relay : WithSound");
		}

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"Led", 0))
	{
		if (str_cmp_upr(val, (char *)"Off", 0))
		{
			Settings.Led = Off;
			USART_String("\n\r Led : Off");
		}
//		else if (str_cmp_upr(val, (char *)"Random", 0))
//		{
//			Settings.Led = Random;
//			USART_String("\n\r Led : Random");
//		}
		else if (str_cmp_upr(val, (char *)"WithSound", 0))
		{
			Settings.Led = WithSound;
			USART_String("\n\r Led : WithSound");
		}

		ret = 1;
	}

//	if (str_cmp_upr(param, (char *)"RelayTime", 0))
//	{
//		Settings.RelayTime = atoi((char *)val);
//		USART_String("\n\r RelayTime = ");
//		USART_String(itoa(Settings.RelayTime, str, 10));

//		ret = 1;
//	}

//	if (str_cmp_upr(param, (char *)"LedTime", 0))
//	{
//		Settings.LedTime = atoi((char *)val);
//		USART_String("\n\r LedTime = ");
//		USART_String(itoa(Settings.LedTime, str, 10));

//		ret = 1;
//	}


	return(ret);
}

double get_time_param(char *param, char *val)			//read time from TIME.TXT and save to RDC
{
	uint8_t br;           // File read count
	char str[64];
	double ret = 0;
	FRESULT res;       // Petit FatFs function common result code

	if (str_cmp_upr(param, (char *)"Day", 0))
	{
		if (str_cmp_upr(val, (char *)"Sunday", 0))
		{
			Time.SaveDayOfWeek = 0;
			USART_String("\n\r SetDayOfWeek : Sunday");
		}
		else if (str_cmp_upr(val, (char *)"Monday", 0))
		{
			Time.SaveDayOfWeek = 1;
			USART_String("\n\r SetDayOfWeek : Monday");
		}
		else if (str_cmp_upr(val, (char *)"Tuesday", 0))
		{
			Time.SaveDayOfWeek = 2;
			USART_String("\n\r SetDayOfWeek : Tuesday");
		}
		else if (str_cmp_upr(val, (char *)"Wednesday", 0))
		{
			Time.SaveDayOfWeek = 3;
			USART_String("\n\r SetDayOfWeek : Wednesday");
		}
		else if (str_cmp_upr(val, (char *)"Thursday", 0))
		{
			Time.SaveDayOfWeek = 4;
			USART_String("\n\r SetDayOfWeek : Thursday");
		}
		else if (str_cmp_upr(val, (char *)"Friday", 0))
		{
			Time.SaveDayOfWeek = 5;
			USART_String("\n\r SetDayOfWeek : Friday");
		}
		else if (str_cmp_upr(val, (char *)"Saturday", 0))
		{
			Time.SaveDayOfWeek = 6;
			USART_String("\n\r SetDayOfWeek : Saturday");
		}

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"Hour", 0))
	{
		Time.SaveHour = atoi((char *)val);
		USART_String("\n\r Hour = ");
		USART_String(itoa(Time.SaveHour, str, 10));

		ret = 1;
	}

	if (str_cmp_upr(param, (char *)"Minute", 0))
	{
		Time.SaveMinute = atoi((char *)val);
		USART_String("\n\r Minute = ");
		USART_String(itoa(Time.SaveMinute, str, 10));

		Time.SaveSecond = 0;

		RTCSendTimeEnable();
		RTCSendReciveTime(1);		//send start

		USART_String("\n\r time sended to RTC");

		res = pf_lseek(0);																	//przejcie na pocz¹tek pliku
		USART_String("\n\r pf_lseek");
		ShowErrors(res);

		if(res == FR_OK)
		{
			res = pf_write("                                           ", 33, &br);					//nadpisanie pliku
			USART_String("\n\r pf_write");
			ShowErrors(res);
		}

		ret = 1;
	}										//seconds always to zero

	return(ret);
}

void ShowErrors(uint8_t error)
{
	switch(error)
	{
		case 0:
			USART_String("\n\r FR_OK");
			break;

		case 1:
			USART_String("\n\r FR_DISK_ERR");
			break;

		case 2:
			USART_String("\n\r FR_NOT_READY");
			break;

		case 3:
			USART_String("\n\r FR_NO_FILE");
			break;

		case 4:
			USART_String("\n\r FR_NO_PATH");
			break;

		case 5:
			USART_String("\n\r FR_NOT_OPENED");
			break;

		case 6:
			USART_String("\n\r FR_NOT_ENABLED");
			break;

		case 7:
			USART_String("\n\r FR_NO_FILESYSTEM");
			break;
	}
}

void LoadConfigFile(void)
{

	BYTE buff[255];     // File read buffer
	uint8_t br;           // File read count
	FRESULT res;       // Petit FatFs function common result code
	WORD j, k;
	char str1[15], str2[15];
	char flag;

	if(CardMountedFlag == Mounted)
	{
		// Open a file
		res = pf_open("CONFIG.TXT");
		USART_String("\n\r pf_open");
		ShowErrors(res);

		if(res == FR_OK)
		{
			// Read data to the memory
			res = pf_read(&buff, Fs.fsize, &br);    					// Read data to the buff[]
			USART_String("\n\r pf_read");
			ShowErrors(res);
		}

		if(res == FR_OK)
		{
			USART_String("\n\r /////////////////////////////////////////CONFIG");

			j = 0;

			while (j < br)
			{
				str1[0] = 0;
				str2[0] = 0;
				k = 0;
				flag = 0;

				// find last position in current line
				while ((buff[j] != '\n') && (j < br))
				{
					if ((buff[j] >= ' ') && (buff[j] <= '~'))
					{
						if (buff[j] == '=')
						{
							// terminate first string
							flag = 1;
							str1[k] = 0;
							k = 0;
						}
						else
						{
							// append to first or second string
							if (flag)
							{
								str2[k] = buff[j];
							}
							else
							{
								str1[k] = buff[j];
							}

							k++;
							if (k >= 64)
							{
								k = 63;
							}
						}
					}

					j++;
				}

				// terminate unterminated strings
				if (flag)
				{
					str2[k] = 0;
				}
				else
				{
					str1[k] = 0;
					str2[0] = 0;
				}

				if ((*str1 != 0) && (*str2 != 0) && (*str1 != ';'))
				{
					// assign the value to the parameter
					set_get_param(str1, str2);
				}

				j++;
			}
			BreakTime = Settings.BreakMinute*60 + Settings.BreakSecond;							//zaktualizowanie czasu przerwy

			USART_String("\n\r /////////////////////////////////////////CONFIG");
			USART_String("\n\r zaladowano CONFIG.TXT");
		}
	}
}

void LoadTimeFile(void)
{
	BYTE buff[255];     // File read buffer
	uint8_t br;           // File read count
	FRESULT res;       // Petit FatFs function common result code
	WORD j, k;
	char str1[15], str2[15];
	char flag;

	if(CardMountedFlag == Mounted)
	{
		// Open a file
		USART_String("\n\r trying to open TIME.TXT");
		res = pf_open("TIME.TXT");
		USART_String("\n\r pf_open");
		ShowErrors(res);

		if(res == 0)
		{
			// Read data to the memory
			res = pf_read(&buff, Fs.fsize, &br);    					// Read data to the buff[]
			USART_String("\n\r pf_read");
			ShowErrors(res);
		}
		else
		{
			USART_String("\n\r brak pliku TIME.TXT");
		}

		if(res == 0)
		{
			USART_String("\n\r /////////////////////////////////////////BEGIN TIME");
			j = 0;

			while (j < br)
			{
				str1[0] = 0;
				str2[0] = 0;
				k = 0;
				flag = 0;

				// find last position in current line
				while ((buff[j] != '\n') && (j < br))
				{
					if ((buff[j] >= ' ') && (buff[j] <= '~'))
					{
						if (buff[j] == '=')
						{
							// terminate first string
							flag = 1;
							str1[k] = 0;
							k = 0;
						}
						else
						{
							// append to first or second string
							if (flag)
							{
								str2[k] = buff[j];
							}
							else
							{
								str1[k] = buff[j];
							}

							k++;
							if (k >= 64)
							{
								k = 63;
							}
						}
					}

					j++;
				}

				// terminate unterminated strings
				if (flag)
				{
					str2[k] = 0;
				}
				else
				{
					str1[k] = 0;
					str2[0] = 0;
				}

				if ((*str1 != 0) && (*str2 != 0) && (*str1 != ';'))
				{
					// assign the value to the parameter
					get_time_param(str1, str2);
				}

				j++;

				USART_String("\n\r /////////////////////////////////////////END TIME");
			}
		}
	}
}

void LoadOnTimesFile(void)
{
	uint32_t br;           // File read count
	FRESULT res;       // Petit FatFs function common result code
	WORD j, k;
	char str1[64], str2[64], str3[64], str4[64];
	char flag;
	char str[64];
	char TempStr[10];
	BYTE DayNumber = 7;
	BYTE buff[600];    				// File read buffer

	USART_String("\n\r in LoadOnTimesFile !!!!!!!!!!!!!!!!!");

	if(CardMountedFlag == Mounted)
	{
		// Mount the volume
//		while(res != FR_OK)
//		{
//			res = pf_mount(&Fs);										//only once mount don`t work
//			USART_String("\n\r  trying to mount SD card");
//			ShowErrors(res);
//		}

		USART_String("\n\r LoadOnTimesFile -> pf_opendir: ");				//open folder with WAV files
		res = pf_opendir(&Dir, "/");
		ShowErrors(res);

		// Open a file
		res = pf_open("ONTIMES.TXT");									//in main folder
		USART_String("\n\r pf_open");
		ShowErrors(res);

		USART_String("\n\r Fs.fsize = ");
		USART_String(itoa(Fs.fsize, str, 10));

		if(res == 0)
		{
			// Read data to the memory
			res = pf_read(&buff, 200 , &br);    					// Read data to the buff[]
			USART_String("\n\r pf_read");
			ShowErrors(res);
		}
		else
		{
			USART_String("\n\r brak pliku ONTIMES.TXT");
		}

		if(res == 0)
		{
			//reset all string buffers
			for(uint8_t l = 0; l< 64; l++)
			{
				str1[l] = 0;
				str2[l] = 0;
				str3[l] = 0;
				str4[l] = 0;
			}

			USART_String("\n\r /////////////////////////////////////////BEGIN ONTIMES");
			j = 0;

			while (j < br)
			{
				str1[0] = 0;
				str2[0] = 0;
				str3[0] = 0;
				str4[0] = 0;
				k = 0;
				flag = 0;

				// find last position in current line
				while ((buff[j] != '\n') && (j < br))
				{
					if ((buff[j] >= ' ') && (buff[j] <= '~'))
					{
						if (buff[j] == ':')
						{
							// terminate first string
							flag ++;
							str2[k] = 0;
							k = 0;
						}
						else
						{
							// append to first or second or third string
							if (flag == 3)								//flag == 3
							{
								str4[k] = buff[j];
							}
							if (flag == 2)								//flag == 2
							{
								str3[k] = buff[j];
							}
							if (flag == 1)								//flag == 1
							{
								str2[k] = buff[j];
							}
							else if(flag == 0)							//flag == 0
							{
								str1[k] = buff[j];
							}

							k++;
							if (k >= 64)
							{
								k = 63;
							}
						}
					}

					j++;
				}

				// terminate unterminated strings
				if (flag == 3)
				{
					str4[k] = 0;
				}
				if (flag == 2)
				{
					str3[k] = 0;
					str4[0] = 0;
				}
				else if(flag == 1)
				{
					str2[k] = 0;
					str3[0] = 0;
					str4[0] = 0;
				}
				else if(flag == 0)
				{
					str1[k] = 0;
					str2[0] = 0;
					str3[0] = 0;
					str4[0] = 0;
				}

				j++;

				DayNumber = 7;											//reset day number

				if(str_cmp_upr(str1, (char *)"SUNDAY", 0))									//convert day of week to number of day
				{
					DayNumber = 0;
				}
				if(str_cmp_upr(str1, (char *)"MONDAY", 0))
				{
					DayNumber = 1;
				}
				if(str_cmp_upr(str1, (char *)"TUESDAY", 0))
				{
					DayNumber = 2;
				}
				if(str_cmp_upr(str1, (char *)"WEDNESDAY", 0))
				{
					DayNumber = 3;
				}
				if(str_cmp_upr(str1, (char *)"THURSDAY", 0))
				{
					DayNumber = 4;
				}
				if(str_cmp_upr(str1, (char *)"FRIDAY", 0))
				{
					DayNumber = 5;
				}
				if(str_cmp_upr(str1, (char *)"SATURDAY", 0))
				{
					DayNumber = 6;
				}

				if(Time.ActualDayOfWeek == DayNumber)					//if day the same, compare hour
				{
					USART_String("\n\r Same day: ");
					USART_String(str1);
					if(Time.ActualHour == atoi(str2))							//if hour the same compare minute
					{
						USART_String("\n\r Same hour: ");
						USART_String(str2);
						if(Time.ActualMinute == atoi(str3))					//if the same minute play sound
						{
							USART_String("\n\r Same minute: ");
							USART_String(str3);

							if(str4[0] > 0)							//if there fourth parameter
							{
								USART_String("\n\r direction to play: ");
								USART_String(str4);

								for(uint8_t i = 0; sizeof(SelectedDir); i++)					//reset SelectedDir bufor
								{
									SelectedDir[i]	=	0;
								}
								memcpy(SelectedDir[0], str4, 10);				//copy str4 to SelectedDir
								USART_String("\n\r selected dir: ");
								USART_String(SelectedDir);

								PlayMusic();									//play music file
							}
							else									//if not use random or normal
							{
								USART_String("\n\r no direction, playing");
								if(Settings.BreakTime == Normal)
								{
									USART_String("\n\r Normal sound");
									PlayMusic();									//play music file
								}
								else if(Settings.BreakTime == Random)
								{
									USART_String("\n\r Random sound");
									PlayMusic();									//play music file
								}
							}
						}
					}
				}
			}
			USART_String("\n\r /////////////////////////////////////////END ONTIMES");
		}
	}
}

void CheckCardMount(void)
{
	FRESULT res;       // Petit FatFs function common result code

	if(PIN_SD_CD == OFF)										//jesli wyjêto kartê
	{
		USART_String("\n\r no SD card");
		RGBLedFlag = LED_NO_SDCARD;
		CardMountedFlag = NotMounted;									//próbuj znowu wykryæ kartê po w³o¿eniu
	}

	if(CardMountedFlag == NotMounted && PIN_SD_CD == ON)				//jeli karta w³o¿ona ale jeszcze nie zamontowana
	{
		// Mount the volume
		while(res != FR_OK)
		{
			res = pf_mount(&Fs);								//only once mount don`t work
			USART_String("\n\r  trying to mount SD card");
			ShowErrors(res);
		}

		if(res == FR_OK)									//jesli zamontowano kartê
		{
			USART_String("\n\r SD card mounted");
			CardMountedFlag = Mounted;
			RGBLedFlag = LED_POWER_ON;
			LoadConfigFile();								//load config file
			LoadTimeFile();									//load time file
		}
	}
}


