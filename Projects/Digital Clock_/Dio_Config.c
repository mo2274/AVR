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
									/* pins configuration */
Dio_Config_t default_configuration = { {  {OUTPUT, 0, PULL_UP, 1, &DDRD, &PORTD, &PIND},
									      {OUTPUT, 1, PULL_UP, 1, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 2, PULL_UP, 1, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 3, PULL_UP, 1, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 4, PULL_UP, 1, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 5, PULL_UP, 1, &DDRD, &PORTD, &PIND},
									/* KeyPad Port */		   
										  {INPUT,  4, PULL_UP, 1, &DDRA, &PORTA, &PINA},
										  {INPUT,  5, PULL_UP, 1, &DDRA, &PORTA, &PINA},
										  {INPUT,  6, PULL_UP, 1, &DDRA, &PORTA, &PINA},
									      {INPUT,  7, PULL_UP, 1, &DDRA, &PORTA, &PINA},
								     	  {OUTPUT, 0, PULL_UP, 1, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 1, PULL_UP, 1, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 2, PULL_UP, 1, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 3, PULL_UP, 1, &DDRA, &PORTA, &PINA},
									/* switch pin */
									      {INPUT,  0, PULL_UP, 1, &DDRB, &PORTB, &PINB}   },
									/* ports configuration */		     
									   {  {OUTPUT, PULL_UP, 0x00, &DDRC, &PORTC, &PINC}   }};
