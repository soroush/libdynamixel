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

#ifndef LIBDYNAMIXEL_X106_HPP
#define LIBDYNAMIXEL_X106_HPP

#include "dynamixel-base.hpp"
#include <cstdint>

namespace dynamixel {

class x106 : public dynamixel::base {
public:
    x106(const uint8_t id);
    x106(const x106&) = default;
    x106(x106&&) = default;
    x106& operator=(const x106&) = default;
    x106& operator=(x106&&) = default;
    ~x106() = default;

    void set_master_mode(bool is_master);
    void set_reverse_mode(bool is_reverse);
    bool master_mode();
    bool reverse_mode();
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_X106_HPP
