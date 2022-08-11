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
#include "sensors.hpp"
#include "serial.hpp"

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

void disableChipSelects(){
	boardTemperatureADCChipSelectPin.setAsOutput().set();
	miscADCChipSelectPin.setAsOutput().set();

	//Payload chip selects should not be set high while payload is off - isolators are unpowered and may be damaged.
	if (payloadEnablePin.getCurrentFunction() == gpio && payloadEnablePin.isOutput() && payloadEnablePin.isHigh()) {
		heaterDigipotChipSelectPin.setAsOutput().set();
		tetherMeasurementADCChipSelectPin.setAsOutput().set();
		dacChipSelectPin.setAsOutput().set(); //tether bias, cathode offset
	}
}

void testDigipot(){
	payloadEnablePin.setAsOutput().set();
	heaterEnablePin.setAsOutput().clear();

	__delay_cycles(1000);

	disableChipSelects();

	Digipot::setChannelToValue(heaterDigipotChannel, 8);
	heaterEnablePin.set();

	while (1){
		redLEDPin.toggle();

		if ( redLEDPin.isHigh() ){
			Digipot::setChannelToValue(heaterDigipotChannel, 0);
		}
		else{
			Digipot::setChannelToValue(heaterDigipotChannel, 0xff);
		}
		__delay_cycles(1000000);
	}
}


void testDAC(){
	payloadEnablePin.setAsOutput().set(); // turn on supply that feeds all tether components
	//heaterEnable.setAsOutput().clear();
	disableChipSelects();

	__delay_cycles(1000); // wait for payload to start up - necessary?

	heaterDigipotChipSelectPin.setAsOutput().set();
	dacChipSelectPin.setAsOutput().set();

	DAC::init();
	DAC::sendCommand(WriteToAndUpdateRegisterX, cathodeOffsetSupplyControlChannel, 0); // write 0xfff to channel DAC A, and update it

	/*while (1) {
		uint16_t x = ADC::readCountFrom(tetherBiasVoltageSensor);
		Serial::printNumLn(x);
		__delay_cycles(100000);
		redLEDPin.toggle();
	}*/
}

void testADC(){
	//usually you would pass in the Sensor you want from PCBMappings rather than creating an initialiser list here, but for testing we just want to try the first channel from each ADC
	//uint16_t result1 = ADC::readCountFrom((Sensor){TetherADC, IN0});
	//uint16_t result2 = ADC::readCountFrom((Sensor){TemperatureADC, IN0});
	//uint16_t result3 = ADC::readCountFrom((Sensor){MiscADC, IN0});
}

typedef uint32_t setterType;
typedef int32_t getterType;
typedef void (*SetFunction)(setterType);
typedef getterType (*GetFunction)(void);

void sweepAndMeasure(SetFunction setTo, GetFunction measureResult, uint32_t minValue, uint32_t maxValue, bool verbose){
	tetherLMSReceiverEnablePin.setAsOutput().clear();
	for (setterType target = minValue; target <= maxValue; target += (maxValue-minValue)/10 ){
		setTo(target);
		if (verbose) Serial::printStr("Set to: ");
		Serial::printNum(target);
		Serial::printStr(", ");

		__delay_cycles(1000000);

		int32_t avg = 0;
		tetherLMSReceiverEnablePin.toggle(); // Trigger oscilloscope
		for (uint8_t i = 0; i < 100; i++) {
			avg += measureResult();
		}
		tetherLMSReceiverEnablePin.toggle();
		avg /= 100;

		redLEDPin.toggle();
		greenLEDPin.toggle();

		if (verbose) Serial::printStr("read as: ");
		Serial::printNum(avg);
		if (verbose) Serial::printStr(". Record the true value, then press any key to continue");
		Serial::printLn();



		char receivedChar = Serial::waitForPacket();

		if (receivedChar == 'b'){
			target -= (maxValue-minValue)/5;
		}
		else if (receivedChar == 'a'){
			target -= (maxValue-minValue)/10;
		}
	}
	Serial::printLn();
	__delay_cycles(1000000);
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

    //Serial setup
    UCA1CTLW0 = UCSWRST__ENABLE;
    UCA1MCTLW = 0xD600u;
    UCA1BRW = 8u;
    UCA1CTLW0 = UCSSEL__SMCLK | UCSWRST__DISABLE;

    P4SEL0 |= BIT2 | BIT3;

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    greenLEDPin.set();
    payloadEnablePin.setAsOutput().set(); // turn on supply that feeds all tether components
    heaterEnablePin.setAsOutput().clear();
    //testDAC();
    //testDigipot();

    disableChipSelects();
    DAC::init();
    //DAC::sendCommand(WriteToAndUpdateRegisterX, cathodeOffsetSupplyControlChannel, 4095);
    //testADC();
//    testSupplyControl();
    //setCathodeOffsetVoltage(0);
    //setHeaterVoltage(0);
    __delay_cycles(1000000);

    while(1){
    	__delay_cycles(100000);
    	//greenLEDPin.setToValue(deploySense1Pin.value());
    	//redLEDPin.setToValue(deploySense2Pin.value());
    	/*uint32_t avg = 0;
    	for (uint8_t i = 0; i < 100; i++){
    		avg += getHeaterVoltage();
    	}
    	avg /= 100;
    	Serial::printNumLn(avg);
    	redLEDPin.toggle();*/
    	sweepAndMeasure(setCathodeOffsetVoltage, getCathodeOffsetCurrent, CATHODE_OFFSET_MIN_VOLTAGE_MILLIVOLTS, CATHODE_OFFSET_MAX_VOLTAGE_MILLIVOLTS, false);

    }
}
