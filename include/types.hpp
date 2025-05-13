#pragma once

#include <deque>
#include <functional>

enum MovementDirection { 
	None, 
	Up = 10, 
	Down = 11, 
	Right = 20, 
	Left = 21,
};

enum CellState {
	Empty,
	Snake,
	Apple,
};

struct Cell {
	CellState state;
	int position[2];
};

using SnakeBody = std::deque<std::reference_wrapper<Cell>>;
