/*
 * KeyPad.h
 *
 * Created: 27/04/2020 06:22:32 
 *  Author: 
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "StdTypes.h"
/*
 *		 keyPad_Read
 * The function is used to read a key from keypad
 * @param: the function will take the port name (PORT_A, PORT_B, PORT_C, PORT_D) 
 * @return: the function will return the key if everything done correctly and null character otherwise. 
 */ 
uint8 keyPad_Read(Port_t port_name);

#endif /* KEYPAD_H_ */