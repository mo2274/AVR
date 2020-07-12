/*
 * Common.h
 *
 * Created: 11/05/2020 05:42:43 
 *  Author: Mohamed Abo Raia
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#define SET_BIT(reg, n)     ((reg) |= (1 << (n)))
#define CLR_BIT(reg, n)     ((reg) &= ~(1 << (n)))
#define GET_BIT(reg, n)     (((reg) & (1 << (n))) >> (n))
#define TOGGLE_BIT(reg, n)  ((reg) ^= 1 << (n))



#endif /* COMMON_H_ */