OBJS=test2.o SolveSquare.o 
CC=g++
CFLAGS=-fprofile-arcs -ftest-coverage -Wall -Wextra

all: build cov dox

build: $(OBJS)
	$(CC) $(CFLAGS) -o a.out $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

cov: cleanCov		
	./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo
	firefox /home/vad/Desktop/code/ded1sem/dz1/covinfo/dz1/index.html

dox: cleanDox
	doxygen Doxyfile
	firefox /home/vad/Desktop/code/ded1sem/dz1/html/index.html

cleanDox:
	rm -rf html

cleanCov:
	rm -rf *gcda *.info covinfo 

clean: cleanCov cleanDox
	rm -rf a.out *.o *gcno 

