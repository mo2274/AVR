/*
 * Timer_Registers.h
 *
 * Created: 02/06/2020 01:18:40 م
 *  Author: scc
 */ 


#ifndef TIMER_REGISTERS_H_
#define TIMER_REGISTERS_H_
#include "StdTypes.h"

/*---------> Timer0 Registers -----------*/
#define TCCR0    *((uint8 volatile*)0x53)
#define TCNT0    *((uint8 volatile*)0x52)
#define OCR0     *((uint8 volatile*)0x5C)

/*---------> Timer1 Registers -----------*/
#define TCCR1A    *((uint8 volatile*)0x4F)
#define TCCR1B    *((uint8 volatile*)0x4E)
#define TCNT1H    *((uint8 volatile*)0x4D)
#define TCNT1L    *((uint8 volatile*)0x4C)
#define OCR1AH    *((uint8 volatile*)0x4B)
#define OCR1AL    *((uint8 volatile*)0x4A)
#define OCR1BH    *((uint8 volatile*)0x49)
#define OCR1BL    *((uint8 volatile*)0x48)
#define ICR1H     *((uint8 volatile*)0x47)
#define ICR1L     *((uint8 volatile*)0x46)

/*---------> Timer2 Registers -----------*/
#define TCCR2    *((uint8 volatile*)0x45)
#define TCNT2    *((uint8 volatile*)0x44)
#define OCR2     *((uint8 volatile*)0x43)


#define TIMSK    *((uint8 volatile*)0x59)
#define TIFR     *((uint8 volatile*)0x58)


#endif /* TIMER_REGISTERS_H_ */