/*
 * digipot.cpp
 *
 *  Created on: 30/06/2022
 *      Author: labadmin-lhef001
 */

#include <stdint.h>
#include "pin.hpp"
#include "PCBV5Mappings.hpp"
#include "spi.hpp"
#include "digipot.hpp"

static const uint32_t digipotMaxResistance = 100000;
static const uint8_t digipotWiperResistance = 100;
static const uint8_t digipotResolution = 255;

void Digipot::setChannelToValue(DigipotChannel channel, uint8_t value){
	payloadSpiSckPin.clear(); // Data on rising edge
	heaterDigipotChipSelectPin.clear();
	bitBangPeripheralSPISend(16, (channel << 8) + value);
	heaterDigipotChipSelectPin.set();
}

uint8_t Digipot::resistanceToCount(uint32_t targetResistance){
	uint8_t count;
	if (targetResistance > digipotMaxResistance){
		count = digipotResolution;
	}
	else if (targetResistance < digipotWiperResistance){
		count = 0;
	}
	else{
		count = ((targetResistance - digipotWiperResistance)*digipotResolution)/digipotMaxResistance;
	}
	return count;
}
