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

#ifndef LIBDYNAMIXEL_MX64_HPP
#define LIBDYNAMIXEL_MX64_HPP

#include <cstdint>
#include "dynamixel-dip-ctg.hpp"

namespace dynamixel {

class mx64: public dynamixel::dip_ctg {
public:
    mx64(const uint8_t id);
    mx64(const mx64&) = default;
    mx64(mx64&&) = default;
    mx64& operator=(const mx64&) = default;
    mx64& operator=(mx64&&) = default;
    ~mx64() = default;
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_MX64_HPP
