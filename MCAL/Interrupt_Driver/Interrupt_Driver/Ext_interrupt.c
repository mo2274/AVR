/*
 * Ext_interrupt.c
 *
 * Created: 18/05/2020 04:11:32
 *  Author: Mohamed Abo Raia
 */ 
#include "Ext_interrupts.h"
#include "Ext_interrputs_configs.h"
#include "Ext_interrputs_Registers.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include "Delay.h"

extern Interrupt_config_t Interrupt_configuration;


/* enable global interrupt */
void Enable_Global_Interrupt(void) {
	SREG |= 0b10000000;
}

/* disable global interrupt */
void Disable_Global_Interrupt(void) {
	SREG &= ~0b10000000;
}

bool Ext_interrupt_init(void) {
	volatile int i;
	for (i = 0; i < EXT_INTERRUPT_NUM; i++) {
		switch (Interrupt_configuration.interrupts[i].interrupt) {
			case INT_0:
				switch (Interrupt_configuration.interrupts[i].trigger) {
					case LOW:
						MCUCR &= ~0b00000011;
						break;
					case FALLING:
						MCUCR &= ~0b00000001;
						MCUCR |= 0b00000010;
						break;
					case RIASING:
						MCUCR |= 0b00000011;
						break;
					case ANY_CHANGE:
						MCUCR &= ~0b00000010;
						MCUCR |= 0b00000001;
						break;
					default:
						return ERROR;
						break;					
				}
				/* enable INT0 */
				GICR |= 0b01000000;	
				break;
			case INT_1:
				switch (Interrupt_configuration.interrupts[i].trigger) {
					case LOW:
						MCUCR &= ~0b00001100;
						break;
					case FALLING:
						MCUCR |= 0b00001000;
						MCUCR &= ~0b00000100;
						break;
					case RIASING:
						MCUCR |= 0b00001100;
						break;
					case ANY_CHANGE:
						MCUCR |= 0b00000100;
						MCUCR &= ~0b00001000;
						break;
					default:
						return ERROR;
						break;
				}
				/* enable INT1 */
				GICR |= 0b10000000;		
				break;
			case INT_2:
				switch (Interrupt_configuration.interrupts[i].trigger) {
					case FALLING:
						MCUCSR &= ~0b01000000;
						break;
					case RIASING:
						MCUCSR |= 0b01000000;
						break;
					default:
						return ERROR;
						break;
				}
				/* enable INT2 */
				GICR |= 0b00100000;	
				break;			
			default:
				return ERROR;
				break;				
		}
	}
	/* enable global interrupt */
	Enable_Global_Interrupt();
	
	return SUCCESS;
}


static void (*ptrToFunc_0)(void);
static void (*ptrToFunc_1)(void);
static void (*ptrToFunc_2)(void);

bool Ext_interrupt0_Function(void (*func_ptr)(void)) {

	ptrToFunc_1 = func_ptr;	
	return SUCCESS;
}

ISR(INT0_vect) {
	ptrToFunc_0();
}

ISR(INT1_vect) {
	Lcd_Out((uint8*)"mohamed");
	DELAY_MS(1000);
	Lcd_ClrScreen();
	//(*ptrToFunc_1)();
}

ISR(INT2_vect) {
	(*ptrToFunc_2)();
}
