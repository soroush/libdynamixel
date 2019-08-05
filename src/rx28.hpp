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

#ifndef LIBDYNAMIXEL_RX28_HPP
#define LIBDYNAMIXEL_RX28_HPP

#include <cstdint>
#include "dynamixel-cms.hpp"

namespace dynamixel {

class rx28: public dynamixel::cms {
public:
    rx28(const uint8_t id);
    rx28(const rx28&) = default;
    rx28(rx28&&) = default;
    rx28& operator=(const rx28&) = default;
    rx28& operator=(rx28&&) = default;
    ~rx28() = default;
};

}  // namespace dynamixel

#endif // LIBDYNAMIXEL_RX28_HPP
