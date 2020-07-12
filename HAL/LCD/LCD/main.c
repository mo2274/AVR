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
#include <stdlib.h>
#include <string.h>

extern Dio_Config_t default_configuration;

uint8* calc(uint8 *data);



int main(void)
{
	uint8 data[25] = {'\0'};
	uint8 *password = (uint8*)"123456";	
	uint8 index = 0; 
	uint8 input_num[2] = {'\0'};
	uint8 *result;
	
	Dio_init(&default_configuration);	
    Lcd_Init();
	
    while (1) {
		/* read till the user enters '=' */
		while (1) {
			while (input_num[0] == '\0') {
				input_num[0] = keyPad_Read(PORT_D);
			}
			if (input_num[0] == '=') {
				break;
			}
			if (input_num[0] == 'C') {
				index--;
				// clear the last number 
				Lcd_Cmd(0x10);
				input_num[0] = '\0'	;
				continue;
			}						
			Lcd_Out(input_num);

			data[index] = input_num[0];
			index++;
			input_num[0] = '\0'	;
		}
		Lcd_ClrScreen();
		if (strcmp((char*)data, (char*)password) == 0) {
			Lcd_Out((uint8*)"Wellcome :)");
		} else {
			Lcd_Out((uint8*)"Wrong Password");
		}
		
		/* calculate the result and print it on LCD */
		//result = calc(data);	
		//Lcd_Out(result);
		while(1);
    }
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