#ifndef IIC_H_
#define IIC_H_

#include <stdint.h>

void InitI2C1();
void I2CSendSingleByte(uint8_t slave_addr, uint8_t data);
void I2CSendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, uint8_t by[]);
uint8_t I2CReadBYTE(uint8_t slave_addr);
uint8_t readjibyte(uint8_t slave_addr,uint8_t ji_slave);
void  writejibyte(uint8_t slave_addr,uint8_t ji_slave,uint8_t data);
#endif
