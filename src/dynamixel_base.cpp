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

#include "dynamixel_base.hpp"

#include <iostream>
#include <stdexcept>

//#endif

using namespace std;
using namespace Dynamixel;
using namespace LibSerial;

DynamixelBase::DynamixelBase(SerialStream& serial, const word& id) :
        m_serial(serial),
        m_id { id },
        m_statusReturnLevel { m_data[0x10] } {
    m_data[3] = this->m_id;
}

DynamixelBase::DynamixelBase(SerialStream& serial, const word& id,
        const word& steps, const word& maxSpeed, const float& startAngle,
        const float& stopAngle, const word& startGap, const word& stopGap,
        const float& resolutionD, const float& resolutionR) :
        m_serial(serial),
        m_id { id },
        m_statusReturnLevel { m_data[0x10] },
        m_steps { steps },
        m_maxSpeed { maxSpeed },
        m_startAngle { startAngle },
        m_stopAngle { stopAngle },
        m_startGap { startGap },
        m_stopGap { stopGap },
        m_resolutionD { resolutionD },
        m_resolutionR { resolutionR },
        m_voltageError { false },
        m_angleError { false },
        m_temperatureError { false },
        m_rangeError { false },
        m_checksumError { false },
        m_loadError { false },
        m_instructionError { false } {
    m_data[3] = this->m_id;
}

DynamixelBase::~DynamixelBase() {
}

void DynamixelBase::read(const size_t& start, const size_t& length) {
    Buffer packet = { static_cast<byte>(0xFF), static_cast<byte>(0xFF),
            this->m_data[3], 0x04, 0x02, static_cast<byte>(start),
            static_cast<byte>(length), 0x00 };
    addChecksum(packet);
    m_serial.write(packet.data(), packet.size());
#ifdef VERBOSE
    cout << "RWRITE: ";
    for (int i = 0; i < 8; ++i) {
        cout << hex << (static_cast<short>(packet[i]) & 0x00FF) << ' ';
    }
    cout << endl;
#endif
    byte statusPacketBuffer[6 + length];
    if (m_statusReturnLevel > 0) {
        m_serial.read(statusPacketBuffer, 6 + length);
        Buffer statusPacket { statusPacketBuffer, statusPacketBuffer + 6
                + length };
#ifdef VERBOSE
        cout << "RREAD : ";
        for (int i = 0; i < 6 + length; ++i) {
            cout << hex << static_cast<int>(statusPacket[i] & 0x00FF) << ' ';
        }
        cout << endl;
#endif
        if (static_cast<int>(statusPacket[4]) == 0x00) {
            if (checkChecksum(statusPacket)) {
                for (byte index = start, sindex = 5; index < start + length;
                        ++index, ++sindex) {
                    m_data[index] = statusPacket[sindex];
                }
                m_voltageError = false;
                m_angleError = false;
                m_temperatureError = false;
                m_rangeError = false;
                m_checksumError = false;
                m_loadError = false;
                m_instructionError = false;
            }
            else {
                cerr << "Returning packet has invalid checksum." << endl;
            }
        }
        else {
            handleError(statusPacket[4]);
        }
    }
}

void DynamixelBase::write(const Buffer& data, const size_t& start) {
    // TODO: Check sanity of given data
    // Send data to dynamixel
    const int packetSize = 7 + data.size();
    Buffer packet;
    packet.resize(packetSize);
    packet[0] = packet[1] = 0xFF;
    packet[2] = this->m_data[3];
    packet[3] = 0x03 + data.size();
    packet[4] = 0x03;
    packet[5] = start;
    for (int i = 0; i < data.size(); ++i) {
        packet[6 + i] = data[i];
    }
    addChecksum(packet);
#ifdef VERBOSE
    cout << "WWRITE: ";
    for (int i = 0; i < packetSize; ++i) {
        cout << hex << (static_cast<short>(packet[i]) & 0x00FF) << ' ';
    }
    cout << endl;
#endif
    m_serial.write(packet.data(), packet.size());
    if (m_statusReturnLevel == 0x02) {
        byte statusPacketBuffer[6];
        m_serial.read(statusPacketBuffer, 6);
        Buffer statusPacket { statusPacketBuffer, statusPacketBuffer + 6 };
#ifdef VERBOSE
        cout << "WREAD : ";
        for (int i = 0; i < 6; ++i) {
            cout << hex << (static_cast<int>(statusPacket[i]) & 0x00FF) << ' ';
        }
        cout << endl;
#endif
        if (statusPacket[4] != 0x00) {
            handleError(statusPacket[4]);
        }
        else if (!checkChecksum(statusPacket)) {
            // TODO: Handle checksum error
        }
    }
}

word DynamixelBase::modelNumber() {
    this->read(0x00, 2);
    word model = ((0x00FF & this->m_data[0x01]) << 8) | this->m_data[0x00];
    return model;
}

