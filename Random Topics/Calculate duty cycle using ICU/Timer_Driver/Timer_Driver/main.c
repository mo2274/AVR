/*
 * Timer_Driver.c
 *
 * Created: 02/06/2020 01:16:31 
 * Author : Mohamed Abo Raia
 */ 

#include "Dio.h"
#include "Timer.h"
#include "Timer_Registers.h"
#include "Common.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include <string.h>




void str_reverse(uint8 *str);

int main(void) {
	
	Dio_init();
	Lcd_Init();
	
	uint8 counter = 0;
	uint16 arr[10] = {0};
	uint32 result1;
	uint32 result2;
	uint32 result = 0;	
	uint8 output[10] = {'\0'}; 
	uint8 index = 0;	
	
	// configure normal mode
	CLR_BIT(TCCR1A, 0);
	CLR_BIT(TCCR1A, 1);
	CLR_BIT(TCCR1B, 3);
	CLR_BIT(TCCR1B, 4);
	// Raising edge
	SET_BIT(TCCR1B, 6);
	// no prescaler
	SET_BIT(TCCR1B, 0);
			
	while (1) {
		// calculate Pulse width
		while (counter < 5) {
			while ((TIFR & (1 << 5)) == 0);		
			SET_BIT(TIFR, 5);
			TCCR1B ^= (1 << 6);
			arr[counter] = ICR1L;
			arr[counter] |= (ICR1H << 8);
			counter++;
		}
		result1 = arr[4] - arr[3];
		counter = 0;
		// calculate the period
		while (counter < 5) {
			while ((TIFR & (1 << 5)) == 0);
			SET_BIT(TIFR, 5);
			arr[counter] = ICR1L;
			arr[counter] |= (ICR1H << 8);
			counter++;
		}		
		result2 = arr[4] - arr[3];
		// calculate duty cycle
		result = ((float32)result1 / (float32)result2) * 100.0;
		while (result > 0) {
			output[index] = result % 10 + 48;
			result /= 10;
			index++;
		}
		// display duty cycle
		str_reverse(output);
		Lcd_Out(output);
		Lcd_Out((uint8*)"% duty Cycle");
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
