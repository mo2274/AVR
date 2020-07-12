/*
 * I2C_Config.c
 *
 * Created: 08/07/2020 06:56:21 م
 *  Author: scc
 */ 
#include "I2C.h"

I2C_Config_t init = {  // freq 1MHz
						1000000,
                       // bit rate 50KHz
					   50000,
					   // address
					   0b00111010 
					                 };