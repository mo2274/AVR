/*
 * I2C_test.c
 *
 * Created: 20/06/2020 08:15:58 م
 * Author : scc
 */ 



#include "Common.h"
#include "Dio.h"
#include "LCD.h"
#include "StdTypes.h"
#include <avr/io.h>
#include "i2c.h"

int main(void)
{
	DDRA = 0x00;
	DDRD = 0x00;
	// enable
	SET_BIT(TWCR, 2);
	// enable ACK
	SET_BIT(TWCR, 6);
	// clear start bit
	CLR_BIT(TWCR, 5);
	// clr stop bit
	CLR_BIT(TWCR, 4);
	// set slave address
	TWAR = 0b00110010;
	// wait until the  slave is addressed by the transmitter
	I2C_Wait_Until_Flag_Set(0);
	I2C_Check_StatusCode(0xA8, 0);
	TWDR = 'a';
	I2C_Clear_INT_AndEnable();
	I2C_Wait_Until_Flag_Set(1);
	I2C_Check_StatusCode(0xC0, 1);
			
    while (1);
}




