#pragma once
#include<raylib.h>

class Block
{
public:
	Block(Vector2 position);
	void Draw();
	Rectangle getRect() const;
private:
	Vector2 m_Position;
};