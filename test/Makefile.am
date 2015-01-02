AM_CPPFLAGS = -I$(srcdir)/.. $(OTHER_CPPFLAGS)
check_PROGRAMS = dynamixel_test 
dynamixel_test_SOURCES = dynamixel.cpp
dynamixel_test_LDADD = $(LIBSERIAL_LIBS) ../src/libdynamixel.la
TESTS = dynamixel_test
