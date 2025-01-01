#
# Makefile - Copyright (c) 2024-2025 - Olivier Poncet
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# ----------------------------------------------------------------------------
# global environment
# ----------------------------------------------------------------------------

OPTLEVEL = -O2 -g
WARNINGS = -Wall
EXTRAS   = -fstack-protector-strong
CC       = gcc
CFLAGS   = -std=c99 $(OPTLEVEL) $(WARNINGS) $(EXTRAS)
CXX      = g++
CXXFLAGS = -std=c++14 $(OPTLEVEL) $(WARNINGS) $(EXTRAS)
CPPFLAGS = -I. -D_DEFAULT_SOURCE -D_FORTIFY_SOURCE=2
LD       = g++
LDFLAGS  = -L.
CP       = cp
CPFLAGS  = -f
RM       = rm
RMFLAGS  = -f

# ----------------------------------------------------------------------------
# default rules
# ----------------------------------------------------------------------------

.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $<

# ----------------------------------------------------------------------------
# global targets
# ----------------------------------------------------------------------------

all: build

build: build_brainfuck
	@echo "=== $@ ok ==="

clean: clean_brainfuck
	@echo "=== $@ ok ==="

check: check_brainfuck
	@echo "=== $@ ok ==="

# ----------------------------------------------------------------------------
# brainfuck files
# ----------------------------------------------------------------------------

brainfuck_PROGRAM = brainfuck.bin

brainfuck_SOURCES = \
	Brainfuck.cc \
	Console.cc \
	Program.cc \
	$(NULL)

brainfuck_HEADERS = \
	Brainfuck.h \
	Console.h \
	Program.h \
	$(NULL)

brainfuck_OBJECTS = \
	Brainfuck.o \
	Console.o \
	Program.o \
	$(NULL)

brainfuck_LDFLAGS = \
	$(NULL)

brainfuck_LDADD = \
	$(NULL)

# ----------------------------------------------------------------------------
# build brainfuck
# ----------------------------------------------------------------------------

build_brainfuck: $(brainfuck_PROGRAM)

$(brainfuck_PROGRAM): $(brainfuck_OBJECTS)
	$(LD) $(LDFLAGS) $(brainfuck_LDFLAGS) -o $(brainfuck_PROGRAM) $(brainfuck_OBJECTS) $(brainfuck_LDADD)

# ----------------------------------------------------------------------------
# clean brainfuck
# ----------------------------------------------------------------------------

clean_brainfuck:
	$(RM) $(RMFLAGS) $(brainfuck_OBJECTS) $(brainfuck_PROGRAM)

# ----------------------------------------------------------------------------
# check brainfuck
# ----------------------------------------------------------------------------

check_brainfuck:
	./$(brainfuck_PROGRAM) "$$(cat examples/hello-world.bf)"

# ----------------------------------------------------------------------------
# End-Of-File
# ----------------------------------------------------------------------------
