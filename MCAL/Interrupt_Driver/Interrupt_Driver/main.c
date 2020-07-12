/*
 * Simple Calculator
 *
 * Created: 17/05/2020 01:15:19 
 * Author :	Mohamed Abo Raia
 */ 
#include "Dio.h"
#include "LCD.h"
#include "KeyPad.h"
#include "StdTypes.h"
#include "Delay.h"
#include "Common.h"
#include <stdlib.h>
#include <string.h>
#include "Ext_interrputs_configs.h"
#include "Ext_interrupts.h"


void func1(void) {
	Lcd_Out((uint8*)"mohamed");
	DELAY_MS(1000);
	Lcd_ClrScreen();
}




uint8* calc(uint8 *data);

int main(void)
{	
	if (Dio_init() == ERROR) {
		return 1;
	}
	if (Lcd_Init() == ERROR) {
		return ERROR;
	}
	
	Ext_interrupt_init(); 

	if (Ext_interrupt0_Function(&func1) == ERROR) {
		return ERROR;
	}
	
	Lcd_Out((uint8*)"mmmmmmm");
	DELAY_MS(1000);
	
    while (1) {
		Lcd_Out((uint8*)"bbbbbbbbbbbb");
		DELAY_MS(1000);
		Lcd_ClrScreen();
	}
	
	return 0;
}




/* function to reverse a string */
void strReverse(uint8 *str) {
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

/* function to calculate the result */
uint8* calc(uint8 *data) {
	uint32 numbers[20];
	uint8 index1 = 0;
	uint8 number[10] = {'\0'};
	uint8 index = 0;
	uint8 operators[10];
	uint8 operator_index = 0;
	uint32 result = numbers[0];
	static uint8 final_result[10] = {'\0'};
	uint8 index3 = 0;

	/* extract the numbers and the operators in different arrays */
	for (uint8 i = 0; data[i] != '\0'; i++) {
		if (data[i] >= '0' && data[i] <= '9') {
			number[index] = data[i];
			index++;
			} else {
			numbers[index1] = atoi((const char*)number);
			operators[operator_index] = data[i];
			operator_index++;
			index1++;
			index = 0;
			memset(number, '\0', sizeof(number));
		}
	}
	numbers[index1] = atoi((const char*)number);
	index1++;
	/* calculate the result */
	result = numbers[0];
	for (uint8 i = 1; i < index1; i++) {
		switch (operators[i - 1]) {
			case 'x':
				result *= numbers[i];
				break;
			case '/':
				result /= numbers[i];
				break;
			case '+':
				result += numbers[i];
				break;
			case '-':
				result -= numbers[i];
				break;
			default:
				break;
		}
	}
	
	/* convert the number to reversed string */
	while (result > 0) {
		final_result[index3] = result % 10 + 48;
		result /= 10;
		index3++;
	}	
	strReverse(final_result);
	return final_result;
}