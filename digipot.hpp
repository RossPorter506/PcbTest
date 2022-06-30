/*
 * digipot.hpp
 *
 *  Created on: 30/06/2022
 *      Author: labadmin-lhef001
 */

#ifndef DIGIPOT_HPP_
#define DIGIPOT_HPP_

#include <stdint.h>

enum DigipotChannel{
	Channel1=0,
	Channel2=1,
};

void setDigipotChannelToValue(DigipotChannel channel, uint8_t value);

#endif /* DIGIPOT_HPP_ */
