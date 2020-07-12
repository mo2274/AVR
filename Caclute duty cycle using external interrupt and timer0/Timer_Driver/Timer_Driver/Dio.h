/*
 * Dio.h
 *
 * Created: 11/05/2020 06:32:43 
 *  Author: Mohamed Abo Raia
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "StdTypes.h"
#include "Dio_Config.h"

/* type of direction */
typedef enum {
	INPUT,
	OUTPUT
}Direction_t;
/* type of pull up resistor */
typedef enum {
	PULL_UP,
	NO_PULL_UP
}Pull_up_t;

/* configuration for single pin */
typedef struct {
	Direction_t       direction;
	uint8             channel_num;
	Pull_up_t         pull_up;
	Data_t            init_value;
	volatile uint8*   ddr;
	volatile uint8*   port;
	volatile uint8*   pin;
}Dio_PinConfig_t;
/* configuration for single port */
typedef struct {
	Direction_t       direction;
	Pull_up_t         pull_up;
	Data_t            init_value;
	volatile uint8*   ddr;
	volatile uint8*   port;
	volatile uint8*   pin;
}Dio_PortConfig_t;
/* configuration for all ports and pins */ 
typedef struct {
	Dio_PinConfig_t  pins_config[NUM_OF_CHANNELS];
	Dio_PortConfig_t port_config[NUM_OF_PORTS];	
}Dio_Config_t;
/*
 *                 bool Dio_init(Dio_Config_t *init)
 * Function to initialize all the channels according to the configuration 
 * @param:   The function will take the address of the configuration struct
 * @return : The function will return SUCCESS if every thing done correctly and ERROR otherwise. 
 */
bool Dio_init(void);
/*
 *                 Dio_Read_pin(Pin_type pin_num, Port_t port_name, Data_t* location)
 * Function to read the state of a single pin
 * @param:   The function will take pin number and the name of the port(A, B, C, D) and location to put the state in.
 * @return : The function will return the SUCCESS if every thing done correctly and ERROR otherwise. 
 */
bool Dio_Read_pin(Pin_type pin_num, Port_t port_name, Data_t* location);
/*
 *                 Dio_Write_pin(uint8 pin_num, Port_t port_name, Data_t value)
 * Function to change the state of a single pin
 * @param:   The function will take pin number and the name of the port(A, B, C, D) and the new state
 * @return : The function will return the SUCCESS if every thing done correctly and ERROR otherwise. 
 */
bool Dio_Write_pin(Pin_type pin_num, Port_t port_name, Data_t value);
/*
 *                 Dio_Read_port(Port_t port_name, Data_t* location)
 * Function to read the state of a specific port
 * @param:   The function will take the name of the port(A, B, C, D) and a location to put the value in
 * @return : The function will return the SUCCESS if every thing done correctly and ERROR otherwise.
 */
bool Dio_Read_port(Port_t port_name, Data_t* location);
/*
 *                 Dio_Write_port(Port_t port_name, Data_t value)
 * Function to change the state of a specific port
 * @param:   The function will take the name of the port(A, B, C, D) and the new value
 * @@return : The function will return the SUCCESS if every thing done correctly and ERROR otherwise.
 */
bool Dio_Write_port(Port_t port_name, Data_t value);
/*
 *                 Dio_set_direction(Pin_type pin_num, Port_t port_name, Direction_t direction)
 * Function to change the direction of a specific pin
 * @param:   The function will take the number of the bin and the name of the port(A, B, C, D) and the new direction
 * @@return : The function will return the SUCCESS if every thing done correctly and ERROR otherwise.
 */
bool Dio_setPin_direction(Pin_type pin_num, Port_t port_name, Direction_t direction);
/*
 *
 *
 *
 */
bool Dio_Write_numOfBits(Port_t port_name, Data_t value, uint8 mask);
 

#endif /* DIO_H_ */