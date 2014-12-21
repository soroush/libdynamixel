ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
lib_LTLIBRARIES = libdynamixel.la
libdynamixel_la_SOURCES = \
	dynamixel.cpp \
	ax12.cpp \
	mx28.cpp 
libdynamixel_la_LDFLAGS = -version-info $(DYNAMIXEL_SO_VERSION)
dynamixel_includedir = $(includedir)/dynamixel
dynamixel_include_HEADERS = \
	dynamixel.hpp \
	ax12.hpp \
	mx28.hpp 