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
#include "StdTypes.h"

bool I2C_MasterTransmit(const uint8 slave_address, const uint8 data[], const uint8 data_size );

int main(void)
{
	Dio_init();
	uint8 data[4] = {1, 2, 3, 4};	
	_delay_ms(6000);
	// adjust bit rate
	TWBR = 2; // 50k bit per second  0b0011101 
	I2C_MasterTransmit(0b0011101, data, 4); 
		
    while (1); 
}


bool I2C_MasterTransmit(const uint8 slave_address, const uint8 data[], const uint8 data_size ) {
	uint8 counter = 0;
	// send start bit
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 5);
	SET_BIT(TWCR, 7);
	// wait until the interrupt flag to be set
	while (GET_BIT(TWCR, 7) == 0);
	// check the status code
	if ((TWSR & 0xF8) != 0x08) {
		return ERROR;
	}
	// send slave address and write bit
	TWDR = slave_address << 1;
	// clear start bit
	CLR_BIT(TWCR, 5);
	// clear flag
	SET_BIT(TWCR, 7);
	// wait until the interrupt flag to be set
	while (GET_BIT(TWCR, 7) == 0);
	// check the status code
	if ((TWSR & 0xF8) != 0x18) {
		return ERROR;
	}	
	// send the first Data byte
	TWDR = data[counter];
	counter++;
	// clear flag
	SET_BIT(TWCR, 7);
	// wait until the interrupt flag to be set	
	while (GET_BIT(TWCR, 7) == 0);
	// send the rest bytes
	while (((TWSR & 0xF8) == 0x28) && counter < data_size) {
		TWDR = data[counter];
		counter++;
		SET_BIT(TWCR, 7);
		while (GET_BIT(TWCR, 7) == 0);
	}
	// send Stop bit
	SET_BIT(TWCR, 4);
	SET_BIT(TWCR, 7);	
	return SUCCESS; 
}