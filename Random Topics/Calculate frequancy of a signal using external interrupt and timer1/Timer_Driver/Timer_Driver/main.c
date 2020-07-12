/*
 * Timer_Driver.c
 *
 * Created: 02/06/2020 01:16:31 
 * Author : Mohamed Abo Raia
 */ 
#define  F_CPU 1000000UL

#include "Dio.h"
#include "Timer.h"
#include "Timer_Registers.h"
#include "Common.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include <string.h>
#include <util/delay.h>
#include "Ext_interrputs_configs.h"
#include "Ext_interrupts.h"

void str_reverse(uint8 *str);

volatile uint8 high_value = 0;
volatile uint8 low_value  = 0;
volatile uint8 flag = 0;

ISR(INT0_vect) {
	high_value = TCNT1H;
	low_value =  TCNT1L;
	flag = 1;
}


int main(void) {
	
	Dio_init();
	Lcd_Init();
	Ext_interrupt_init();
	
	uint8 counter = 0;
	uint16 arr[10] = {0};
	uint16 result;
	uint8 output[10] = {'\0'}; 
	uint8 index = 0;	
	
	// configure normal mode
	CLR_BIT(TCCR1A, 0);
	CLR_BIT(TCCR1A, 1);
	CLR_BIT(TCCR1B, 3);
	CLR_BIT(TCCR1B, 4);
	// 1024 prescaler
	SET_BIT(TCCR1B, 0);
	SET_BIT(TCCR1B, 2);
			
	while (1) {
		while (counter < 10) {
			while (flag == 0);	
			flag = 0; 
			arr[counter] = low_value;
			arr[counter] |= high_value << 8;
			counter++;
		}
		result = arr[9] - arr[8];
		//result = 976 / result;
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
