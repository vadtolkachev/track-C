PROG_OBJS=textSort.o test.o
CC=g++
CFLAGS=-fprofile-arcs -ftest-coverage -Wall -Wextra


all: build cov dox

build: $(PROG_OBJS)
	$(CC) $(CFLAGS) -o a.out $(PROG_OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

cov:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log ./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo

dox:
	doxygen Doxyfile

cleanCov:
	rm -rf *gcda *.info covinfo 

clean: cleanCov
	rm -rf valgrind_info.log a.out *.o html *gcno res.txt

