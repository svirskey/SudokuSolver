#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// TODO
// class which contains vector or other container, maybe make with template
// class which solute sudoku and working with container as a pair of iterators or just reference

namespace svirskey
{
	class sudoku_solver
	{
	private:

		using container = std::vector<std::vector<std::vector<int32_t>>>;
		//TODO 
		// container which contains only written numbers
		// another temp vector with 3rd dimension of possible numbers
		// return 2-d vector or maybe another container
		container field;

		int32_t size;

		void clear();

		void check_square(int32_t cell, const int32_t str, const int32_t col);

		bool is_solved();

		void fill_field();

	public:

		sudoku_solver(std::istream& in, int32_t size = 9);

		bool soft_solve(); // should return container

		bool hard_solve(); // should return container

		friend std::ostream& operator <<(std::ostream& out, sudoku_solver& solve);

		friend std::istream& operator >>(std::istream& in, sudoku_solver& solve);
	};
}
