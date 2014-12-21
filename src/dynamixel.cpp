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
using namespace std;
using namespace LibSerial;

Dynamixel::Dynamixel(SerialStream& serial, const unsigned int& id) :
        m_serial(serial), m_id { id } {
    m_data[3] = this->m_id;
}

void Dynamixel::read(const byte& start, const byte& length) {
    byte packet[8] = { 0xFF, 0xFF, this->m_data[3], 0x04, 0x02, start, length,
            0x00 };
    addChecksum(packet, 8);
    m_serial.write(packet, 8);
    byte statusPacket[6 + length];
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
