/*
 * I2C.c
 *
 * Created: 04/07/2020 12:52:46 
 *  Author: 
 */ 
#include "I2C.h"

void I2C_SetSlaveAdress(void)
{
	// set slave address
	TWAR = 0b00110010;
}

void I2C_Enable(void)
{
	// enable
	SET_BIT(TWCR, 2);
}

void I2C_ACK(void)
{
	// enable ACK
	SET_BIT(TWCR, 6);
}

void I2C_ClearStartBit(void)
{
	// clear start bit
	CLR_BIT(TWCR, 5);
}

void I2C_ClearStopBit(void)
{
	// clear stop bit
	CLR_BIT(TWCR, 4);
}

void I2C_WaitUtilFlagToBeSet(void)
{
	// wait until the flag is set
	while (GET_BIT(TWCR, 7) == 0);
}

void I2C_CheckStatusCode(uint8 statusCode, uint8 errorNo)
{
	// check status code
	if ((TWSR & 0xF8) == statusCode) {
		SET_BIT(PORTA, errorNo);
		} else {
		SET_BIT(PORTD, errorNo);
	}
}

void Slave_init(void) {
	I2C_SetSlaveAdress();
	I2C_Enable();
	I2C_ACK();
	I2C_ClearStartBit();
	I2C_ClearStopBit();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0x60, 0);
	
}



void I2C_SendData(uint8 data)
{
	TWDR = data;
}

void I2C_ClearFlag(void)
{
	// clear flag
	SET_BIT(TWCR, 7);
}