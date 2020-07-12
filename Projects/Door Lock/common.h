/*
 * coomon.h
 *
 * Created: 23/04/2020 05:20:33 ص
 *  Author: scc
 */ 


#ifndef COOMON_H_
#define COOMON_H_


#define SETBET(reg, n)  ((reg) |= (1 << (n)))
#define CLRBET(reg, n)  ((reg) &= ~(1 << (n)))
#define GETBET(reg, n)  ((reg) & (1 << (n)))



#endif /* COOMON_H_ */