/*
 *       20x4 LCD Driver  
 * To use this driver you should determine:
 * 1- the port registers that LCD data connected to by these macros (LCD_PORT) and (LCD_DDR)
 * 2- the port registers that the control pins (EN And RS) connected to  by these macros (LCD_CTRPORT) and (LCD_CTRDDR)
 * 3- the number of the pins for EN and RS connected to.
 * 4- finally you should determine the mode of the LCD (8 or 4 bit mode) by defining (LCD_MODE_FOUR_BIT) for 4 bit mode 
 * or (LCD_MODE_EIGHT_BIT) for 8 bit mode 
 * 
 * Created: 23/04/2020 05:08:44 
 *  Author: Mohamed Abo Raia
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_PORT    PORTB
#define LCD_DDR     DDRB
#define LCD_CTRPORT PORTA
#define LCD_CTRDDR  DDRA
#define RS          1
#define EN          0
#define LCD_MODE_FOUR_BIT

/*		        Lcd_Init	
 * This used to initialize the LCD by sending some commands to LCD 
 * @param: this function takes nothing.
 * @return: the function return nothing;     
 */
extern void Lcd_Init(void);
/*		        Lcd_Out	
 * This used to output data on LCD 
 * @param: this function takes a string represent the data.
 * @return: the function return nothing;     
 */
extern void Lcd_Out(char *str);
/*		        Lcd_Cmd	
 * This used to send commands to LCD 
 * @param: this function takes the command.
 * @return: the function return nothing;     
 */
void Lcd_Cmd(uint8_t cmd);
/*		        Lcd_goto_row_coloumn	
 * This used to go to a specific row and column on the LCD
 * @param: this function takes number of row and the number of column.
 * @return: the function return nothing;     
 */
extern void Lcd_goto_row_coloumn(uint8_t row,uint8_t coloumn);


#endif /* LCD_H_ */