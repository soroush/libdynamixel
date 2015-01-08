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

#include "x106.hpp"

using namespace std;
using namespace Dynamixel;
using namespace LibSerial;

X106::X106(DynamixelBase& dxl) :
        m_dynamixel(dxl) {
}

void X106::setMasterMode(const bool& isMaster) {
    m_dynamixel.read(0x0A, 1);
    Buffer newMode = { static_cast<byte>(m_dynamixel.m_data[0x0A] |
            (isMaster ? byte{0x02} : byte{0x00})) };
    m_dynamixel.write(newMode,0x0A);
}

void X106::setReverseMode(const bool& isReverse) {
    m_dynamixel.read(0x0A, 1);
    Buffer newMode = { static_cast<byte>(m_dynamixel.m_data[0x0A] |
            (isReverse ? byte{0x01} : byte{0x00})) };
    m_dynamixel.write(newMode,0x0A);
}

bool X106::masterMode() {
    m_dynamixel.read(0x0A, 1);
    if (m_dynamixel.m_data[0x0A] & 0x02 == 0x02) {
        return true;
    }
    else {
        return false;
    }
}

bool X106::reverseMode() {
    m_dynamixel.read(0x0A, 1);
    if (m_dynamixel.m_data[0x0A] & 0x01 == 0x01) {
        return true;
    }
    else {
        return false;
    }
}
