/*
 * I2C_slave.c
 *
 * Created: 01/07/2020 08:17:25
 * Author : 
 */ 

#include "I2C.h"
#include "Dio.h"
#include "LCD.h"



int main(void)
{	
	uint8 data_read = 0;
	uint8 data_write = 5;
	uint8 output[2] = {'\0'};
	
	Dio_init();
	Slave_init();
	// send ACK
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0x80, 1);
	data_read = TWDR;
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xA0, 2);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xA8, 3);
	I2C_SendData(data_write);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xC0, 4);
	Lcd_Init();
	output[0] = data_read + 48;
	Lcd_Out(output);		
    while (1);
	return 0;
}

