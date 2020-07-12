/*
 * I2C_slave.c
 *
 * Created: 01/07/2020 08:17:25 م
 * Author : scc
 */ 

#include <avr/io.h>
#include "Common.h"
#include "StdTypes.h"
#include "Dio.h"
#include "LCD.h"

void Slave_init(void);

int main(void)
{
	uint8 data[100] = {'\0'};
	int index = 0;	
	
	Dio_init();
	Slave_init();
	// clear flag
	SET_BIT(TWCR, 7);
	// wait until the flag is set
	while (GET_BIT(TWCR, 7) == 0);
	// check the status code
	while ((TWSR & 0xF8) == 0x80) {
		data[index] = TWDR + 48;
		index++;
		SET_BIT(TWCR, 7);
		// wait until the flag is set
		while (GET_BIT(TWCR, 7) == 0);
	}

	Lcd_Init();
	Lcd_Out(data);
	
    
    while (1);
}

void Slave_init(void) {
	// set slave address
	TWAR = 0b00110010;
	// enable
	SET_BIT(TWCR, 2);
	// enable ACK
	SET_BIT(TWCR, 6);
	// clear start bit
	CLR_BIT(TWCR, 5);
	// clear stop bit
	CLR_BIT(TWCR, 4);
	// wait until the flag is set
	while (GET_BIT(TWCR, 7) == 0);
	// check status code
	if ((TWSR & 0xF8) == 0x60) {
		SET_BIT(PORTA, 0);
	} else {
		SET_BIT(PORTD, 0);
	}	
}