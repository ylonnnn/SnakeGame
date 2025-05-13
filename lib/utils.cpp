#include "../include/types.hpp"
#include <iostream>
#include "../include/utils.hpp"

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
	return os << (cell.state == CellState::Snake ? " # " : cell.state == CellState::Apple ? " @ " : "   ");
}
