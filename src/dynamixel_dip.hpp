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

#ifndef DYNAMIXEL_DIP_HPP_
#define DYNAMIXEL_DIP_HPP_

#include "dynamixel_base.hpp"

namespace Dynamixel {

class Dynamixel_DIP: public DynamixelBase {
public:
    Dynamixel_DIP(LibSerial::SerialStream&, const word& id);
    Dynamixel_DIP(LibSerial::SerialStream&, const word& id, const word& steps,
            const word& maxSpeed, const float& startAngle,
            const float& stopAngle, const word& startGap, const word& stopGap,
            const float& resolutionD, const float& resolutionR
            );
	word multiTurnOffset();
	word resolutionDivider();
    word D();
    word I();
    word P();
    word goalAcceleration();

    void setD(const word&);
    void setI(const word&);
    void setP(const word&);
    void setGoalAcceleration(const word&);

};

}  // namespace Dynamixel

#endif /* DYNAMIXEL_DIP_HPP_ */
