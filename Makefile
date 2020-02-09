CC = gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = -rdynamic $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = -rdynamic $(shell $(PKGCONFIG) --libs gtk+-3.0)
LDLIBS = -g -lSDL -lSDL_mixer -rdynamic -export-dynamic

SRC = main.c glade_function.c
OBJ = ${SRC:.c=.o}

all: main

main: ${OBJ}
	$(CC) -o $(@F) $(LIBS) $(OBJ) $(LDLIBS) 
    
glade_function: ${OBJ}
	$(CC) -o $(@F) $(LIBS) $(OBJ) $(LDLIBS) 
	
.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} main     # remove main program


