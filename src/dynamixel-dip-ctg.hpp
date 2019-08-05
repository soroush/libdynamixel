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

#ifndef LIBDYNAMIXEL_DYNAMIXEL_DIP_CTG_HPP
#define LIBDYNAMIXEL_DYNAMIXEL_DIP_CTG_HPP

#include <cstdint>
#include "dynamixel-dip.hpp"

namespace dynamixel {

class dip_ctg: virtual public dip {
public:
    dip_ctg(const uint8_t id);
    dip_ctg(const uint8_t id, const uint16_t steps,
            const uint16_t max_speed,
            const float start_angle, const float stop_angle,
            const uint16_t start_gap, const uint16_t stop_gap,
            const float resolution_d, const float resolution_r);
    dip_ctg(const dip_ctg&) = default;
    dip_ctg(dip_ctg&&) = default;
    dip_ctg& operator=(const dip_ctg&) = default;
    dip_ctg& operator=(dip_ctg&&);
    virtual ~dip_ctg() = default;

    uint16_t current();
    bool torque_control_mode();
    uint16_t goal_torque();
    void set_current(const uint16_t current);
    void set_torque_control_mode(const bool mode);
    void set_goal_torque(const uint16_t torque);
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_DYNAMIXEL_DIP_CTG_HPP
