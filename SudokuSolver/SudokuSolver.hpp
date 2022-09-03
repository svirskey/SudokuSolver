#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

class SudokuSolver
{

private:

	std::vector<std::vector<std::vector<int>>> field;

	int size = 0;

	void resetData();

	void Square(int& sch, const int str, const int col);

	bool checkField();

	bool isSolved();

public:

	SudokuSolver(int a);

	void inputFile(std::string path);

	bool solve();

	void outputFile(std::string path = "");

	friend std::ostream& operator <<(std::ostream& io, SudokuSolver& solve);
};
