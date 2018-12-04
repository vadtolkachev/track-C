CPP=g++
CPPFLAGS=-Wall -Wextra -iquote ../dz4 -iquote VTree
OBJFILES=main.o VTree/VTreeNode.o

all: build

build: $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o a.out $(OBJFILES)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -rf a.out *.o VTree/*.o