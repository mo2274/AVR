/*
 * KeyPad.c
 *
 * Created: 27/04/2020 06:22:1
 *  Author: 
 */ 

#include "StdTypes.h"
#include "Dio.h"

Data_t keyPad_Read(Port_t port_name) {
	Data_t key = '\0';
	Data_t keypad_input;
	if (Dio_Write_port(port_name, 0xFF) == ERROR){
		return '\0';
	} 
	if (Dio_Write_pin(0, port_name, 0) == ERROR) {
		return '\0';
	}
	if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
		return '\0';
	}
	switch (keypad_input & 0xF0) {
		case 0xE0:
			key = '7';
			while ((keypad_input & 0xF0) == 0xE0) {
				if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
					return '\0';
				}
			};
			break;
		case 0xD0:
			key = '8';
			while ((keypad_input & 0xF0) == 0xD0) {
				if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
					return '\0';
				}
			};
			break;
		case 0xB0:
			key = '9';
			while ((keypad_input & 0xF0) == 0xB0) {
				if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
					return '\0';
				}
			};
			break;
		case 0x70:
			key = '/';
			while ((keypad_input & 0xF0) == 0x70) {
				if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
					return '\0';
				}
			};
			break;
		default:
			if (Dio_Write_pin(0, port_name, 1) == ERROR) {
				return '\0';
			}
			if (Dio_Write_pin(1, port_name, 0) == ERROR) {
				return '\0';
			}
			if (Dio_Read_port(port_name, &keypad_input)) {
				return '\0';
			}
			switch (keypad_input & 0xF0) {
				case 0xE0:
					key = '4';
					while ((keypad_input & 0xF0) == 0xE0) {
						if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
							return '\0';
						}
					};
					break;
				case 0xD0:
					key = '5';
					while ((keypad_input & 0xF0) == 0xD0) {
						if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
							return '\0';
						}
					};
					break;
				case 0xB0:
					key = '6';
					while ((keypad_input & 0xF0) == 0xB0) {
						if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
							return '\0';
						}
					};
					break;
				case 0x70:
					key = 'x';
					while ((keypad_input & 0xF0) == 0x70) {
						if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
							return '\0';
						}
					};
					break;
				default:
				if (Dio_Write_pin(1, port_name, 1) == ERROR) {
					return '\0';
				}
				if (Dio_Write_pin(2, port_name, 0) == ERROR) {
					return '\0';
				}
				if (Dio_Read_port(port_name, &keypad_input)) {
					return '\0';
				}
					switch (keypad_input & 0xF0) {
						case 0xE0:
							key = '1';
							while ((keypad_input & 0xF0) == 0xE0) {
								if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
									return '\0';
								}
							};
							break;
						case 0xD0:
							key = '2';
							while ((keypad_input & 0xF0) == 0xD0) {
								if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
									return '\0';
								}
							};
							break;
						case 0xB0:
							key = '3';
							while ((keypad_input & 0xF0) == 0xB0) {
								if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
									return '\0';
								}
							};
							break;
						case 0x70:
							key = '-';
							while ((keypad_input & 0xF0) == 0x70) {
								if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
									return '\0';
								}
							};
							break;
						default:
						if (Dio_Write_pin(2, port_name, 1) == ERROR) {
							return '\0';
						}
						if (Dio_Write_pin(3, port_name, 0) == ERROR) {
							return '\0';
						}
						if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
							return '\0';
						}
							switch (keypad_input & 0xF0){
								case 0xE0:
									key = 'C';
									while ((keypad_input & 0xF0) == 0xE0) {
										if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
											return '\0';
										}
									};
									break;
								case 0xD0:
									key = '0';
									while ((keypad_input & 0xF0) == 0xD0) {
										if (Dio_Read_port(port_name, &keypad_input)) {
											return '\0';
										}
									};
									break;
								case 0xB0:
									key = '=';
									while ((keypad_input & 0xF0) == 0xB0) {
										if (Dio_Read_port(port_name, &keypad_input)) {
											return '\0';
										}
									};
									break;
								case 0x70:
									key = '+';
									while ((keypad_input & 0xF0) == 0x70) {
										if (Dio_Read_port(port_name, &keypad_input) == ERROR) {
											return '\0';
										}
									};
									break;
								default:
									key = '\0';
									break;
							}
							break;
					}
					break;
			}
			break;
	}	
	return key;
}

