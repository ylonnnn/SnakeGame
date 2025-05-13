#include "include/Snake.hpp"
#include "include/SnakeGame.hpp"

int main() {
	class Snake snake;

	int starting_pos[2] = {3, 5}; 
	SnakeGame game(10, snake, starting_pos);

	game.start();
	game.map_field();

	return 0;
}
