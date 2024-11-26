#pragma once
#include <vector>
#include "Blocks.hpp"
#include "Utils/Bullet.hpp"


class Obstacle
{
public:
	Obstacle(Vector2 pos);
	void Draw();
	Vector2 postion;
	//bulletList blocks;
	std::vector<Block> blocks;
	static std::vector<std::vector<int>> grid;
};