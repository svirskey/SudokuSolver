#include <iostream>
#include <fstream>
#include "sudoku.hpp"


void test_file(const std::string& filename_, std::ostream& fout)
{
	std::ifstream fin(filename_);
	if (!fin.good())
		return;
	svirskey::sudoku_solver solver(fin);

	svirskey::sudoku_field result = solver.solve();

		if (result.is_solved())
		result.print(fout);
	else
		std::cerr << "Cannot solve sudoku from " << filename_ << " file." <<  std::endl;
}

// todo with gtest
int main(int argc, char* argv[])
{
	std::ofstream fout("output.txt");
	//auto &fout = std::cout;

	test_file("test_data/simple.txt", fout);
	test_file("test_data/hard.txt", fout);
}
