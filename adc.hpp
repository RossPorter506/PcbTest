/*
 * adc.hpp
 *
 *  Created on: 7/07/2022
 *      Author: labadmin-lhef001
 */

#ifndef ADC_HPP_
#define ADC_HPP_

enum ADC {
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
	ADC adc;
	ADCChannel channel;
};

uint16_t readValueFromADCSensor(const Sensor &sensor);

#endif /* ADC_HPP_ */
