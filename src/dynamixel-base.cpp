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

#include "dynamixel-base.hpp"

#include <iostream>
#include <stdexcept>
#include <string.h>

dynamixel::base::base(uint8_t id) :
    m_id{id},
    m_is_half_duplex{false},
    m_com{nullptr} {
    m_data = new uint8_t[74];
    m_data[3] = this->m_id;
    m_status_return_level = 0x02;
}

dynamixel::base::base(uint8_t id, uint16_t steps,
                      uint16_t max_speed,
                      float start_angle, float stop_angle,
                      uint16_t start_gap, uint16_t stop_gap,
                      float resolution_d, float resolution_r):
    m_id {id},
    m_steps {steps},
    m_max_speed { max_speed },
    m_start_angle { start_angle },
    m_stop_angle { stop_angle },
    m_start_gap { start_gap },
    m_stop_gap { stop_gap },
    m_resolution_d { resolution_d },
    m_resolution_r { resolution_r },
    m_voltage_error { false },
    m_angle_error { false },
    m_temperature_error { false },
    m_range_error { false },
    m_checksum_error { false },
    m_load_error { false },
    m_instruction_error { false },
    m_is_half_duplex {false},
    m_com{nullptr} {
    m_data = new uint8_t[74];
    m_data[3] = this->m_id;
    m_status_return_level = 0x02;
}

dynamixel::base::base(const dynamixel::base& other) {
    m_data = new uint8_t[74];
    ::memcpy(&m_data[0], &other.m_data[0], 74);
    m_id = other.m_id;
    m_status_return_level = other.m_status_return_level;
    m_steps = other.m_steps;
    m_max_speed = other.m_max_speed;
    m_start_angle = other.m_start_angle;
    m_stop_angle = other.m_stop_angle;
    m_start_gap = other.m_start_gap;
    m_stop_gap = other.m_stop_gap;
    m_resolution_d = other.m_resolution_d;
    m_resolution_r = other.m_resolution_r;
    m_voltage_error = other.m_voltage_error;
    m_angle_error = other.m_angle_error;
    m_temperature_error = other.m_temperature_error;
    m_range_error = other.m_range_error;
    m_checksum_error = other.m_checksum_error;
    m_load_error = other.m_load_error;
    m_instruction_error = other.m_instruction_error;
    m_is_half_duplex = other.m_is_half_duplex;
    m_com = other.m_com;
}

dynamixel::base::base(dynamixel::base&& other) {
    m_data = other.m_data;
    other.m_data = nullptr;
    m_id = other.m_id;
    m_status_return_level = other.m_status_return_level;
    m_steps = other.m_steps;
    m_max_speed = other.m_max_speed;
    m_start_angle = other.m_start_angle;
    m_stop_angle = other.m_stop_angle;
    m_start_gap = other.m_start_gap;
    m_stop_gap = other.m_stop_gap;
    m_resolution_d = other.m_resolution_d;
    m_resolution_r = other.m_resolution_r;
    m_voltage_error = other.m_voltage_error;
    m_angle_error = other.m_angle_error;
    m_temperature_error = other.m_temperature_error;
    m_range_error = other.m_range_error;
    m_checksum_error = other.m_checksum_error;
    m_load_error = other.m_load_error;
    m_instruction_error = other.m_instruction_error;
    m_is_half_duplex = other.m_is_half_duplex;
    m_com = other.m_com;
}

dynamixel::base& dynamixel::base::operator=(const dynamixel::base& other) {
    if(this == &other) {
        return *this;
    }
    ::memcpy(m_data, other.m_data, 74);
    m_id = other.m_id;
    m_status_return_level = other.m_status_return_level;
    m_steps = other.m_steps;
    m_max_speed = other.m_max_speed;
    m_start_angle = other.m_start_angle;
    m_stop_angle = other.m_stop_angle;
    m_start_gap = other.m_start_gap;
    m_stop_gap = other.m_stop_gap;
    m_resolution_d = other.m_resolution_d;
    m_resolution_r = other.m_resolution_r;
    m_voltage_error = other.m_voltage_error;
    m_angle_error = other.m_angle_error;
    m_temperature_error = other.m_temperature_error;
    m_range_error = other.m_range_error;
    m_checksum_error = other.m_checksum_error;
    m_load_error = other.m_load_error;
    m_instruction_error = other.m_instruction_error;
    m_is_half_duplex = other.m_is_half_duplex;
    m_com = other.m_com;
    return *this;
}

