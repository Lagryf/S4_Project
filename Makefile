# Makefile

CC = gcc
CPPFLAGS =
CFLAGS =
LDFLAGS =
LDLIBS = -lSDL -lSDL_mixer
SRC = main.c glade_function.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main convert

main: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}           # remove object files
	${RM} ${DEP}   	       # remove dependency files
	${RM} main convert     # remove main program


