/*
 libDynamixel, Dynamixel Servo Controller API

 Copyright 2014 Soroush Rabiei <soroush@phemto-tech.com>

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

#include "mx106.hpp"
#include <cmath>

#define _USE_MATH_DEFINES

using namespace std;
using namespace Dynamixel;

MX106::MX106(Serial& serial, const word& id) :
        Dynamixel_DIP_CTG { serial, id, 4095, 1023, 0.0, 360.0, 0, 0, 4096.0
                / 360.0, 4096.0 / 2 * M_PI }, X106(
                static_cast<DynamixelBase&>(*this)) {
}

