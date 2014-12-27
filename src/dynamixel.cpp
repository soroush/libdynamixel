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

#include "dynamixel.hpp"
#include <stdexcept>
using namespace std;
using namespace LibSerial;

Dynamixel::Dynamixel(SerialStream& serial, const word& id) :
        m_serial(serial), m_id { id } {
    m_data[3] = this->m_id;
}

Dynamixel::Dynamixel(SerialStream& serial, const word& id, const word& steps,
        const word& maxSpeed, const float& startAngle, const float& stopAngle,
        const word& startGap, const word& stopGap, const float& resolutionD,
        const float& resolutionR) :
        m_serial(serial), m_id { id }, m_steps { steps }, m_startAngle {
                startAngle }, m_stopAngle { stopAngle }, m_startGap { startGap }, m_stopGap {
                stopGap }, m_resolutionD { resolutionD }, m_resolutionR {
                resolutionR } {
    m_data[3] = this->m_id;
}

void Dynamixel::read(const size_t& start, const size_t& length) {
    char packet[8] = { 0xFF, 0xFF, this->m_data[3], 0x04, 0x02, //
            static_cast<char>(start), static_cast<char>(length), 0x00 };
    addChecksum(packet, 8);
    m_serial.write(packet, 8);
    char statusPacket[6 + length];
    m_serial.read(statusPacket, 6 + length);
    if (statusPacket[4] == 0x00) {
        if (checkChecksum(statusPacket, 6 + length)) {
            for (byte index = start, sindex = 5; index < start + length;
                    ++index, ++sindex) {
                m_data[index] = statusPacket[sindex];
            }
        } else {
            // TODO: Handle checksum error
        }
    } else {
        // TODO: Handle motor error
    }
}

void Dynamixel::write(const byte* data, const size_t& size,
        const size_t& start) {
    // TODO: Check sanity of given data
    // Send data to dynamixel
    const int packetSize = 7 + size;
    byte packet[packetSize];
    packet[0] = packet[1] = 0xFF;
    packet[2] = this->m_data[3];
    packet[3] = 0x03 + size;
    packet[4] = 0x03;
    packet[5] = start;
    for (int i = 0; i < size; ++i) {
        packet[6 + i] = data[i];
    }
    addChecksum(packet, packetSize);
    m_serial.write(packet, packetSize);
    // Read status packet
    byte statusPacket[6];
    m_serial.read(statusPacket, 6);
    if (statusPacket[4] != 0x00) {
        // TODO: Handle response error
    } else if (!checkChecksum(statusPacket, 6)) {
        // TODO: Handle checksum error
    } else {
        // Update current table
        for (int i = start, j = 0; i < start + size; ++i, ++j) {
            m_data[i] = data[j];
        }
    }
}

word Dynamixel::presentPosition() {
    this->read(0x24, 2);
    word position = 0xFFFF;
    position |= this->m_data[0x25];
    position = (position << 8);
    position |= this->m_data[0x24];
    return position;
}

word Dynamixel::presentSpeed() {
    this->read(0x26, 2);
    word speed = 0xFFFF;
    speed |= this->m_data[0x27];
    speed = (speed << 8);
    speed |= this->m_data[0x26];
    return speed;
}

void Dynamixel::setGoalPosition(const word& position) {
    byte packet[2] = { // L-H
            static_cast<byte>(position >> 8), static_cast<byte>(position & 0xFF), };
    this->write(packet, 2, 0x1E);
}

void Dynamixel::setMovingSpeed(const word& speed) {
    byte packet[2] = { // L-H
            static_cast<byte>(speed >> 8), static_cast<byte>(speed & 0xFF), };
    this->write(packet, 2, 0x20);
}

void Dynamixel::setGoalPositionSpeed(const word& position, const word& speed) {
    byte packet[4] = { // L-H
            static_cast<byte>(position >> 8),
                    static_cast<byte>(position & 0xFF), static_cast<byte>(speed
                            >> 8), static_cast<byte>(speed & 0xFF), };
    this->write(packet, 4, 0x1E);
}

void Dynamixel::goTo(const float& target, const float& speed,
        const Coordinate& universe, const AngleUnit& a_unit,
        const VelocityUnit& v_unit) {
    word targetPosition;
    word targetSpeed;
    switch (a_unit) {
    case AngleUnit::Default:
        targetPosition = static_cast<word>(target);
        break;
    case AngleUnit::Degree:
        targetPosition = static_cast<word>(target * m_resolutionD) - m_startGap;
        break;
    case AngleUnit::Radian:
        targetPosition = static_cast<word>(target * m_resolutionR) - m_startGap;
        break;
    default:
        break;
    }
    switch (universe) {
    case Coordinate::Default:
        break;
    case Coordinate::Trigonometric:
        if (a_unit == AngleUnit::Default) {
            // TODO: Handle Error
        }
        targetPosition += static_cast<word>(180.0F * m_resolutionD);
        break;
    default:
        break;
    }
    if (v_unit != VelocityUnit::Default) {
        throw std::logic_error { "Not implemented" };
    }
    // TODO: Handle velocity units
    setGoalPositionSpeed(targetPosition, targetSpeed);
}

void Dynamixel::rotate(const float& rotation, const word& speed,
        const Dynamixel::AngleUnit& units,
        const Dynamixel::VelocityUnit& v_unit) {
    word currentPosition = this->presentPosition();
    word targetPosition;
    word targetSpeed;
    switch (units) {
    case AngleUnit::Default:
        targetPosition = currentPosition + rotation;
        break;
    case AngleUnit::Degree:
        targetPosition = currentPosition + rotation * m_resolutionD;
        break;
    case AngleUnit::Radian:
        targetPosition = currentPosition + rotation * m_resolutionR;
        break;
    default:
        break;
    }
    // TODO: Complete speed conversion
    if (targetPosition < 0) {
        // TODO: Handle underflow error
        targetPosition = 0;
    } else if (targetPosition > this->m_steps) {
        // TODO: Handle overflow error
        targetPosition = this->m_steps;
    }
    if (speed > this->m_maxSpeed) {
        // TODO: Handle overflow error
        targetSpeed = this->m_maxSpeed;
    } else {
        targetSpeed = speed;
    }
    this->setGoalPositionSpeed(targetPosition, targetSpeed);
}

void Dynamixel::rotate(const float& rotation, const Dynamixel::AngleUnit& units,
        const Dynamixel::VelocityUnit& v_unit) {
    word currentPosition = this->presentPosition();
    word targetPosition;
    switch (units) {
    case AngleUnit::Default:
        targetPosition = currentPosition + rotation;
        break;
    case AngleUnit::Degree:
        targetPosition = currentPosition + rotation * m_resolutionD;
        break;
    case AngleUnit::Radian:
        targetPosition = currentPosition + rotation * m_resolutionR;
        break;
    default:
        break;
    }
    this->setGoalPosition(targetPosition);
}

void Dynamixel::addChecksum(byte* input, const size_t& length) {
    word sum = 0;
    for (size_t index = 2; index < length - 1; ++index) {
        sum += input[index];
    }
    byte low = ~(static_cast<byte>(sum));
    input[length - 1] = low;
}

bool Dynamixel::checkChecksum(const byte* input, const size_t& length) {
    word sum = 0;
    for (size_t index = 2; index < length - 1; ++index) {
        sum += input[index];
    }
    byte low = ~(static_cast<byte>(sum));
    return low == input[length - 1];
}
