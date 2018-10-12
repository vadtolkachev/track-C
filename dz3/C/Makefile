PROG_OBJS=test.o stack.o
CC=gcc
CFLAGS=-Wall -Wextra

all: build

build: $(PROG_OBJS)
	$(CC) $(CFLAGS) -o a.out $(PROG_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf a.out *.o