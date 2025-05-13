#include <random>
#include <vector>
#include <ostream>

#include "types.hpp"

std::ostream &operator<<(std::ostream &os, const Cell &cell);

template <typename T>std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
	os << "{ ";

	size_t v_size = vec.size();

	for (int i = 0; i < v_size; i++) {
		const T &val = vec[i];

		os << val << (i < (v_size - 1) ? ", " : "");
	}

	return os << " }";
}

template <typename T>T &random_element(std::vector<T> &vec) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> int_dist(0, vec.size() - 1);

	return vec[int_dist(gen)];
}
