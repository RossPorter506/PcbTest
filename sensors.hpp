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

int32_t getTetherBiasVoltage();

int32_t getTetherBiasCurrent();

/* Cathode Offset */

void setCathodeOffsetVoltage(uint32_t targetVoltageMillivolts);

int32_t getCathodeOffsetVoltage();

int32_t getCathodeOffsetCurrent();

/* Repeller */

int32_t getRepellerVoltage();


#endif /* SENSORS_HPP_ */
