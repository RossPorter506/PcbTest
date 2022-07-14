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

/* Temperature */

uint8_t getLMSTemperature(const LMSTemperatureSensor &sensor){
	uint16_t adcVoltage = ADC::readVoltageFrom(sensor);
	return LMS_TEMPERATURE_EQ(adcVoltage);
}

uint8_t getPayloadTemperature(const PayloadTemperatureSensor &sensor){
	uint16_t adcVoltage = ADC::readVoltageFrom(sensor);
	return PAYLOAD_TEMPERATURE_EQ(adcVoltage);
}

/* Supplies */
/* Heater */

void setHeaterVoltage(uint16_t targetVoltageMillivolts){
	if (targetVoltageMillivolts > HEATER_MAX_VOLTAGE_MILLIVOLTS){
		targetVoltageMillivolts = HEATER_MAX_VOLTAGE_MILLIVOLTS;
	}
	uint32_t digitpotTargetResistance = HEATER_TARGET_VOLTAGE_TO_DIGIPOT_RESISTANCE(targetVoltageMillivolts);
	uint8_t digipotDigitalValue = Digipot::resistanceToCount(digitpotTargetResistance);
	Digipot::setChannelToValue(heaterDigipotChannel, digipotDigitalValue);
}

uint16_t getHeaterVoltage(){
	uint16_t adcVoltage = ADC::readVoltageFrom(heaterVoltageSensor);
	return HEATER_VOLTAGE_EQ(adcVoltage);
}

uint16_t getHeaterCurrent(){
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

uint32_t getTetherBiasVoltage(uint32_t targetVoltageMillivolts){
	uint16_t adcVoltage = ADC::readVoltageFrom(tetherBiasVoltageSensor);
	return TETHER_BIAS_VOLTAGE_EQ(adcVoltage);
}

uint32_t getTetherBiasCurrent(uint32_t targetVoltageMillivolts){
	uint16_t adcVoltage = ADC::readVoltageFrom(tetherBiasCurrentSensor);
	return TETHER_BIAS_CURRENT_EQ(adcVoltage);
}

/* Cathode Offset */

void setCathodeOffsetVoltage(uint32_t targetVoltageMillivolts){
	if (targetVoltageMillivolts > CATHODE_OFFSET_MAX_VOLTAGE_MILLIVOLTS){
		targetVoltageMillivolts = CATHODE_OFFSET_MAX_VOLTAGE_MILLIVOLTS;
	}
	uint16_t dacVoltage = CATHODE_OFFSET_TARGET_VOLTAGE_TO_DAC_VOLTAGE(targetVoltageMillivolts);
	uint16_t count = DAC::voltageToCount(dacVoltage);
	DAC::sendCommand(WriteToAndUpdateRegisterX, cathodeOffsetSupplyControlChannel, count);
}

uint32_t getCathodeOffsetVoltage(uint32_t targetVoltageMillivolts){
	uint16_t adcVoltage = ADC::readVoltageFrom(cathodeOffsetVoltageSensor);
	return CATHODE_OFFSET_VOLTAGE_EQ(adcVoltage);
}

uint32_t getCathodeOffsetCurrent(uint32_t targetVoltageMillivolts){
	uint16_t adcVoltage = ADC::readVoltageFrom(cathodeOffsetCurrentSensor);
	return CATHODE_OFFSET_CURRENT_EQ(adcVoltage);
}

/* Repeller */

uint32_t getRepellerVoltage(){
	uint16_t adcVoltage = ADC::readVoltageFrom(repellerVoltageSensor);
	return REPELLER_VOLTAGE_EQ(adcVoltage);
}
