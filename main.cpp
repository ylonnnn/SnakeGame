#include "include/Snake.hpp"
#include "include/SnakeGame.hpp"

// The size of the field in terms of the base when squared
// 10 - 10x10
#define FIELD_SIZE 10

// The starting position of the snake in the field
// NOTE: The position must be within the bounds of the field
const int STARTING_POSITION[2] = { 3, 5 };

int main() {
	class Snake snake;
	SnakeGame game(10, snake, STARTING_POSITION);

	game.start();

	return 0;
}
