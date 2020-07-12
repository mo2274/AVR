/*
 * I2C.c
 *
 * Created: 08/07/2020 06:51:07
 *  Author: 
 */ 
#include "I2C.h"
#include "I2C_Registers.h"
#include "Common.h"
#include <avr/interrupt.h>


extern I2C_Config_t init;

extern volatile uint8 received_data[100];
extern volatile uint8 transmit_data[100];
extern volatile uint8 received_data_size;
extern volatile uint8 Transmit_data_size;


volatile uint8 index2 = 0;

bool I2C_init() {
	// set address
	TWAR = init.address << 1;
	// set bit rate
	TWBR = (init.freq - (init.bit_rate * 16)) / (init.bit_rate * 2);
	// enable I2C
	SET_BIT(TWCR, 2);
	// enable ACK
	SET_BIT(TWCR, 6);
	// clear start bit
	CLR_BIT(TWCR, 5);
	// clear stop bit
	CLR_BIT(TWCR, 4);
	// clear flag
	SET_BIT(TWCR, 7);	
	// enable interrupt for I2C
	SET_BIT(TWCR, 0);
	// enable global interrupt
	SET_BIT(SREG, 7);
	
	return SUCCESS;		
}

bool I2C_MasterTransmit(const uint8 slave_address) {
	// wait for the slave to be ready this time depends on the application
	_delay_ms(100);
	uint8 counter = 0;
	// check if no data to transmit
	if (Transmit_data_size <= 0) {
		return ERROR;
	}
	// disable interrupt for I2C
	CLR_BIT(TWCR, 0);
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
	TWDR = transmit_data[counter];
	counter++;
	// clear flag
	SET_BIT(TWCR, 7);
	// wait until the interrupt flag to be set
	while (GET_BIT(TWCR, 7) == 0);
	// send the rest bytes
	while (((TWSR & 0xF8) == 0x28) && counter < Transmit_data_size) {
		TWDR = transmit_data[counter];
		counter++;
		SET_BIT(TWCR, 7);
		while (GET_BIT(TWCR, 7) == 0);
	}
	// send Stop bit
	SET_BIT(TWCR, 4);
	SET_BIT(TWCR, 7);
	// enable interrupt
	SET_BIT(TWCR, 0);	
	return SUCCESS;
}


bool I2C_MasterReceive(const uint8 slave_address) {
	// wait for the slave to be ready this time depends on the application
	_delay_ms(100);	
	uint8 counter = 0;
	TWDR = 0x00;
	TWCR = 0x00;	
	// check if there is no data to receive 
	if (received_data_size <= 0) {
		return ERROR;
	}	
	// send start bit
	SET_BIT(TWCR, 5);
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
	while (GET_BIT(TWCR, 7) == 0);
	// check the status code
	if ((TWSR & 0xF8) != 0x08) {
		return ERROR;
	}
	// send slave address and read bit
	TWDR = (slave_address << 1) | 1;
	// clear start bit
	CLR_BIT(TWCR, 5);	
	// clear flag
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
	// wait until the interrupt flag to be set
	while (GET_BIT(TWCR, 7) == 0);
	// check the status code
	if ((TWSR & 0xF8) != 0x40) {
		return ERROR;
	}
	// receive data from the slave
	while (counter < (received_data_size - 1)) {
		_delay_us(25);
		// send ACK
		SET_BIT(TWCR, 6);
		// clear flag and enable
		SET_BIT(TWCR, 2);
		SET_BIT(TWCR, 7);
		// wait until the interrupt flag to be set
		while (GET_BIT(TWCR, 7) == 0);
		// check the status code
		if ((TWSR & 0xF8) != 0x50) {
			return ERROR;
		}
		received_data[counter++] = TWDR + 48;					
	} 
	_delay_us(25);
	// receive the last byte
	// send NACK
	CLR_BIT(TWCR, 6);
	// clear flag
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
	// wait until the interrupt flag to be set
	while (GET_BIT(TWCR, 7) == 0);
	// check the status code
	if ((TWSR & 0xF8) != 0x58) {
		return ERROR;
	}
	received_data[counter++] = TWDR + 48;	
	// send Stop bit
	SET_BIT(TWCR, 4);
	SET_BIT(TWCR, 2);
	SET_BIT(TWCR, 7);
	// enable interrupt
	SET_BIT(TWCR, 0);
	// enable ACK for slave operation
	SET_BIT(TWCR, 6);	
	return SUCCESS;
}

void I2C_SendData(uint8 data)
{
	TWDR = data;
}

ISR(TWI_vect) {
	// disable interrupt for I2C
	CLR_BIT(TWCR, 0);
	switch (TWSR & 0xF8) {
		// receive data
		case 0x60:
			SET_BIT(PORTA, 0);
			// clear flag
			SET_BIT(TWCR, 7);
			// wait until the flag is set
			while (GET_BIT(TWCR, 7) == 0);
			// check the status code
			while ((TWSR & 0xF8) == 0x80) {
				received_data[received_data_size] = TWDR + 48;
				received_data_size++;
				SET_BIT(TWCR, 7);
				// wait until the flag is set
				while (GET_BIT(TWCR, 7) == 0);
			}
			// clear flag
			SET_BIT(TWCR, 7);
			break;
		// transmit data	
		case 0xA8:
			// send the first byte as 0 
			TWDR = 0;
			// clear flag
			SET_BIT(TWCR, 7);
			// wait until the flag is set
			while (GET_BIT(TWCR, 7) == 0);
			// send the remaining data
			while (((TWSR & 0xF8) == 0xB8) && Transmit_data_size > 0) {
				TWDR = transmit_data[index2];
				Transmit_data_size--;
				index2++;
				// clear flag
				SET_BIT(TWCR, 7);
				// wait until the flag is set
				while (GET_BIT(TWCR, 7) == 0);				
			}	
			index2 = 0;			
			// clear flag
			SET_BIT(TWCR, 7);			
			break;	
		default:
			break;		
	}
	// enable interrupt
	SET_BIT(TWCR, 0);
}



