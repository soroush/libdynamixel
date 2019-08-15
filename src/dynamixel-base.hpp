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

#ifndef LIBDYNAMIXEL_DYNAMIXEL_BASE_HPP
#define LIBDYNAMIXEL_DYNAMIXEL_BASE_HPP

#include <cstdint>
#include <cstddef>

namespace dynamixel {

class base {
    friend class X106;
public:
    enum class model_t {
        unknown = 0,
        dx113 = 113,
        dx116 = 116,
        dx117 = 117,
        ax12w = 44,
        ax12 = 12,
        ax12plus = ax12,
        ax12a = ax12,
        ax18f = 18,
        ax18a = ax18f,
        rx10 = 10,
        rx24f = 24,
        rx28 = 28,
        rx64 = 64,
        ex106plus = 107,
        mx12w = 104,
        mx28 = 29,
        mx28t = mx28,
        mx28r = mx28,
        mx64 = 54,
        mx106 = 320,
        mx28a = mx28,
        mx28at = mx28,
        mx28ar = mx28,
        mx64a = mx64,
        mx64at = mx64,
        mx64ar = mx64,
        xl320 = 350,
    };
    enum class coordinate_t {
        trigonometric,
    };
    enum class angle_t {
        step, degree, radian
    };
    base(uint8_t id);
    base(uint8_t id, uint16_t steps,
         uint16_t max_speed, float start_angle,
         float stop_angle, uint16_t start_gap, uint16_t stop_gap,
         float resolutionD, float resolutionR);
    base(const base& other);
    base(base&& other);
    base& operator=(const base& other);
    base& operator=(base&& other);
    virtual ~base();
    // Low level API layer
    void read_mem(const std::size_t start, const std::size_t size);
    void write_mem(const uint8_t* data, const size_t size, const size_t start);
    // | High level API layer
    // |--- Readers
    uint16_t model_number();
    model_t model();
    uint16_t firmware();
    uint16_t id();
    uint16_t baudrate();
    uint16_t delay();
    uint16_t cw_angle_limit();
    uint16_t ccw_angle_limit();
    uint16_t high_temperature_limit();
    uint16_t low_voltage_limit();
    uint16_t high_voltage_limit();
    uint16_t max_torque();
    uint16_t status_level();
    uint16_t alarm_led();
    uint16_t alarm_shutdown();
    bool is_torque_enabled();
    bool is_led_enabled();
    uint16_t goal_position();
    uint16_t rotation_speed();
    uint16_t torque_limit();
    uint16_t current_position();
    uint16_t current_speed();
    uint16_t current_load();
    uint16_t current_voltage();
    uint16_t current_temperature();
    bool is_registered();
    bool is_moving();
    bool is_locked();
    uint16_t punch();
    // |--- Writers
    void set_id(uint8_t id);
    void set_position(uint16_t target);
    void set_speed(uint16_t speed);
    void set_position_speed(uint16_t target, uint16_t speed);
    void set_torque_limit(uint16_t limit);
    void set_lock(bool is_locked);
    void set_punch(uint16_t punch);

    void go(const float position, float speed,
            const angle_t unit = angle_t::degree);
    void go(const float target,
            const angle_t a_unit = angle_t::degree);

    void rotate(const float rotation, const uint16_t speed,
                const angle_t a_unit = angle_t::degree);
    void rotate(const float rotation,
                const angle_t aunit = angle_t::degree);

protected:
    void add_checksum(uint8_t* const buffer, const size_t length);
    bool check_checksum(const uint8_t* const input, const size_t length);
    void handle_error(uint8_t error_code);
    uint8_t* m_data;
    uint8_t m_id;
    uint8_t m_status_return_level;
    uint16_t m_steps;
    uint16_t m_max_speed;
    float m_start_angle;
    float m_stop_angle;
    uint16_t m_start_gap;
    uint16_t m_stop_gap;
    float m_resolution_d;
    float m_resolution_r;
    bool m_voltage_error;
    bool m_angle_error;
    bool m_temperature_error;
    bool m_range_error;
    bool m_checksum_error;
    bool m_load_error;
    bool m_instruction_error;
};

}  // namespace dynamixel

#endif /* LIBDYNAMIXEL_DYNAMIXEL_BASE_HPP_ */
