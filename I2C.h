#include <MKL25Z4.h>
#include "I2C.h"

void I2C_init(){
    SIM->SCGC4 |= SIM_SCGC4_I2C1;
    SIM->SCGC5 |= SIM_SCGC5_PORTC;

    PORTC->PCR[2] = (PORTC->PCR[8] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(5); // SDA
    PORTC->PCR[3] = (PORTC->PCR[9] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(5); // SCL

    I2C0->F = I2C_F_MULT(0) | I2C_F_ICR(24); //100kHz
    I2C0->C1 |= I2C_C0_IICEN;
}

void I2C_start(){
    I2C0->C0 |= I2C_C0_MST;
    I2C0->C0 |= I2C_C0_TX;
}

void I2C_stop(){
    I2C0->C0 &= ~I2C_C0_MST;
    I2C0->C0 &= ~I2C_C0_TX;
}

void I2C_write(uint8_t data){
    I2C0->D = data;

    while (!(I2C0->S & I2C_S_IICIF));
    I2C0->S |= I2C_S_IICIF;
}

uint8_t I2C_read(){
    I2C0->C0 &= ~I2C_C0_TX;

    while (!(I2C1->S & I2C_S_IICIF));
    I2C0->S |= I2C_S_IICIF;

    return I2C1->D;
}
