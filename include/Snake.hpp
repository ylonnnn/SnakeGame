#pragma once

#include "types.hpp"
#include "SnakeGame.hpp"

class Snake {
	protected:
		SnakeGame *game;
		
	 	SnakeBody body;
		MovementDirection direction;

		int score;

	public: 
		Snake();

		void initialize(SnakeGame &game_c); 

		void unlink();

		void update_direction(MovementDirection dir);
		void update_score(int n_score);

		void place_at(int pos[2]); 
		
		bool eat(Cell &cell);
		void move();

		int get_score();
};
