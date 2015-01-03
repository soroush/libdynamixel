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

#ifndef DYNAMIXEL_HPP_
#define DYNAMIXEL_HPP_

#include <cstddef>
#include <memory>
#include <vector>
#include <SerialStream.h>

typedef char byte;
typedef uint_fast16_t word;
typedef std::vector<byte> Buffer;

namespace Dynamixel {

class DynamixelBase {
	friend class X106;
public:
	enum class Coordinate {
		Default, Trigonometric,
	};
	enum class AngleUnit {
		Default, Degree, Radian
	};
	enum class VelocityUnit {
		Default, RPM
	};
	DynamixelBase(LibSerial::SerialStream&, const word& id);
	DynamixelBase(LibSerial::SerialStream&, const word& id, const word& steps,
			const word& maxSpeed, const float& startAngle,
			const float& stopAngle, const word& startGap, const word& stopGap,
			const float& resolutionD, const float& resolutionR);
	virtual ~DynamixelBase();
	// Low level API layer
	void read(const std::size_t&, const std::size_t&);
	void write(const Buffer&, const std::size_t&);
	// | High level API layer
	// |--- Readers
	word model();
	word firmware();
	void setId(const byte&);
	word id();
	word baudrate();
	word delay();
	word cwAngleLimit();
	word ccwAngleLimit();
	word highTemperatureLimit();
	word lowVoltageLimit();
	word highVoltageLimit();
	word maxTorque();
	word statusReturnLevel();
	word alarmLED();
	word alarmShutdown();
	bool torqueEnable();
	bool LEDEnable();
	word goalPosition();
	word movingSpeed();
	word torqueLimit();
	word presentPosition();
	word presentSpeed();
	word presentLoad();
	word presentVoltage();
	word presentTemperature();
	bool registered();
	bool moving();
	bool locked();
	word punch();
	// |--- Writers
	void setGoalPosition(const word&);
	void setMovingSpeed(const word&);
	void setGoalPositionSpeed(const word& step, const word& speed);
	void setTorqueLimit(const word&);
	void setLock(const bool&);
	void setPunch(const word&);

	virtual void goTo(const float& target, const float& speed,
			const Coordinate& universe = Coordinate::Default,
			const AngleUnit& a_unit = AngleUnit::Default,
			const VelocityUnit& v_unit = VelocityUnit::Default);
	virtual void goTo(const float& target, const Coordinate& universe =
			Coordinate::Default, const AngleUnit& a_unit = AngleUnit::Default,
			const VelocityUnit& v_unit = VelocityUnit::Default);

	virtual void rotate(const float& rotation, const word& speed,
			const AngleUnit& a_unit = AngleUnit::Default,
			const VelocityUnit& v_unit = VelocityUnit::Default);
	virtual void rotate(const float& rotation, const AngleUnit& a_unit =
			AngleUnit::Default, const VelocityUnit& v_unit =
			VelocityUnit::Default);

protected:
	void addChecksum(Buffer&);
	bool checkChecksum(const Buffer&);
	LibSerial::SerialStream &m_serial;
	byte m_data[74];
	word m_id;
	word m_steps;
	word m_maxSpeed;
	float m_startAngle;
	float m_stopAngle;
	word m_startGap;
	word m_stopGap;
	float m_resolutionD;
	float m_resolutionR;
};

}  // namespace Dynamixel

#endif /* DYNAMIXEL_HPP_ */
