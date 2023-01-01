#pragma once

#include <string>
#include <fstream>
#include "vectors.hpp"

namespace svirskey
{
	const int32_t sudoku_size = 9;
	const int32_t sudoku_size_mini = 6;

	class sudoku_field final : public vector_2d<int32_t, sudoku_size>
	{
	private:
		using vector_2d<int32_t, sudoku_size>::size_outer_;
		using vector_2d<int32_t, sudoku_size>::size_middle_;
		using vector_2d<int32_t, sudoku_size>::field_;

	public:

		sudoku_field() : vector_2d<int32_t, sudoku_size>() {}

		sudoku_field(const vector_3d<int32_t, sudoku_size, sudoku_size>& other) : vector_2d<int32_t, sudoku_size>(other) {}
	
		bool is_solved() const //TODO check for correct
		{
			for (int32_t i = 0; i < size_outer_; ++i)
			{
				for (int32_t j = 0; j < size_middle_; ++j)
				{
					if (field_[i][j] == 0)
						return false;
				}
			}
			return true;
		}
	};

	class sudoku_solver final
	{	
	private:

		vector_3d<int32_t, sudoku_size, sudoku_size, 1> field_;

		int32_t size_ = sudoku_size;

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
					for (int32_t k = field_[str][col].size() - 1; k >= 0; k--)
					{
						if (i != str && j != col && field_[i][j].size() == 1 && field_[str][col][k] == field_[i][j][0])
						{
							field_[str][col].erase(field_[str][col].begin() + k);
							cell = 0;
						}
					}
				}
			}
		}

		void fill_field()
		{
			for (int32_t i = 0; i < size_; ++i) //  current row
			{
				for (int32_t j = 0; j < size_; ++j) // current col
				{
					if (field_[i][j][0] == 0)
					{
						field_[i][j].pop_back();

						for (int32_t k = 0; k < size_; ++k)   // push possible numbers in cell and then remove which have met
						{
							field_[i][j].push_back(k + 1);
						}
					}
				}
			}
		}

		void clear();

		bool apply_simple()
		{
			int32_t cell = 0;

			while (cell < size_ * size_)
			{
				for (int32_t i = 0; i < size_; ++i) //  current row
				{
					for (int32_t j = 0; j < size_; ++j) // current col
					{
						if (field_[i][j].size() > 1)
						{
							for (int32_t k = 0; k < size_; ++k)
							{
								for (int32_t l = field_[i][j].size() - 1; l >= 0; --l) // check duplicates in row
								{
									if (j != k && field_[i][k].size() == 1 && field_[i][j][l] == field_[i][k][0]) 
									{
										field_[i][j].erase(field_[i][j].begin() + l);
										cell = 0;
									}
								}

								for (int32_t l = field_[i][j].size() - 1; l >= 0; --l) //  check duplicates in col
								{
									if (i != k && field_[k][j].size() == 1 && field_[i][j][l] == field_[k][j][0])
									{
										field_[i][j].erase(field_[i][j].begin() + l);
										cell = 0;
									}
								}
							}
							check_square(cell, i, j); //  check duplicates in square 3x3

							if (field_[i][j].size() == 0) // no possible numbers for this cell
								return false;
						}
						++cell;
					}
				}
			}
			#ifdef LOG_FLAG
			field_.print(std::cout);
			#endif
			return true;
		}

		bool apply_recursion()
		{
			do // TODO refactoring
			{
				if (!apply_simple())
					return false;

				if (is_solved())
					return true;

				int32_t i0 = -1, j0 = -1, min = -1;

				for (int32_t i = 0; i < size_; ++i) // find smallest count of possible numbers
				{
					for (int32_t j = 0; j < size_; ++j)
					{
						if (field_[i][j].size() > 1 && (min == -1 || min > field_[i][j].size()))
						{
							min = field_[i][j].size();
							i0 = i;
							j0 = j;
						}
					}
				}

				//recursion

				std::vector<int32_t> old_nums = field_[i0][j0]; // set of possible numbers before recursion 

				vector_3d old_field_ = field_;

				field_[i0][j0].clear();
				field_[i0][j0].push_back(old_nums[old_nums.size() - 1]);

				if (!apply_recursion()) //TODO for correct check
				{
					field_ = old_field_; 
					field_[i0][j0].pop_back();
				}
				else
					return true;
			} while (true);		
		}

		bool is_solved() //TODO check for correct
		{
			for (int32_t i = 0; i < size_; ++i)
			{
				for (int32_t j = 0; j < size_; ++j)
				{
					if (field_[i][j].size() != 1)
						return false;
				}
			}
			return true;
		}

	public:

		sudoku_solver(const vector_2d<int32_t, sudoku_size>& other): field_(other) {}

		sudoku_solver(std::istream& in): field_(in) {}

		sudoku_field simple_solve()
		{
			fill_field();
			apply_simple();
			//field_.print(std::cout);
			return sudoku_field(field_);
		}

		sudoku_field solve()
		{
			fill_field();
			//field_.print(std::cout);
			apply_recursion();
			return sudoku_field(field_);
			// if (result_.is_solved())
			// 	return result_;
			// else
			// 	throw std::runtime_error("Cannot solve");
		}
	};
}
