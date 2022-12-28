#include <iostream>
#include <fstream>
#include "sudoku.hpp"

int main(int argc, char* argv[])
{
	std::ifstream fin("test_data/hard.txt");
	std::ofstream fout("output.txt");

	svirskey::sudoku_solver solver(fin);

	if (solver.hard_solve())
		fout << solver;
	else
		std::cerr << "Cannot solve sudoku..." << std::endl;
}
