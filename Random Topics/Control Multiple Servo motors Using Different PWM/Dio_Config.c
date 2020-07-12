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
										  {OUTPUT, 0, PULL_UP, 1, &DDRD, &PORTD, &PIND},	  	  
										  {OUTPUT, 1, PULL_UP, 1, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 2, PULL_UP, 1, &DDRD, &PORTD, &PIND},
										  {OUTPUT, 3, PULL_UP, 1, &DDRD, &PORTD, &PIND}	  	  	  											  	    		  											  		     
																						 }};
