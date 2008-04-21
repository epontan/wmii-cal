# wmii-cal version
VERSION = 0.2

# Customize below to fit your system

# debug
#DEBUG = -ggdb -std=c99 -pedantic

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = -I. $(shell pkg-config gtk+-2.0 --cflags)
LIBS = $(shell pkg-config gtk+-2.0 --libs)

# flags
CFLAGS = ${DEBUG} -Wall -Os ${INCS} -DVERSION=\"${VERSION}\"
LDFLAGS = ${DEBUG} ${LIBS}

# compiler and linker
CC = cc
