/*
 * I2C.c
 *
 * Created: 28/06/2020 08:52:57 م
 *  Author: scc
 */ 
#include <avr/io.h>
#include "Dio.h"
#include "Common.h"




static void I2C_Check_StatusCode(uint8_t status_code, uint8_t num)
{
	if ((TWSR & 0xF8) == status_code) {
		SET_BIT(PORTA, num);
	} else {
		SET_BIT(PORTD, num);
	}
}

static void I2C_Clear_INT_AndEnable()
{
	/* clear the interrupt flag */
	SET_BIT(TWCR, 7);
	/*  enable the TWI */
	SET_BIT(TWCR, 2);
}


static void I2C_Wait_Until_Flag_Set(uint8_t num)
{
	while(GET_BIT(TWCR, 7) == 0) {
		PORTD ^= 1 << num;
	}
}

uint8_t* I2C_Rx(void) {
	static uint8_t data[100] = {'\0'};
	int index = 0;	
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
	

	while (1) {
		I2C_Clear_INT_AndEnable();
		I2C_Wait_Until_Flag_Set(1);
		if ((TWSR & 0xF8) == 0x80) {
			SET_BIT(PORTA, 3);
		} else if ((TWSR & 0xF8) == 0xA0) {
			break;
			SET_BIT(PORTD, 3);
		}
		data[index] = TWDR;
		index++;
	}
	
	return data;
}

void I2C_init(uint8_t address) {
	TWAR = address;
}