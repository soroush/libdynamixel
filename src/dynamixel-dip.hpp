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

#ifndef LIBDYNAMIXEL_DYNAMIXEL_DIP_HPP
#define LIBDYNAMIXEL_DYNAMIXEL_DIP_HPP

#include <cstdint>
#include "dynamixel-base.hpp"

namespace dynamixel {

class dip: virtual public base {
public:
    dip(const uint8_t id);
    dip(const uint8_t id,
        const uint16_t steps,
        const uint16_t max_speed,
        const float start_angle, const float stop_angle,
        const uint16_t start_gap, const uint16_t stop_gap,
        const float resolution_d, const float resolution_r);
    dip(const dip&) = default;
    dip(dip&&) = default;
    dip& operator=(const dip&) = default;
    dip& operator=(dip&&);
    virtual ~dip()=default;

    uint16_t multi_turn_offset();
    uint16_t resolution_divider();
    uint16_t d();
    uint16_t i();
    uint16_t p();
    uint16_t goal_acceleration();

    void set_d(const uint16_t d);
    void set_i(const uint16_t i);
    void set_p(const uint16_t p);
    void set_goal_acceleration(const uint16_t acceleration);
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_DYNAMIXEL_DIP_HPP
