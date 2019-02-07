CPP=g++
CPPFLAGS=-Wall -Wextra -g -MD -iquote ../dz4 -iquote VTree -iquote .
OBJFILES=test4.o VDerivator.o VTree/VTree.o VTree/VTreeParser.o VTree/VTreeNode.o

all: test.x

test.x: $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o test.x $(OBJFILES)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean_d:
	rm -rf dump/* *.log

clean: clean_d
	rm -rf test.x *.o VTree/*.o *.d VTree/*.d

-include *.d