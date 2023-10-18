#include <MKL25Z4.h>
#include "SPI.h"

void SPI_init(){
    SIM->SCGC4 |= SIM_SCGC4_SPI0;
    SIM->SCGC5 |= SIM_SCGC5_PORTD;

    PORTD->PCR[1] = (PORTD->PCR[1] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(2); // SCK
    PORTD->PCR[2] = (PORTD->PCR[2] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(2); // MOSI
    PORTD->PCR[3] = (PORTD->PCR[3] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(2); // MISO

    SPI1->C1 = 0;
    SPI1->BR = 7;

    SPI1->C1 |= SPI_C1_SPE;
}

void SPI_sendData(uint8_t d){
    while (!(SPI1->S & SPI_S_SPTEF));
    SPI1->D = d;
}

uint8_t SPI_receiveData(){
    while (!(SPI1->S & SPI_S_SPRF));
    return SPI1->D;
}
