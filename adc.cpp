/*
 * adc.cpp
 *
 *  Created on: 7/07/2022
 *      Author: labadmin-lhef001
 */

#include "pin.hpp"
#include "PCBV5Mappings.hpp"
#include "spi.hpp"
#include "adc.hpp"

// Note: ADC always sends the value of IN0 when first selected, second reading will be from the channel provided.
uint16_t readValueFromADCSensor(const Sensor &sensor){
	uint16_t result = 0;
	payloadSpiSckPin.set(); // Data on falling edge

	switch(sensor.adc){
	case TemperatureADC: boardTemperatureADCChipSelectPin.setAsOutput().clear(); break;
	case TetherADC: 	 tetherMeasurementADCChipSelectPin.setAsOutput().clear(); break;
	case MiscADC: 		 miscADCChipSelectPin.setAsOutput().clear(); break;
	}

	if (sensor.channel == IN0){
		bitBangPeripheralSPIReceive(4); // ADC setting up, so no valid output yet, and we don't care about setting the channel if (channel == IN0)
		result = bitBangPeripheralSPIReceive(12);
	}
	else{

		// ADC takes four cycles to track signal. Nothing to do for first two.
		bitBangPeripheralSPIReceive(2);

		// Send channel. ADC Sends the first bit of IN0, which we don't care about.
		bitBangPeripheralSPISend(3, sensor.channel);

		//Wait out the rest of the IN0 reading being sent to us
		bitBangPeripheralSPIReceive(11);

		// ADC is now tracking the channel we want
		bitBangPeripheralSPIReceive(4);

		//Finally receive ADC value from the channel we care about
		result = bitBangPeripheralSPIReceive(12);

	}
	return result;
}

// Given an ADC count, returns the voltage in millivolts
uint16_t adcCountToVoltage(uint16_t count){
	const uint16_t maxVoltageInMillivolts = 5000;
	const uint16_t adcResolution = 4095;
	return ((uint32_t)count * maxVoltageInMillivolts) / adcResolution;
}

