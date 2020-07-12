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
	uint8 data = 0;
	uint8 output[2] = {'\0'};
	Dio_init();
	// set slave address
	TWAR = 0b00110010;
	
	
    
    while (1) {
		TWCR = 0x00;
		TWDR = 0x00;
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
		// receive
		if ((TWSR & 0xF8) == 0x60) {
			SET_BIT(PORTA, 0);
   			// clear flag
   			SET_BIT(TWCR, 7);
   			// wait until the flag is set
   			while (GET_BIT(TWCR, 7) == 0);
   			// check the status code
   			if ((TWSR & 0xF8) == 0x88) {
	   			SET_BIT(PORTA, 1);
	   		} else {
	   			SET_BIT(PORTD, 1);
   			}
   			CLR_BIT(TWCR, 7);
   			data = TWDR + 48;
   			output[0] = data;
   			Lcd_Init();
   			Lcd_Out(output);			
		// transmit	
		} else if ((TWSR & 0xF8) == 0xA8) {
			SET_BIT(PORTD, 0);
			TWDR = 3;
		    SET_BIT(TWCR, 7);
			while (GET_BIT(TWCR, 7) == 0);
   			if ((TWSR & 0xF8) == 0xC0) {
	   			SET_BIT(PORTA, 2);
	   		} else {
	   			SET_BIT(PORTD, 2);
   			}					
		// error	
		} else {
			SET_BIT(PORTD, 7);
		}		
	}
}

void Slave_init(void) {
	
}