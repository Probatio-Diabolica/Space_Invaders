#pragma once
#include <vector>
#include "Blocks.h"

class Obstacle
{
public:
	Obstacle(Vector2 pos);
	void Draw();
	Vector2 postion;
	std::vector<Block> blocks;
	static std::vector<std::vector<int>> grid;
private:
};