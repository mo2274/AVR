/*
 * Timer_Driver.c
 *
 * Created: 02/06/2020 01:16:31 
 * Author : Mohamed Abo Raia
 */ 
#define  F_CPU 1000000UL

#include "Dio.h"
#include "Timer.h"
//#include "Timer_Registers.h"
#include "Common.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include <string.h>
#include "Ext_interrputs_configs.h"
#include "Ext_interrupts.h"
#include <avr/io.h>
#include <stdio.h>
void str_reverse(uint8 *str);
void int_Tostring(uint8 output[], uint32 integer);

volatile uint16 arr[3];
volatile uint8 counter = 0;
volatile uint32 counter1 = 0;

ISR(INT0_vect) {
	arr[counter] = TCNT0 + counter1;
	MCUCR ^= 1;
	counter++;
	
}

ISR(TIMER0_OVF_vect) {
	counter1 += 256;
}

int main(void) {
	
	Dio_init();
	Lcd_Init();
	Ext_interrupt_init();
	uint32 result;
	uint8 output[20] = {'\0'};
	// configure normal mode
	CLR_BIT(TCCR0, 3);
	CLR_BIT(TCCR0, 6);
	// no prescaler
	SET_BIT(TCCR0, 0);
	// enable interrupt
	SET_BIT(TIMSK, 0);
	SET_BIT(SREG, 7);
			
	while (1) {
		
		if (counter >= 3) {
			Disable_Global_Interrupt();
			result = arr[0];
			int_Tostring(output, result);
			str_reverse(output);
			Lcd_Out(output);
			Lcd_Out((uint8*)"% duty cycle");
			while (1);	
		}
		//result = ((arr[1] - arr[0]) / (arr[2] - arr[0])) * 100;
		

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

void int_Tostring(uint8 output[], uint32 integer) {
	uint8 index = 0;
	while (integer > 0) {
		output[index] = integer % 10 + 48;
		integer /= 10;
		index++;
	}	
}