/*
 * Dio_Config.c
 *
 * Created: 15/05/2020 05:37:47
 *  Author: 
 */ 
#include "StdTypes.h"
#include "Dio_Registers.h"
#include "Dio.h"
#include "Dio_Config.h"
									
										
Dio_Config_t Dio_configuration = {  // pins
									 {},
								    // ports
									{  {OUTPUT, NO_PULL_UP, 0, &DDRA, &PORTA, &PINA},
									   {OUTPUT, NO_PULL_UP, 0, &DDRD, &PORTD, &PIND},
									   {OUTPUT, NO_PULL_UP, 0, &DDRB, &PORTB, &PINB}  }      
										                                              };
