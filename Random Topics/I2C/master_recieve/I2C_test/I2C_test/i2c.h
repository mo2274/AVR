/*
 * i2c.h
 *
 * Created: 28/06/2020 09:21:25 
 *  Author: 
 */ 
#define F_CPU  1000000UL
#include <stdint.h>

#ifndef I2C_H_
#define I2C_H_


void I2C_init(void);
static void I2C_Tx(uint8_t data);


#endif /* I2C_H_ */