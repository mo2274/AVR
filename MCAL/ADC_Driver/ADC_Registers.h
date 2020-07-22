/*
 * ADC_Registers.h
 *
 * Created: 19/07/2020 10:39:51 
 *  Author: Mohamed Abo Raia
 */ 
#ifndef ADC_REGISTERS_H_
#define ADC_REGISTERS_H_
#include "StdTypes.h"

#define ADMUX     *((volatile uint8*)0x27)
#define ADCSRA    *((volatile uint8*)0x26)
#define ADCH      *((volatile uint8*)0x25)
#define ADCL      *((volatile uint8*)0x24)
#define SFIOR     *((volatile uint8*)0x50)

#endif /* ADC_REGISTERS_H_ */