PROG_OBJS=textSort.o test2.o
CC=g++
COVFLAGS=-fprofile-arcs -ftest-coverage
CFLAGS=-Wall -Wextra
VFLAGS=--tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log


all: clean build 

build: $(PROG_OBJS)
	$(CC) $(CFLAGS) -o a.out $(PROG_OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

cov: 
	valgrind $(VFLAGS) ./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo

dox:
	doxygen Doxyfile

cleanCov:
	rm -rf *gcda *.info covinfo 

clean: cleanCov
	rm -rf valgrind_info.log a.out *.o html *gcno res.txt

