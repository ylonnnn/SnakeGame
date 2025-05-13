#include <functional>
#include <iostream>

#include "../include/types.hpp"
#include "../include/Snake.hpp"

Snake::Snake() : direction(MovementDirection::None) {}

void Snake::initialize(SnakeGame &game_c) {
	game = &game_c;
}

void Snake::unlink() {
	delete game;
	game = nullptr;
}

void Snake::update_direction(MovementDirection dir) {
	int dist = std::abs(direction- dir);

	// If the distance between the current direction and the new direction is 0, they are the same, therefore, do nothing
	if (dist == 0)
		return;

	// If the length of the snake is greater than 1, moving to the opposite direction of the current direction will not be allowed 
	if (body.size() > 1 && dist == 1)
		return;
	
	direction = dir;
}

void Snake::update_score(int n_score) {
	score = n_score;
}

void Snake::place_at(int pos[2]) {
	Cell &cell = game->get_cell(pos); 

	// Update the state of the cell as it will be the position of the snake
	cell.state = CellState::Snake;

	// Append the cell to the snake's body
	body.push_front(std::ref(cell));
}

bool Snake::eat(Cell &cell) {
	switch (cell.state) {
		case CellState::Apple:
			// Increment the score
			score++;

			// Place random apple(s)
			game->place_apples();

			return true;

		// If the snake is attempting to eat a part of its body, end the game as that is one of the game ending conditions
		case CellState::Snake:
			game->attempt_terminate();

			return false;

		default: 
			return true;
	}
}

void Snake::move() {
	// If the direction of the snake is none, the snake will not move
	// Default State
	std::cout << direction << " : " << MovementDirection::None << "\n";
	if (direction == MovementDirection::None)
		return;

	// Retrieve the offset of the next head from the current head based on the direction
	int offset[2] = { direction == MovementDirection::Up ? -1 : direction == MovementDirection::Down ? 1 : 0, direction == MovementDirection::Right ? 1 : direction == MovementDirection::Left ? -1 : 0 };

	Cell &head = body.front();
	
	// If the position of the next head exceeds the field, the snake will bump to a wall
	// Therefore, it will be game over
	int next_head_pos[2] = { head.position[0] + offset[0], head.position[1] + offset[1] };
	if (game->exceeds_field(next_head_pos)) {
		game->attempt_terminate();
		
		return;	
	}

	Cell &next_head = game->get_cell(next_head_pos);
	if (!eat(next_head))
		return;

	// Store the current length of the snake
	int snake_len = body.size();

	// Update the state of the cell as part of the snake and append it to the front of the queue
	next_head.state = CellState::Snake;
	body.push_front(std::ref(next_head));
	
	// Update the state of the tail's cell as it will no longer be part of the snake
	Cell &curr_tail = body.back();
	curr_tail.state = CellState::Empty;

	// If the length of the snake is greater than the score, pop the back of the body
	// The score will always be less by 1 compared to the actual length as the score starts at 0 while the snake's length starts at 1
	if (snake_len > score) body.pop_back();
}
