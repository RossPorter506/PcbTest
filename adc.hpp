/*
 * adc.hpp
 *
 *  Created on: 7/07/2022
 *      Author: labadmin-lhef001
 */

#ifndef ADC_HPP_
#define ADC_HPP_

enum TargetADC {
	TetherADC,
	TemperatureADC,
	MiscADC,
};

enum ADCChannel {
	IN0=0,
	IN1=1,
	IN2=2,
	IN3=3,
	IN4=4,
	IN5=5,
	IN6=6,
	IN7=7,
};

struct Sensor {
	TargetADC adc;
	ADCChannel channel;
};

struct LMSTemperatureSensor : public Sensor {
	LMSTemperatureSensor(TargetADC adc,ADCChannel channel) : Sensor{adc,channel} {};
};

struct PayloadTemperatureSensor : public Sensor{
	PayloadTemperatureSensor(TargetADC adc,ADCChannel channel) : Sensor{adc,channel} {};
};

struct VoltageSensor : public Sensor {
	VoltageSensor(TargetADC adc,ADCChannel channel) : Sensor{adc,channel} {};
};

struct CurrentSensor : public Sensor {
	CurrentSensor(TargetADC adc,ADCChannel channel) : Sensor{adc,channel} {};
};

namespace ADC {
	uint16_t readCountFrom(const Sensor &sensor);
	uint16_t countToVoltage(uint16_t count);
	uint16_t readVoltageFrom(const Sensor &sensor);
}
#endif /* ADC_HPP_ */
