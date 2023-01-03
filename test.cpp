#include <iostream>
#include <fstream>
#include "sudoku.hpp"
#include <filesystem>

void test_file(const std::filesystem::path& path, std::ostream& fout)
{
	std::ifstream fin(path);
	if (!fin.good())
		return;
	svirskey::sudoku_solver solver(fin);

	svirskey::sudoku_field result = solver.simple_solve();

	if (result.is_solved())
	{
		std::cout << "Sudoku " << path.string() << " solved without recursion" <<  std::endl;
		result.print(fout);
		return ;
	}
	result = solver.solve();
	if (result.is_solved())
	{
		std::cout << "Sudoku " << path.string() << " solved with recursion" <<  std::endl;
		result.print(fout);
	}
	else
		std::cout << "Cannot solve sudoku from " << path.string() << " file." <<  std::endl;
}

// todo with gtest
int main(int argc, char* argv[])
{
	std::ofstream fout("output.txt");
	//auto &fout = std::cout;
	for (const auto& entry: std::filesystem::directory_iterator(".\\test_data"))
		test_file(entry.path(), fout);
}
