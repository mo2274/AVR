/*
 * Ext_interrupts.h
 *
 * Created: 18/05/2020 04:11:53 
 *  Author: Mohamed Abo Raia
 */ 


#ifndef EXT_INTERRUPTS_H_
#define EXT_INTERRUPTS_H_

#include "StdTypes.h"
#include "Ext_interrputs_configs.h"

typedef enum {
	INT_0,
	INT_1,
	INT_2
}Interrupt_t;

typedef enum {
	LOW,
	RIASING,
	FALLING,
	ANY_CHANGE
}Trigger_t;

typedef struct {
	Interrupt_t interrupt;
	Trigger_t   trigger;	
}Interrupt_config;

typedef struct {
	Interrupt_config interrupts[EXT_INTERRUPT_NUM];
}Interrupt_config_t;



/* function to configure external interrupt */
bool Ext_interrupt_init(void);
/* function to send the desired function to ISR */
bool Ext_interrupt0_Function(void (*func_ptr)(void));
/* enable global interrupt */
void Enable_Global_Interrupt(void);
/* disable global interrupt */
void Disable_Global_Interrupt(void);
	
#endif /* EXT_INTERRUPTS_H_ */