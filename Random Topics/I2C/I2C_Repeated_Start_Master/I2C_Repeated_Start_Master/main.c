/*
 * I2C_master.c
 *
 * Created: 01/07/2020 08:14:51 
 * Author : 
 */ 
#include "Dio.h"
#include "LCD.h"
#include "I2C.h"



int main(void)
{
	uint8 data_write = 6;
	uint8 data_read = 0;
	uint8 output[2] = {'\0'};
		
	Dio_init();	
	Lcd_Init();
	I2C_BitRate();
	I2C_StartBit();
	I2C_ClearFlagAndEnable();	
	I2C_WaitForTheFlagToBeSet();
	I2C_CheckStatusCode(0x08, 0);
	// send slave address and write
	I2C_SetSlaveAddress(0b00110010);
	I2C_ClearStartBit();
	I2C_ClearFlagAndEnable();
    I2C_WaitForTheFlagToBeSet();
	I2C_CheckStatusCode(0x18, 1);
	// flag set so the clock is disabled
	// send data
	TWDR = data_write;
	I2C_ClearFlagAndEnable();
	I2C_WaitForTheFlagToBeSet();
	I2C_CheckStatusCode(0x28, 2);		
	// send repeated start
	I2C_StartBit();
	I2C_ClearFlagAndEnable();
	I2C_WaitForTheFlagToBeSet();
	I2C_CheckStatusCode(0x10, 3);
	// send slave address and read
	I2C_SetSlaveAddress(0b00110011);
	I2C_ClearStartBit();
	I2C_ClearFlagAndEnable();
	I2C_WaitForTheFlagToBeSet();
	I2C_CheckStatusCode(0x40, 4);
	// send NACK
	I2C_NACK();
	I2C_ClearFlagAndEnable();
	I2C_WaitForTheFlagToBeSet();
	I2C_CheckStatusCode(0x58, 5);	
	data_read = TWDR;			
	// Stop bit
	I2C_StopBit();
	I2C_ClearFlagAndEnable();
	output[0] = data_read + 48;	
	Lcd_Out(output);
    while (1); 
}

