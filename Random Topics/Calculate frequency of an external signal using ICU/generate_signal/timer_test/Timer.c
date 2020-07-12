/*
 * Timer.c
 *
 * Created: 02/06/2020 01:19:07 
 *  Author: 
 */ 

#include "Timer.h"
#include "StdTypes.h"
#include "Timer_Registers.h"
#include "Timer_config.h"


static bool set_prescaler(Prescaler_t prescaler) {
	switch (prescaler) {
		case NO_PRESCALER:
			// TODO
			break;
		case PRESCALER_8:
			// TODO
			break;
		case PRESCALER_64:
			// TODO
			break;
		case PRESCALER_256:
			// TODO
			break;		
		case PRESCALER_1024:
			// TODO
			break;
		case EXT_CLK_FAILING:
			// TODO
			break;
		case EXT_CLK_RAISING:
			// TODO
			break;
		default:
			return ERROR;
	}
	return SUCCESS;
}

static bool set_mode(Timer_Name_t name, Timer_Mode_t mode) {
	
}