dynamixel::base& dynamixel::base::operator=(base&& other) {
    if(this == &other) {
        return *this;
    }
    delete[] m_data;
    m_data = other.m_data;
    other.m_data = nullptr;
    m_id = other.m_id;
    m_status_return_level = other.m_status_return_level;
    m_steps = other.m_steps;
    m_max_speed = other.m_max_speed;
    m_start_angle = other.m_start_angle;
    m_stop_angle = other.m_stop_angle;
    m_start_gap = other.m_start_gap;
    m_stop_gap = other.m_stop_gap;
    m_resolution_d = other.m_resolution_d;
    m_resolution_r = other.m_resolution_r;
    m_voltage_error = other.m_voltage_error;
    m_angle_error = other.m_angle_error;
    m_temperature_error = other.m_temperature_error;
    m_range_error = other.m_range_error;
    m_checksum_error = other.m_checksum_error;
    m_load_error = other.m_load_error;
    m_instruction_error = other.m_instruction_error;
    m_is_half_duplex = other.m_is_half_duplex;
    return *this;
}

dynamixel::base::~base() {
    delete m_data;
    m_data = nullptr;
}

void dynamixel::base::read_mem(const size_t start, const size_t length) {
    if(!m_com) {
        return;
    }
    uint8_t packet[] = {
        uint8_t{0xFF},
        uint8_t{0xFF},
        m_data[3],
        0x04,
        0x02,
        static_cast<uint8_t>(start),
        static_cast<uint8_t>(length),
        0x00,
    };
    add_checksum(packet, 0x08);
    if(m_status_return_level > 0) {
        size_t expected_status_size = 6 + length;
        uint8_t* status_packet = new uint8_t[expected_status_size];
        m_com->raw_write_read(packet, sizeof(packet), status_packet, expected_status_size, m_is_half_duplex);
        if(status_packet[4] == 0x00) {
            if(check_checksum(status_packet, expected_status_size)) {
                ::memcpy(&status_packet[5], &m_data[start], length);
                m_voltage_error = false;
                m_angle_error = false;
                m_temperature_error = false;
                m_range_error = false;
                m_checksum_error = false;
                m_load_error = false;
                m_instruction_error = false;
            } else {
                std::cerr << "Returning packet has invalid checksum.\n" ;
            }
        } else {
            handle_error(status_packet[4]);
        }
        delete[] status_packet;
    } else {
        m_com->raw_write_read(packet, sizeof(packet), nullptr, 0, m_is_half_duplex);
    }
}

void dynamixel::base::write_mem(const uint8_t* data,
                                const size_t size,
                                const size_t start) {
    // TODO: Check sanity of given data
    // Send data to dynamixel
    uint8_t* packet = new uint8_t(7 + size);
    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = m_data[3];
    packet[3] = static_cast<uint8_t>(0x03 + size);
    packet[4] = 0x03;
    packet[5] = start;
    ::memcpy(&packet[6], &data, size);
    add_checksum(packet, 7 + size);
    // m_serial.write(packet.data(), packet.size());
    if(m_status_return_level == 0x02) {
        uint8_t status[6];
        // m_serial.read_mem(statusPacketBuffer, 6);
        if(status[4] != 0x00) {
            handle_error(status[4]);
        } else if(!check_checksum(status, 6)) {
            // TODO: Handle checksum error
        }
    }
    delete[] packet;
}

uint16_t dynamixel::base::model_number() {
    this->read_mem(0x00, 2);
    uint16_t model = ((0x00FF & this->m_data[0x01]) << 8) | this->m_data[0x00];
    return model;
}

dynamixel::base::model_t dynamixel::base::model() {
    uint16_t number = model_number();
    switch(number) {
        case 113:
            return model_t::dx113;
            break;
        case 116:
            return model_t::dx116;
            break;
        case 117:
            return model_t::dx117;
            break;
        case 44:
            return model_t::ax12w;
            break;
        case 12:
            return model_t::ax12;
            break;
        case 18:
            return model_t::ax18f;
            break;
        case 10:
            return model_t::rx10;
            break;
        case 24:
            return model_t::rx24f;
            break;
        case 28:
            return model_t::rx28;
            break;
        case 64:
            return model_t::rx64;
            break;
        case 107:
            return model_t::ex106plus;
            break;
        case 104:
            return model_t::mx12w;
            break;
        case 29:
            return model_t::mx28;
            break;
        case 54:
            return model_t::mx64;
            break;
        case 320:
            return model_t::mx106;
            break;
        case 350:
            return model_t::xl320;
            break;
        default:
            return model_t::unknown;
    }
}

