/*
 * DIO Driver.c
 *
 * Created: 09/05/2020 06:00:46 
 */ 
#include "StdTypes.h"
#include "Common.h"
#include "Dio.h"
#include "Delay.h"
#include "Dio_Config.h"
#include "SevenSegment.h"
#include "KeyPad.h"
#include <util/delay.h>

extern Dio_Config_t default_configuration; 
bool Digital_Clock(void);

int main(void)
{	
	if (Dio_init(&default_configuration) == ERROR) {
		return ERROR;
	}
    while (1) {
		if (Digital_Clock() == ERROR) {
			return ERROR;
		}
	}
	return SUCCESS;
}



bool Digital_Clock(void) {
	int8 num1 = -1, num2 = -1;
	for (uint8 hours = 0; hours <= 12; hours++) {
		for (uint8 min = 0; min < 60; min++) {
			for (uint8 sec = 0; sec < 60; sec++) {
				for (int i = 0; i < 58; i++) {
					/* adjust the digital clock */
					
					if (keyPad_Read(PORT_A) == 'C') {
						/* read the hours */
						while (num1 < 0) {
							num1  = keyPad_Read(PORT_A) - 48;
							while ( num2 < 0) {
								num2  = keyPad_Read(PORT_A) - 48;
							}
						}
						hours = num2 * 10 + num1;
						num1 = -1;
						num2 = -1;
						/* read the minutes */
						while (num1 < 0) {
							num1  = keyPad_Read(PORT_A) - 48;
							while ( num2 < 0) {
								num2  = keyPad_Read(PORT_A) - 48;
							}
						}
						min = num2 * 10 + num1;
						num1 = -1;
						num2 = -1;
						/* read the seconds */
						while (num1 < 0) {
							num1  = keyPad_Read(PORT_A) - 48;
							while ( num2 < 0) {
								num2  = keyPad_Read(PORT_A) - 48;
							}
						}
						sec = num2 * 10 + num1;
						num1 = -1;
						num2 = -1;
					}
					if (Dio_Write_pin(5, PORT_D, 1) == ERROR) {
						return ERROR;
					}
					if (Dio_Write_pin(0, PORT_D, 0) == ERROR) {
						return ERROR;
					}
					if(SevenSeg_Display(sec / 10, PORT_C) == ERROR) {
						return ERROR;
					} 
					_delay_us(2600);
					if (Dio_Write_pin(0, PORT_D, 1) == ERROR) {
						return ERROR;
					}
					if (Dio_Write_pin(1, PORT_D, 0) == ERROR) {
						return ERROR;
					}
					if (SevenSeg_Display(sec % 10, PORT_C) == ERROR) {
						return ERROR;
					}
					_delay_us(2600);
					if (Dio_Write_pin(1, PORT_D, 1) == ERROR) {
						return ERROR;
					}
					if (Dio_Write_pin(2, PORT_D, 0) == ERROR) {
						return ERROR;
					}
					if (SevenSeg_Display(min / 10, PORT_C) == ERROR) {
						return ERROR;
					}
					_delay_us(2600);
					if (Dio_Write_pin(2, PORT_D, 1) == ERROR) {
						return ERROR;
					}
					if (Dio_Write_pin(3, PORT_D, 0) == ERROR) {
						return ERROR;
					} 
					if (SevenSeg_Display(min % 10, PORT_C) == ERROR) {
						return ERROR;
					}
					_delay_us(2600);
					if (Dio_Write_pin(3, PORT_D, 1)) {
						return ERROR;
					}
					if (Dio_Write_pin(4, PORT_D, 0) == ERROR) {
						return ERROR;
					}
					if (SevenSeg_Display(hours / 10, PORT_C) == ERROR) {
						return ERROR;
					}
					_delay_us(2600);
					if (Dio_Write_pin(4, PORT_D, 1) == ERROR) {
						return ERROR;
					}
					if (Dio_Write_pin(5, PORT_D, 0) == ERROR) {
						return ERROR;
					}
					if (SevenSeg_Display(hours % 10, PORT_C) == ERROR) {
						return ERROR;
					}
					_delay_us(2600);
				}
			}
		}
	}
	return SUCCESS;	
}