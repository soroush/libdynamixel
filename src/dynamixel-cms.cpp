/*
 libDynamixel, Dynamixel Servo Controller API

 Copyright 2014-2019 Soroush Rabiei <soroush@ametisco.ir>

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

#include "dynamixel-cms.hpp"

dynamixel::cms::cms(const uint8_t id) :
    dynamixel::base {id} {
}

dynamixel::cms::cms(const uint8_t id,
                    const uint16_t steps, const uint16_t maxSpeed, const float startAngle,
                    const float stopAngle, const uint16_t startGap, const uint16_t stopGap,
                    const float resolutionD, const float resolutionR) :
    dynamixel::base {id, steps, maxSpeed, startAngle, stopAngle,
                     startGap, stopGap, resolutionD, resolutionR } {
}

uint16_t dynamixel::cms::cw_compliance_margine() {
    this->read_mem(0x1A, 1);
    uint16_t margin = static_cast<uint16_t>(this->m_data[0x1A]) & 0x00FF;
    return margin;
}

uint16_t dynamixel::cms::ccw_compliance_margine() {
    this->read_mem(0x1B, 1);
    uint16_t margin = static_cast<uint16_t>(this->m_data[0x1B]) & 0x00FF;
    return margin;
}

uint16_t dynamixel::cms::cw_compliance_slope() {
    this->read_mem(0x1C, 1);
    uint16_t margin = static_cast<uint16_t>(this->m_data[0x1C]) & 0x00FF;
    return margin;
}

uint16_t dynamixel::cms::ccw_compliance_slope() {
    this->read_mem(0x1D, 1);
    uint16_t margin = static_cast<uint16_t>(this->m_data[0x1D]) & 0x00FF;
    return margin;
}

void dynamixel::cms::set_cw_compliance_margine(const uint16_t margin) {
    uint8_t packet[] = { static_cast<uint8_t>(margin & 0x00FF), };
    this->write_mem(packet, 0x01, 0x1A);
}

void dynamixel::cms::set_ccw_compliance_margine(const uint16_t margin) {
    uint8_t packet[] = { static_cast<uint8_t>(margin & 0x00FF), };
    this->write_mem(packet, 0x01, 0x1B);
}

void dynamixel::cms::set_cw_compliance_slope(const uint16_t margin) {
    uint8_t packet[] = { static_cast<uint8_t>(margin & 0x00FF), };
    this->write_mem(packet, 0x01, 0x1C);
}

void dynamixel::cms::set_ccw_compliance_slope(const uint16_t margin) {
    uint8_t packet[] = { static_cast<uint8_t>(margin & 0x00FF), };
    this->write_mem(packet, 0x01, 0x1D);
}
