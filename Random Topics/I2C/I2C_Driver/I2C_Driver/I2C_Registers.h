/*
 * I2C_Registers.h
 *
 * Created: 08/07/2020 07:00:03 م
 *  Author: scc
 */ 


#ifndef I2C_REGISTERS_H_
#define I2C_REGISTERS_H_

#include "StdTypes.h"

#define TWDR   *((volatile uint8*) 0x23)
#define TWCR   *((volatile uint8*) 0x56)
#define TWAR   *((volatile uint8*) 0x22)
#define TWBR   *((volatile uint8*) 0x20)
#define TWSR   *((volatile uint8*) 0x21)

#endif /* I2C_REGISTERS_H_ */