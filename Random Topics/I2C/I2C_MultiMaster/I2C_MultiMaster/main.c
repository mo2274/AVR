/*
 * I2C_master.c
 *
 * Created: 01/07/2020 08:14:51 م
 * Author : scc
 */ 

#include <avr/io.h>
#include "Common.h"
#include "Dio.h"
#include <util/delay.h>
#include "LCD.h"


int main(void)
{
	uint8 data = 5;
	uint8 output[2] = {'\0'};
	
	Dio_init();
	Lcd_Init();
	_delay_ms(2000);
	// adjust bit rate
	TWBR = 2; // 50k bit per second
	// start bit
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 5);
	SET_BIT(TWCR, 7);	
	while (GET_BIT(TWCR, 7) == 0);
	if ((TWSR & 0xF8) == 0x08) {
		SET_BIT(PORTA, 0);
	} else {
		SET_BIT(PORTB, 0);
	}
	// SLA + R  0b0011001 0
	TWDR = 0b00110011;
	// clear start bit
	CLR_BIT(TWCR, 5);
	// clear flag and enable	
	SET_BIT(TWCR, 7);
	SET_BIT(TWCR, 2);
	while (GET_BIT(TWCR, 7) == 0);
	if ((TWSR & 0xF8) == 0x40) {
		SET_BIT(PORTA, 1);
	} else  {
		SET_BIT(PORTD, 1);
		// Stop bit
		SET_BIT(TWCR, 4);
		SET_BIT(TWCR, 7);		
	}
	// send NACK
	SET_BIT(TWCR, 2);
	CLR_BIT(TWCR, 6);
	SET_BIT(TWCR, 7);
	while (GET_BIT(TWCR, 7) == 0);
	if ((TWSR & 0xF8) == 0x58) {
		SET_BIT(PORTA, 1);
	} else  {
		SET_BIT(PORTD, 1);
		// Stop bit
		SET_BIT(TWCR, 4);
		SET_BIT(TWCR, 7);
	}	
	// Data
	data = TWDR;
    // Stop bit
	SET_BIT(TWCR, 4);
	SET_BIT(TWCR, 7);
	
	output[0] = data + 48;
	Lcd_Out(output);
	
    while (1); 
}

