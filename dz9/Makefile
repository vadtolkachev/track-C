CPP=g++
CPPFLAGS=-Wall -Wextra -iquote ../dz4 -iquote VTree
CPPFILES=test3.cpp VTree/VTreeNode.cpp VTree/VTree.cpp VTree/VTreeParser.cpp VAkinator.cpp

all: clean build

build:
	$(CPP) $(CPPFLAGS) $(CPPFILES) -o a.out

clean_d:
	rm -rf dumps/* *.log

clean: clean_d
	rm -rf a.out