#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class SudokuSolver
{

private:

	std::vector<std::vector<std::vector<int>>> field;

	int size = 0;

	void resetData();

	void checkSquare(int& cell, const int str, const int col);

	bool easySolve();

	bool isSolved();

	void fillField();

public:

	SudokuSolver(int size = 9);

	void inputFile(std::string path);

	bool solve();

	void outputFile(std::string path = "Output.txt");

	friend std::ostream& operator <<(std::ostream& io, SudokuSolver& solve);
};
