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
#include "LCD.h"
#include "Dio.h"


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
uint8_t I2C_Rx(uint8_t address);

int main(void)
{
	Dio_init();
	Lcd_Init();
	// bit rate 50k
	TWBR = 2;
	uint8_t data;
	uint8_t output[2] = {'\0'};
		
	data = I2C_Rx(98);
	output[0] = data;
	Lcd_Out(output);	
		
    while (1); 
  
}


uint8_t I2C_Rx(uint8_t address) {
	uint8_t data = 0;
	/*---------- start bit --------*/
	TWDR = 0x00;
	I2C_StartBit();
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x08, 0);
	/*-------- SLA + R---------*/
	// address << 1 | 1
	TWDR = 0b00110011;
	// clear the start bit
	CLR_BIT(TWCR, 5);
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x40, 1);
	//_delay_us(2);
	// write data
	data = TWDR;
	// send NACKs
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set();
	I2C_Check_StatusCode(0x58, 2);
	// stop bit
	I2C_StopBit();
	return data;	
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
