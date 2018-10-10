all: build cov dox

build:
	g++ -fprofile-arcs -ftest-coverage dz2.2.cpp -Wall -Wextra

cov:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log ./a.out
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory covinfo

dox:
	doxygen Doxyfile

cleanCov:
	rm -rf *gcda *.info covinfo 

clean: cleanCov
	rm -rf valgrind_info.log a.out html *gcno res.txt

