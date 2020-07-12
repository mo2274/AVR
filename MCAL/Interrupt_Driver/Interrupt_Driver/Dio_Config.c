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
										/* INT2 */
Dio_Config_t Dio_configuration = { { 	  {INPUT, 2, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										/* LCD Port */
										  {OUTPUT, 4, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 5, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 6, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 7, PULL_UP, 0, &DDRB, &PORTB, &PINB},
										  {OUTPUT, 0, PULL_UP, 0, &DDRA, &PORTA, &PINA},
										  {OUTPUT, 1, PULL_UP, 0, &DDRA, &PORTA, &PINA},											  
										/* INT0 */	  	  
										  {INPUT, 2, PULL_UP, 0, &DDRD, &PORTD, &PIND},
										/* INT1 */	  
										  {INPUT, 3, PULL_UP, 0, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 3, PULL_UP, 0, &DDRC, &PORTC, &PINC}											 },
									/* ports configuration */		     
																						 };
