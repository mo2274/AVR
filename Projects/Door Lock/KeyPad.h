/*
 * KeyPad.h
 *
 * Created: 27/04/2020 06:22:32 
 *  Author: 
 */ 

#include "common.h"
#include <avr/io.h>

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KeyPadPORT PORTD
#define KeyPadDDR  DDRD
#define KeyPadPIN  PIND 
/*
 *
 *
 * 
 *  
 */ 
void keyPadInit(void);
/*
 * 
 *
 *  
 *  
 */ 
char readKey(void);

#endif /* KEYPAD_H_ */