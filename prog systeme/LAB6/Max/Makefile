OBJ=main.o time.o
OS := $(shell uname)

ifeq ($(OS),Darwin)
LDFLAGS=-lpthread -lc -lm
CC=clang
else
LDFLAGS=-lpthread -lc -lm -lrt
CC=gcc
endif

all:max

max:$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c header.h
	$(CC) -o $@ -c $<

clean:
	rm -rf *.o max
