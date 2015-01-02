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

#include "serial.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace Dynamixel;

Serial::Serial(const string& name, const BaudRate& baud,
		const CharacterSize& size, const Parity& parity, const StopBits& stop,
		const FlowControlEnum& flow) {
	m_fd = ::open(name.c_str(), O_RDWR | O_NOCTTY);
	struct termios port_settings; // structure to store the port settings in
	tcgetattr(m_fd, &port_settings);
	cfsetispeed(&port_settings, B57600); // set baud rate
	cfsetospeed(&port_settings, B57600); // set baud rate
	port_settings.c_cflag |= CLOCAL | CREAD;
	port_settings.c_cflag &= ~CRTSCTS; // disable H/W flow control
	port_settings.c_lflag &= ~(ISIG | // disable SIGxxxx signals
			IEXTEN | // disable extended functions
			ECHO | ECHOE | // disable all auto-echo functions
			ICANON);
	port_settings.c_oflag &= ~OPOST; // raw output
	port_settings.c_iflag &= ~(IXON | IXOFF | IXANY); // disable S/W flow control;
	port_settings.c_cc[VTIME] = 1; // wait 0.1 second to get data
	port_settings.c_cc[VMIN] = 100;

	port_settings.c_cflag = (port_settings.c_cflag &= ~CSIZE) | CS8; // set data byte size
	port_settings.c_cflag &= ~CSTOPB; // set stop bit 1
	port_settings.c_cflag &= ~PARENB; // set no parity
	port_settings.c_iflag |= IGNPAR; // ignore parity
	port_settings.c_iflag &= ~(INPCK | ISTRIP | PARMRK);

	// Set
	if (tcsetattr(m_fd, TCSADRAIN, &port_settings) != 0) {
		//TODO: Handle errors
	} else {
		tcflush(m_fd, TCIOFLUSH);
	}
}

Serial::~Serial() {
}

bool Serial::close() {
	// TODO: Handle closing port error
	if (::close(m_fd) == 0) {
		return true;
	}
	return false;
}

vector<unsigned char> Serial::read(const size_t& minimum) {
	vector<unsigned char> retVal;
	unsigned char* buffer = new unsigned char[minimum];
//	cout << "Reading " << minimum << " bytes..." << endl;
    ssize_t packetSize = ::read(m_fd, buffer, minimum);
//	cout << packetSize << " bytes received." << endl;
    if (packetSize != -1)
    {
//        for (size_t i = 0; i < packetSize; ++i)
//        {
//            cout << std::hex << setfill('0') << setw(2)
//                 << static_cast<int>(buffer[i]) << ' ';
//        }
//        cout << std::dec << endl;
        for(size_t i=0; i<packetSize; ++i){
        	retVal.push_back(buffer[i]);
        }
        delete[] buffer;
        return retVal;
    }
    else
    {
        perror("Failed to read: ");
    }
}

void Serial::write(const vector<unsigned char>& data) {
	char buffer[data.size()];
	for(int i=0; i<data.size(); ++i){
		buffer[i]=data[i];
	}
	int wsize = ::write(m_fd, buffer, data.size());
}
