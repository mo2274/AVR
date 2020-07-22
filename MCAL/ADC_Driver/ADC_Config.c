/*
 * ADC_Config.c
 *
 * Created: 19/07/2020 10:39:23 
 *  Author: Mohamed Abo Raia
 */ 
#include "ADC.h"
#include "ADC_Config.h"

ADC_Config_t adc_configuration  = { // reference voltage
									INTERNAL,
	                                // resolution
									TEN_BIT,
									// ADC trigger mode
									FREE_RUNNING,
									// Prescaler
									PRESCLAER_8
									              };


ADC_Channel_t channels[ADC_NUM_OF_CHANNELS] = {ADC_0, ADC_1, ADC_2, ADC_3, ADC_4, ADC_5, ADC_6};