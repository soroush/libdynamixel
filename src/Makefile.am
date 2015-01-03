ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
lib_LTLIBRARIES = libdynamixel.la
libdynamixel_la_SOURCES = \
	dynamixel.cpp \
	dynamixel_cms.cpp \
	dx113.cpp \
	dx116.cpp \
	dx117.cpp \
	ax12.cpp \
	rx10.cpp \
	rx24f.cpp \
	rx28.cpp \
	rx64.cpp \
	ex106plus.cpp \
	dynamixel_dip.cpp \
	x106.cpp \
	mx12w.cpp \
	mx28.cpp \
	mx64.cpp \
	mx106.cpp \
	dynamixel_dip_ctg.cpp
libdynamixel_la_LIBADD = $(LIBSERIAL_LIBS)
libdynamixel_la_LDFLAGS = -version-info $(DYNAMIXEL_SO_VERSION)
dynamixel_includedir = $(includedir)/dynamixel
dynamixel_include_HEADERS = \
	dynamixel.hpp \
	dynamixel_cms.hpp \
	dx113.hpp \
	dx116.hpp \
	dx117.hpp \
	ax12.hpp \
	rx10.hpp \
	rx24f.hpp \
	rx28.hpp \
	rx64.hpp \
	ex106plus.hpp \
	dynamixel_dip.hpp \
	x106.hpp \
	mx12w.hpp \
	mx28.hpp \
	mx64.hpp \
	mx106.hpp \
	dynamixel_dip_ctg.hpp