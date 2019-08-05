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

#ifndef LIBDYNAMIXEL_DYNAMIXEL_CMS_HPP
#define LIBDYNAMIXEL_DYNAMIXEL_CMS_HPP

#include <cstdint>
#include "dynamixel-base.hpp"

namespace dynamixel {

class cms: public base {
public:
    cms(const uint8_t id);
    cms(const uint8_t id, const uint16_t steps,
        const uint16_t maxSpeed, const float startAngle,
        const float stopAngle, const uint16_t startGap, const uint16_t stopGap,
        const float resolutionD, const float resolutionR);
    cms(const cms&) = default;
    cms(cms&&) = default;
    cms& operator=(const cms&) = default;
    cms& operator=(cms&&) = default;
    virtual ~cms() = default;
    uint16_t cw_compliance_margine();
    uint16_t cw_compliance_slope();
    uint16_t ccw_compliance_margine();
    uint16_t ccw_compliance_slope();
    void set_cw_compliance_margine(const uint16_t);
    void set_cw_compliance_slope(const uint16_t);
    void set_ccw_compliance_margine(const uint16_t);
    void set_ccw_compliance_slope(const uint16_t);
};

}  // namespace Dynamixel

#endif /* DYNAMIXEL_CMS_HPP_ */