uint16_t dynamixel::base::firmware() {
    this->read_mem(0x03, 1);
    uint16_t firmware = static_cast<uint16_t>(m_data[0x03]) & 0x00FF;
    return firmware;
}

uint16_t dynamixel::base::id() {
    return m_id;
}

void dynamixel::base::set_id(uint8_t id) {
    uint8_t data[] = { id };
    this->write_mem(data, 0x01, 0x03);
    m_data[3] = id;
    m_id = id;
}

uint16_t dynamixel::base::baudrate() {
    this->read_mem(0x04, 1);
    uint16_t baudrate = static_cast<uint16_t>(this->m_data[0x04]) & 0x00FF;
    return baudrate;
}

uint16_t dynamixel::base::delay() {
    this->read_mem(0x05, 1);
    uint16_t delayTime = static_cast<uint16_t>(this->m_data[0x05]) & 0x00FF;
    return delayTime;
}

uint16_t dynamixel::base::cw_angle_limit() {
    this->read_mem(0x06, 2);
    uint16_t limit = ((static_cast<uint16_t>(this->m_data[0x07]) & 0x00FF) << 8)
                     | (static_cast<uint16_t>(this->m_data[0x06]) & 0x00FF);
    return limit;
}

uint16_t dynamixel::base::ccw_angle_limit() {
    this->read_mem(0x08, 2);
    uint16_t limit = ((static_cast<uint16_t>(this->m_data[0x09]) & 0x00FF) << 8)
                     | (static_cast<uint16_t>(this->m_data[0x08]) & 0x00FF);
    return limit;
}

uint16_t dynamixel::base::high_temperature_limit() {
    this->read_mem(0x0B, 1);
    uint16_t temperature = static_cast<uint16_t>(this->m_data[0x0B]) & 0x00FF;
    return temperature;
}

uint16_t dynamixel::base::low_voltage_limit() {
    this->read_mem(0x0C, 1);
    uint16_t voltage = static_cast<uint16_t>(this->m_data[0x0C]) & 0x00FF;
    return voltage;
}

uint16_t dynamixel::base::high_voltage_limit() {
    this->read_mem(0x0D, 1);
    uint16_t voltage = static_cast<uint16_t>(this->m_data[0x0D]) & 0x00FF;
    return voltage;
}

uint16_t dynamixel::base::max_torque() {
    this->read_mem(0x0E, 2);
    uint16_t torque = ((static_cast<uint16_t>(this->m_data[0x0F]) & 0x00FF) << 8)
                      | (static_cast<uint16_t>(this->m_data[0x0E]) & 0x00FF);
    return torque;
}

uint16_t dynamixel::base::status_level() {
    this->read_mem(0x10, 1);
    uint16_t level = static_cast<uint16_t>(this->m_data[0x10]) & 0x00FF;
    return level;
}

// uint16_t dynamixel::base::alarm_led() {
// }

// uint16_t dynamixel::base::alarm_shutdown() {
// }

bool dynamixel::base::is_torque_enabled() {
    this->read_mem(0x18, 1);
    if(this->m_data[0x18] == 1) {
        return true;
    } else {
        return false;
    }
}

bool dynamixel::base::is_led_enabled() {
    this->read_mem(0x19, 1);
    if(this->m_data[0x19] == 1) {
        return true;
    } else {
        return false;
    }
}

uint16_t dynamixel::base::goal_position() {
    this->read_mem(0x1E, 2);
    uint16_t position = ((static_cast<uint16_t>(this->m_data[0x1F]) & 0x00FF) << 8)
                        | (static_cast<uint16_t>(this->m_data[0x1E]) & 0x00FF);
    return position;
}

uint16_t dynamixel::base::rotation_speed() {
    this->read_mem(0x20, 2);
    uint16_t speed = ((static_cast<uint16_t>(this->m_data[0x21]) & 0x00FF) << 8)
                     | (static_cast<uint16_t>(this->m_data[0x20]) & 0x00FF);
    return speed;
}

uint16_t dynamixel::base::torque_limit() {
    this->read_mem(0x22, 2);
    uint16_t limit = ((static_cast<uint16_t>(this->m_data[0x23]) & 0x00FF) << 8)
                     | (static_cast<uint16_t>(this->m_data[0x22]) & 0x00FF);
    return limit;
}

