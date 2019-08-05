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

#ifndef LIBDYNAMIXEL_MX12W_HPP
#define LIBDYNAMIXEL_MX12W_HPP

#include <cstdint>
#include "dynamixel-dip.hpp"

namespace dynamixel {

class mx12w: public dynamixel::dip {
public:
    mx12w(const uint8_t id);
    mx12w(const mx12w&) = default;
    mx12w(mx12w&&) = default;
    mx12w& operator=(const mx12w&) = default;
    mx12w& operator=(mx12w&&) = default;
    ~mx12w() = default;
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_MX12W_HPP
