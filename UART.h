#include <MKL25Z4.h>
#include "UART.h"

#define UART1_baud 9600

void UART1_init(){
    SIM->SCGC4 |= SIM_SCGC4_UART1;
    SIM->SCGC5 |= SIM_SCGC5_PORTA;
    
    PORTA->PCR[1] = (PORTA->PCR[1] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(3);
    PORTA->PCR[2] = (PORTA->PCR[2] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(3);

    UART1->BDH = 0;
    UART1->BDL = (SystemCoreClock / (16 * UART1_baud)) & 0xFF;
    
    UART1->C2 |= UART_C2_TE | UART_C2_RE;
}

void UART1_senData(char d){
    while (!(UART1->S1 & UART_S1_TDRE));
    UART1->D = d;
}

char UART1_receiveData(){
    while (!(UART1->S1 & UART_S1_RDRF));
    return UART0->D;
}
