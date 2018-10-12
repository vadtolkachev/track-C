all: 
	g++ test.cpp -Wall -Wextra

mem:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log ./a.out

clean:
	rm -rf valgrind_info.log a.out
