/*
 * i2c.c
 *
 *  Created on: 23-09-2015
 *      Author: DESAR
 */

#include "i2c.h"
#include <avr/io.h>
#include <util/delay.h>

/******************************************************************************************************/
/*                                               I2C                                                  */
/******************************************************************************************************/

BYTE I2CReadBuffer;

/******************************************************************************************************/
/*                                             I2C Address                                            */
/******************************************************************************************************/

#define I2CReadAddress  0xA3
#define I2CWriteAddress 0xA2

/******************************************************************************************************/
/*                                              I2C Speed                                             */
/******************************************************************************************************/

#define CPUClock 	20000000
#define SCLFreq  	250000
#define I2CSpeed    ((CPUClock/SCLFreq)-16)/8

/******************************************************************************************************/
/*                                        I2C Configuration 0                                         */
/******************************************************************************************************/

void I2CConfig(void)
{
	TWBR = I2CSpeed;
	TWSR &= ~((1<<TWPS1)|(1<<TWPS0));							//TWI bit rate register = "1"
}

/******************************************************************************************************/
/*                                            I2C Status 0                                            */
/******************************************************************************************************/

BYTE I2CStatus(void)
{
	BYTE Status;
    Status = TWSR;                                          	//Read I2C status

	return Status;                                              //Return status
}

/******************************************************************************************************/
/*                                             I2C Start 0                                            */
/******************************************************************************************************/

void I2CStartSet(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)| (1<<TWIE);                                      //Set I2C start
}

/******************************************************************************************************/
/*                                         I2C Clear Start 0                                          */
/******************************************************************************************************/

void I2CStartClear(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWIE);                                           		//Clear I2C start
}

/******************************************************************************************************/
/*                                             I2C Stop 0                                             */
/******************************************************************************************************/

void I2CStopSet(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO)| (1<<TWIE);                                         //Set I2C stop
}

/******************************************************************************************************/
/*                                     I2C Clear Interrupt Flag 0                                     */
/******************************************************************************************************/

void I2CInterruptClear(void)
{
	TWCR &= ~(1<<TWINT);                                    //Clear I2C interrupt
}

/******************************************************************************************************/
/*                                          I2C Acknowlidge 0                                         */
/******************************************************************************************************/

void I2CAckSet(void)
{
	TWCR |= (1<<TWEA);                                         //Set I2C acknowledge
}

/******************************************************************************************************/
/*                                       I2C Clear Acknowledge 0                                      */
/******************************************************************************************************/

void I2CAckClear(void)
{
	TWCR &= ~(1<<TWEA);                                         //Set I2C acknowledge
}

/******************************************************************************************************/
/*                                          I2C Write Data 0                                           */
/******************************************************************************************************/

void I2CWrite(BYTE Data)
{
	TWDR = Data;                                          //Write data to I2C data register
	TWCR = (1<<TWINT) | (1<<TWEN)| (1<<TWIE);
}

/******************************************************************************************************/
/*                                           I2C Read Data 0                                          */
/******************************************************************************************************/

BYTE I2CRead(void)
{
	BYTE Data;
    Data = TWDR;                                             //Read data from I2C data register

	return Data;                                                //Return data value
}

/******************************************************************************************************/
/*                                  	     Write Byte to I2C   	                                  */
/******************************************************************************************************/

BYTE I2CByteWrite(BYTE I2CWriteCommand, BYTE I2CWriteData)
{
  static BYTE WriteIndex = 0x01;
   		 BYTE Status;

  switch(I2CStatus())                                     //Check I2C status
  {
     case I2CStart:                                        //I2C start status
		I2CWrite(I2CWriteAddress);                      	//Write I2C memory address and set to write
        I2CStartClear();                                   	//Clear I2C interrupt

		Status = 0;

		break;                                              //Break

     case I2CSlaveWriteAck:                                //I2C write address status
		I2CWrite(I2CWriteCommand);                     		//Write I2C high bits data address
		I2CInterruptClear();                                //Clear I2C interrupt

		Status = 0;

		break;                                              //Break

     case I2CDataByteWrite:                                //I2C write data status
		if(WriteIndex == 1)                                 //Write one data
        {
			                        						//Write I2C data
            I2CWrite(I2CWriteData);
			I2CInterruptClear();                            //Clear I2C interrupt
			Status = 0;
		}

		if(WriteIndex == 2)                                 //If one data write
        {
          I2CStopSet();
		  I2CAckClear();                                   	//Set I2C stop
		  I2CInterruptClear();                             	//Clear I2C interrupt
          WriteIndex = 0;
		  Status = 1;                                      //Return ok data write information
        }

        WriteIndex++;                                       //Increment write index

		break;                                              //Break

     default:
		I2CStopSet();
		I2CAckClear();                                    	//Set I2C stop
        I2CInterruptClear();                                //Clear I2C interrupt
 //       Delay(2000);
        _delay_us(2000);

		Status = 1;                                        //Return error data write information
		break;
    }

	return Status;
}

/******************************************************************************************************/
/*                                           Read Byte from I2C                                       */
/******************************************************************************************************/

BYTE I2CByteRead(BYTE I2CReadCommand)
{
  	BYTE Status;

    switch(I2CStatus())                                     //Check I2C status
    {
      case I2CStart:                                         //I2C start status
       	I2CWrite(I2CWriteAddress);                     		 //Write I2C memory address and set to write
        I2CStartClear();                                    //Clear I2C interrupt

		Status = 0;

		break;                                               //Break

      case I2CSlaveWriteAck:                                 //I2C write data status
		I2CWrite(I2CReadCommand);                           //Write I2C low bits data address
        I2CInterruptClear();                                //Clear I2C interrupt

		Status = 0;

		break;                                               //Break

      case I2CDataByteWrite:
        I2CStartSet();                                    	//Set I2C restart
        I2CInterruptClear();                              	//Clear I2C interrupt
        Status = 0;
		break;                                               //Break

      case I2CRepeatStart:                                   //I2C restart status
        I2CWrite(I2CReadAddress);                   		//Write I2C memory address and set to read
        I2CStartClear();                                    //Clear I2C interrupt

		Status = 0;

		break;                                               //Break

      case I2CSlaveReadAck:                                  //I2C read data acknowledge status
        I2CAckSet();
		I2CInterruptClear();                                //Clear I2C interrupt

		Status = 0;

		break;                                               //Break

      case I2CDataByteRead:                                  //I2C read data status
        I2CReadBuffer = I2CRead();                                   //Read I2C data
        I2CAckClear();                                      //Clear I2C acknowledge

		Status = 0;

		break;                                               //Break

      case I2CStop:                                          //I2C stop status
        I2CStopSet();
		I2CAckClear();                                     //Set I2C stop
        I2CInterruptClear();                                //Clear I2C interrupt

		Status = 1;                                         //Return value

		break;

      default:
        I2CStopSet();
		I2CAckClear();                                      //Set I2C stop
        I2CInterruptClear();                                //Clear I2C interrupt

		Status = 2;                                         //Return empty value

		break;
    }

	return Status;
}

/******************************************************************************************************/
/*                                   Read Byte from PCF8563                                     	  */
/******************************************************************************************************/

void I2CSendStart(void)
{
	I2CStartSet();                                            //Set I2C start
}
