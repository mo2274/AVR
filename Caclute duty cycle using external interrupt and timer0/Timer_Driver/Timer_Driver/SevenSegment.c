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

#include "StdTypes.h"
#include "SevenSegment.h"
#include "Dio_Registers.h"
#include "Dio.h"

/* function to display the number on the seven segment */
bool SevenSeg_Display(Data_t number, Port_t port_name) {
	#ifdef COMMON_ANODE	
	switch (number) {
	case 0x0:	
		if (Dio_Write_port(port_name, ~0b00111111) == ERROR) {
			return ERROR;
		}
		break;	
	case 0x1:
		if (Dio_Write_port(port_name, ~0b00110000) == ERROR) {
			return ERROR;
		}	
		break;	
	case 0x2:
		if (Dio_Write_port(port_name, ~0b01011011) == ERROR) {
			return ERROR;
		}
		break;
	case 0x3:
		if (Dio_Write_port(port_name, ~0b01001111) == ERROR) {
			return ERROR;
		}
		break;
	case 0x4:
		if (Dio_Write_port(port_name, ~0b01100110) == ERROR) {
			return ERROR;
		}
		break;
	case 0x5:
		if (Dio_Write_port(port_name, ~0b01101101) == ERROR) {
			return ERROR;
		}
		break;
	case 0x6:
	    if (Dio_Write_port(port_name, ~0b01111101) == ERROR) {
			return ERROR;
		}
		break;
	case 0x7:
		 if (Dio_Write_port(port_name, ~0b00000111) == ERROR) {
			 return ERROR;
		 }
		break;
	case 0x8:
		if (Dio_Write_port(port_name, ~0b01111111) == ERROR) {
			return ERROR;
		}
		break;
	case 0x9:
		if (Dio_Write_port(port_name, ~0b01101111) == ERROR) {
			return ERROR;
		}
		break;
	case 0xA:
		if (Dio_Write_port(port_name, ~0b01110111) == ERROR) {
			return ERROR;
		}
		break;
	case 0xB:
		if (Dio_Write_port(port_name, ~0b01111100) == ERROR) {
			return ERROR;
		}
		break;
	case 0xC:
		if (Dio_Write_port(port_name, ~0b00111001) == ERROR) {
			return ERROR;
		}
		break;
	case 0xD:
		if (Dio_Write_port(port_name, ~0b01011110) == ERROR) {
			return ERROR;
		} 
		break;				
	case 0xE:
		if (Dio_Write_port(port_name, ~0b01111001) == ERROR) {
			return ERROR;
		}
		break;
	case 0xF:
		if (Dio_Write_port(port_name, ~0b01110001) == ERROR) {
			return ERROR;
		}
		break;
	default:
		return ERROR;
		break;							
	}
	#endif
	
	#ifdef COMMON_CATHODE
	switch (number) {
		case 0x0:
			if (Dio_Write_port(port_name, 0b00111111) == ERROR) {
				return ERROR;
			}
			break;
		case 0x1:
			if (Dio_Write_port(port_name, 0b00110000) == ERROR) {
				return ERROR;
			}
			break;
		case 0x2:
			if (Dio_Write_port(port_name, 0b01011011) == ERROR) {
				return ERROR;
			}
			break;
		case 0x3:
			if (Dio_Write_port(port_name, 0b01001111) == ERROR) {
				return ERROR;
			}
			break;
		case 0x4:
			if (Dio_Write_port(port_name, 0b01100110) == ERROR) {
				return ERROR;
			}
			break;
		case 0x5:
			if (Dio_Write_port(port_name, 0b01101101) == ERROR) {
				return ERROR;
			}
			break;
		case 0x6:
			if (Dio_Write_port(port_name, 0b01111101) == ERROR) {
				return ERROR;
			}
			break;
		case 0x7:
			if (Dio_Write_port(port_name, 0b00000111) == ERROR) {
				return ERROR;
			}
			break;
		case 0x8:
			if (Dio_Write_port(port_name, 0b01111111) == ERROR) {
				return ERROR;
			}
			break;
		case 0x9:
			if (Dio_Write_port(port_name, 0b01101111) == ERROR) {
				return ERROR;
			}
			break;
		case 0xA:
			if (Dio_Write_port(port_name, 0b01110111) == ERROR) {
				return ERROR;
			}
			break;
		case 0xB:
			if (Dio_Write_port(port_name, 0b01111100) == ERROR) {
				return ERROR;
			}
			break;
		case 0xC:
			if (Dio_Write_port(port_name, 0b00111001) == ERROR) {
				return ERROR;
			}
			break;
		case 0xD:
			if (Dio_Write_port(port_name, 0b01011110) == ERROR) {
				return ERROR;
			}
			break;
		case 0xE:
			if (Dio_Write_port(port_name, 0b01111001) == ERROR) {
				return ERROR;
			}
			break;
		case 0xF:
			if (Dio_Write_port(port_name, 0b01110001) == ERROR) {
				return ERROR;
			}
			break;
		default:
			return ERROR;
			break;
	}
	
	#endif
	
	/* success */
	return SUCCESS;
}

