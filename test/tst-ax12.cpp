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

#include "ax12.hpp"
#include <cstdint>
#include <iostream>

int main() {
    dynamixel::communicator c{"/dev/ttyUSB0", B115200};
    dynamixel::ax12 a{5};
    a.set_communicator(&c);
    uint16_t model = a.model_number();
    std::cout << model << '\n';
    return 0;
}
