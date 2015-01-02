/*
 libDynamixel, Dynamixel Servo Controller API

 Copyright 2014 Soroush Rabiei <soroush@phemto-tech.com>

 libDynamixel is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 See the file COPYING included with this distribution for more
 information.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef SERIAL_HPP_
#define SERIAL_HPP_

#include <termios.h>
#include <string>
#include <vector>

namespace Dynamixel {

class Serial {
public:
	enum class BaudRate {
		BAUD_50 = B50,
		BAUD_75 = B75,
		BAUD_110 = B110,
		BAUD_134 = B134,
		BAUD_150 = B150,
		BAUD_200 = B200,
		BAUD_300 = B300,
		BAUD_600 = B600,
		BAUD_1200 = B1200,
		BAUD_1800 = B1800,
		BAUD_2400 = B2400,
		BAUD_4800 = B4800,
		BAUD_9600 = B9600,
		BAUD_19200 = B19200,
		BAUD_38400 = B38400,
		BAUD_57600 = B57600,
		BAUD_115200 = B115200,
		BAUD_230400 = B230400,
		// B460800 is defined on Linux but not on Mac OS
		// X. What about other operating systems ?
#ifdef __linux__
		BAUD_460800 = B460800,
#endif
		BAUD_DEFAULT = BAUD_57600
	};
	enum class CharacterSize {
		CHAR_SIZE_5 = CS5,
		CHAR_SIZE_6 = CS6,
		CHAR_SIZE_7 = CS7,
		CHAR_SIZE_8 = CS8,
		CHAR_SIZE_DEFAULT = CHAR_SIZE_8
	};
	enum class Parity {
		PARITY_EVEN, PARITY_ODD, PARITY_NONE, PARITY_DEFAULT = PARITY_NONE
	};
	enum class StopBits{
		STOP_BITS_1,
		STOP_BITS_2,
	};
	enum class FlowControlEnum {
		FLOW_CONTROL_HARD,
		FLOW_CONTROL_SOFT,
		FLOW_CONTROL_NONE,
		FLOW_CONTROL_DEFAULT,
		FLOW_CONTROL_INVALID,
	};
//	Serial();
	Serial(const std::string& name,
			const BaudRate& baud,
			const CharacterSize& size,
			const Parity& parity,
			const StopBits& stop,
			const FlowControlEnum& flow);
	virtual ~Serial();
	//bool open();
	bool close();
	std::vector<unsigned char> read(const size_t& minimum=0);
	void write(const std::vector<unsigned char>& data);
private:
	int m_fd;
};

} /* namespace Dynamixel */

#endif /* SERIAL_HPP_ */
