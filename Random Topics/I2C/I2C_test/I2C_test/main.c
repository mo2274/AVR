/*
 * I2C_test.c
 *
 * Created: 20/06/2020 08:15:58 م
 * Author : scc
 */ 

#define F_CPU  1000000UL
#include <avr/io.h>
#include "Common.h"
#include <util/delay.h>

#define LED (0)

void I2C_Error(uint8_t num)
{	
	while (1) {
		PORTA ^= 1 << num;
		_delay_ms(500);	
	}
}

void I2C_Check_StatusCode(uint8_t status_code, uint8_t num)
{
	// check if the status code is correct
	if ((TWSR & 0xF8) != status_code) {
		I2C_Error(num);
	}
}

void I2C_Clear_INT_AndEnable()
{
	/* clear the interrupt flag */
	SET_BIT(TWCR, 7);
	/*  enable the TWI */
	SET_BIT(TWCR, 2);
}

void I2C_StartBit()
{
	/* start bit */
	SET_BIT(TWCR, 5);
}

void I2C_Wait_Until_Flag_Set()
{
	while(GET_BIT(TWCR, 7) == 0);
}

void I2C_StopBit()
{
	SET_BIT(TWCR, 4);
}

void I2C_StopBit_Disable()
{
	CLR_BIT(TWCR, 4);
}

void I2C_Tx(uint8_t data, uint8_t address);
void I2C_send_string(uint8_t* data, uint8_t address);

int main(void)
{
	DDRA = 0xFF;
	_delay_ms(31);
	// bit rate 50k
	TWBR = 2;


	I2C_Tx('m', 100); 
	_delay_ms(10);
	I2C_send_string((uint8_t*)"d", 200); 
	_delay_ms(70);
	I2C_send_string((uint8_t*)"mohamed", 200);	

	
    while (1); 
  
}


void I2C_Tx(uint8_t data, uint8_t address) {
	/*---------- start bit --------*/
	TWDR = 0x00;
	TWCR = 0x00;
	I2C_StartBit();
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x08, 0);
	/*-------- SLA + W---------*/
	TWDR = address;
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


void I2C_send_string(uint8_t* data, uint8_t address) {
	/*---------- start bit --------*/
	TWDR = 0x00;
	TWCR = 0x00;
	I2C_StartBit();
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x08, 0);
	/*-------- SLA + W---------*/
	TWDR = address;
	// clear the start bit
	CLR_BIT(TWCR, 5);
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x18, 1);
	// write data
	while (*data != '\0') {
		TWDR = *data;
		I2C_Clear_INT_AndEnable();
		I2C_Wait_Until_Flag_Set();
		I2C_Check_StatusCode(0x28, 2);
		data++;
	}
	// stop bit
	I2C_StopBit();
}
