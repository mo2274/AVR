/*
 * decimalCounter.c
 *
 * Created: 23/04/2020 01:32:50 
 * Author : 
 */ 
#define F_CPU 1000000UL
#define SW  0


#include <avr/io.h>
#include <util/delay.h>
#include "SevenSegment.h"
#include "common.h"
#include "LCD.h"
#include "KeyPad.h"
#include <string.h>


extern int column;
extern int row;


int main(void) {
	char key;
	char str[6];
	char *password = "12345";
	str[5] = '\0';
	int count = 3;

	
	Lcd_Init();
	keyPadInit();
	
	Lcd_goto_row_coloumn(row, column);
			
    while (1) {	
		Lcd_Out("enter your password:");
		for (uint8_t i = 0; i <= 4; ) {
			key = readKey();
			if (key != '\0') {
				Lcd_Out("*");
				str[i] = key;
				i++;
			}			
		}
		if (strcmp(str, password) == 0) {
			Lcd_Cmd(0x1);
			row = 1;
			column = 0;
			Lcd_Out("     Welcome :)");
			while (1);	
		}
		else {
			if (count == 1) {
			Lcd_Cmd(0x1);
			row = 0;
			column = 0;
			Lcd_Out("you entered the password three times    wrong");
			while (1);
			}
			Lcd_Cmd(0x1);
			row = 1;
			column = 0;			
			Lcd_Out(" WORONG PASSWORD :(  TRY AGAIN");
			_delay_ms(1000);
			Lcd_Cmd(0x1);
			row = 0;
			column = 0;	
			count--;		
		}

    }
}

