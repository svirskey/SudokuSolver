#include <iostream>
#include <vector>
#include "SudokuSolver.hpp"



int main(int argc, char* argv[])
{
	int size = 9;

	SudokuSolver solver(size);
	solver.inputFile("inputHard.txt");

	if (solver.solve())
		solver.outputFile("Output.txt");

	solver.inputFile("inputEasy.txt");

	if (solver.solve())
		solver.outputFile("Output.txt");
	else
		std::cerr << "Cannot solve sudoku..." << std::endl << std::endl;;
}
