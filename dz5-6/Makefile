PROG_OBJS=src/test3.cpp src/MyAssembler.cpp src/MyDisassembler.cpp ../dz4/debug/MyStack.cpp src/MyProcessor.cpp 
CPP=g++
COVFLAGS=-fprofile-arcs -ftest-coverage
CFLAGS=-Wall -Wextra
VFLAGS=--tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log

all: clean build

build: $(PROG_OBJS)
	$(CPP) $(PROG_OBJS) $(CFLAGS) -o a.out 

run: cleanInfo
	./a.out

val:
	valgrind $(VFLAGS) ./a.out

cov:
	./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo
	firefox /home/vad/Desktop/code/ded1sem/dz4/covinfo/index.html

cleanCov:
	rm -rf *gcda *.info covinfo 

cleanInfo:
	rm -rf logs/*.log code/mach_code.txt code/mach_code.bin code/mach_code2.txt code/asm_code_res.txt

clean: cleanCov cleanInfo
	rm -rf a.out *.o *gcno valgrind_info.log 