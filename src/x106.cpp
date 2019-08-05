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

#include "x106.hpp"

dynamixel::x106::x106(const uint8_t id) :
    dynamixel::base{id} {
}

void dynamixel::x106::set_master_mode(bool is_master) {
    read_mem(0x0A, 1);
    uint8_t new_mode[] = {
        static_cast<uint8_t>(m_data[0x0A] | (is_master ? 0x02 : 0x00)),
    };
    write_mem(new_mode, 0x01, 0x0A);
}

void dynamixel::x106::set_reverse_mode(bool is_reverse) {
    read_mem(0x0A, 1);
    uint8_t new_mode[] = {
        static_cast<uint8_t>(m_data[0x0A] | (is_reverse ? 0x01 : 0x00)),
    };
    write_mem(new_mode, 0x01, 0x0A);
}

bool dynamixel::x106::master_mode() {
    read_mem(0x0A, 1);
    if ((m_data[0x0A] & 0x02) == 0x02) {
        return true;
    }
    else {
        return false;
    }
}

bool dynamixel::x106::reverse_mode() {
    read_mem(0x0A, 1);
    if ((m_data[0x0A] & 0x01) == 0x01) {
        return true;
    }
    else {
        return false;
    }
}