DynamixelBase::Model DynamixelBase::model() {
    word number = this->modelNumber();
    Model model;
    switch (number) {
    case 113:
        return Model::DX113;
        break;
    case 116:
        return Model::DX116;
        break;
    case 117:
        return Model::DX117;
        break;
    case 44:
        return Model::AX12W;
        break;
    case 12:
        return Model::AX12;
        break;
    case 18:
        return Model::AX18F;
        break;
    case 10:
        return Model::RX10;
        break;
    case 24:
        return Model::RX24F;
        break;
    case 28:
        return Model::RX28;
        break;
    case 64:
        return Model::RX64;
        break;
    case 107:
        return Model::EX106PLUS;
        break;
    case 104:
        return Model::MX12W;
        break;
    case 29:
        return Model::MX28;
        break;
    case 54:
        return Model::MX64;
        break;
    case 320:
        return Model::MX106;
        break;
    case 350:
        return Model::XL320;
        break;
    default:
        return Model::Unknown;
    }
}

word DynamixelBase::firmware() {
    this->read(0x03, 1);
    word firmware = static_cast<word>(this->m_data[0x03]) & 0x00FF;
    return firmware;
}

word DynamixelBase::id() {
    return this->m_id;
}

void DynamixelBase::setId(const byte& id) {
    Buffer data = { id };
    this->write(data, 0x03);
    this->m_data[3] = id;
    this->m_id = id;
}

word DynamixelBase::baudrate() {
    this->read(0x04, 1);
    word baudrate = static_cast<word>(this->m_data[0x04]) & 0x00FF;
    return baudrate;
}

word DynamixelBase::delay() {
    this->read(0x05, 1);
    word delayTime = static_cast<word>(this->m_data[0x05]) & 0x00FF;
    return delayTime;
}

word DynamixelBase::cwAngleLimit() {
    this->read(0x06, 2);
    word limit = ((static_cast<word>(this->m_data[0x07]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x06]) & 0x00FF);
    return limit;
}

word DynamixelBase::ccwAngleLimit() {
    this->read(0x08, 2);
    word limit = ((static_cast<word>(this->m_data[0x09]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x08]) & 0x00FF);
    return limit;
}

word DynamixelBase::highTemperatureLimit() {
    this->read(0x0B, 1);
    word temperature = static_cast<word>(this->m_data[0x0B]) & 0x00FF;
    return temperature;
}

word DynamixelBase::lowVoltageLimit() {
    this->read(0x0C, 1);
    word voltage = static_cast<word>(this->m_data[0x0C]) & 0x00FF;
    return voltage;
}

word DynamixelBase::highVoltageLimit() {
    this->read(0x0D, 1);
    word voltage = static_cast<word>(this->m_data[0x0D]) & 0x00FF;
    return voltage;
}

word DynamixelBase::maxTorque() {
    this->read(0x0E, 2);
    word torque = ((static_cast<word>(this->m_data[0x0F]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x0E]) & 0x00FF);
    return torque;
}

word DynamixelBase::statusReturnLevel() {
    this->read(0x10, 1);
    word level = static_cast<word>(this->m_data[0x10]) & 0x00FF;
    return level;
}

word DynamixelBase::alarmLED() {
}

word DynamixelBase::alarmShutdown() {
}

