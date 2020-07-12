/*
 * SevenSegment.h
 *
 * Created: 23/04/2020 01:36:48 ص
 *  Author: scc
 */ 
#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_
#include "StdTypes.h"
/*
 *		uint8_t display(uint8_t number, Port_t port_name)
 * Function to display a number on seven segment
 * @param: The function will take a number between 0 and F and the port name (A, B, C, D)
 *@return: The function will return	SUCCESS if every thing done correctly and ERROR otherwise
 */
bool SevenSeg_Display(Data_t number, Port_t port_name);

#endif /* SEVENSEGMENT_H_ */