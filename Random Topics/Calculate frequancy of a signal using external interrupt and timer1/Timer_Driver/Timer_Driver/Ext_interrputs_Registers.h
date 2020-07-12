/*
 * Ext_interrputs_Registers.h
 *
 * Created: 18/05/2020 04:13:29 
 *  Author: Mohamed Abo Raia
 */ 


#ifndef EXT_INTERRPUTS_REGISTERS_H_
#define EXT_INTERRPUTS_REGISTERS_H_

#include "StdTypes.h"

/* External interrupts registers */

#define MCUCR    *((volatile uint8*)0x55)
#define MCUCSR   *((volatile uint8*)0x54)
#define GICR     *((volatile uint8*)0x5B)
#define GIFR     *((volatile uint8*)0x5A)
#define SREG     *((volatile uint8*)0x5F)

#endif /* EXT_INTERRPUTS_REGISTERS_H_ */