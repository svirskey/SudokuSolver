all:
	@g++ -std=c++20 -c sudoku.cpp -o sudoku.o
	@g++ -std=c++20 -O2 test.cpp sudoku.o -o result.exe
	@./result.exe
# test: all
# TODO : current all rule change to test, all rule can read from terminal