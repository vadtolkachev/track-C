PROG_OBJS=test2.cpp debug/MyStack.cpp
CPP=g++
COVFLAGS=-fprofile-arcs -ftest-coverage
CFLAGS=-Wall -Wextra
VFLAGS=--tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log

all: clean build

build: $(PROG_OBJS)
	$(CPP) $(PROG_OBJS) $(CFLAGS) -o a.out 

val:
	valgrind $(VFLAGS) ./a.out

cov:
	./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo
	firefox /home/vad/Desktop/code/ded1sem/dz4/covinfo/index.html

cleanCov:
	rm -rf *gcda *.info covinfo 

cleanLog:
	rm -rf logs/stackInfo*.log

clean: cleanCov cleanLog
	rm -rf a.out *.o *gcno valgrind_info.log 