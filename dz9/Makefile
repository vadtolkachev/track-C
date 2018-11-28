CPP=g++
CPPFLAGS=-Wall -Wextra -iquote ../dz4 -iquote VTree
OBJFILES=test3.o VTree/VTreeNode.o VTree/VTree.o VTree/VTreeParser.o VAkinator.o

all: clean_d build

build: $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o a.out $(OBJFILES)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean_d:
	rm -rf dumps/* *.log

clean: clean_d
	rm -rf *.o VTree/*.o a.out