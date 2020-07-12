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


int main(void) {
	
	Dio_init();
	
	// CTC mode
	CLR_BIT(TCCR1A, 0);
	CLR_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	CLR_BIT(TCCR1B, 4);
	// Compare match value for OC1A
	OCR1AH = 0x4E;
	OCR1AL = 0x1F;
	// enable compare match interrupt for timer1
	SET_BIT(TIMSK, 4);
	SET_BIT(SREG, 7);
	// set 1 prescaler
	TCCR1B |= 0x1;
				
	while (1) {
		if (((TCNT1H << 8) | TCNT1L) >= 800 && ((TCNT1H << 8) | TCNT1L) < 5400) {
			if(((TCNT1H << 8) | TCNT1L) >= 1000 && ((PORTD & 1) == 1)) {
				CLR_BIT(PORTD, 0);
			}
			if(((TCNT1H << 8) | TCNT1L) >= 2000 && (((PORTD & (1 << 1)) >> 1) == 1)) {
				CLR_BIT(PORTD, 1);
			}
			if(((TCNT1H << 8) | TCNT1L) >= 3000 && (((PORTD & (1 << 2)) >> 2) == 1)) {
				CLR_BIT(PORTD, 2);
			}
			if(((TCNT1H << 8) | TCNT1L) >= 4000 && (((PORTD & (1 << 3)) >> 3) == 1)) {
				CLR_BIT(PORTD, 3);
			}		
		}

	}
	
	return 0;
}

ISR(TIMER1_COMPA_vect) {
	SET_BIT(PORTD, 0);
	SET_BIT(PORTD, 1);
	SET_BIT(PORTD, 2);
	SET_BIT(PORTD, 3);	
}

