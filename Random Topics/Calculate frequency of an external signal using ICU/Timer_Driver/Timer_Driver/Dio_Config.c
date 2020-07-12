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
										
Dio_Config_t Dio_configuration = { { 	 
										  {OUTPUT, 0, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 1, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 2, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 3, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 4, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 5, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 6, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 7, PULL_UP, 0, &DDRB, &PORTB, &PINB},
											  
										  {OUTPUT, 0, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 1, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 2, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 3, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 4, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 5, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 6, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 7, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										// ICP
										  {INPUT, 6, PULL_UP, 0, &DDRD, &PORTD, &PIND}	  
											  											  	    		  											  		     
																						 }};
