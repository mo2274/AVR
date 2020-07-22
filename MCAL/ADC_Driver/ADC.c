/*
 * ADC.c
 *
 * Created: 19/07/2020 10:38:14 
 *  Author: Mohamed Abo Raia
 */ 
#include "ADC.h"
#include "Common.h"
#include "ADC_Registers.h"
#include <avr/interrupt.h>
#include "ADC_Config.h"


extern ADC_Config_t adc_configuration;
volatile uint16 ADC_Buffer[ADC_NUM_OF_CHANNELS] = {0}; 
extern ADC_Channel_t channels[ADC_NUM_OF_CHANNELS];	 
volatile uint8 ADC_Buffer_index = 0; 
static void (* Global_pointer) (void);


// function to initialize ADC
bool  ADC_init(void) {
	uint8 ADC_ADMUX_TEMP = 0;
	uint8 ADC_SFIOR_TEMP = 0;
	uint8 ADC_ADCSRA_TEMP = 0;
	// check for error in vref value
	if ((adc_configuration.vref < 0) || (adc_configuration.vref > 3)) {
		return ERROR;
	}
	// clear vref bits
	ADC_ADMUX_TEMP &= 0b00111111;
	// configure reference voltage
	ADC_ADMUX_TEMP |= adc_configuration.vref << 6;
	// check for error in resolution value
	if ((adc_configuration.resolution < 0) || (adc_configuration.resolution > 1)) {
		return ERROR;
	}
	// clear resolution bit
	CLR_BIT(ADC_ADMUX_TEMP, 5);
	// Configure resolution
	ADC_ADMUX_TEMP |= adc_configuration.resolution << 5;
	//  check for error in trigger value
	if ((adc_configuration.trigger < 0) || (adc_configuration.trigger > 7)) {
		return ERROR;
	}
	// Configure trigger mode
	if (adc_configuration.trigger == FREE_RUNNING) {
		// disable auto trigger
		CLR_BIT(ADC_ADCSRA_TEMP, 5);
		ADC_SFIOR_TEMP &= 0b00011111;
	} else {
		// enable auto trigger
		SET_BIT(ADC_ADCSRA_TEMP, 5);
		ADC_SFIOR_TEMP &= 0b00011111;  
		// select the source of the trigger
		ADC_SFIOR_TEMP |= adc_configuration.trigger << 5;
	}
	// configure prescaler
	ADC_ADCSRA_TEMP &= 0b11111000;
	ADC_ADCSRA_TEMP |= adc_configuration.prescaler;
	// enable ADC
	SET_BIT(ADC_ADCSRA_TEMP, 7);
	
	ADMUX = ADC_ADMUX_TEMP;
	SFIOR |= ADC_SFIOR_TEMP; 
	ADCSRA = ADC_ADCSRA_TEMP; 
	// SUCCESS
	return SUCCESS;		
}
// Function to read the converted result from a channel
bool ADC_ChannelRead(ADC_Channel_t channel, uint16* result) {
	// select the channel
	uint8 ADC_ADMUX_TEMP = ADMUX;
	ADC_ADMUX_TEMP &= 0b11100000;
	ADC_ADMUX_TEMP |= channel;
	ADMUX |= ADC_ADMUX_TEMP;
	if (adc_configuration.trigger == FREE_RUNNING) {
		// start conversion
		SET_BIT(ADCSRA, 6);
	}	
	// wait for the result
	while (GET_BIT(ADCSRA, 4) == 0);
	// clear flag
	SET_BIT(ADCSRA, 4);
	// return result
	if (adc_configuration.resolution == EIGHT_BIT) {
		*result = ADCH;
	} else if ((adc_configuration.resolution == TEN_BIT)) {
		*result = ADCL;
		*result |= ADCH << 8;
	} else {
		return ERROR;
	}
	return SUCCESS;
}

// function to start the ADC in the interrupt mode
bool ADC_start_InterruptMode(void (*ADC_complete_function) (void)) {
	// select the channel
	uint8 ADC_ADMUX_TEMP = ADMUX;
	ADC_ADMUX_TEMP &= 0b11100000;
	ADC_ADMUX_TEMP |= channels[0];
	ADMUX = ADC_ADMUX_TEMP;
	// assign the address of the input function to the global pointer
	Global_pointer = ADC_complete_function;
	// enable interrupt for ADC
	SET_BIT(ADCSRA, 3);
	if (adc_configuration.trigger == FREE_RUNNING) {
		// start conversion
		SET_BIT(ADCSRA, 6);
	}
	// enable global interrupt
	sei();
	
	return SUCCESS;
} 

ISR(ADC_vect) {	
	// store the result of conversion in a buffer	
	if (adc_configuration.resolution == EIGHT_BIT) {
		ADC_Buffer[ADC_Buffer_index] = ADCH;
		ADC_Buffer_index++;
	} else {
		ADC_Buffer[ADC_Buffer_index] =  ADCL;
		ADC_Buffer[ADC_Buffer_index] |= ADCH << 8;
		ADC_Buffer_index++;
	}
	// check if there is input from other channels
	if (ADC_Buffer_index < ADC_NUM_OF_CHANNELS) {
		// go to next channel
		uint8 ADC_ADMUX_TEMP = ADMUX;
		ADC_ADMUX_TEMP &= 0b11100000;
		ADC_ADMUX_TEMP |= channels[ADC_Buffer_index];
		ADMUX = ADC_ADMUX_TEMP;			
	} else {
		ADC_Buffer_index = 0;
		Global_pointer();
		// go to first channel
		uint8 ADC_ADMUX_TEMP = ADMUX;
		ADC_ADMUX_TEMP &= 0b11100000;
		ADC_ADMUX_TEMP |= channels[ADC_Buffer_index];
		ADMUX = ADC_ADMUX_TEMP;		
	}	
	if (adc_configuration.trigger == FREE_RUNNING) {
		// start conversion
		SET_BIT(ADCSRA, 6);
	} 
}
