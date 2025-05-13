#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <conio.h>
#include <unordered_map>
#include <vector>

#include "../include/SnakeGame.hpp"
#include "../include/Snake.hpp"
#include "../include/utils.hpp"

SnakeGame::SnakeGame(int size, class Snake &snake) : size(size), snake(snake), ended(false) {
	snake.initialize(*this);
	initialize_field();
	
	starting_pos[0] = 0, starting_pos[1] = 0;
}

SnakeGame::SnakeGame(int size, class Snake &snake, const int (&pos)[2]) : size(size), snake(snake), ended(false) {
	snake.initialize(*this);
	initialize_field();

	starting_pos[0] = pos[0], starting_pos[1] = pos[1];
}

void SnakeGame::initialize_field() {
	field = std::vector<std::vector<Cell>>(size);

	for (int i = 0; i < size; i++) {
		field[i] = std::vector<Cell>();

		std::vector<Cell> &row = field[i];
		row.reserve(size);

		for (int j = 0; j < size; j++) {
			Cell cell = {CellState::Empty, {i, j}};

			row.push_back(std::move(cell));
		}
	}
}

void SnakeGame::map_field() {
	std::string h_line;
	for (int i = 0; i <= (size + 1); i++) {
		h_line += " * ";
	}

	std::cout << h_line << "\n";

	for (int i = 0; i < size; i++) {
		const std::vector<Cell> &row = field[i];

		for (int j = -1; j <= size; j++) {
			if (j < 0 || j >= size)  {
				std::cout << " * ";

				continue;
			}

			const Cell &cell = row[j];

			std::cout << (cell.state == CellState::Apple ? " @ " : cell.state == CellState::Snake ? " # " : "   ");
		}

		std::cout << "\n";
	}

	std::cout << h_line << "\n";

	// Display the score of the snake 
	std::cout << "SCORE: " << snake.get_score() << "\n";
} 

Cell &SnakeGame::get_cell(int pos[2]) {
	return field[pos[0]][pos[1]];
}

std::vector<std::reference_wrapper<Cell>> SnakeGame::get_empty_cells() {
	std::vector<std::reference_wrapper<Cell>> empty_cells;
	empty_cells.reserve(size * size);

	for (std::vector<Cell> &row : field) {
		for (Cell &cell : row) {
			if (cell.state != CellState::Empty)
				continue;

			empty_cells.push_back(std::ref(cell));
		}
	}

	return empty_cells;
}

bool SnakeGame::exceeds_field(int pos[2]) {
	int row = pos[0], col = pos[1];

	return (row < 0 || row >= size) || (col < 0 || col >= size);
}

void SnakeGame::read_input() {
	if (!_kbhit())
		return;
	
	char ch = _getch();

	switch (ch) {
		case 'w':
		case 'k':
			snake.update_direction(MovementDirection::Up);
			break;

		case 's':
		case 'j':
			snake.update_direction(MovementDirection::Down);
			break;

		case 'a':
		case 'h':
			snake.update_direction(MovementDirection::Left);
			break;

		case 'd':
		case 'l':
			snake.update_direction(MovementDirection::Right);
			break;

		case 'q':
			end(); 

			break;
	}
}

void SnakeGame::place_apples(int count) {
	std::vector<std::reference_wrapper<Cell>> empty_cells = get_empty_cells();
	std::unordered_map<int, bool> pos_record;

	for (int i = 0; i < count; i++) {
		Cell &r_cell = random_element(empty_cells);
		int normalized_pos = (r_cell.position[0] * size) + (r_cell.position[1] + 1);

		// If the normalized position is already in the position records, an apple has already been placed there
		if (pos_record.find(normalized_pos) != pos_record.end()) {
			i--;

			continue;
		}
			
		r_cell.state = CellState::Apple;
		pos_record[normalized_pos] = true;	
	}
}

void SnakeGame::start() {
	snake.place_at(starting_pos);

	// Place the initial apple
	place_apples();

	// Clear the screen
	std::cout << "\033[2J\033[1;1H";

	while (!ended) {
		std::cout << "\x1b[H";

		read_input();
		snake.move();

		map_field();
		std::this_thread::sleep_for(std::chrono::milliseconds(450));
	}

	// Clear the screen
	std::cout << "\033[2J\033[1;1H";

	end();
}

void SnakeGame::attempt_terminate() {
	ended = true;
}

void SnakeGame::end() {
	std::cout << "GAME OVER!\nYou scored " << snake.get_score() << "\n";
} 
