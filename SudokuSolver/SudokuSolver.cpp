#include "SudokuSolver.hpp"

bool SudokuSolver::easySolve()
{
	int cell = 0;

	while (cell < size * size)
	{
		for (int i = 0; i < size; i++) //  current row
		{
			for (int j = 0; j < size; j++) // current col
			{
				if (field[i][j].size() > 1)
				{
					for (int k = 0; k < size; k++)
					{
						for (int l = field[i][j].size() - 1; l >= 0; l--) // check duplicates in row
						{
							if (j != k && field[i][k].size() == 1 && field[i][j][l] == field[i][k][0]) 
							{
								field[i][j].erase(field[i][j].begin() + l);
								cell = 0;
							}
						}

						for (int l = field[i][j].size() - 1; l >= 0; l--) //  check duplicates in col
						{
							if (i != k && field[k][j].size() == 1 && field[i][j][l] == field[k][j][0])
							{
								field[i][j].erase(field[i][j].begin() + l);
								cell = 0;
							}
						}
					}
					checkSquare(cell, i, j); //  check duplicates in square 3x3

					if (field[i][j].size() == 0) // no possible numbers for this cell
						return false;
				}
				cell++;
			}
		}
	}
	return true;
}

bool SudokuSolver::isSolved()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (field[i][j].size() != 1)
				return false;
		}
	}
	return true;
}

void SudokuSolver::fillField()
{
	for (int i = 0; i < size; i++) //  current row
	{
		for (int j = 0; j < size; j++) // current col
		{
			if (field[i][j][0] == 0)
			{
				field[i][j].pop_back();

				for (int k = 0; k < size; k++)   // push possible numbers in cell and then remove which have met
				{
					field[i][j].push_back(k + 1);
				}
			}
		}
	}
}

bool SudokuSolver::solve()
{
	fillField();

	do
	{
		if (!easySolve())
			return false;

		if (isSolved())
			return true;

		int i0 = -1, j0 = -1, min = -1;

		for (int i = 0; i < size; i++) // find smallest count of possible numbers
		{
			for (int j = 0; j < size; j++)
			{
				if (field[i][j].size() > 1 && (min == -1 || min > field[i][j].size()))
				{
					min = field[i][j].size();
					i0 = i;
					j0 = j;
				}
			}
		}

		//recursion

		std::vector<int> oldNums = field[i0][j0]; // set of possible numbers before recursion 

		std::vector<std::vector<std::vector<int>>> oldField = field;

		field[i0][j0].clear();
		field[i0][j0].push_back(oldNums[oldNums.size() - 1]);

		if (!solve())
		{
			field = oldField;
			field[i0][j0].pop_back();
		}
		else
			return true;
	} while (true);

	return true;
}

void SudokuSolver::outputFile(std::string path)
{
	if (path.empty() || path == "")
	{
		std::cout << *this << std::endl;
	}
	else
	{
		std::ofstream fout(path, std::ios_base::out);

		if (!fout.good())
		{
			std::cerr << "Cannot open file: \"" << path << "\"" << std::endl << std::endl;
			return;
		}
		std::cout << "Result written to file: " << path << std::endl;
		fout << *this << "\n";
	}
}

std::ostream& operator <<(std::ostream& io, SudokuSolver& solve)
{
	for (int i = 0; i < solve.size; i++)
	{
		for (int j = 0; j < solve.size; j++)
		{
			io << solve.field[i][j][0] << " ";
		}
		io << std::endl;
	}
	return io;
}

void SudokuSolver::resetData()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			field[i][j].clear();
		}
	}
}

SudokuSolver::SudokuSolver(int size)
{
	this->size = size;
	field.resize(size);
	for (int i = 0; i < size; i++)
	{
		field[i].resize(size);
	}
}

void SudokuSolver::inputFile(std::string path)
{
	resetData();

	std::ifstream fin(path);
	if (!fin.good())
	{
		std::cerr << "Cannot open file: \"" << path << "\"" << std::endl << std::endl;
		resetData();
		fin.close();
		return;
	}

	int tmp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			try
			{
				fin >> tmp;
			}
			catch (const std::exception& exc)
			{
				std::cerr << "Error! Exception: " << exc.what();
				resetData();
				return;
			}
			field[i][j].push_back(tmp);
		}
	}
}

void SudokuSolver::checkSquare(int& cell, const int str, const int col)
{
	int str_to,
		col_to;

	str_to = (str < 3) ? 3 : (str < 6) ? 6 : 9;
	col_to = (col < 3) ? 3 : (col < 6) ? 6 : 9;

	for (int i = str_to - 3; i < str_to; i++)
	{
		for (int j = col_to - 3; j < col_to; j++)
		{
			for (int k = field[str][col].size() - 1; k >= 0; k--)
			{
				if (i != str && j != col && field[i][j].size() == 1 && field[str][col][k] == field[i][j][0])
				{
					field[str][col].erase(field[str][col].begin() + k);
					cell = 0;
				}
			}
		}
	}
}
