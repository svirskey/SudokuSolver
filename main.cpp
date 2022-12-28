#include <iostream>
#include "SudokuSolver.hpp"

int main(int argc, char* argv[])
{
	const int size = 9;

	SudokuSolver solver(size);
	solver.inputFile("inputHard.txt");

	if (solver.solve())
		solver.outputFile();
	else
		std::cerr << "Cannot solve sudoku..." << std::endl << std::endl;;
}
