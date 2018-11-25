CPP=g++
CPPFLAGS=-Wall -Wextra
PROG_OBJS=test.cpp VTree.cpp VAkinator.cpp

all: clean build

build:
	$(CPP) $(PROG_OBJS) $(CFLAGS) -o a.out

clean_d:
	rm -rf dumps/*

clean: clean_d
	rm -rf a.out