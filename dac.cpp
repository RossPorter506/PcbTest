/*
 * dac.cpp
 *
 *  Created on: 30/06/2022
 *      Author: labadmin-lhef001
 */

#include <stdint.h>
#include "pin.hpp"
#include "PCBV5Mappings.hpp"
#include "dac.hpp"
#include "spi.hpp"

static const uint16_t dacResolution = 4095;

void DAC::sendCommand(DACCommand command, DACChannel channel, uint16_t value){
	payloadSpiSckPin.clear(); //Data on rising edge
	dacChipSelectPin.clear();
	uint32_t total = (uint32_t)((uint32_t)command << 20) | ((uint32_t)channel << 16) | ((uint32_t)value << 4);
	bitBangPeripheralSPISend(24, total);
	dacChipSelectPin.set();
}

void DAC::init(){
	sendCommand(SelectExternalReference, ChannelA, 0x000); // select external reference
}

uint16_t DAC::voltageToCount(uint16_t targetVoltageMillivolts){
	if (targetVoltageMillivolts > DAC_VCC_VOLTAGE_MILLIVOLTS){
		targetVoltageMillivolts = DAC_VCC_VOLTAGE_MILLIVOLTS;
	}
	return ((uint32_t)targetVoltageMillivolts * dacResolution) / DAC_VCC_VOLTAGE_MILLIVOLTS;
}



