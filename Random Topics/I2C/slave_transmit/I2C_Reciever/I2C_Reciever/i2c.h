/*
 * i2c.h
 *
 * Created: 28/06/2020 08:56:28 م
 *  Author: scc
 */ 


#ifndef I2C_H_
#define I2C_H_


void I2C_Check_StatusCode(uint8_t status_code, uint8_t num);
void I2C_Clear_INT_AndEnable();
void I2C_Wait_Until_Flag_Set(uint8_t num);
void I2C_init(uint8_t address);
uint8_t I2C_Rx(void);

#endif /* I2C_H_ */