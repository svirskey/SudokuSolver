#include <iostream>
#include <fstream>
#include "sudoku.hpp"

int main(int argc, char* argv[])
{
	std::ifstream fin("test_data/simple.txt");
	std::ofstream fout("output.txt");

	svirskey::sudoku_solver solver(fin);

	svirskey::sudoku_field result = solver.simple_solve();

	//if (result.is_solved())
		//result.print(fout);
	//else
		//std::cerr << "Cannot solve sudoku..." << std::endl;
}
