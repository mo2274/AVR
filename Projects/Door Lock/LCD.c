/*
 *    LCD driver 
 * driver for 20x4 LCD 
 *
 * Created: 23/04/2020 05:08:11 
 *  Author: Mohamed Abo Raia
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "common.h"
#include "LCD.h"



// to control the writing on the LCD
int column = 0;
int row = 0;

static void EnPulse(void) {
	// high to low pulse
	SETBET(LCD_CTRPORT, EN);
	_delay_us(1);
	CLRBET(LCD_CTRPORT, EN);	
}

#ifdef LCD_MODE_FOUR_BIT
static void Lcd_Write_4(uint8_t data) {
	// Clear all data bits
	LCD_PORT &= 0x0F;
	// Put the high nibble on the data bits and apply an enable pulse
	LCD_PORT |= data & 0xF0;
	EnPulse();
	// Clear all data bits
	LCD_PORT &= 0x0F;
	// Put the low nibble on the data bits and apply an enable pulse 
	LCD_PORT |= (data & 0x0F) << 4;
	EnPulse();
	// Wait 2 ms
	_delay_ms(2);	
}
#endif

#ifdef LCD_MODE_EIGHT_BIT
static void Lcd_Write_8(uint8_t data) {
	// Put the data on the data bits and apply an enable pulse
	LCD_PORT = data;
	EnPulse();
	// Wait 2 ms
	_delay_ms(2);
}
#endif

void Lcd_Cmd(uint8_t cmd) {
	// Clear RS pin
	CLRBET(LCD_CTRPORT, RS);
	// check for LCD mode
	#ifdef LCD_MODE_FOUR_BIT
	// Write the cmd byte
	Lcd_Write_4(cmd);
	#else
	Lcd_Write_8(cmd);
	#endif
}

static void Lcd_Data(uint8_t data) {
	// set RS pin
	SETBET(LCD_CTRPORT, RS);
	// check for LCD mode
	#ifdef LCD_MODE_FOUR_BIT
	// Write the cmd byte
	Lcd_Write_4(data);
	#else
	Lcd_Write_8(data);
	#endif
}


extern void Lcd_Init(void) {
	// Configure the EN and RS pins as output
	SETBET(LCD_CTRDDR, EN);
	SETBET(LCD_CTRDDR, RS);
	// check for LCD mode
	#ifdef LCD_MODE_FOUR_BIT
	// Configure the port pins as output
	LCD_DDR |= 0xF0;
	// clear the port
	LCD_PORT &= 0x0F; 
	// Wait 15 ms
	_delay_ms(15);
	// write 0x33 on LCD port for 4 bit mode
	Lcd_Cmd(0x30);
	// write 0x32 on LCD port for 4 bit mode
	Lcd_Cmd(0x20);
	EnPulse();
	// write 0x28 on LCD port for 4 bit mode
	Lcd_Cmd(0x28);
	// write 0x0F for display on and cursor blinking
	Lcd_Cmd(0x0F);
	#else
	// Configure the port pins as output
	LCD_DDR |= 0xFF;
	// clear the LCD port
	LCD_PORT &= 0x00; 
	// Wait 15 ms
	_delay_ms(15);	
	// write 0x33 on LCD port for 8 bit mode
	Lcd_Cmd(0x38);
	// write 0x0F for display on and cursor blinking
	Lcd_Cmd(0x0E);
	EnPulse();
	#endif	
	// write 0x01 for clear screen	            
	Lcd_Cmd(0x01);             
	// write 0x06 to shift cursor write
	Lcd_Cmd(0x06);	
}

extern void Lcd_goto_row_coloumn(uint8_t row,uint8_t coloumn) {
	switch (row) {
	case 0:
		Lcd_Cmd(0x80 + coloumn);
		break;
	case 1:
		Lcd_Cmd(0xC0 + coloumn);
		break;
	case 2:
		Lcd_Cmd(0x94 + coloumn);
		break;
	case 3:
		Lcd_Cmd(0xD4 + coloumn);	
		break;
	default:
		break;					
	}
}


extern void Lcd_Out(char *str) {
	while (*str != '\0') {
		Lcd_Data(*str);
		column += 1;
		if (column == 20) {
			row++;
			column = 0;
		}
		Lcd_goto_row_coloumn(row, column);
		str++;
	}	
}
