/*
 * I2C.h
 *
 * Created: 04/07/2020 12:16:13
 *  Author: 
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "Common.h"
#include "StdTypes.h"

void I2C_BitRate(void);
void I2C_StartBit(void);
void I2C_ClearFlagAndEnable(void);
void I2C_WaitForTheFlagToBeSet(void);
void I2C_CheckStatusCode(uint8 statusCode, uint8 errorNo);
void I2C_SetSlaveAddress(uint8);
void I2C_ClearStartBit(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_StopBit(void);


#endif /* I2C_H_ */