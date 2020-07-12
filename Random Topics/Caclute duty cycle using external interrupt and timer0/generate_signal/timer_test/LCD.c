/*
 *    LCD driver 
 * driver for 20x4 LCD 
 *
 * Created: 23/04/2020 05:08:11 
 *  Author: Mohamed Abo Raia
 */ 

#define F_CPU 1000000UL

#include <util/delay.h>
#include "common.h"
#include "LCD.h"
#include "StdTypes.h"
#include "Dio.h"



// to control the writing on the LCD
int column = 0;
int row = 0;

static bool EnPulse(void) {
	// high to low pulse
	if (Dio_Write_pin(EN, LCD_CtrPort, 1) == ERROR) {
		return ERROR;
	}
	_delay_us(1);
	if (Dio_Write_pin(EN, LCD_CtrPort, 0) == ERROR) {
		return ERROR;
	}
	return SUCCESS;	
}

#ifdef LCD_MODE_FOUR_BIT
static bool Lcd_Write_4(uint8 data) {
	// Clear all data bits the data bits will be the most bits
	if (Dio_Write_numOfBits(LCD_DataPort, 0, 0xF0) == ERROR) {
		return ERROR;
	}
	// Put the high nibble on the data bits and apply an enable pulse
	if (Dio_Write_numOfBits(LCD_DataPort, data & 0xF0, 0xF0) == ERROR) {
		return ERROR;
	}
	if (EnPulse() == ERROR) {
		return ERROR;
	} 
	// Clear all data bits the data bits will be the most bits
	if (Dio_Write_numOfBits(LCD_DataPort, 0, 0xF0) == ERROR) {
		return ERROR;
	}
	// Put the low nibble on the data bits and apply an enable pulse 
	if (Dio_Write_numOfBits(LCD_DataPort, (data & 0x0F) << 4 , 0xF0) == ERROR) {
		return ERROR;
	}
	if (EnPulse() == ERROR) {
		return ERROR;
	}
	// Wait 2 ms
	_delay_ms(2);
	return SUCCESS;	
}
#endif

#ifdef LCD_MODE_EIGHT_BIT
static bool Lcd_Write_8(uint8 data) {
	// Put the data on the data bits and apply an enable pulse
	if (Dio_Write_port(LCD_DataPort, data) == ERROR) {
		return ERROR;
	}
	if (EnPulse() == ERROR) {
		return ERROR;
	}
	// Wait 2 ms
	_delay_ms(2);
	return SUCCESS;
}
#endif

extern bool Lcd_Cmd(uint8 cmd) {
	// Clear RS pin
	if (Dio_Write_pin(RS, LCD_CtrPort, 0) == ERROR) {
		return ERROR;
	}
	#ifdef LCD_MODE_FOUR_BIT
	if (Lcd_Write_4(cmd) == ERROR) {
		return ERROR;
	}
	#endif
	#ifdef LCD_MODE_EIGHT_BIT 
	if (Lcd_Write_8(cmd) == ERROR) {
		return ERROR;
	}
	#endif
	return SUCCESS;
}

static bool Lcd_Data(uint8 data) {
	// Set RS pin
	if (Dio_Write_pin(RS, LCD_CtrPort, 1) == ERROR) {
		return ERROR;
	}
	#ifdef LCD_MODE_FOUR_BIT
	if (Lcd_Write_4(data) == ERROR) {
		return ERROR;
	}
	#endif
	#ifdef LCD_MODE_EIGHT_BIT
	if (Lcd_Write_8(data) == ERROR) {
		return ERROR;
	}
	#endif
	return SUCCESS;
}

extern bool Lcd_Init(void) {
	// Wait 15 ms
	_delay_ms(15);	
	#ifdef LCD_MODE_FOUR_BIT
	// write 0x33 on LCD port for 4 bit mode
	if(Lcd_Cmd(0x30) == ERROR) {
		return ERROR;
	}
	// write 0x32 on LCD port for 4 bit mode
	if(Lcd_Cmd(0x20) == ERROR) {
		return ERROR;
	}
	if (EnPulse() == ERROR) {
		return ERROR;
	}
	// write 0x28 on LCD port for 4 bit mode
	if (Lcd_Cmd(0x28) == ERROR) {
		return ERROR;
	}
	// write 0x0F for display on and cursor blinking
	if (Lcd_Cmd(0x0F) == ERROR) {
		return ERROR;
	}
	#endif
	#ifdef LCD_MODE_EIGHT_BIT
	// write 0x33 on LCD port for 8 bit mode
	if (Lcd_Cmd(0x38) == ERROR) {
		return ERROR;
	}
	// write 0x0F for display on and cursor blinking
	if (Lcd_Cmd(0x0E) == ERROR) {
		return ERROR;
	}
	if (EnPulse() == ERROR) {
		return ERROR;
	}
	#endif	
	// write 0x01 for clear screen	            
	if (Lcd_Cmd(0x01) == ERROR) {
		return ERROR;
	}             
	// write 0x06 to shift cursor write
	if (Lcd_Cmd(0x06) == ERROR) {
		return ERROR;
	}
	return SUCCESS;	
}

bool Lcd_goto_row_coloumn(uint8 row,uint8 coloumn) {
	switch (row) {
	case 0:
		if (Lcd_Cmd(0x80 + coloumn) == ERROR) {
			return ERROR;
		}
		break;
	case 1:
		if (Lcd_Cmd(0xC0 + coloumn) == ERROR) {
			return ERROR;
		}
		break;
	case 2:
		if (Lcd_Cmd(0x94 + coloumn) == ERROR) {
			return ERROR;
		}
		break;
	case 3:
		if (Lcd_Cmd(0xD4 + coloumn) == ERROR) {
			return ERROR;
		}	
		break;
	default:
		return ERROR;
		break;					
	}
	return SUCCESS;
}


extern bool Lcd_Out(uint8 *str) {
	while (*str != '\0') {
		if (Lcd_Data(*str) == ERROR) {
			return ERROR;
		}
		str++;
	}
	return SUCCESS;	
}

extern bool Lcd_ClrScreen(void) {
	// write 0x01 for clear screen
	if (Lcd_Cmd(0x01) == ERROR) {
		return ERROR;
	}
	return SUCCESS;
}