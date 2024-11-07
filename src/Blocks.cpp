#include "Blocks.hpp"

Block::Block(Vector2 position)
	: m_Position(position)
{
}

void Block::Draw()
{
	DrawRectangle(m_Position.y,m_Position.x,3,3,RED);
}

Rectangle Block::getRect() const
{
	Rectangle rect;
	rect.x = m_Position.x;
	rect.y = m_Position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;
}


