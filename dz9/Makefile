CPP=g++
CPPFLAGS=-Wall -Wextra -iquote ../dz4 -iquote VTree
CPPFILES=test2.cpp VTree/VTreeNode.cpp VTree/VTree.cpp VTree/VTreeParser.cpp VAkinator.cpp

all: clean build

build:
	$(CPP) $(CPPFLAGS) $(CPPFILES) -o a.out

clean_d:
	rm -rf dumps/* *.txt *.log

clean: clean_d
	rm -rf a.out