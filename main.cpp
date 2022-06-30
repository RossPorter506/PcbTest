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
#include "dac.hpp"
#include "digipot.hpp"

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

enum PayloadState{
	payloadOff=0,
	payloadOn=1,
};

void setChipSelects(PayloadState state){
	boardTemperatureADCChipSelect.setAsOutput().set();
	miscADCChipSelect.setAsOutput().set();

	if (state == payloadOn){ //isolators are not powered when payload off, pins should not be set high.
		heaterDigipotChipSelect.setAsOutput().set(); //heater
		tetherMeasurementADCChipSelect.setAsOutput().set();
		dacChipSelect.setAsOutput().set(); //tether bias, cathode offset
	}
}

void testDigipot(){
	payloadEnable.setAsOutput().set();
	heaterEnable.setAsOutput().clear();

	__delay_cycles(1000);

	setChipSelects(payloadOn);

	setDigipotChannelToValue(Channel1, 0xff);
	heaterEnable.set();

	while (1){
		redLED.toggle();

		if ( redLED.isHigh() ){
			setDigipotChannelToValue(Channel1, 0x00);
		}
		else{
			setDigipotChannelToValue(Channel1, 0xff);
		}
		__delay_cycles(4000000);
	}
}


void testDAC(){
	payloadEnable.setAsOutput().set(); // turn on supply that feeds all tether components
	//heaterEnable.setAsOutput().clear();

	__delay_cycles(1000); // wait for payload to start up - necessary?

	heaterDigipotChipSelect.setAsOutput().set();
	dacChipSelect.setAsOutput().set();

	dacInit();
	dacCommand(WriteToAndUpdateRegisterX, ChannelA, 0xfff); // write 0xfff to channel DAC A, and update it

	dacCommand(WriteToAndUpdateRegisterX, ChannelC, 0xFFF);
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    greenLED.setAsOutput().clear();
    yellowLED.setAsOutput().clear();
    redLED.setAsOutput().clear();

    //initialisePeripheralSPI();
    InitialiseBitBangSPI();

    //boardTemperatureADCChipSelect.setAsOutput().set();
    //cathodeSwitch.setAsOutput().set(); // Connect cathode+ to exterior

    deploySense1.setAsInput();
    deploySense2.setAsInput();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    //testDAC();
    //testDigipot();

    while(1){
    	//__delay_cycles(1000000);
    	greenLED.setToValue(deploySense1.value());
    	redLED.setToValue(deploySense2.value());
    }
}
