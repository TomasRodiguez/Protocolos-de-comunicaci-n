#include <MKL25Z4.h>
#ifndef SPI_H
#define SPI_H

void SPI_init();
void SPI_sendData(uint8_t d);
uint8_t SPI_receiveData();

#endif
