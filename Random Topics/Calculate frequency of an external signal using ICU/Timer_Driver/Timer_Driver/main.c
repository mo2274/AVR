/*
 * Timer_Driver.c
 *
 * Created: 02/06/2020 01:16:31 
 * Author : Mohamed Abo Raia
 */ 

#define F_CPU  1000000UL

#include "Dio.h"
#include "Timer.h"
#include "Timer_Registers.h"
#include "Common.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include <string.h>
#include <util/delay.h>

void str_reverse(uint8 *str);
volatile uint32 count = 0;

ISR(TIMER1_OVF_vect) {
	count += 65536;
}

int main(void) {
	
	Dio_init();
	Lcd_Init();
	
	uint8 counter = 0;
	uint16 arr[10] = {0};
	uint32 result;
	uint8 output[10] = {'\0'}; 
	uint8 index = 0;	
	
	// configure normal mode
	CLR_BIT(TCCR1A, 0);
	CLR_BIT(TCCR1A, 1);
	CLR_BIT(TCCR1B, 3);
	CLR_BIT(TCCR1B, 4);
	// Falling edge
	CLR_BIT(TCCR1B, 6);
	// 1024 prescaler
	SET_BIT(TCCR1B, 0);
	SET_BIT(TCCR1B, 2);
	// enable over flow interrupt
	SET_BIT(TIMSK, 2);
	// enable global interrupt
	SET_BIT(SREG, 7);
			
	while (1) {
		while (counter < 5) {
			while ((TIFR & (1 << 5)) == 0);		
			SET_BIT(TIFR, 5);
			arr[counter] = ICR1L;
			arr[counter] |= (ICR1H << 8);
			arr[counter] += count;
			counter++;
		}
		result = arr[4] - arr[3];
		result = (F_CPU / 1024) / result;
		while (result > 0) {
			output[index] = result % 10 + 48;
			result /= 10;
			index++;
		}
		
		str_reverse(output);
		Lcd_Out(output);
		Lcd_Out((uint8*)"Hz");
		while (1);

	}

	
	return 0;
}

void str_reverse(uint8 *str) {
	uint8 start = 0;
	uint8 end = strlen((char*)str) - 1;
	uint8 temp;

	while (end > start) {
		temp = str[end];
		str[end] = str[start];
		str[start] = temp;
		end--;
		start++;
	}
}
