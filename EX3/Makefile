#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CFLAGS += -O2 -g -Wall #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS +=

OBJ = frame.o


all: game

game: ${OBJ}
		${arm-cortexm3-uclinuxeabi-gcc} ${CFLAGS} game.c ${OBJ} -o game ${LDFLAGS}



clean:
	-rm -f game *.o

install:


.PHONY: all install clean

# end of development makefile
