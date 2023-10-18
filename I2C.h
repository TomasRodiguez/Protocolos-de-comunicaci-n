#include <MKL25Z4.h>
#ifndef I2C_h
#define I2C_h

void I2C_init();
void I2C_start();
void I2C_stop();
void I2C_write(uint8_t data);
uint8_t I2C_read();

#endif
