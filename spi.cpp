#include <msp430.h>
#include "pin.hpp"
#include "spi.hpp"
#include "PCBV5Mappings.hpp"

void initialisePeripheralSPI() {

    // Set up MISO line
    payloadSpiMisoPin.setFunction(primary);

    // Set up MOSI line and clock line
    payloadSpiMosiPin.setFunction(primary);
    payloadSpiSckPin.setFunction(primary);

    //Disable the USCI Module
    UCB1CTL1 |= UCSWRST;

    //Reset OFS_UCBxCTLW0 values
    UCB1CTL0 &= ~(UCCKPH + UCCKPL + UC7BIT + UCMSB + UCMST + UCMODE_3 + UCSYNC);
    UCB1CTL0 |= (UCMSB + UCMST + UCCKPL + UCSYNC);

    //Reset OFS_UCBxCTLW0 values
    UCB1CTL1 &= ~(UCSSEL_3);
    //Select Clock
    UCB1CTL1 |= UCSSEL_2; // SMCLK

    //Set clock divider
    //HWREG16(baseAddress + OFS_UCBxBRW) =
    //   (uint16_t)(param->clockSourceFrequency / param->desiredSpiClock);
    UCB1BRW = 2; //

    UCB1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
}

void InitialiseBitBangSPI(){
	payloadSpiMisoPin.setAsInput();
	payloadSpiMosiPin.setAsOutput().clear();
	payloadSpiSckPin.setAsOutput().clear();
}

//These functions only toggle the sck pin, make sure it is the right value first. Low for data on rising edge, high for data on falling edge
void bitBangPeripheralSPISend(uint8_t len, uint32_t val){
	uint8_t currentPos = 0;
	while (currentPos < len){
		if ( val & ((uint32_t)1 << (len - currentPos - 1)) ){
			payloadSpiMosiPin.set();
		}
		else{
			payloadSpiMosiPin.clear();
		}

		payloadSpiSckPin.toggle();
		__delay_cycles(80); //duty cycle correction
		payloadSpiSckPin.toggle();

		currentPos++;
	}
}

uint32_t bitBangPeripheralSPIReceive(uint8_t len){
	uint32_t result = 0;
	uint8_t currentPos = 0;
	while (currentPos < len){

		payloadSpiSckPin.toggle();
		__delay_cycles(40); //duty cycle correction
		result = (result << 1) | payloadSpiMisoPin.value(); // read some time after edge to give slave time to output
		payloadSpiSckPin.toggle();

		currentPos++;
	}
	return result;
}

uint32_t bitBangPeripheralSPIDuplex(uint8_t len, uint32_t val){
	uint32_t result = 0;
	uint8_t currentPos = 0;
	while (currentPos < len){
		// Write before edge
		if ( val & ((uint32_t)1 << (len - currentPos - 1)) ){
			payloadSpiMosiPin.set();
		}
		else{
			payloadSpiMosiPin.clear();
		}

		payloadSpiSckPin.toggle(); // active edge
		__delay_cycles(80); //duty cycle correction
		result = (result << 1) | payloadSpiMisoPin.value(); // read some time after edge to give slave time to output
		payloadSpiSckPin.toggle();

		currentPos++;
	}
	return result;
}
