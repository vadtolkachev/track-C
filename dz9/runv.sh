#!/bin/bash

make clean_d
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind_info.log ./a.out