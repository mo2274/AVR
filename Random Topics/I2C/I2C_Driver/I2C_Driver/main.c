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


extern volatile uint8 received_data[100];
extern volatile uint8 transmit_data[100];
extern volatile uint8 received_data_size;
extern volatile uint8 Transmit_data_size;


int main(void)
{	
	Dio_init();
	Lcd_Init();
	I2C_init();  
	
	Transmit_data_size = 10;
	transmit_data[0] = 6;
	transmit_data[1] = 6;
	transmit_data[2] = 6;
	transmit_data[3] = 6;
	transmit_data[4] = 6;
	transmit_data[5] = 6;
	transmit_data[6] = 6;
	transmit_data[7] = 6;
	transmit_data[8] = 6;
	transmit_data[9] = 6;
	I2C_MasterTransmit(0b0011001); 
	   
	  
    while (1) {
		if (received_data_size > 0) {
			Lcd_Out(received_data);
			received_data_size = 0;
		}
	}
}

