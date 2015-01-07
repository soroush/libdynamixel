AM_CPPFLAGS = -I$(srcdir)/.. $(OTHER_CPPFLAGS)
check_PROGRAMS = mx28_test 
mx28_test_SOURCES = mx28.cpp
mx28_test_LDADD = $(LIBSERIAL_LIBS) ../src/libdynamixel.la
TESTS = mx28_test
