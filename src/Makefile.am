# libDynamixel, Dynamixel Servo Controller API
#
# Copyright 2014-2019 Soroush Rabiei <soroush@ametisco.ir>
#
# libDynamixel is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# See the file COPYING included with this distribution for more
# information.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CPPFLAGS = \
    --pedantic -Wall -Werror \
    $(PTHREAD_CFLAGS)

lib_LTLIBRARIES = libdynamixel.la

libdynamixel_la_SOURCES = \
    communicator.cpp \
    dynamixel-base.cpp \
    dynamixel-cms.cpp \
    dynamixel-dip.cpp \
    dynamixel-dip-ctg.cpp \
    ax12.cpp \
    dx113.cpp \
    dx116.cpp \
    dx117.cpp \
    rx10.cpp \
    rx24f.cpp \
    rx28.cpp \
    rx64.cpp \
    x106.cpp \
    mx12w.cpp \
    mx28.cpp \
    mx64.cpp \
    mx106.cpp \
    ex106plus.cpp

libdynamixel_la_LDFLAGS = -version-info $(DYNAMIXEL_SO_VERSION)

libdynamixel_la_LIBADD = \
    $(PTHREAD_LIBS)

dynamixel_includedir = $(includedir)/dynamixel
dynamixel_include_HEADERS = \
    communicator.hpp \
    dynamixel-base.hpp \
    dynamixel-cms.hpp \
    dynamixel-dip.hpp \
    dynamixel-dip-ctg.hpp \
    ax12.hpp \
    dx113.hpp \
    dx116.hpp \
    dx117.hpp \
    rx10.hpp \
    rx24f.hpp \
    rx28.hpp \
    rx64.hpp \
    x106.hpp \
    mx12w.hpp \
    mx28.hpp \
    mx64.hpp \
    mx106.hpp \
    ex106plus.hpp

noinst_dynamixel_includedir = $(includedir)/dynamixel/details
noinst_dynamixel_include_HEADERS = \
    details/io-lock.hpp
