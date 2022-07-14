/*
 * dac.hpp
 *
 *  Created on: 30/06/2022
 *      Author: labadmin-lhef001
 */

#ifndef DAC_HPP_
#define DAC_HPP_

enum DACCommand{
	WriteToRegisterX=0b000,
	UpdateRegisterX=0b0001,
	WriteToRegisterXAndUpdateAll=0b0010,
	WriteToAndUpdateRegisterX=0b0011,
	PowerOffChannelX=0b100,
	PowerOffChip=0b0101,
	SelectInternalReference=0b0110,
	SelectExternalReference=0b0111,
	NoOp=0b1111,
};

enum DACChannel{
	ChannelA=0b0000,
	ChannelB=0b0001,
	ChannelC=0b0010,
	ChannelD=0b0011,
	AllChannels=0b1111,
};

namespace DAC{
	void sendCommand(DACCommand command, DACChannel channel, uint16_t value);
	void init();
	uint16_t voltageToCount(uint16_t targetVoltageMillivolts);
}
#endif /* DAC_HPP_ */
