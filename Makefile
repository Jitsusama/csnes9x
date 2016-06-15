#-------------------------------------------------#
#
# Make file for Snes9X ROM Launcher
#
# Comment, Uncomment, or Edit the following
# lines in order to enable, disable, and/or Edit
# certain options.
#
#-------------------------------------------------#
# C++ compiler
CC= g++
DEBUG= -g -Wall -pedantic
OPT= -O6 -Wall -pedantic

#Uncomment below for normal use
CFLAGS= $(OPT) $(DEPS)
#Uncomment below for Debugging
#CFLAGS= $(DEBUG) $(DEPS)

PKGINSTALL= install
LIBS= -ltermcap -lreadline
INSTALLDIR= /usr/local/bin
MANDIR= /usr/local/man
RM= /bin/rm -f

.cpp.c.o: 
	$(CC) -c $(CFLAGS)

all: sneslaunch

sneslaunch: main.cpp funcs.hpp header.hpp
	$(CC) $(CFLAGS) $(INCS) main.cpp $(LIBS) -o csnes9x

install: sneslaunch
	$(PKGINSTALL) csnes9x $(INSTALLDIR)
	strip $(INSTALLDIR)/csnes9x

clean:
	$(RM) csnes9x

uninstall: $(INSTALLDIR)/csnes9x
	$(RM) $(INSTALLDIR)/csnes9x
