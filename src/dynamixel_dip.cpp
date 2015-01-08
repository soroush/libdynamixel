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

#include "dynamixel_dip.hpp"

using namespace std;
using namespace Dynamixel;
using namespace LibSerial;

Dynamixel_DIP::Dynamixel_DIP(SerialStream& serial, const word& id) :
        DynamixelBase { serial, id } {
}

Dynamixel_DIP::Dynamixel_DIP(SerialStream& serial, const word& id,
        const word& steps, const word& maxSpeed, const float& startAngle,
        const float& stopAngle, const word& startGap, const word& stopGap,
        const float& resolutionD, const float& resolutionR) :
        DynamixelBase { serial, id, steps, maxSpeed, startAngle, stopAngle,
                startGap, stopGap, resolutionD, resolutionR } {
}

word Dynamixel_DIP::multiTurnOffset() {
    this->read(0x14, 2);
    word offset = ((static_cast<word>(this->m_data[0x15]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x14]) & 0x00FF);
    return offset;
}

word Dynamixel_DIP::resolutionDivider() {
    this->read(0x16, 1);
    word divider = static_cast<word>(this->m_data[0x16]) & 0x00FF;
    return divider;
}

word Dynamixel_DIP::D() {
    this->read(0x1A, 1);
    word d = static_cast<word>(this->m_data[0x1A]) & 0x00FF;
    return d;
}

word Dynamixel_DIP::I() {
    this->read(0x1B, 1);
    word i = static_cast<word>(this->m_data[0x1B]) & 0x00FF;
    return i;
}

word Dynamixel_DIP::P() {
    this->read(0x1C, 1);
    word p = static_cast<word>(this->m_data[0x1C]) & 0x00FF;
    return p;
}

word Dynamixel_DIP::goalAcceleration() {
    this->read(0x49, 1);
    word acceleration = static_cast<word>(this->m_data[0x49]) & 0x00FF;
    return acceleration;
}

void Dynamixel_DIP::setD(const word& d) {
    Buffer packet = { static_cast<byte>(d & 0x00FF), };
    this->write(packet, 0x1A);
}

void Dynamixel_DIP::setI(const word& i) {
    Buffer packet = { static_cast<byte>(i & 0x00FF), };
    this->write(packet, 0x1B);
}

void Dynamixel_DIP::setP(const word& p) {
    Buffer packet = { static_cast<byte>(p & 0x00FF), };
    this->write(packet, 0x1C);
}

void Dynamixel_DIP::setGoalAcceleration(const word& acceleration) {
    Buffer packet = { static_cast<byte>(acceleration & 0x00FF), };
    this->write(packet, 0x49);
}
