//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  Texas Instruments, Inc
//  July 2013
//***************************************************************************************

#include <msp430.h>
#include <stdint.h>
#include "PCBV5Mappings.hpp"
#include "pin.hpp"
#include "spi.hpp"

void toggleLEDs(){
    static uint8_t i = 0;
    switch (i){
        case 0: break;
        case 1: greenLED.toggle(); break;
        case 2: yellowLED.toggle(); break;
        case 3: redLED.toggle(); break;
    }
    i = (i+1) & 0b11;
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    greenLED.setAsOutput().clear();
    yellowLED.setAsOutput().clear();
    redLED.setAsOutput().clear();

    initialisePeripheralSPI();

    emitterEnable.setAsOutput().clear();
    /*
    payloadSpiMiso.setAsInput();
    payloadSpiMosi.setAsOutput().clear();
    payloadSpiSck.setAsOutput().clear();*/

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                                // to activate previously configured port settings
    while(1){
        toggleLEDs();
        __delay_cycles(50000);
    }
}