bool DynamixelBase::torqueEnable() {
    this->read(0x18, 1);
    if (this->m_data[0x18] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool DynamixelBase::LEDEnable() {
    this->read(0x19, 1);
    if (this->m_data[0x19] == 1) {
        return true;
    }
    else {
        return false;
    }
}

word DynamixelBase::goalPosition() {
    this->read(0x1E, 2);
    word position = ((static_cast<word>(this->m_data[0x1F]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x1E]) & 0x00FF);
    return position;
}

word DynamixelBase::movingSpeed() {
    this->read(0x20, 2);
    word speed = ((static_cast<word>(this->m_data[0x21]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x20]) & 0x00FF);
    return speed;
}

word DynamixelBase::torqueLimit() {
    this->read(0x22, 2);
    word limit = ((static_cast<word>(this->m_data[0x23]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x22]) & 0x00FF);
    return limit;
}

word DynamixelBase::presentPosition() {
    this->read(0x24, 2);
    word position = ((static_cast<word>(this->m_data[0x25]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x24]) & 0x00FF);
    return position;
}

word DynamixelBase::presentSpeed() {
    this->read(0x26, 2);
    word speed = ((static_cast<word>(this->m_data[0x27]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x26]) & 0x00FF);
    return speed;
}

word DynamixelBase::presentLoad() {
    this->read(0x28, 2);
    word load = ((static_cast<word>(this->m_data[0x29]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x28]) & 0x00FF);
    return load;
}

word DynamixelBase::presentVoltage() {
    this->read(0x2A, 1);
    word voltage = ((static_cast<word>(this->m_data[0x2B]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x2A]) & 0x00FF);
    return voltage;
}

word DynamixelBase::presentTemperature() {
    this->read(0x2B, 1);
    word temperature = ((static_cast<word>(this->m_data[0x2C]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x2B]) & 0x00FF);
    return temperature;
}

bool DynamixelBase::registered() {
    this->read(0x2C, 1);
    if (this->m_data[0x2C] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool DynamixelBase::moving() {
    this->read(0x2E, 1);
    if (this->m_data[0x2E] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool DynamixelBase::locked() {
    this->read(0x2F, 1);
    if (this->m_data[0x2F] == 1) {
        return true;
    }
    else {
        return false;
    }
}

word DynamixelBase::punch() {
    this->read(0x30, 2);
    word punch = ((static_cast<word>(this->m_data[0x31]) & 0x00FF) << 8)
            | (static_cast<word>(this->m_data[0x30]) & 0x00FF);
    return punch;
}

void DynamixelBase::setGoalPosition(const word& position) {
    Buffer packet = { // L-H
            static_cast<byte>(position & 0x00FF), static_cast<byte>(position
                    >> 8), };
    this->write(packet, 0x1E);
}

void DynamixelBase::setMovingSpeed(const word& speed) {
    Buffer packet = { // L-H
            static_cast<byte>(speed & 0x00FF), static_cast<byte>(speed >> 8), };
    this->write(packet, 0x20);
}

void DynamixelBase::setGoalPositionSpeed(const word& position,
        const word& speed) {
    Buffer packet = { // L-H
            static_cast<byte>(position & 0x00FF), static_cast<byte>(position
                    >> 8), static_cast<byte>(speed & 0x00FF),
                    static_cast<byte>(speed >> 8), };
    this->write(packet, 0x1E);
}

void DynamixelBase::setTorqueLimit(const word& limit) {
    Buffer packet = { // L-H
            static_cast<byte>(limit & 0x00FF), static_cast<byte>(limit >> 8), };
    this->write(packet, 0x22);
}

void DynamixelBase::setLock(const bool& locked) {
    Buffer packet = { static_cast<byte>(locked ? 0x01 : 0x00) };
    this->write(packet, 0x2F);
}

void DynamixelBase::setPunch(const word& punch) {
    Buffer packet = { // L-H
            static_cast<byte>(punch & 0x00FF), static_cast<byte>(punch >> 8), };
    this->write(packet, 0x30);
}

void DynamixelBase::goTo(const float& target, const float& speed,
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
        throw logic_error { "Not implemented" };
    }
    targetSpeed = static_cast<word>(speed);
    // TODO: Handle velocity units
    setGoalPositionSpeed(targetPosition, targetSpeed);
}

void DynamixelBase::goTo(const float& target, const Coordinate& universe,
        const AngleUnit& a_unit, const VelocityUnit& v_unit) {
    word targetPosition;
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
        throw logic_error { "Not implemented" };
    }
    // TODO: Handle velocity units
    setGoalPosition(targetPosition);
}

void DynamixelBase::rotate(const float& rotation, const word& speed,
        const DynamixelBase::AngleUnit& units,
        const DynamixelBase::VelocityUnit& v_unit) {
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
    }
    else if (targetPosition > this->m_steps) {
        // TODO: Handle overflow error
        targetPosition = this->m_steps;
    }
    if (speed > this->m_maxSpeed) {
        // TODO: Handle overflow error
        targetSpeed = this->m_maxSpeed;
    }
    else {
        targetSpeed = speed;
    }
    this->setGoalPositionSpeed(targetPosition, speed);
}

void DynamixelBase::rotate(const float& rotation,
        const DynamixelBase::AngleUnit& units,
        const DynamixelBase::VelocityUnit& v_unit) {
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

void DynamixelBase::addChecksum(Buffer& input) {
    size_t length = input.size();
    word sum = 0;
    for (size_t index = 2; index < length - 1; ++index) {
        sum += input[index];
    }
    byte low = ~(static_cast<byte>(sum));
    input[length - 1] = low;
}

bool DynamixelBase::checkChecksum(const Buffer& input) {
    word sum = 0;
    size_t length = input.size();
    for (size_t index = 2; index < length - 1; ++index) {
        sum += input[index];
    }
    byte low = ~(static_cast<byte>(sum));
    return low == input[length - 1];
}

void DynamixelBase::handleError(const byte& errorCode) {
    m_voltageError = false;
    m_angleError = false;
    m_temperatureError = false;
    m_rangeError = false;
    m_checksumError = false;
    m_loadError = false;
    m_instructionError = false;
    if ((errorCode & 0x01) == 0x01) {
        cerr << "Input voltage is out of range." << endl;
        m_voltageError = true;
    }
    if ((errorCode & 0x02) == 0x02) {
        cerr << "Goal position is out of range." << endl;
        m_angleError = true;
    }
    if ((errorCode & 0x04) == 0x04) {
        cerr << "Temperature is out of range." << endl;
        m_temperatureError = true;
    }
    if ((errorCode & 0x08) == 0x08) {
        cerr << "Range is invalid." << endl;
        m_rangeError = true;
    }
    if ((errorCode & 0x10) == 0x10) {
        cerr << "Checksum is invalid." << endl;
        m_checksumError = true;
    }
    if ((errorCode & 020) == 0x20) {
        cerr << "Load is out of range." << endl;
        m_loadError = true;
    }
    if ((errorCode & 040) == 0x40) {
        cerr << "Instruction is out of range." << endl;
        m_instructionError = true;
    }
}
