/*
 * I2C.c
 *
 * Created: 04/07/2020 12:15:56 
 *  Author: 
 */ 
#include "I2C.h"

void I2C_BitRate(void)
{
	// adjust bit rate
	TWBR = 2; // 50k bit per second
}

void I2C_StartBit(void)
{
	// start bit
	SET_BIT(TWCR, 5);
}

void I2C_ClearFlagAndEnable(void)
{
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
}

void I2C_WaitForTheFlagToBeSet(void)
{
	while (GET_BIT(TWCR, 7) == 0);
}

void I2C_CheckStatusCode(uint8 statusCode, uint8 errorNo)
{
	if ((TWSR & 0xF8) == statusCode) {
		SET_BIT(PORTA, errorNo);
	} else {
		SET_BIT(PORTB, errorNo);
	}
}

void I2C_SetSlaveAddress(void)
{
	// SLA + R
	TWDR = 0b00110011;
}

void I2C_ClearStartBit(void)
{
	// clear start bit
	CLR_BIT(TWCR, 5);
}

void I2C_ACK(void)
{
	SET_BIT(TWCR, 6);
}

void I2C_NACK(void)
{
	CLR_BIT(TWCR, 6);
}

void I2C_StopBit(void)
{
	SET_BIT(TWCR, 4);
}