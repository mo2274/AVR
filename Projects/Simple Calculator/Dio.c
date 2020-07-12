
#include "Dio_Config.h"
#include "StdTypes.h"
#include "Dio_Registers.h"
#include "Dio.h"
	
/* initialization function */	
bool Dio_init(Dio_Config_t *init) {	
	bool status = SUCCESS;
	/* configuration of pins */
	for (int i = 0; i < NUM_OF_CHANNELS; i++) {
		if (init->pins_config[i].direction == INPUT) {
			*(init->pins_config[i].ddr) &= ~(1 << init->pins_config[i].channel_num); 
			if (init->pins_config[i].pull_up == PULL_UP) {
				*(init->pins_config[i].port) |= (1 << init->pins_config[i].channel_num); 
			} else if (init->pins_config[i].pull_up == NO_PULL_UP) {
				*(init->pins_config[i].port) &= ~(1 << init->pins_config[i].channel_num); 
			} else {
				status = ERROR;
				return status;
			}
		} else if (init->pins_config[i].direction == OUTPUT) {
			*(init->pins_config[i].ddr) |= (1 << init->pins_config[i].channel_num);
			*(init->pins_config[i].port) |= (init->pins_config[i].init_value << init->pins_config[i].channel_num);			 
		} else {
			status = ERROR;
			return status;
		}
	}
	/* configuration of ports */
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		if (init->port_config[i].direction == INPUT) {
			*(init->port_config[i].ddr) = 0x00;
			if (init->port_config[i].pull_up == PULL_UP) {
				*(init->port_config[i].port) = 0xFF;
				} else if (init->port_config[i].pull_up == NO_PULL_UP) {
				*(init->port_config[i].port) = 0x00;
				} else {
				status = ERROR;
				return status;
			}
			} else if (init->port_config[i].direction == OUTPUT) {
			*(init->port_config[i].ddr) = 0xFF;
			*(init->port_config[i].port) = init->port_config[i].init_value;
			} else {
			status = ERROR;
			return status;
		}		
	}		
	return status;
}

/* read the status of a specific pin */
bool Dio_Read_pin(Pin_type pin_num, Port_t port_name, Data_t* location) {
	/* check for error input */
	if (pin_num < 0 || pin_num > 7) {
		return ERROR;
	}
	switch (port_name) {
	case PORT_A:
		*location = ((PINA & (1 << pin_num)) >> pin_num);
		break;
	case PORT_B:
		*location = ((PINB & (1 << pin_num)) >> pin_num);
		break;
	case PORT_C:
		*location = ((PINC & (1 << pin_num)) >> pin_num);
		break;
	case PORT_D:
		*location = ((PIND & (1 << pin_num)) >> pin_num);
		break;
	default:
		return ERROR;					
	}
	return SUCCESS;
}
/* change the status of a specific pin */
bool Dio_Write_pin(Pin_type pin_num, Port_t port_name, Data_t value) {
	/* check for error input */
	if (pin_num < 0 || pin_num > 7) {
		return ERROR;
	}

	switch (port_name) {
	case PORT_A:
		if (value) {
			PORTA |= (1 << pin_num);
		} else {
			PORTA &= ~(1 << pin_num);
		}	
		break;
	case PORT_B:
		if (value) {
			PORTB |= (1 << pin_num);
			} else {
			PORTB &= ~(1 << pin_num);
		}
		break;
	case PORT_C:
		if (value) {
			PORTC |= (1 << pin_num);
			} else {
			PORTC &= ~(1 << pin_num);
		}
		break;
	case PORT_D:
		if (value) {
			PORTD |= (1 << pin_num);
			} else {
			PORTD &= ~(1 << pin_num);
		}
		break;
	default:
		return ERROR;					
	}
	return SUCCESS;
}
/* read the data from a specific port */
bool Dio_Read_port(Port_t port_name, Data_t* location) {
	
	switch (port_name) {
	case PORT_A:
		*location = PINA;
		break;
	case PORT_B:
		*location = PINB;
		break;
	case PORT_C:
		*location = PINC;
		break;
	case PORT_D:
		*location = PIND;
		break;
	default:
		return ERROR;
	}
	
	return SUCCESS;	
}
/* change the value of a specific port */
bool Dio_Write_port(Port_t port_name, Data_t value) {
	if (value < 0 || value > 255) {
		return ERROR;
	}
	switch (port_name) {
	case PORT_A:
		PORTA = value;
		break;
	case PORT_B:
		PORTB = value;
		break;
	case PORT_C:
		PORTC = value;
		break;
	case PORT_D:
		PORTD = value;
		break;
	default:
		return ERROR;
	}
	
	return SUCCESS;	
}

/* set pin direction */
bool Dio_setPin_direction(Pin_type pin_num, Port_t port_name, Direction_t direction) {
	/* check for error input */
	if (pin_num < 0 || pin_num > 7) {
		return ERROR;
	}

	switch (port_name) {
	case PORT_A:
		if (direction == OUTPUT) {
			DDRA |= (1 << pin_num);
		} else if (direction == INPUT) {
			DDRA &= ~(1 << pin_num);
		} else {
			return ERROR;
		}
		break;
	case PORT_B:
		if (direction == OUTPUT) {
			DDRB |= (1 << pin_num);
		} else if (direction == INPUT) {
			DDRB &= ~(1 << pin_num);
		} else {
			return ERROR;
		}
		break;
	case PORT_C:
		if (direction == OUTPUT) {
			DDRC |= (1 << pin_num);
		} else if (direction == INPUT) {
			DDRC &= ~(1 << pin_num);
		} else {
			return ERROR;
		}
		break;
	case PORT_D:
		if (direction == OUTPUT) {
			DDRD |= (1 << pin_num);
		} else if (direction == INPUT) {
			DDRD &= ~(1 << pin_num);
		} else {
			return ERROR;
		}
		break;
	default:
		return ERROR;
	}
	return SUCCESS;
}

/* change the value of number of bits in a specific port according to a mask (put ones on the desired pins)*/
bool Dio_Write_numOfBits(Port_t port_name, Data_t value, uint8 mask) {
	if (value < 0 || value > 255) {
		return ERROR;
	}
	switch (port_name) {
	case PORT_A:
		if (value == 1) {
			PORTA |= mask ;
		} else if(value == 0) {
			PORTA &= ~mask;			
		} else {
			PORTA |= value & mask;
		}		
		break;
	case PORT_B:
		if (value == 1) {
			PORTB |= mask ;
			} else if(value == 0) {
			PORTB &= ~mask;
			} else {
			PORTB |= value & mask;
		}
		break;
	case PORT_C:
		if (value == 1) {
			PORTC |= mask ;
			} else if(value == 0) {
			PORTC &= ~mask;
			} else {
			PORTC |= value & mask;
		}
		break;
	case PORT_D:
		if (value == 1) {
			PORTD |= mask ;
			} else if(value == 0) {
			PORTD &= ~mask;
			} else {
			PORTD |= value & mask;
		}
		break;
	default:
		return ERROR;
	}
	
	return SUCCESS;
}