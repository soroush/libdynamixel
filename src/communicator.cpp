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

#include "communicator.hpp"
#include "details/io-lock.hpp"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

dynamixel::communicator::communicator(const std::string& port, const int baudrate) :
    m_fd{0} {
    open_port(port, baudrate);
}

dynamixel::communicator::~communicator() {
    close_port();
}

void dynamixel::communicator::open_port(const std::string& port, const int baudrate) {
    if(port.empty()) {
        return;
    }
    m_fd = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if(m_fd < 0) {
        // TODO: Handle error and exit
        return;
    }
    struct termios tty;
    ::memset(&tty, 0, sizeof tty);
    if(::tcgetattr(m_fd, &tty) != 0) {
        // TODO: Handle error
        return;
    }
    ::cfsetospeed(&tty, baudrate);
    ::cfsetispeed(&tty, baudrate);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;      // disable break processing
    tty.c_lflag = 0;             // no signaling chars, no echo, no canonical processing
    tty.c_oflag = 0;             // no remapping, no delays
    tty.c_cc[VMIN]  = 1;         // read does block
    tty.c_cc[VTIME] = 5;         // 0.5 seconds read timeout
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD);        // ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= 0;                       // no parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    if(::tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        // TODO: Handle error
        return;
    }
}

void dynamixel::communicator::close_port() {
    close(m_fd);
    m_fd = -1;
}

void dynamixel::communicator::raw_write_read(const uint8_t* data, const size_t wsize,
        uint8_t* rdata, const std::size_t rsize,
        bool half_duplex) {
    dynamixel::details::io_lock_guard guard(*m_lock);
    if(half_duplex) {
        uint8_t* echo = new uint8_t[wsize];
        this->raw_write(data, wsize);
        this->raw_read(echo, wsize);
        // TODO : assert echo
        if(::memcmp(echo, data, wsize) != 0) {
            std::cerr << "Echo data differs!\n";
        }
        delete[] echo;
    } else {
        this->raw_write(data, wsize);
    }
    if(rdata) {
        this->raw_read(rdata, rsize);
    }
}

void dynamixel::communicator::raw_read(uint8_t* rdata, const size_t rsize) {
    if(m_fd < 0) {
        return;
    }
    size_t total = 0;
    uint8_t* current = rdata;
    while(total != rsize) {
        std::size_t r = ::read(m_fd, current, rsize - total);
        total = total + r;
        current = current + r;
    }
}

void dynamixel::communicator::raw_write(const uint8_t* data, const size_t wsize) {
    if(m_fd < 0) {
        return;
    }
    ssize_t wrote = ::write(m_fd, data, wsize);
    if(wrote != static_cast<ssize_t>(wsize)) {
        std::cerr << "Unable to write!\n";
    }
    ::tcflush(m_fd, TCIOFLUSH);
}
