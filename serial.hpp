/*
 * serial.hpp
 *
 *  Created on: 17/07/2022
 *      Author: labadmin-lhef001
 */

#ifndef SERIAL_HPP_
#define SERIAL_HPP_


namespace Serial{
	void printNum(int32_t value);
	void printNumLn(int32_t value);
	void printUnsigned(uint32_t value);
	void printUnsignedLn(uint32_t value);
	void printStr(const char string[]);
	void printStrLn(const char string[]);
	void printLn();
	char waitForPacket();
}


#endif /* SERIAL_HPP_ */
