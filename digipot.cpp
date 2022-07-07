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

void setDigipotChannelToValue(DigipotChannel channel, uint8_t value){
	payloadSpiSckPin.clear(); // Data on rising edge
	heaterDigipotChipSelectPin.clear();
	bitBangPeripheralSPISend(9, (channel << 8) + value);
	heaterDigipotChipSelectPin.set();
}

