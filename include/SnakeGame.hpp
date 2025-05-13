#pragma once

#include <functional>
#include <vector>

#include "types.hpp"

class Snake;

class SnakeGame {
	protected:
		int size;
		std::vector<std::vector<Cell>> field;

		class Snake &snake;
		int starting_pos[2];

		bool ended;

		void initialize_field();

	public:
		SnakeGame(int size, class Snake &snake);
		SnakeGame(int size, class Snake &snake, const int (&starting_pos)[2]);

		void map_field();
		Cell &get_cell(int pos[2]);

		std::vector<std::reference_wrapper<Cell>> get_empty_cells();

		bool exceeds_field(int pos[2]);

		void read_input();

		void place_apples(int count = 1);

		void start();
		void attempt_terminate();
		void end();
};
