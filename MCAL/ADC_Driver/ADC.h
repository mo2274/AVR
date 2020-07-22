/*
 * ADC.h
 *
 * Created: 19/07/2020 10:38:30 
 *  Author: Mohamed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "StdTypes.h"

// reference voltage
typedef enum {
	AREF     = 0b00,
	AVCC     = 0b01,
	INTERNAL = 0b11
}ACD_Vref_t;
// resolution
typedef enum {
	TEN_BIT,
	EIGHT_BIT 
}ADC_Resolution_t;
// ADC Channels
typedef enum {
	ADC_0,
	ADC_1,
	ADC_2,
	ADC_3,
	ADC_4,
	ADC_5,
	ADC_6,
	ADC_7
}ADC_Channel_t;
// ADC prescaler
typedef enum {
	PRESCLAER_2 = 1,
	PRESCLAER_4,
	PRESCLAER_8,
	PRESCLAER_16,
	PRESCLAER_32,
	PRESCLAER_64,
	PRESCLAER_128
}ADC_Prescaler_t;
// ADC mode
typedef enum {
	FREE_RUNNING,
	Analog_Comparator,
	External_Interrupt_Request_0,
	Timer0_Compare_Match,
	Timer0_Overflow,
	Timer1_Compare_Match_B,
	Timer1_Overflow,
	Timer1_CaptureEvent
}ADC_Trigger_t;
// ADC configurations
typedef struct {
	ACD_Vref_t         vref;
	ADC_Resolution_t   resolution;
	ADC_Trigger_t      trigger;
	ADC_Prescaler_t    prescaler;
}ADC_Config_t;

bool  ADC_init(void);
bool ADC_ChannelRead(ADC_Channel_t channel, uint16* result) ;
bool ADC_start_InterruptMode(void (*p) (void));

#endif /* ADC_H_ */