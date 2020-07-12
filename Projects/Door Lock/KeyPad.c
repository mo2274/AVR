/*
 * KeyPad.c
 *
 * Created: 27/04/2020 06:22:1
 *  Author: 
 */ 


#include "KeyPad.h" 

void keyPadInit(void) {
	KeyPadDDR = 0x0F;
	KeyPadPORT = 0xFF;
}

char readKey(void) {
	char key = '\0';
	KeyPadPORT = 0xFF;;
	
	CLRBET(KeyPadPORT, 0);
	switch (KeyPadPIN & 0xF0) {
		case 0xE0:
			key = '7';
			while ((KeyPadPIN & 0xF0) == 0xE0);
			break;
		case 0xD0:
			key = '8';
			while ((KeyPadPIN & 0xF0) == 0xD0);
			break;
		case 0xB0:
			key = '9';
			while ((KeyPadPIN & 0xF0) == 0xB0);
			break;
		case 0x70:
			key = '-';
			while ((KeyPadPIN & 0xF0) == 0x70);
			break;
		default:
			SETBET(KeyPadPORT, 0);
			CLRBET(KeyPadPORT, 1);
			switch ((KeyPadPIN & 0xF0) & 0xF0) {
				case 0xE0:
					key = '4';
					while ((KeyPadPIN & 0xF0) == 0xE0);
					break;
				case 0xD0:
					key = '5';
					while ((KeyPadPIN & 0xF0) == 0xD0);
					break;
				case 0xB0:
					key = '6';
					while ((KeyPadPIN & 0xF0) == 0xB0);
					break;
				case 0x70:
					key = 'x';
					while ((KeyPadPIN & 0xF0) == 0x70);
					break;
				default:
					SETBET(KeyPadPORT, 1);
					CLRBET(KeyPadPORT, 2);
					switch ((KeyPadPIN & 0xF0) & 0xF0) {
						case 0xE0:
							key = '1';
							while ((KeyPadPIN & 0xF0) == 0xE0);
							break;
						case 0xD0:
							key = '2';
							while ((KeyPadPIN & 0xF0) == 0xD0);
							break;
						case 0xB0:
							key = '3';
							while ((KeyPadPIN & 0xF0) == 0xB0);
							break;
						case 0x70:
							key = '-';
							while ((KeyPadPIN & 0xF0) == 0x70);
							break;
						default:
							SETBET(KeyPadPORT, 2);
							CLRBET(KeyPadPORT, 3);
							switch ((KeyPadPIN & 0xF0) & 0xF0){
								case 0xE0:
									key = 'C';
									while ((KeyPadPIN & 0xF0) == 0xE0);
									break;
								case 0xD0:
									key = '0';
									while ((KeyPadPIN & 0xF0) == 0xD0);
									break;
								case 0xB0:
									key = '=';
									while ((KeyPadPIN & 0xF0) == 0xB0);
									break;
								case 0x70:
									key = '+';
									while ((KeyPadPIN & 0xF0) == 0x70);
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

