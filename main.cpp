#include <iostream>
#include <fstream>
#include "sudoku.hpp"

int main(int argc, char* argv[])
{
	std::ifstream fin("./test_data/empty.txt");
	std::ofstream fout("output.txt");

	svirskey::sudoku_solver solver(fin);
	svirskey::sudoku_field  result = solver.solve();
	result.print(fout);
}
