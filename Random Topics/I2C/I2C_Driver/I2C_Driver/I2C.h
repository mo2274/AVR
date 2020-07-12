/*
 * I2C.h
 *
 * Created: 08/07/2020 06:51:24 م
 *  Author: scc
 */ 
#define  F_CPU 1000000UL

#ifndef I2C_H_
#define I2C_H_
#include "StdTypes.h"
#include "Common.h"
#include <util/delay.h>


typedef struct {
	uint32 freq;
	uint32 bit_rate;
	uint8  address;
}I2C_Config_t;


bool I2C_init();
bool I2C_MasterTransmit(const uint8 slave_address);
bool I2C_MasterReceive(const uint8 slave_address);

#endif /* I2C_H_ */