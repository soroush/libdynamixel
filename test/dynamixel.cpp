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

#include "../src/ax12.hpp"
#include "../src/mx28.hpp"
#include "../src/serial.hpp"
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace Dynamixel;

int main() {
	Serial port { "/dev/ttyUSB0", Serial::BaudRate::BAUD_57600,
			Serial::CharacterSize::CHAR_SIZE_8, Serial::Parity::PARITY_NONE,
			Serial::StopBits::STOP_BITS_1,
			Serial::FlowControlEnum::FLOW_CONTROL_NONE };
	MX28 m1 { port, 2 };
	m1.goTo(0);
	while (m1.moving()) {
		usleep(200000);
		cout << "Moving..." << endl;
	}
	cout << "Done" << endl;
//	m1.rotate(90,DynamixelBase::AngleUnit::Degree);
//	for (int i = 0; i < 4096; i += 50) {
//		usleep(500000);
//		m1.goTo(0);
//	cout << "Position: " << m1.presentPosition() << endl;
//	cout << "Speed: " << m1.presentSpeed() << endl;
//	cout << "Voltage: " << m1.presentVoltage() << endl;
//	cout << "Temperature: " << m1.presentTemperature() << endl;
//		usleep(500000);
//		m1.goTo(4095);
//	}
//	usleep(1000000);
//	usleep(1000000);
//	usleep(1000000);

//	m1.rotate(-90, DynamixelBase::AngleUnit::Degree);
//	m1.rotate(+90, DynamixelBase::AngleUnit::Degree);
//	port.Close();

//
//	for (int i = 0; i < 4000; i+=100) {
//		cout << i << ": " << endl;
//		std::vector<unsigned char> x = {0xff, 0xff, 0x02, 0x05, 0x03, 0x1e, static_cast<unsigned char>(((i)&0x00FF)<<8),
//                static_cast<unsigned char>(((i)&0xFF00)>>8),
//                0xe3};
//		x[8] = ~(x[2] + x[3] + x[4] + x[5] + x[6] + x[7]);
//		port.write(x);
//		for (const auto& i : x) {
//			cout << std::hex << (static_cast<int>(i) & 0x00FF) << ' ';
//		}
//		std::vector<unsigned char> y;
//		y = port.read(8);
//		for (const auto& i : y) {
//			cout << std::hex << (static_cast<int>(i) & 0x00FF) << ' ';
//		}
//		cout << endl;
//		usleep(100000);
//	}
//	port.close();
}
