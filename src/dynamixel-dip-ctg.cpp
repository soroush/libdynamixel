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

#include "dynamixel-dip-ctg.hpp"

dynamixel::dip_ctg::dip_ctg(const uint8_t id) :
    dynamixel::base{id},
    dynamixel::dip{id} {
}

dynamixel::dip_ctg::dip_ctg(const uint8_t id,
                            const uint16_t steps, const uint16_t max_speed,
                            const float start_angle, const float stop_angle,
                            const uint16_t start_gap, const uint16_t stop_gap,
                            const float resolution_d, const float resolution_r) :
    dynamixel::base{id},
    dynamixel::dip{id, steps,
                   max_speed, start_angle, stop_angle,
                   start_gap, stop_gap, resolution_d, resolution_r } {
}

dynamixel::dip_ctg& dynamixel::dip_ctg::operator=(dynamixel::dip_ctg&& other) {
    static_cast<dynamixel::base&>(*this) = static_cast<dynamixel::base&&>(other);
    return *this;
}

uint16_t dynamixel::dip_ctg::current() {
    this->read_mem(0x44, 2);
    uint16_t current = ((static_cast<uint16_t>(this->m_data[0x45]) & 0x00FF) << 8)
                       | (static_cast<uint16_t>(this->m_data[0x44]) & 0x00FF);
    return current;
}

bool dynamixel::dip_ctg::torque_control_mode() {
    this->read_mem(0x46, 1);
    if (this->m_data[0x46] == 1) {
        return true;
    }
    else {
        return false;
    }
}

uint16_t dynamixel::dip_ctg::goal_torque() {
    this->read_mem(0x47, 2);
    uint16_t torque = ((static_cast<uint16_t>(this->m_data[0x48]) & 0x00FF) << 8)
                      | (static_cast<uint16_t>(this->m_data[0x47]) & 0x00FF);
    return torque;
}

void dynamixel::dip_ctg::set_current(const uint16_t current) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(current & 0x00FF),
        static_cast<uint8_t>(current >> 8),
    };
    this->write_mem(packet, 0x02, 0x44);
}

void dynamixel::dip_ctg::set_torque_control_mode(const bool mode) {
    uint8_t packet[] = { static_cast<uint8_t>(mode ? 0x01 : 0x00) };
    this->write_mem(packet, 0x01, 0x46);
}

void dynamixel::dip_ctg::set_goal_torque(const uint16_t torque) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(torque & 0x00FF),
        static_cast<uint8_t>(torque >> 8),
    };
    this->write_mem(packet, 0x02, 0x47);
}
