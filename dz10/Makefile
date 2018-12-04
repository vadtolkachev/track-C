CPP=g++
CPPFLAGS=-Wall -Wextra -iquote ../dz4 -iquote VTree
OBJFILES=main.o VTree/VTree.o VTree/VTreeParser.o VTree/VTreeNode.o

all: clean_d build

build: $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o a.out $(OBJFILES)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean_d:
	rm -rf dump/* *.log

clean:
	rm -rf a.out *.o VTree/*.o