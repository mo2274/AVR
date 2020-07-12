/*
 * Timer.h
 *
 * Created: 02/06/2020 01:18:53 م
 *  Author: scc
 */ 


#ifndef TIMER_H_
#define TIMER_H_

typedef enum {
	T0,
	T1, 
	T2
}Timer_Name_t;

typedef enum {
	NO_PRESCALER   = 1,
	PRESCALER_8    = 8,
	PRESCALER_64   = 64,
	PRESCALER_256  = 256,
	PRESCALER_1024 = 1024,
	EXT_CLK_RAISING,
	EXT_CLK_FAILING	
}Prescaler_t;

typedef enum {
	NORMAL,
	PWD_FC,
	CTC,
	PWD_F,
	COUNTER	
}Timer_Mode_t;	 

typedef struct {
	Timer_Name_t name;
	Prescaler_t  Prescaler;
	Timer_Mode_t mode;
}Timer_t;







#endif /* TIMER_H_ */