/*
 * Delay.h
 *
 * Created: 11/05/2020 07:12:29 
 *  Author: Mohamed Abo Raia
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include "StdTypes.h"

#define CLOCK        (1000000)
#define ERROR_RATIO  (13)

#define DELAY_MS(n)   {for (uint32 i = (CLOCK / 1000) * n / ERROR_RATIO; i > 0; i--) {__asm("NOP");}} 

#endif /* DELAY_H_ */