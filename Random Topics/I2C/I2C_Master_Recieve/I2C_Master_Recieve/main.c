/*
 * I2C_master.c
 *
 * Created: 01/07/2020 08:14:51 
 * Author : 
 */ 
#include "Dio.h"
#include "LCD.h"
#include "I2C.h"
#include <util/delay.h>

volatile uint8 data[7] = {'\0'};
volatile uint8 data_size = 5;	

int main(void)
{
	int index = 0;
	Dio_init();	
	Lcd_Init();
	
	TWBR = 2;
	// send start bit
	SET_BIT(TWCR, 5);
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);	
	while (GET_BIT(TWCR, 7) == 0);
	if ((TWSR & 0xF8) == 0x08) {
		SET_BIT(PORTA, 0);
	} else {
		SET_BIT(PORTB, 0);
	}
	// set slave address and write bit
	TWDR = 0b00110011;
	// clear start bit
	CLR_BIT(TWCR, 5);
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
    while (GET_BIT(TWCR, 7) == 0);
	//I2C_CheckStatusCode(0x40, 1);
	if ((TWSR & 0xF8) == 0x40) {
		SET_BIT(PORTA, 1);
	} else {
		SET_BIT(PORTB, 1);
	}	
	// flag set so the clock is disabled	
	while (index < (data_size - 1)) {
		_delay_us(25);
		// send ACK
		SET_BIT(TWCR, 6);
		SET_BIT(TWCR, 2);
		SET_BIT(TWCR, 7);
		while (GET_BIT(TWCR, 7) == 0);
		if ((TWSR & 0xF8) == 0x50) {
			SET_BIT(PORTA, 2);
		} else {
			SET_BIT(PORTB, 2);
		}
		data[index] = TWDR + 48;
		index++;
	}	
	_delay_us(25);							
	// send NACK
	CLR_BIT(TWCR, 6);
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
	while (GET_BIT(TWCR, 7) == 0);
	//I2C_CheckStatusCode(0x40, 1);
	if ((TWSR & 0xF8) == 0x58) {
		SET_BIT(PORTA, 3);
		} else {
		SET_BIT(PORTB, 3);
	}	
	data[index] = TWDR + 48;
	index++;			
	// Stop bit
	SET_BIT(TWCR, 4);
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
	Lcd_Out(data);
    while (1); 
}

