/*
 * I2C.c
 *
 * Created: 28/06/2020 08:52:57 م
 *  Author: scc
 */ 
#include <avr/io.h>
#include "Dio.h"
#include "Common.h"




void I2C_Check_StatusCode(uint8_t status_code, uint8_t num)
{
	if ((TWSR & 0xF8) == status_code) {
		SET_BIT(PORTA, num);
	} else {
		SET_BIT(PORTD, num);
	}
}

void I2C_Clear_INT_AndEnable()
{
	/* clear the interrupt flag */
	SET_BIT(TWCR, 7);
	/*  enable the TWI */
	SET_BIT(TWCR, 2);
}


void I2C_Wait_Until_Flag_Set(uint8_t num)
{
	while(GET_BIT(TWCR, 7) == 0) {
		PORTD ^= 1 << num;
	}
}

uint8_t I2C_Rx(void) {
	uint8_t data = 0;
	// enable bit
	I2C_Clear_INT_AndEnable();
	// ACK enable
	SET_BIT(TWCR, 6);
	// clear start bit
	CLR_BIT(TWCR, 5);
	// clear stop bit
	CLR_BIT(TWCR, 4);
	I2C_Wait_Until_Flag_Set(0);
	I2C_Check_StatusCode(0x60, 0);
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set(1);
	I2C_Check_StatusCode(0x80, 1);
	data = TWDR;
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set(2);
	I2C_Check_StatusCode(0xA0, 2);
	return data;
}

void I2C_init(uint8_t address) {
	TWAR = address;
}