uint16_t dynamixel::base::current_position() {
    this->read_mem(0x24, 2);
    uint16_t position = ((static_cast<uint16_t>(this->m_data[0x25]) & 0x00FF) << 8)
                        | (static_cast<uint16_t>(this->m_data[0x24]) & 0x00FF);
    return position;
}

uint16_t dynamixel::base::current_speed() {
    this->read_mem(0x26, 2);
    uint16_t speed = ((static_cast<uint16_t>(this->m_data[0x27]) & 0x00FF) << 8)
                     | (static_cast<uint16_t>(this->m_data[0x26]) & 0x00FF);
    return speed;
}

uint16_t dynamixel::base::current_load() {
    this->read_mem(0x28, 2);
    uint16_t load = ((static_cast<uint16_t>(this->m_data[0x29]) & 0x00FF) << 8)
                    | (static_cast<uint16_t>(this->m_data[0x28]) & 0x00FF);
    return load;
}

uint16_t dynamixel::base::current_voltage() {
    this->read_mem(0x2A, 1);
    uint16_t voltage = ((static_cast<uint16_t>(this->m_data[0x2B]) & 0x00FF) << 8)
                       | (static_cast<uint16_t>(this->m_data[0x2A]) & 0x00FF);
    return voltage;
}

uint16_t dynamixel::base::current_temperature() {
    this->read_mem(0x2B, 1);
    uint16_t temperature = ((static_cast<uint16_t>(this->m_data[0x2C]) & 0x00FF) << 8)
                           | (static_cast<uint16_t>(this->m_data[0x2B]) & 0x00FF);
    return temperature;
}

bool dynamixel::base::is_registered() {
    this->read_mem(0x2C, 1);
    if(this->m_data[0x2C] == 1) {
        return true;
    } else {
        return false;
    }
}

bool dynamixel::base::is_moving() {
    this->read_mem(0x2E, 1);
    if(this->m_data[0x2E] == 0x01) {
        return true;
    } else {
        return false;
    }
}

bool dynamixel::base::is_locked() {
    this->read_mem(0x2F, 1);
    if(this->m_data[0x2F] == 1) {
        return true;
    } else {
        return false;
    }
}

uint16_t dynamixel::base::punch() {
    this->read_mem(0x30, 2);
    uint16_t punch = ((static_cast<uint16_t>(this->m_data[0x31]) & 0x00FF) << 8)
                     | (static_cast<uint16_t>(this->m_data[0x30]) & 0x00FF);
    return punch;
}

void dynamixel::base::set_position(uint16_t position) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(position & 0x00FF),
        static_cast<uint8_t>(position >> 8),
    };
    this->write_mem(packet, 0x02, 0x1E);
}

void dynamixel::base::set_speed(uint16_t speed) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(speed & 0x00FF),
        static_cast<uint8_t>(speed >> 8),
    };
    this->write_mem(packet, 0x02, 0x20);
}

void dynamixel::base::set_position_speed(uint16_t position, uint16_t speed) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(position & 0x00FF),
        static_cast<uint8_t>(position >> 8),
        static_cast<uint8_t>(speed & 0x00FF),
        static_cast<uint8_t>(speed >> 8),
    };
    this->write_mem(packet, 0x04, 0x1E);
}

void dynamixel::base::set_torque_limit(uint16_t limit) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(limit & 0x00FF),
        static_cast<uint8_t>(limit >> 8),
    };
    this->write_mem(packet, 0x02, 0x22);
}

void dynamixel::base::set_lock(bool is_locked) {
    uint8_t packet[] = { static_cast<uint8_t>(is_locked ? 0x01 : 0x00) };
    this->write_mem(packet, 0x01, 0x2F);
}

void dynamixel::base::set_punch(uint16_t punch) {
    uint8_t packet[] = { // L-H
        static_cast<uint8_t>(punch & 0x00FF),
        static_cast<uint8_t>(punch >> 8),
    };
    this->write_mem(packet, 0x02, 0x30);
}

void dynamixel::base::go(float target, float speed,
                         angle_t a_unit) {
    uint16_t target_position{0};
    uint16_t target_speed{0};
    switch(a_unit) {
        case angle_t::step:
            target_position = static_cast<uint16_t>(target); // No gap needed
            break;
        case angle_t::degree:
            target_position = static_cast<uint16_t>(target * m_resolution_d) - m_start_gap;
            break;
        case angle_t::radian:
            target_position = static_cast<uint16_t>(target * m_resolution_r) - m_start_gap;
            break;
        default:
            break;
    }
    target_speed = static_cast<uint16_t>(speed);
    set_position_speed(target_position, target_speed);
}


