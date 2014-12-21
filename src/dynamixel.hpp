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

#ifndef DYNAMIXEL_HPP_
#define DYNAMIXEL_HPP_

#include <cstddef>
#include <memory>
#include <SerialStream.h>

typedef char byte;
typedef int word;

class Dynamixel {
public:
    Dynamixel(LibSerial::SerialStream&, const unsigned int& id);
    virtual ~Dynamixel();
    // Low level API layer
    void read(const byte&, const byte&);
    void write(const byte*, const std::size_t&, const std::size_t&);
    // High level API layer
    unsigned int model();
    unsigned int firmware();
    unsigned int id();
    unsigned int baudrate();
    unsigned int delay();
    unsigned int cwAngleLimit();
    unsigned int ccwAngleLimit();
    unsigned int highTemperatureLimit();
    unsigned int lowVoltageLimit();
    unsigned int highVoltageLimit();
    unsigned int maxTorque();
    unsigned int minTorque();
    unsigned int statusReturnLevel();
    unsigned int alarmLED();
    unsigned int alarmShutdown();
    unsigned int multiTurnOffset();
    unsigned int resolutionDivider();
    bool torqueEnable();
protected:
    void addChecksum(byte*, const std::size_t&);
    bool checkChecksum(const byte*, const std::size_t&);
    LibSerial::SerialStream &m_serial;
    byte m_data[74];
    unsigned int m_id;
};

#endif /* DYNAMIXEL_HPP_ */
