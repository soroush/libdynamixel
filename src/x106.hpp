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

#ifndef X106_HPP_
#define X106_HPP_

#include "dynamixel.hpp"

class MX106;

class X106 {
public:
    X106(Dynamixel& dxl);
    void setMasterMode(bool isMaster);
    void setReverseMode(bool isMaster);
    bool masterMode();
    bool reverseMode();
private:
    Dynamixel& m_dynamixel;
};

#endif /* X106_HPP_ */
