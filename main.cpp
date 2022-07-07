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
        case 1: greenLEDPin.toggle(); break;
        case 2: yellowLEDPin.toggle(); break;
        case 3: redLEDPin.toggle(); break;
    }
    i = (i+1) & 0b11;
}

enum PayloadState{
	payloadIsOff=0,
	payloadIsOn=1,
};

void setChipSelects(PayloadState state){
	boardTemperatureADCChipSelectPin.setAsOutput().set();
	miscADCChipSelectPin.setAsOutput().set();

	if (state == payloadIsOn){ //isolators are not powered when payload off, pins should not be set high.
		heaterDigipotChipSelectPin.setAsOutput().set(); //heater
		tetherMeasurementADCChipSelectPin.setAsOutput().set();
		dacChipSelectPin.setAsOutput().set(); //tether bias, cathode offset
	}
}

void testDigipot(){
	payloadEnablePin.setAsOutput().set();
	heaterEnablePin.setAsOutput().clear();

	__delay_cycles(1000);

	setChipSelects(payloadIsOn);

	setDigipotChannelToValue(heaterDigipotChannel, 0xff);
	heaterEnablePin.set();

	while (1){
		redLEDPin.toggle();

		if ( redLEDPin.isHigh() ){
			setDigipotChannelToValue(heaterDigipotChannel, 0x00);
		}
		else{
			setDigipotChannelToValue(heaterDigipotChannel, 0xff);
		}
		__delay_cycles(4000000);
	}
}


void testDAC(){
	payloadEnablePin.setAsOutput().set(); // turn on supply that feeds all tether components
	//heaterEnable.setAsOutput().clear();
	setChipSelects(payloadIsOn);

	__delay_cycles(1000); // wait for payload to start up - necessary?

	heaterDigipotChipSelectPin.setAsOutput().set();
	dacChipSelectPin.setAsOutput().set();

	dacInit();
	dacCommand(WriteToAndUpdateRegisterX, cathodeOffsetSupplyControlChannel, 0xfff); // write 0xfff to channel DAC A, and update it
}

void testADC(){
	uint16_t result1 = readValueFromADCSensor((Sensor){TetherADC, IN0}); //usually you would pass in the Sensor you want from PCBMappings, but for testing this is fine.
	uint16_t result2 = readValueFromADCSensor((Sensor){TemperatureADC, IN0});
	uint16_t result3 = readValueFromADCSensor((Sensor){MiscADC, IN0});
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    greenLEDPin.setAsOutput().clear();
    yellowLEDPin.setAsOutput().clear();
    redLEDPin.setAsOutput().clear();

    //initialisePeripheralSPI();
    InitialiseBitBangSPI();

    //boardTemperatureADCChipSelect.setAsOutput().set();
    //cathodeSwitch.setAsOutput().set(); // Connect cathode+ to exterior

    deploySense1Pin.setAsInput();
    deploySense2Pin.setAsInput();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    //testDAC();
    //testDigipot();
    testADC();

    while(1){
    	//__delay_cycles(1000000);
    	greenLEDPin.setToValue(deploySense1Pin.value());
    	redLEDPin.setToValue(deploySense2Pin.value());
    }
}
