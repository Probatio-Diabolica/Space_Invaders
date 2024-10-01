#include "Bullet.h"
#include<iostream>

Bullet::Bullet(Vector2 position, short int spd)
	:m_Position(position)
	, m_SPD(spd)
{
	//m_Position.x = position.x;
	//m_Position.y = position.y;
	m_Active = true;
}

void Bullet::Update()
{
	m_Position.y -= m_SPD;
	if (m_Position.y < 0 and m_Active)
	{	
		m_Active = false;
	}
}

void Bullet::Draw() const
{
	DrawRectangle(m_Position.x, m_Position.y, 4, 15, YELLOW);
}

bool Bullet::IsActive() const
{
	return m_Active;
}

void Bullet::Die()
{
	m_Active = false;
}

Rectangle Bullet::getRect()
{
	Rectangle rect;
	rect.x = m_Position.x;
	rect.y = m_Position.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}
