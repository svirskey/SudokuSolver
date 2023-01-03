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
		using vector_2d<int32_t, sudoku_size>::field_;

		bool has_square_duplicates(const int32_t& str, const int32_t& col) const
		{
			int32_t str_to,
				col_to;

			str_to = (str < 3) ? 3 : (str < 6) ? 6 : 9;
			col_to = (col < 3) ? 3 : (col < 6) ? 6 : 9;

			for (int32_t i = str_to - 3; i < str_to; ++i)
			{
				for (int32_t j = col_to - 3; j < col_to; ++j)
				{
					if (i != str && j != col  && field_[str][col] == field_[i][j])
						return true;
				}
			}
			return false;
		}

	public:

		sudoku_field() : vector_2d<int32_t, sudoku_size>() {}

		sudoku_field(const vector_3d<int32_t, sudoku_size, sudoku_size>& other) : vector_2d<int32_t, sudoku_size>(other) {}
	
		bool is_solved() const
		{
			for (int32_t i = 0; i < sudoku_size; ++i)
			{
				for (int32_t j = 0; j < sudoku_size; ++j)
				{
					if (field_[i][j] == 0)
						return false;
				}
			}

			for (int32_t i = 0; i < sudoku_size; ++i) //  current row
			{
				for (int32_t j = 0; j < sudoku_size; ++j) // current col
				{
					for (int32_t k = 0; k < sudoku_size; ++k)
					{
						if (j != k && field_[i][j] == field_[i][k]) //  check duplicates in row
							return false;
						if (i != k  && field_[i][j] == field_[k][j]) // check duplicates in col
							return false;
					}
					if (has_square_duplicates(i, j)) //  check duplicates in square 3x3
						return false; 
				}
			}
			return true;
		}
	};

	class sudoku_solver final
	{	
	private:

		sudoku_field origin_;

		vector_3d<int32_t, sudoku_size, sudoku_size, 1> field_;

		int32_t size_ = sudoku_size;

		void erase_with_square(int32_t cell, const int32_t str, const int32_t col)
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

		bool has_square_duplicates(const int32_t& str, const int32_t& col)
		{
			int32_t str_to,
				col_to;

			str_to = (str < 3) ? 3 : (str < 6) ? 6 : 9;
			col_to = (col < 3) ? 3 : (col < 6) ? 6 : 9;

			for (int32_t i = str_to - 3; i < str_to; ++i)
			{
				for (int32_t j = col_to - 3; j < col_to; ++j)
				{
					if (i != str && j != col  && field_[str][col][0] == field_[i][j][0])
						return true;
				}
			}
			return false;
		}

		void fill_field()
		{
			clear();

			for (int32_t i = 0; i < size_; ++i)
            {
                for (int32_t j = 0; j < size_; ++j)
                {
                    field_[i][j][0] = origin_[i][j];
                }
            }

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

		void clear()
		{
			for (int32_t i = 0; i < size_; ++i) //  current row
			{
				for (int32_t j = 0; j < size_; ++j) // current col
				{
					field_[i][j].clear();
					field_[i][j].push_back(0);
				}
			}
		}

		bool apply_simple()
		{
			int32_t cell = 0;
			
			while (cell < size_ * size_)
			{
				for (int32_t i = 0; i < size_; ++i) //  current row
				{
					for (int32_t j = 0; j < size_; ++j) // current col
					{
						if (field_[i][j].size() > 1) // TODO do we need this if?
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
							erase_with_square(cell, i, j); //  erase duplicates in square 3x3

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
			return is_solved();
		}
		bool is_correct()
		{
			for (int32_t i = 0; i < size_; ++i)
			{
				for (int32_t j = 0; j < size_; ++j)
				{
					if (origin_[i][j] < 0 || origin_[i][j] > 9)
						return false;
				}
			}
			return true;
		}

		bool has_variants()
		{
			for (int32_t i = 0; i < size_; ++i)
			{
				for (int32_t j = 0; j < size_; ++j)
				{
					if (field_[i][j].size() == 0)
						return false;
				}
			}
			return true;
		}

		bool apply_recursion()
		{		
			do // TODO refactoring
			{
				if (apply_simple())
					return true;

				if (!has_variants())
					return false;

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
				std::vector<int32_t> old_nums = field_[i0][j0]; // set of possible numbers before recursion 

				vector_3d old_field_ = field_;

				field_[i0][j0].clear();
				field_[i0][j0].push_back(old_nums[old_nums.size() - 1]);

				if (!apply_recursion())
				{
					field_ = old_field_; 
					field_[i0][j0].pop_back();
				}
				else
					return true;
			} while (true);		
		}

		bool is_solved()
		{
			for (int32_t i = 0; i < size_; ++i)
			{
				for (int32_t j = 0; j < size_; ++j)
				{
					if (field_[i][j].size() != 1 || field_[i][j][0] == 0)
						return false;
				}
			}
			for (int32_t i = 0; i < size_; ++i) //  current row
			{
				for (int32_t j = 0; j < size_; ++j) // current col
				{
					for (int32_t k = 0; k < size_; ++k)
					{
						if (j != k && field_[i][j][0] == field_[i][k][0]) //  check duplicates in row
							return false;
						if (i != k  && field_[i][j][0] == field_[k][j][0]) // check duplicates in col
							return false;
					}
					if (has_square_duplicates(i, j)) //  check duplicates in square 3x3
						return false; 
				}
			}
			return true;
		}

	public:

		sudoku_solver(const sudoku_field& other): origin_(other), field_() {}

		sudoku_solver(std::istream& in): origin_(in), field_() {}

		void fill(const sudoku_field& other)
		{
			clear();
			origin_ = other;
		}

		sudoku_field simple_solve()
		{
			if (!is_correct())
				return sudoku_field();
			fill_field();
			apply_simple();
			return sudoku_field(field_);
		}

		sudoku_field solve()
		{
			if (!is_correct())
				return sudoku_field();
			fill_field();
			apply_recursion();
			return sudoku_field(field_);
		}
	};
}

/*
сделать вектор 2д, который будет хранить изначальное поле, в функции солв или софт солв инициализировать филд, ставя флаг заполненности вектора
при выходе из функции опускать флаг обратно

*/