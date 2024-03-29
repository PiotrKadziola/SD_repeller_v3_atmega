/*
 * i2c.h
 *
 *  Created on: 23-09-2015
 *      Author: DESAR
 */

#ifndef I2C_H_
#define I2C_H_

#include "Type.h"

/**********************************************************************************************/
/*                                        I2C Status Values                                   */
/**********************************************************************************************/

#define I2CStart          0x08
#define I2CStop           0x58
#define I2CRepeatStart    0x10
#define I2CSlaveWriteAck  0x18
#define I2CDataByteWrite  0x28
#define I2CSlaveReadAck   0x40
#define I2CDataByteRead   0x50
#define I2CNotDone        0xF8


/**********************************************************************************************/
/*                                        I2C Configuration 0                                 */
/**********************************************************************************************/

void I2CConfig(void);

/**********************************************************************************************/
/*                                            I2C Status 0                                    */
/**********************************************************************************************/

BYTE I2CStatus(void);

/**********************************************************************************************/
/*                                             I2C Start 0                                    */
/**********************************************************************************************/

void I2CStartSet(void);

/**********************************************************************************************/
/*                                         I2C Clear Start 0                                  */
/**********************************************************************************************/

void I2CStartClear(void);

/**********************************************************************************************/
/*                                             I2C Stop 0                                     */
/**********************************************************************************************/

void I2CStopSet(void);

/**********************************************************************************************/
/*                                     I2C Clear Interrupt Flag 0                             */
/**********************************************************************************************/

void I2CInterruptClear(void);

/**********************************************************************************************/
/*                                          I2C Acknowlidge 0                                 */
/**********************************************************************************************/

void I2CAckSet(void);

/**********************************************************************************************/
/*                                       I2C Clear Acknowlidge 0                              */
/**********************************************************************************************/

void I2CAckClear(void);

/**********************************************************************************************/
/*                                          I2C Write Data 0                                  */
/**********************************************************************************************/

void I2CWrite(BYTE Data);

/**********************************************************************************************/
/*                                           I2C Read Data 0                                  */
/**********************************************************************************************/

BYTE I2CRead(void);

/**********************************************************************************************/
/*                                  	   Write Byte to I2C  	                              */
/**********************************************************************************************/

BYTE I2CByteWrite(BYTE I2CWriteCommand, BYTE I2CWriteData);

/**********************************************************************************************/
/*                                   Read Byte from PCF8563     	                          */
/**********************************************************************************************/

BYTE I2CByteRead(BYTE I2CReadCommand);


/**********************************************************************************************/
/*                                   Send Start To PCF8563	                              	  */
/**********************************************************************************************/

void I2CSendStart(void);

#endif /* I2C_H_ */
