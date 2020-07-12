/*
 * DIO Driver.c
 *
 * Created: 09/05/2020 06:00:46 
 */ 

#include "Registers.h"
#include "StdTypes.h"
#include "Common.h"
#include "Dio.h"
#include "Delay.h"
#include "Dio_Config.h"

extern Dio_Config_t default_configuration; 

int main(void)
{
	uint8 data;
	bool status;
	
	Dio_init(&default_configuration);
	
    while (1) {
		Dio_Read_pin(1, A, &data);
		status = Dio_Write_pin(2, B, data);
		if (status == ERROR) {
			SET_BIT(PORTB, 6);
		}
		Dio_Read_port(D, &data);
		Dio_Write_port(C, data);
		DELAY_MS(1000);
		Dio_Write_port(C, 0x00);
		DELAY_MS(1000);
    }
}

