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

#include "dynamixel_cms.hpp"

using namespace std;
using namespace Dynamixel;
using namespace LibSerial;

Dynamixel_CMS::Dynamixel_CMS(SerialStream& serial, const word& id) :
        DynamixelBase { serial, id } {
}

Dynamixel_CMS::Dynamixel_CMS(LibSerial::SerialStream& serial, const word& id,
        const word& steps, const word& maxSpeed, const float& startAngle,
        const float& stopAngle, const word& startGap, const word& stopGap,
        const float& resolutionD, const float& resolutionR) :
        DynamixelBase { serial, id, steps, maxSpeed, startAngle, stopAngle,
                startGap, stopGap, resolutionD, resolutionR } {
}

word Dynamixel_CMS::complianceMargineCW() {
    this->read(0x1A, 1);
    word margin = static_cast<word>(this->m_data[0x1A]) & 0x00FF;
    return margin;
}

word Dynamixel_CMS::complianceMargineCCW() {
    this->read(0x1B, 1);
    word margin = static_cast<word>(this->m_data[0x1B]) & 0x00FF;
    return margin;
}

word Dynamixel_CMS::complianceSlopeCW() {
    this->read(0x1C, 1);
    word margin = static_cast<word>(this->m_data[0x1C]) & 0x00FF;
    return margin;
}

word Dynamixel_CMS::complianceSlopeCCW() {
    this->read(0x1D, 1);
    word margin = static_cast<word>(this->m_data[0x1D]) & 0x00FF;
    return margin;
}

void Dynamixel_CMS::setComplianceMargineCW(const word& margin) {
    Buffer packet = { static_cast<byte>(margin & 0x00FF), };
    this->write(packet, 0x1A);
}

void Dynamixel_CMS::setComplianceMargineCCW(const word& margin) {
    Buffer packet = { static_cast<byte>(margin & 0x00FF), };
    this->write(packet, 0x1B);
}

void Dynamixel_CMS::setComplianceSlopeCW(const word& margin) {
    Buffer packet = { static_cast<byte>(margin & 0x00FF), };
    this->write(packet, 0x1C);
}

void Dynamixel_CMS::setComplianceSlopeCCW(const word& margin) {
    Buffer packet = { static_cast<byte>(margin & 0x00FF), };
    this->write(packet, 0x1D);
}
