/*
 * SevenSegment.c
 *
 *              Driver for seven segment
 * To use it you should provide the name of the port 
 * to connect the seven segment to and the number to be printed
 * 
 * Created: 23/04/2020 01:36:26 
 *  Author: Mohamed Abo Raia
 */ 

#include <stdint.h>
#include <avr/io.h>
#include "SevenSegment.h"



/* function to initialize the port */
static uint8_t init() {
	/* make the port as output port */
	SevSegPORTd = 0xFF;
	/* success */ 
	return 0;
}

/* function to display the number on the seven segment */
uint8_t display(uint8_t number) {
	/* port initialization */
	init();
	
	switch (number) {
	case 0x0:	
		SevSegPORT = 0b00111111;
		break;	
	case 0x1:
		SevSegPORT = 0b00110000;	
		break;	
	case 0x2:
		SevSegPORT = 0b01011011;
		break;
	case 0x3:
		SevSegPORT = 0b01001111;
		break;
	case 0x4:
		SevSegPORT = 0b01100110;
		break;
	case 0x5:
		SevSegPORT = 0b01101101;
		break;
	case 0x6:
		SevSegPORT = 0b01111101;
		break;
	case 0x7:
		SevSegPORT = 0b00000111;
		break;
	case 0x8:
		SevSegPORT = 0b01111111;
		break;
	case 0x9:
		SevSegPORT = 0b01101111;
		break;
	case 0xA:
		SevSegPORT = 0b01110111;
		break;
	case 0xB:
		SevSegPORT = 0b01111100;
		break;
	case 0xC:
		SevSegPORT = 0b00111001;
		break;
	case 0xD:
		SevSegPORT = 0b01011110;
		break;				
	case 0xE:
		SevSegPORT = 0b01111001;
		break;
	case 0xF:
		SevSegPORT = 0b01110001;
		break;
	default:
		SevSegPORT = 0b00111111;
		break;							
	}
	
	/* success */
	return 0;
}

