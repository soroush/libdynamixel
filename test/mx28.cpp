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
#include <unistd.h>
#include <iostream>
#include <SerialPort.h>
#include <SerialStream.h>

using namespace std;
using namespace Dynamixel;
using namespace LibSerial;

int main() {
	SerialStream stream("/dev/ttyUSB0", SerialStreamBuf::BAUD_57600,
			SerialStreamBuf::CHAR_SIZE_8, SerialStreamBuf::PARITY_NONE, 1,
			SerialStreamBuf::FLOW_CONTROL_NONE);
    stream.SetVMin(100);
    stream.SetVTime(1);
	MX28 m1 { stream, 1 };
	m1.setGoalPositionSpeed(2090,30);
	usleep(1000000);
//	while(m1.moving()){
//		cout << "Position  : " << m1.presentPosition() << endl;
//		cout << "Speed  : " << m1.presentSpeed() << endl;
//		cout << "Voltage: " << m1.presentVoltage() << endl;
//		usleep(10000);
//	}
//	m1.rotate(45,50,DynamixelBase::AngleUnit::Degree,
//			DynamixelBase::VelocityUnit::Default);
//	for(int i=0; i< 4096; i+= 100){
//		usleep(50000);
//		m1.goTo(i);
//		usleep(100000);
//		cout << m1.presentPosition() << endl;
//		cout << m1.presentSpeed() << endl;
//		cout << m1.presentLoad() << endl;
//		cout << m1.presentVoltage() << endl;
//	}
//	for(int i=0; i< 4096; i+= 100){
//		usleep(10000);
//		m1.goTo(4095);
//		cout << m1.presentPosition() << endl;
//		cout << m1.presentSpeed() << endl;
//		cout << m1.presentLoad() << endl;
//		cout << m1.presentVoltage() << endl;
//		usleep(10000);
//		m1.goTo(0);
//		cout << m1.presentPosition() << endl;
//		cout << m1.presentSpeed() << endl;
//		cout << m1.presentLoad() << endl;
//		cout << m1.presentVoltage() << endl;
//	}
}
