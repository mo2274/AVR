/*
 * i2c.c
 *
 * Created: 28/06/2020 09:21:09 
 *  Author: 
 */ 
#include "i2c.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Common.h"

static void I2C_Error(uint8_t num)
{
	while (1) {
		PORTA ^= 1 << num;
		_delay_ms(500);
		
	}
}

static void I2C_Check_StatusCode(uint8_t status_code, uint8_t num)
{
	// check if the status code is correct
	if ((TWSR & 0xF8) != status_code) {
		I2C_Error(num);
	}
}

static void I2C_Clear_INT_AndEnable()
{
	/* clear the interrupt flag */
	SET_BIT(TWCR, 7);
	/*  enable the TWI */
	SET_BIT(TWCR, 2);
}

static void I2C_StartBit()
{
	/* start bit */
	SET_BIT(TWCR, 5);
}

static void I2C_Wait_Until_Flag_Set()
{
	while(GET_BIT(TWCR, 7) == 0);
}

static void I2C_StopBit()
{
	SET_BIT(TWCR, 4);
}

static void I2C_Tx(uint8_t data) {
	/*---------- start bit --------*/
	TWDR = 0x00;
	TWCR = 0x00;
	I2C_StartBit();
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x08, 0);
	/*-------- SLA + W---------*/
	TWDR = 100;
	// clear the start bit
	CLR_BIT(TWCR, 5);
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x18, 1);
	// write data
	TWDR = data;
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x28, 2);
	// stop bit
	I2C_StopBit();
}

void I2C_init(void) {
	// bit rate 50k
	TWBR = 2;
}