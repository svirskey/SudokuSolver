#include "sudoku.hpp"

namespace svirskey
{
	sudoku_solver::sudoku_solver(std::istream& in, int32_t size) : size(size), field(size)
	{
		int32_t tmp;

		for (int32_t i = 0; i < size; i++)
		{
			for (int32_t j = 0; j < size; j++)
			{
				in >> tmp;
				field[i][j].push_back(tmp);
			}
		}
	}

	void sudoku_solver::clear()
	{
		for (int32_t i = 0; i < size; i++)
		{
			for (int32_t j = 0; j < size; j++)
			{
				field[i][j].clear();
			}
		}
	}

	std::ostream& operator <<(std::ostream& out, sudoku_solver& solve)
	{
		for (int32_t i = 0; i < solve.size; i++)
		{
			for (int32_t j = 0; j < solve.size; j++)
			{
				out << solve.field[i][j][0] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	std::istream& operator >>(std::istream& in, sudoku_solver& solve)
	{
		int32_t tmp;

		solve.clear();
		for (int32_t i = 0; i < solve.size; i++)
		{
			for (int32_t j = 0; j < solve.size; j++)
			{
				in >> tmp;
				solve.field[i][j].push_back(tmp);
			}
		}
		return in;
	}

	bool sudoku_solver::hard_solve()
	{
		fill_field();

		do // TODO refactoring
		{
			if (!soft_solve())
				return false;

			if (is_solved())
				return true;

			int32_t i0 = -1, j0 = -1, min = -1;

			for (int32_t i = 0; i < size; i++) // find smallest count of possible numbers
			{
				for (int32_t j = 0; j < size; j++)
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

			std::vector<int32_t> oldNums = field[i0][j0]; // set of possible numbers before recursion 

			std::vector<std::vector<std::vector<int32_t>>> oldField = field;

			field[i0][j0].clear();
			field[i0][j0].push_back(oldNums[oldNums.size() - 1]);

			if (!hard_solve())
			{
				field = oldField;
				field[i0][j0].pop_back();
			}
			else
				return true;
		} while (true);

		return true;
	}

	void sudoku_solver::fill_field()
	{
		for (int32_t i = 0; i < size; i++) //  current row
		{
			for (int32_t j = 0; j < size; j++) // current col
			{
				if (field[i][j][0] == 0)
				{
					field[i][j].pop_back();

					for (int32_t k = 0; k < size; k++)   // push possible numbers in cell and then remove which have met
					{
						field[i][j].push_back(k + 1);
					}
				}
			}
		}
	}

	bool sudoku_solver::soft_solve()
	{
		int32_t cell = 0;

		while (cell < size * size)
		{
			for (int32_t i = 0; i < size; i++) //  current row
			{
				for (int32_t j = 0; j < size; j++) // current col
				{
					if (field[i][j].size() > 1)
					{
						for (int32_t k = 0; k < size; k++)
						{
							for (int32_t l = field[i][j].size() - 1; l >= 0; l--) // check duplicates in row
							{
								if (j != k && field[i][k].size() == 1 && field[i][j][l] == field[i][k][0]) 
								{
									field[i][j].erase(field[i][j].begin() + l);
									cell = 0;
								}
							}

							for (int32_t l = field[i][j].size() - 1; l >= 0; l--) //  check duplicates in col
							{
								if (i != k && field[k][j].size() == 1 && field[i][j][l] == field[k][j][0])
								{
									field[i][j].erase(field[i][j].begin() + l);
									cell = 0;
								}
							}
						}
						check_square(cell, i, j); //  check duplicates in square 3x3

						if (field[i][j].size() == 0) // no possible numbers for this cell
							return false;
					}
					cell++;
				}
			}
		}
		return true;
	}

	bool sudoku_solver::is_solved()
	{
		for (int32_t i = 0; i < size; i++)
		{
			for (int32_t j = 0; j < size; j++)
			{
				if (field[i][j].size() != 1)
					return false;
			}
		}
		return true;
	}

	void sudoku_solver::check_square(int32_t cell, const int32_t str, const int32_t col)
	{
		int32_t str_to,
			col_to;

		str_to = (str < 3) ? 3 : (str < 6) ? 6 : 9;
		col_to = (col < 3) ? 3 : (col < 6) ? 6 : 9;

		for (int32_t i = str_to - 3; i < str_to; i++)
		{
			for (int32_t j = col_to - 3; j < col_to; j++)
			{
				for (int32_t k = field[str][col].size() - 1; k >= 0; k--)
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
}