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

volatile static uint8 counter1 = 0;
volatile static uint8 high1 = 10;
volatile static uint8 low1 = 20;

volatile static uint8 counter2 = 0;
volatile static uint8 high2 = 5;
volatile static uint8 low2 = 25;

volatile static uint8 counter3 = 0;
volatile static uint8 high3 = 15;
volatile static uint8 low3 = 15;

volatile static uint8 counter4 = 0;
volatile static uint8 high4 = 12;
volatile static uint8 low4 = 18;

ISR(TIMER1_COMPA_vect) {
	counter1++;
	counter2++;
	counter3++;
	counter4++;
	// first signal
	if (counter1 == high1 && (PORTD & 1) == 1) {
		CLR_BIT(PORTD, 0);
		counter1 = 0;
	}
	if (counter1 == low1 && (PORTD & 1) == 0) {
		SET_BIT(PORTD, 0);
		counter1 = 0;
	}
	// second signal
	if (counter2 == high2 && ((PORTD & (1 << 1)) >> 1) == 1) {
		CLR_BIT(PORTD, 1);
		counter2 = 0;
	}
	if (counter2 == low2 && ((PORTD & (1 << 1)) >> 1) == 0) {
		SET_BIT(PORTD, 1);
		counter2 = 0;
	}
	// third signal
	if (counter3 == high3 && ((PORTD & (1 << 2)) >> 2) == 1) {
		CLR_BIT(PORTD, 2);
		counter3 = 0;
	}
	if (counter3 == low3 && ((PORTD & (1 << 2)) >> 2) == 0) {
		SET_BIT(PORTD, 2);
		counter3 = 0;
	}
	// fourth signal		
	if (counter4 == high4 && ((PORTD & (1 << 3)) >> 3) == 1) {
		CLR_BIT(PORTD, 3);
		counter4 = 0;
	}
	if (counter4 == low4 && ((PORTD & (1 << 3)) >> 3) == 0) {
		SET_BIT(PORTD, 3);
		counter4 = 0;
	}
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




