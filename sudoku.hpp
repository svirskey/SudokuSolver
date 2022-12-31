#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "vectors.hpp"

namespace svirskey
{
	template<size_t sz = 9>
	requires (sz > 0 && (sz == 6 || sz == 9))
	class sudoku_field final : public vector_2d<int32_t, sz, sz>
	{
	private:
		using vector_2d<int32_t, sz, sz>::size_A;
		using vector_2d<int32_t, sz, sz>::size_B;
		using vector_2d<int32_t, sz, sz>::field;

	public:

		sudoku_field() : vector_2d<int32_t, sz, sz>() {}

		//sudoku_field(const sudoku_field& other) {} //TODO

		bool is_solved() const //TODO check for correct
		{
			for (int32_t i = 0; i < size_A; ++i)
			{
				for (int32_t j = 0; j < size_B; ++j)
				{
					if (field[i][j] == 0)
						return false;
				}
			}
			return true;
		}
	};

	template<size_t sz = 9>
	requires (sz == 6 || sz == 9)
	class sudoku_solver final
	{	
	private:

		sudoku_field<sz> result;

		vector_3d<int32_t, 9, 9, 1> field;

		int32_t size;

		void check_square(int32_t cell, const int32_t str, const int32_t col)
		{
			int32_t str_to,
				col_to;

			str_to = (str < 3) ? 3 : (str < 6) ? 6 : 9;
			col_to = (col < 3) ? 3 : (col < 6) ? 6 : 9;

			for (int32_t i = str_to - 3; i < str_to; ++i)
			{
				for (int32_t j = col_to - 3; j < col_to; ++j)
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

		void fill_field()
		{
			for (int32_t i = 0; i < size; ++i) //  current row
			{
				for (int32_t j = 0; j < size; ++j) // current col
				{
					if (field[i][j][0] == 0)
					{
						field[i][j].pop_back();

						for (int32_t k = 0; k < size; ++k)   // push possible numbers in cell and then remove which have met
						{
							field[i][j].push_back(k + 1);
						}
					}
				}
			}
		}

		void clear();

		void apply_simple()
		{
			int32_t cell = 0;

			while (cell < size * size)
			{
				for (int32_t i = 0; i < size; ++i) //  current row
				{
					for (int32_t j = 0; j < size; ++j) // current col
					{
						if (field[i][j].size() > 1)
						{
							for (int32_t k = 0; k < size; ++k)
							{
								for (int32_t l = field[i][j].size() - 1; l >= 0; --l) // check duplicates in row
								{
									if (j != k && field[i][k].size() == 1 && field[i][j][l] == field[i][k][0]) 
									{
										field[i][j].erase(field[i][j].begin() + l);
										cell = 0;
									}
								}

								for (int32_t l = field[i][j].size() - 1; l >= 0; --l) //  check duplicates in col
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
								throw std::runtime_error("invalid data");
						}
						++cell;
					}
				}
			}
		}

		void apply_recursion()
		{
			fill_field();

			do // TODO refactoring
			{
				apply_simple();

				if (result.is_solved())
					return ;

				int32_t i0 = -1, j0 = -1, min = -1;

				for (int32_t i = 0; i < size; ++i) // find smallest count of possible numbers
				{
					for (int32_t j = 0; j < size; ++j)
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

				std::vector<int32_t> old_nums = field[i0][j0]; // set of possible numbers before recursion 

				vector_3d old_field = field;

				field[i0][j0].clear();
				field[i0][j0].push_back(old_nums[old_nums.size() - 1]);

				apply_recursion();
				if (!result.is_solved())
				{
					field = old_field;
					field[i0][j0].pop_back();
				}
				else
					return ;
			} while (true);		
		}


	public:

		sudoku_solver(const vector_2d<int32_t, 9>& other): field(other) { size = other.get_size_A();}

		sudoku_solver(std::istream& in, int size): size(size), field(in) {}

		vector_2d<int32_t, 9> simple_solve()
		{
			apply_simple();
			return result;
		}

		vector_2d<int32_t, sz> solve()
		{
			apply_recursion();

			if (result.is_solved())
				return result;
			else
				throw std::runtime_error("Cannot solve");
		}
	};
}
