/*
 * I2C_slave.c
 *
 * Created: 01/07/2020 08:17:25
 * Author : 
 */ 

#include "I2C.h"
#include "Dio.h"



int main(void)
{	
	Dio_init();
	Slave_init();
	I2C_SendData(7);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xB8, 1);
	I2C_SendData(6);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xB8, 2);
	I2C_SendData(1);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xB8, 2);
	I2C_SendData(2);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xB8, 2);		
	I2C_SendData(3);
	I2C_ClearFlag();
	I2C_WaitUtilFlagToBeSet();
	I2C_CheckStatusCode(0xC0, 3);		
    while (1);
	return 0;
}

