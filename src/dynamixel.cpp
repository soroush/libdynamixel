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
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace Dynamixel;

DynamixelBase::DynamixelBase(Serial& serial, const word& id) :
		m_serial(serial), m_id { id } {
	m_data[3] = this->m_id;
}

DynamixelBase::DynamixelBase(Serial& serial, const word& id, const word& steps,
		const word& maxSpeed, const float& startAngle, const float& stopAngle,
		const word& startGap, const word& stopGap, const float& resolutionD,
		const float& resolutionR) :
		m_serial(serial), m_id { id }, m_steps { steps }, m_startAngle {
				startAngle }, m_stopAngle { stopAngle }, m_startGap { startGap }, m_stopGap {
				stopGap }, m_resolutionD { resolutionD }, m_resolutionR {
				resolutionR } {
	m_data[3] = this->m_id;
}

DynamixelBase::~DynamixelBase() {
}

void DynamixelBase::read(const size_t& start, const size_t& length) {
	Buffer packet = { 0xFF, 0xFF, this->m_data[3], 0x04, 0x02, //
			static_cast<char>(start), static_cast<char>(length), 0x00 };
	addChecksum(packet);
	m_serial.write(packet);
//	cout << "RWRITE: ";
//	for (int i = 0; i < 8; ++i) {
//		cout << std::hex << (static_cast<short>(packet[i]) & 0x00FF) << ' ';
//	}
//	cout << std::endl;
//	usleep(1000);
	Buffer statusPacket;
	statusPacket.resize(6+length);
	statusPacket = m_serial.read(6 + length);
//	cout << "RREAD : ";
//	for (int i = 0; i < 6 + length; ++i) {
//		cout << std::hex << static_cast<int>(statusPacket[i] & 0x00FF) << ' ';
//	}
//	cout << endl;
	if (static_cast<int>(statusPacket[4]) == 0x00) {
		if (checkChecksum(statusPacket)) {
			for (byte index = start, sindex = 5; index < start + length;
					++index, ++sindex) {
				m_data[index] = statusPacket[sindex];
			}
		} else {
			throw std::runtime_error {
					"Checksum error detected on returned packet. Terminating..." };
		}
	}
//	else {
//		// TODO: Handle error code
//		throw std::runtime_error {
//				"Motor error detected on returned packet. Terminating..." };
//	}
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
//	cout << "WWRITE: ";
//	for (int i = 0; i < packetSize; ++i) {
//		cout << std::hex << (static_cast<short>(packet[i]) & 0x00FF) << ' ';
//	}
//	cout << std::endl;
	m_serial.write(packet);
//	m_serial.flush();
	// Read status packet
//	usleep(1000);
	Buffer statusPacket = m_serial.read(6);
	//m_serial.flush();
//	cout << "WREAD : ";
//	for (int i = 0; i < 6; ++i) {
//		cout << std::hex << (static_cast<int>(statusPacket[i]) & 0x00FF) << ' ';
//	}
//	cout << std::endl;

	if (statusPacket[4] != 0x00) {
		// TODO: Handle response error
	} else if (!checkChecksum(statusPacket)) {
		// TODO: Handle checksum error
	}
}

word DynamixelBase::model() {
	this->read(0x00, 2);
	word model = ((0x00FF & this->m_data[0x01]) << 8) | this->m_data[0x00];
	return model;
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
	const byte data[1] = { id };
//	this->write(data, 1, 0x03);
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
}

word DynamixelBase::alarmLED() {
}

word DynamixelBase::alarmShutdown() {
}

bool DynamixelBase::torqueEnable() {
	this->read(0x18, 1);
	if (this->m_data[0x18] == 1) {
		return true;
	} else {
		return false;
	}
}

bool DynamixelBase::LEDEnable() {
	this->read(0x19, 1);
	if (this->m_data[0x19] == 1) {
		return true;
	} else {
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
	} else {
		return false;
	}
}

bool DynamixelBase::moving() {
	this->read(0x2E, 1);
	if (this->m_data[0x2E] == 1) {
		return true;
	} else {
		return false;
	}
}

bool DynamixelBase::locked() {
	this->read(0x2F, 1);
	if (this->m_data[0x2F] == 1) {
		return true;
	} else {
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
	Buffer packet = { //
			locked ? 0x01 : 0x00, };
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
		throw std::logic_error { "Not implemented" };
	}
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
		throw std::logic_error { "Not implemented" };
	}
	// TODO: Handle velocity units
	setGoalPosition(targetPosition);
}

void DynamixelBase::rotate(const float& rotation, const word& speed,
		const DynamixelBase::AngleUnit& units,
		const DynamixelBase::VelocityUnit& v_unit) {
	word currentPosition = this->presentPosition();
	cout << "Current position: " << currentPosition << endl;
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
	cout << "Target position: " << targetPosition << endl;
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

void DynamixelBase::rotate(const float& rotation,
		const DynamixelBase::AngleUnit& units,
		const DynamixelBase::VelocityUnit& v_unit) {
	word currentPosition = this->presentPosition();
	cout << "Current position: " << currentPosition << endl;
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
	cout << "Target position: " << targetPosition << endl;
	this->setGoalPosition(targetPosition);
}

void DynamixelBase::addChecksum(Buffer& input) {
	size_t length=input.size();
	word sum = 0;
	for (size_t index = 2; index < length - 1; ++index) {
		sum += input[index];
	}
	byte low = ~(static_cast<byte>(sum));
	input[length - 1] = low;
}

bool DynamixelBase::checkChecksum(const Buffer& input) {
	word sum = 0;
	size_t length=input.size();
	for (size_t index = 2; index < length - 1; ++index) {
		sum += input[index];
	}
	byte low = ~(static_cast<byte>(sum));
	return low == input[length - 1];
}
