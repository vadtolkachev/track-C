PROG_OBJS=test.o MyStack.o MyElement.o
CC=g++
COVFLAGS=-fprofile-arcs -ftest-coverage
CFLAGS=$(COVFLAGS) -Wall -Wextra
VFLAGS=--tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log

all: build cov

build: $(PROG_OBJS)
	$(CC) $(CFLAGS) -o a.out $(PROG_OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

val:
	valgrind $(VFLAGS) ./a.out

cov:
	./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo
	firefox /home/vad/Desktop/code/ded1sem/dz3/C++/covinfo/index.html


cleanCov:
	rm -rf *gcda *.info covinfo 

clean: cleanCov
	rm -rf a.out *.o *gcno valgrind_info.log