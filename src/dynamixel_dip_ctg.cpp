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

#include "dynamixel_dip_ctg.hpp"

using namespace std;
using namespace Dynamixel;
using namespace LibSerial;

Dynamixel_DIP_CTG::Dynamixel_DIP_CTG(SerialStream& serial, const word& id) :
        Dynamixel_DIP { serial, id } {
}

Dynamixel_DIP_CTG::Dynamixel_DIP_CTG(SerialStream& serial, const word& id,
        const word& steps, const word& maxSpeed, const float& startAngle,
        const float& stopAngle, const word& startGap, const word& stopGap,
        const float& resolutionD, const float& resolutionR) :
        Dynamixel_DIP { serial, id, steps, maxSpeed, startAngle, stopAngle,
                startGap, stopGap, resolutionD, resolutionR } {
}

word Dynamixel_DIP_CTG::current() {
    this->read(0x44, 2);
    word current = ((static_cast<word>(this->m_data[0x45]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x44]) & 0x00FF);
    return current;
}

bool Dynamixel_DIP_CTG::torqueControlMode() {
    this->read(0x46, 1);
    if (this->m_data[0x46] == 1) {
        return true;
    }
    else {
        return false;
    }
}

word Dynamixel_DIP_CTG::goalTorque() {
    this->read(0x47, 2);
    word torque = ((static_cast<word>(this->m_data[0x48]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x47]) & 0x00FF);
    return torque;
}

void Dynamixel_DIP_CTG::setCurrent(const word& current) {
    Buffer packet = { // L-H
            static_cast<byte>(current & 0x00FF), static_cast<byte>(current >> 8), };
    this->write(packet, 0x44);
}

void Dynamixel_DIP_CTG::setTorqueControlMode(const bool& mode) {
    Buffer packet = { static_cast<byte>(mode ? 0x01 : 0x00) };
    this->write(packet, 0x46);
}

void Dynamixel_DIP_CTG::setGoalTorque(const word& torque) {
    Buffer packet = { // L-H
            static_cast<byte>(torque & 0x00FF), static_cast<byte>(torque >> 8), };
    this->write(packet, 0x47);
}
