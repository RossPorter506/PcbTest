#include <msp430.h>
#include "pin.hpp"
#include "spi.hpp"
#include "PCBV5Mappings.hpp"

void initialisePeripheralSPI() {

    // Set up MISO line
    payloadSpiMiso.setFunction(primary);

    // Set up MOSI line and clock line
    payloadSpiMosi.setFunction(primary);
    payloadSpiSck.setFunction(primary);

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
	payloadSpiMiso.setAsInput();
	payloadSpiMosi.setAsOutput().clear();
	payloadSpiSck.setAsOutput().clear();
}

void bitBangPeripheralSPI(uint8_t len, uint32_t val){
	uint8_t currentPos = 0;
	while (currentPos < len){
		if ( val & ((uint32_t)1 << (len - currentPos - 1)) ){
			payloadSpiMosi.set();
		}
		else{
			payloadSpiMosi.clear();
		}

		payloadSpiSck.set();
		__delay_cycles(80); //duty cycle correction
		payloadSpiSck.clear();

		currentPos++;
	}
}
