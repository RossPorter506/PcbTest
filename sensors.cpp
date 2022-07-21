/*
 * sensors.cpp
 *
 *  Created on: 14/07/2022
 *      Author: labadmin-lhef001
 */
#include "pin.hpp"
#include "PCBV5Mappings.hpp"
#include "spi.hpp"
#include "adc.hpp"
#include "digipot.hpp"
#include <stdint.h>

/***** Temperature *****/

uint8_t getLMSTemperature(const LMSTemperatureSensor &sensor){ //Temperature in Kelvin
	uint16_t adcVoltage = ADC::readVoltageFrom(sensor);
	return LMS_TEMPERATURE_EQ(adcVoltage);
}

uint8_t getPayloadTemperature(const PayloadTemperatureSensor &sensor){ //Temperature in Kelvin
	uint16_t adcVoltage = ADC::readVoltageFrom(sensor);
	return PAYLOAD_TEMPERATURE_EQ(adcVoltage);
}

/***** Supplies *****/
/* Heater */

void setHeaterVoltage(uint16_t targetVoltageMillivolts){ // CHECKED: Undershoots by about 8%. Changing to linear control on the next board anyway.
	if (targetVoltageMillivolts > HEATER_MAX_VOLTAGE_MILLIVOLTS){
		targetVoltageMillivolts = HEATER_MAX_VOLTAGE_MILLIVOLTS;
	}
	uint32_t digitpotTargetResistance = HEATER_TARGET_VOLTAGE_TO_DIGIPOT_RESISTANCE(targetVoltageMillivolts);
	uint8_t digipotDigitalValue = Digipot::resistanceToCount(digitpotTargetResistance);
	Digipot::setChannelToValue(heaterDigipotChannel, digipotDigitalValue);
}

int16_t getHeaterVoltage(){ // CHECKED
	uint16_t adcVoltage = ADC::readVoltageFrom(heaterVoltageSensor);
	return HEATER_VOLTAGE_EQ(adcVoltage);
}

int16_t getHeaterCurrent(){ // CHECKED: Correct order of magnitude, limited by missing 1mohm sense resistor on PCB, using a solder bridge instead >.<
	uint16_t adcVoltage = ADC::readVoltageFrom(heaterCurrentSensor);
	return HEATER_CURRENT_EQ(adcVoltage);
}

/* Tether Bias */

void setTetherBiasVoltage(uint32_t targetVoltageMillivolts){
	if (targetVoltageMillivolts > TETHER_BIAS_MAX_VOLTAGE_MILLIVOLTS){
		targetVoltageMillivolts = TETHER_BIAS_MAX_VOLTAGE_MILLIVOLTS;
	}
	uint16_t dacVoltage = TETHER_BIAS_TARGET_VOLTAGE_TO_DAC_VOLTAGE(targetVoltageMillivolts);
	uint16_t count = DAC::voltageToCount(dacVoltage);
	DAC::sendCommand(WriteToAndUpdateRegisterX, tetherBiasSupplyControlChannel, count);
}

int32_t getTetherBiasVoltage(){
	uint16_t adcVoltage = ADC::readVoltageFrom(tetherBiasVoltageSensor);
	return TETHER_BIAS_VOLTAGE_EQ(adcVoltage);
}

int32_t getTetherBiasCurrent(){
	uint16_t adcVoltage = ADC::readVoltageFrom(tetherBiasCurrentSensor);
	return TETHER_BIAS_CURRENT_EQ(adcVoltage);
}

/* Cathode Offset */

void setCathodeOffsetVoltage(uint32_t targetVoltageMillivolts){ // CHECKED
	if (targetVoltageMillivolts > CATHODE_OFFSET_MAX_VOLTAGE_MILLIVOLTS){
		targetVoltageMillivolts = CATHODE_OFFSET_MAX_VOLTAGE_MILLIVOLTS;
	}
	uint16_t dacVoltage = CATHODE_OFFSET_TARGET_VOLTAGE_TO_DAC_VOLTAGE(targetVoltageMillivolts);
	uint16_t count = DAC::voltageToCount(dacVoltage);
	DAC::sendCommand(WriteToAndUpdateRegisterX, cathodeOffsetSupplyControlChannel, count);
}

int32_t getCathodeOffsetVoltage(){ // CHECKED
	uint16_t adcVoltage = ADC::readVoltageFrom(cathodeOffsetVoltageSensor);
	return CATHODE_OFFSET_VOLTAGE_EQ(adcVoltage);
}

int32_t getCathodeOffsetCurrent(){
	uint16_t adcVoltage = ADC::readVoltageFrom(cathodeOffsetCurrentSensor);
	return CATHODE_OFFSET_CURRENT_EQ(adcVoltage);
}

/* Repeller */

int32_t getRepellerVoltage(){
	uint16_t adcVoltage = ADC::readVoltageFrom(repellerVoltageSensor);
	return REPELLER_VOLTAGE_EQ(adcVoltage);
}