void dynamixel::base::go(const float target, const angle_t a_unit) {
    uint16_t target_position;
    switch(a_unit) {
        case angle_t::degree:
            target_position = static_cast<uint16_t>(target * m_resolution_d) - m_start_gap;
            break;
        case angle_t::radian:
            target_position = static_cast<uint16_t>(target * m_resolution_r) - m_start_gap;
            break;
        case angle_t::step:
        default:
            target_position = static_cast<uint16_t>(target);
            break;
            break;
    }
    set_position(target_position);
}

void dynamixel::base::rotate(const float angle, const uint16_t speed,
                             const dynamixel::base::angle_t a_u) {
    const uint16_t current_position = this->current_position();
    uint16_t target_position;
    uint16_t target_speed;
    switch(a_u) {
        case angle_t::degree:
            target_position = current_position + (angle * m_resolution_r);
            break;
        case angle_t::radian:
            target_position = current_position + (angle * m_resolution_r);
            break;
        case angle_t::step:
        default:
            target_position = current_position + angle;
            break;
            break;
    }
    if(target_position < 0) {
        // TODO: Handle underflow error
        target_position = 0;
    } else if(target_position > this->m_steps) {
        // TODO: Handle overflow error
        target_position = this->m_steps;
    }
    if(speed > this->m_max_speed) {
        // TODO: Handle overflow error
        target_speed = this->m_max_speed;
    } else {
        target_speed = speed;
    }
    set_position_speed(target_position, target_speed);
}

void dynamixel::base::rotate(const float angle,
                             const dynamixel::base::angle_t a_u) {
    const uint16_t current_position = this->current_position();
    uint16_t target_position;
    switch(a_u) {
        case angle_t::degree:
            target_position = current_position + (angle * m_resolution_r);
            break;
        case angle_t::radian:
            target_position = current_position + (angle * m_resolution_r);
            break;
        case angle_t::step:
        default:
            target_position = current_position + angle;
            break;
    }
    if(target_position < 0) {
        // TODO: Handle underflow error
        target_position = 0;
    } else if(target_position > this->m_steps) {
        // TODO: Handle overflow error
        target_position = this->m_steps;
    }
    set_position(target_position);
}

void dynamixel::base::add_checksum(uint8_t* const input, const size_t length) {
    uint16_t sum = 0;
    for(size_t index = 2; index < length - 1; ++index) {
        sum += input[index];
    }
    uint8_t low = ~(static_cast<uint8_t>(sum));
    input[length - 1] = low;
}

bool dynamixel::base::check_checksum(const uint8_t* const input, const size_t length) {
    uint16_t sum = 0;
    for(size_t index = 2; index < length - 1; ++index) {
        sum += input[index];
    }
    uint8_t low = ~(static_cast<uint8_t>(sum));
    return low == input[length - 1];
}

void dynamixel::base::handle_error(const uint8_t error_code) {
    m_voltage_error = false;
    m_angle_error = false;
    m_temperature_error = false;
    m_range_error = false;
    m_checksum_error = false;
    m_load_error = false;
    m_instruction_error = false;
    if((error_code & 0x01) == 0x01) {
        std::cerr << "Input voltage is out of range.\n";
        m_voltage_error = true;
    }
    if((error_code & 0x02) == 0x02) {
        std::cerr << "Goal position is out of range.\n";
        m_angle_error = true;
    }
    if((error_code & 0x04) == 0x04) {
        std::cerr << "Temperature is out of range.\n";
        m_temperature_error = true;
    }
    if((error_code & 0x08) == 0x08) {
        std::cerr << "Range is invalid.\n";
        m_range_error = true;
    }
    if((error_code & 0x10) == 0x10) {
        std::cerr << "Checksum is invalid.\n";
        m_checksum_error = true;
    }
    if((error_code & 020) == 0x20) {
        std::cerr << "Load is out of range.\n";
        m_load_error = true;
    }
    if((error_code & 040) == 0x40) {
        std::cerr << "Instruction is out of range.\n";
        m_instruction_error = true;
    }
}

// Serial Communication
void dynamixel::base::set_communicator(dynamixel::communicator* com) {
    m_com = com;
}
