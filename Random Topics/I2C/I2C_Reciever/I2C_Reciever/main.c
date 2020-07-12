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
	uint8_t data = 0;
	uint8 output[2] = {'\0'};
			
	Dio_init();
	Lcd_Init();
	I2C_init(100);
	
    while (1) {
		data = I2C_Rx();
		output[0] = data;
		Lcd_Out(output);
	}
}




