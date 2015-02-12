# paths
PREFIX = /usr/local

# includes and libs
INCS = -I. $(shell pkg-config gtk+-2.0 --cflags)
LIBS = $(shell pkg-config gtk+-2.0 --libs)
LIBS += -lX11 -lXinerama

# flags
CFLAGS = ${DEBUG} -Wall -Os ${INCS} -DVERSION=\"${VERSION}\"
LDFLAGS = ${DEBUG} ${LIBS}

# compiler and linker
CC = cc
LD = ${CC}
