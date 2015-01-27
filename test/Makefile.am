AM_CPPFLAGS = -I$(srcdir)/.. $(OTHER_CPPFLAGS)
check_PROGRAMS = ax12_test
#mx28_test 
ax12_test_SOURCES = ax12.cpp
ax12_test_LDADD = $(LIBSERIAL_LIBS) ../src/libdynamixel.la
#mx28_test_SOURCES = mx28.cpp
#mx28_test_LDADD = $(LIBSERIAL_LIBS) ../src/libdynamixel.la
TESTS = ax12_test
# mx28_test 
