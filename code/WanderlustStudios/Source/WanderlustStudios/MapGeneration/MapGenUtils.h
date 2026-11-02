#pragma once

#include <unordered_map>

namespace WanderlustStudios::MapGeneration {
	enum DIRECTIONS {
		INVALID = -1,
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	static const std::unordered_map<DIRECTIONS, std::pair<int, int>> DirectionVectors = {
		{DIRECTIONS::UP, {0, 1}},
		{DIRECTIONS::RIGHT, {1, 0}},
		{DIRECTIONS::DOWN, {0, -1}},
		{DIRECTIONS::LEFT, {-1, 0}}
	};
}
