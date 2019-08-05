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

#ifndef LIBDYNAMIXEL_RX24F_HPP
#define LIBDYNAMIXEL_RX24F_HPP

#include <cstdint>
#include "dynamixel-cms.hpp"

namespace dynamixel {

class rx24f: public dynamixel::cms {
public:
    rx24f(const uint8_t id);
    rx24f(const rx24f&) = default;
    rx24f(rx24f&&) = default;
    rx24f& operator=(const rx24f&) = default;
    rx24f& operator=(rx24f&&) = default;
    ~rx24f() = default;
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_RX24F_HPP
