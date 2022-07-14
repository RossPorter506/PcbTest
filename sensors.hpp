/*
 * sensors.hpp
 *
 *  Created on: 14/07/2022
 *      Author: labadmin-lhef001
 */

#ifndef SENSORS_HPP_
#define SENSORS_HPP_


uint8_t getLMSTemperature(const LMSTemperatureSensor &sensor);

uint8_t getPayloadTemperature(const PayloadTemperatureSensor &sensor);

/* Supplies */
/* Heater */

void setHeaterVoltage(uint16_t targetVoltageMillivolts);

uint16_t getHeaterVoltage();

uint16_t getHeaterCurrent();

/* Tether Bias */

void setTetherBiasVoltage(uint32_t targetVoltageMillivolts);

uint32_t getTetherBiasVoltage(uint32_t targetVoltageMillivolts);

uint32_t getTetherBiasCurrent(uint32_t targetVoltageMillivolts);

/* Cathode Offset */

void setCathodeOffsetVoltage(uint32_t targetVoltageMillivolts);

uint32_t getCathodeOffsetVoltage(uint32_t targetVoltageMillivolts);

uint32_t getCathodeOffsetCurrent(uint32_t targetVoltageMillivolts);

/* Repeller */

uint32_t getRepellerVoltage();


#endif /* SENSORS_HPP_ */
