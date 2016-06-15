Snes9x Command Line Launcher
============================

Introduction
------------
This is a very simple launcher for snes9x. It simply searches
the directory specified by either the SNES96_ROM_DIR environment
variable, the option supplied by --d, or the default directory
/roms/ and prints out the names of all the roms. It then asks
you to chose one of them to play.

This program will also accept any of the command line options that
snes9x uses and will pass them unto the emulator.

Another feature of this program is the ability to tell it what the
name of the snes9x executable is. That way you can have it load up
gsnes9x for 3Dfx graphics, or ssnes9x for console play. Just change
the value of the SNES96_EXEC variable to the executable you wish to
use. IE: export SNES96_EXEC=gsnes9x if you are using bash, or setenv
SNES96_EXEC gsnes9x for tcsh or other variants. You can also use the
--e option to set it to a different value.

Also, if you wish for csnes9x to log the snes9x error messages,
set SNES96_LOG_FILE or the --l option, to specify what file to
log these errors to (it defaults to /dev/null).

Installation
------------
1. make
2. make install

