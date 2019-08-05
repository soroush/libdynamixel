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

AC_INIT([libdynamixel], [0.1.1], [soroush@ametisco.ir], [libdynamixel],
        [https://github.com/soroush/libdynamixel])
AC_PREREQ([2.69])
AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

LT_INIT([shared static pic-only])

# Checks for header files.
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

AC_SUBST([DYNAMIXEL_SO_VERSION], [1:0:0])
AC_SUBST([DYNAMIXEL_API_VERSION], [0.1.1])

AC_CONFIG_FILES([Makefile
                src/Makefile
                test/Makefile
                libdynamixel.pc])
AC_OUTPUT
