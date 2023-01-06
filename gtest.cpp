	#include <gtest/gtest.h>
	#include <iostream>
	#include <fstream>
	#include "sudoku.hpp"

	TEST(Correct_9x9_common, no_need_recursion) {
	std::ifstream input_fin("../test_data/simple.txt");
	svirskey::sudoku_solver solver(input_fin);
	svirskey::sudoku_field result_field = solver.solve();

	std::ifstream expected_fin("../expected_data/simple.txt");
	svirskey::sudoku_field expected_field(expected_fin);

	EXPECT_EQ(solver.get_status(), svirskey::solve_status::solved_no_recursion);
	EXPECT_EQ(result_field, expected_field);
	}

	TEST(Correct_9x9_common, need_recursion_1) {
	std::ifstream input_fin("../test_data/hard.txt");
	svirskey::sudoku_solver solver(input_fin);
	svirskey::sudoku_field result_field = solver.solve();

	std::ifstream expected_fin("../expected_data/hard.txt");
	svirskey::sudoku_field expected_field(expected_fin);

	EXPECT_EQ(solver.get_status(), svirskey::solve_status::solved_with_recursion);
	EXPECT_EQ(result_field, expected_field);
	}

	TEST(Correct_9x9_common, need_recursion_2) {
	std::ifstream input_fin("../test_data/crazy.txt");
	svirskey::sudoku_solver solver(input_fin);
	svirskey::sudoku_field result_field = solver.solve();

	std::ifstream expected_fin("../expected_data/crazy.txt");
	svirskey::sudoku_field expected_field(expected_fin);

	EXPECT_EQ(solver.get_status(), svirskey::solve_status::solved_with_recursion);
	EXPECT_EQ(result_field, expected_field);
	}

	TEST(Valid_9x9_common, empty) {
	std::ifstream input_fin("../test_data/empty.txt");
	svirskey::sudoku_solver solver(input_fin);
	svirskey::sudoku_field result_field = solver.solve();

	std::ifstream expected_fin("../expected_data/empty.txt");
	svirskey::sudoku_field expected_field(expected_fin);

	EXPECT_EQ(solver.get_status(), svirskey::solve_status::solved_with_recursion);
	EXPECT_EQ(result_field, expected_field);
	}


	TEST(Invalid_9x9_common, duplicate_numbers) {
	std::ifstream input_fin("../test_data/duplicates.txt");
	svirskey::sudoku_solver solver(input_fin);
	svirskey::sudoku_field result_field = solver.solve();

	std::ifstream expected_fin("../expected_data/duplicates.txt");
	svirskey::sudoku_field expected_field(expected_fin);

	EXPECT_EQ(solver.get_status(), svirskey::solve_status::invalid);
	EXPECT_EQ(result_field, expected_field);
	}

	TEST(Invalid_9x9_common, invalid_nums) {
	std::ifstream input_fin("../test_data/invalid_nums.txt");
	svirskey::sudoku_solver solver(input_fin);
	svirskey::sudoku_field result_field = solver.solve();

	std::ifstream expected_fin("../expected_data/invalid_nums.txt");
	svirskey::sudoku_field expected_field(expected_fin);

	EXPECT_EQ(solver.get_status(), svirskey::solve_status::invalid);
	EXPECT_EQ(result_field, expected_field);
	}

