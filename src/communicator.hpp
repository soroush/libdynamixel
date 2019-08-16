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

#ifndef LIBDYNAMIXEL_COMMUNICATOR_HPP
#define LIBDYNAMIXEL_COMMUNICATOR_HPP

#include <string>
#include <cstdint>
#include <cstddef>
#include <termios.h>

namespace dynamixel {
namespace details {
struct io_lock;
}
}

namespace dynamixel {
class communicator {
public:
    communicator(const std::string& port = "", const int baudrate = B115200);
    ~communicator();
    void open_port(const std::string& port = "", const int baudrate = B115200);
    void close_port();
    void raw_write_read(const uint8_t* data, const size_t wsize,
                        uint8_t* rdata, const size_t rsize,
                        bool half_duplex = false);

private:
    void raw_read(uint8_t* rdata, const size_t rsize);
    void raw_write(const uint8_t* data, const size_t wsize);

private:
    int m_fd;
    details::io_lock* m_lock;
};
}

#endif // LIBDYNAMIXEL_COMMUNICATOR_HPP
