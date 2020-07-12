/*
 * Timer_Driver.c
 *
 * Created: 02/06/2020 01:16:31 
 * Author : Mohamed Abo Raia
 */ 

#include "Dio.h"
#include "Timer_Registers.h"
#include "Common.h"
#include <avr/interrupt.h>



ISR(TIMER1_COMPA_vect) {
	PORTD ^= 1;
}

int main(void) {
	
	Dio_init();
	
	// CTC mode
	CLR_BIT(TCCR1A, 0);
	CLR_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	CLR_BIT(TCCR1B, 4);
	// Compare match value for OC1A
	OCR1AH = 0x03;
	OCR1AL = 0xE8;
	// enable compare match interrupt for timer1
	SET_BIT(TIMSK, 4);
	SET_BIT(SREG, 7);
	// set 1 prescaler
	TCCR1B |= 0x1;
				
	while (1);
	
	return 0;
}




