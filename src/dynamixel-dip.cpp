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

#include "dynamixel-dip.hpp"

dynamixel::dip::dip(const uint8_t id):
    dynamixel::base{id} {
}

dynamixel::dip::dip(const uint8_t id,
                    const uint16_t steps,
                    const uint16_t max_speed,
                    const float start_angle, const float stop_angle,
                    const uint16_t start_gap, const uint16_t stop_gap,
                    const float resolution_d, const float resolution_r):
    dynamixel::base {id, steps, max_speed,
                     start_angle, stop_angle,
                     start_gap, stop_gap,
                     resolution_d, resolution_r } {
}

dynamixel::dip& dynamixel::dip::operator=(dynamixel::dip&& other) {
    static_cast<dynamixel::base&>(*this) = static_cast<dynamixel::base&&>(other);
    return *this;
}

uint16_t dynamixel::dip::multi_turn_offset() {
    read_mem(0x14, 2);
    uint16_t offset = ((static_cast<uint16_t>(m_data[0x15]) & 0x00FF) << 8)
                  | (static_cast<uint16_t>(m_data[0x14]) & 0x00FF);
    return offset;
}

uint16_t dynamixel::dip::resolution_divider() {
    read_mem(0x16, 1);
    uint16_t divider = static_cast<uint16_t>(m_data[0x16]) & 0x00FF;
    return divider;
}

uint16_t dynamixel::dip::d() {
    read_mem(0x1A, 1);
    uint16_t d = static_cast<uint16_t>(m_data[0x1A]) & 0x00FF;
    return d;
}

uint16_t dynamixel::dip::i() {
    read_mem(0x1B, 1);
    uint16_t i = static_cast<uint16_t>(m_data[0x1B]) & 0x00FF;
    return i;
}

uint16_t dynamixel::dip::p() {
    read_mem(0x1C, 1);
    uint16_t p = static_cast<uint16_t>(m_data[0x1C]) & 0x00FF;
    return p;
}

uint16_t dynamixel::dip::goal_acceleration() {
    read_mem(0x49, 1);
    uint16_t acceleration = static_cast<uint16_t>(m_data[0x49]) & 0x00FF;
    return acceleration;
}

void dynamixel::dip::set_d(const uint16_t d) {
    uint8_t packet[] = { static_cast<uint8_t>(d & 0x00FF), };
    write_mem(packet, 0x01, 0x1A);
}

void dynamixel::dip::set_i(const uint16_t i) {
    uint8_t packet[] = { static_cast<uint8_t>(i & 0x00FF), };
    write_mem(packet, 0x01, 0x1B);
}

void dynamixel::dip::set_p(const uint16_t p) {
    uint8_t packet[] = { static_cast<uint8_t>(p & 0x00FF), };
    write_mem(packet, 0x01, 0x1C);
}

void dynamixel::dip::set_goal_acceleration(const uint16_t acceleration) {
    uint8_t packet[] = { static_cast<uint8_t>(acceleration & 0x00FF), };
    write_mem(packet, 0x01,  0x49);
}
