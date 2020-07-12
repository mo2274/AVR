/*
 * I2C.h
 *
 * Created: 04/07/2020 12:53:05 ص
 *  Author: scc
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "StdTypes.h"
#include <avr/io.h>
#include "Common.h"

void I2C_SetSlaveAdress(void);
void I2C_Enable(void);
void I2C_ACK(void);
void I2C_ClearStartBit(void);
void I2C_ClearStopBit(void);
void I2C_WaitUtilFlagToBeSet(void);
void I2C_CheckStatusCode(uint8 statusCode, uint8 errorNo);
void Slave_init(void);
void I2C_SendData(uint8 data);
void I2C_ClearFlag(void);


#endif /* I2C_H_ */