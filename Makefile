# wmii-cal - calendar for wmii

include config.mk
sinclude config.local.mk

# wmii-cal version
VERSION = 0.9

BIN = wmii-cal
SRC = wmii-cal.c
OBJ = ${SRC:.c=.o}

all: options ${BIN}

options:
	@echo ${BIN} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"
	@echo "LD       = ${LD}"

${BIN}: ${OBJ}
	@echo LD $@
	@${LD} -o $@ ${OBJ} ${LDFLAGS}
	@if [ -z "${DEBUG}" ]; then echo "Stripping $@"; strip $@; fi

${BINDIR}:
	@mkdir -p ${BINDIR}

${OBJ}: config.mk

.c.o:
	@echo CC $@
	@${CC} -c ${CFLAGS} $<

debug: DEBUG = -ggdb
debug: all

test: CFLAGS += -DTEST
test: debug

clean:
	@echo cleaning
	@rm -f ${BIN} ${OBJ} ${BIN}-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p ${BIN}-${VERSION}
	@cp -R COPYING Makefile README config.mk ${SRC} ${BIN}-${VERSION}
	@tar -cf ${BIN}-${VERSION}.tar ${BIN}-${VERSION}
	@gzip ${BIN}-${VERSION}.tar
	@rm -rf ${BIN}-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/${BIN}

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/${BIN}

.PHONY: all test debug options clean dist install uninstall
