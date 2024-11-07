#include "Enemy.hpp"

Texture2D HeianAlien::alienImages[3] = {};

HeianAlien::HeianAlien(int type, Vector2 position)
	:m_Type(type),
	Position(position)
{

	Image = LoadTexture("");

	if (alienImages[type - 1].id == 0)
	{
		switch (m_Type)
		{
		case 1:
			alienImages[0] = LoadTexture(pathA);
			break;
		case 2:
			alienImages[1] = LoadTexture(pathB);
			break;
		case 3:
			alienImages[2] = LoadTexture(pathC);
			break;
		}
	}
}

void HeianAlien::Draw()
{
	DrawTextureV(alienImages[m_Type-1], Position, WHITE);
}

void HeianAlien::Update()
{
	Move(1);
}

int HeianAlien::GetType() const
{
	return m_Type;
}

void HeianAlien::Move(int direction)
{
	Position.x += direction;
}

Rectangle HeianAlien::getRect()
{
	return {Position.x,Position.y,float(Image.width),float(Image.height)};
}


