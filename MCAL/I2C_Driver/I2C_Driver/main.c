/*
 * I2C_slave.c
 *
 * Created: 01/07/2020 08:17:25 
 * Author :
 */ 

#include <avr/io.h>
#include "Common.h"
#include "StdTypes.h"
#include "Dio.h"
#include "LCD.h"
#include "I2C.h"



volatile uint8 received_data[100] = {0};
volatile uint8 transmit_data[100] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
volatile uint8 received_data_size = 0;
volatile uint8 Transmit_data_size = 9;


int main(void)
{	
	Dio_init();
	Lcd_Init();
	I2C_init();
	
	I2C_MasterTransmit(0b0011001);
		  
    while (1) {
		if (received_data_size > 0) {
			Lcd_Out(received_data);
			received_data_size = 0;
		}
	};
}

