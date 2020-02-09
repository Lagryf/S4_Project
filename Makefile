
CC = gcc
debug = -g
OPT = -O0
WARN = -Wall -Wextra -Werror
PTHREAD = -pthread

CCFLAGS = $(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB = `pkp-config --cflags --libs gtk+-3.0`

LD = gcc
LDFLGAS = $(PTHREAD) $(GTKLIB) -export-dynamic

SRC = main.c glade_function.c
OBJ = $(SRC:%.c=%.o)

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
%.o: %.c
	$(CC) $(CCFLAGS) -c $^ -o $(GTKLIB) -o main.o
	
.PHONY : clean	
clean:
	rm -f *.o 
