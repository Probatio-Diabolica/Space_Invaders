#include "Bullet.hpp"
#include<iostream>

Bullet::Bullet()
{
	m_Active = false;
	m_Position = { -20,-20 };
	m_SPD = 0;
}

Bullet::Bullet(Vector2 position, short int spd)
	:m_Position(position)
	, m_SPD(spd)
{
	m_Active = true;
}

void Bullet::Update()
{
	m_Position.y -= m_SPD;
	if ((m_Position.y < 0) or (m_Position.y>800))
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

Bullet* Bullet::operator=(Bullet* a)
{
	this->m_Active	 = a->m_Active;
	this->m_Position = a->m_Position;
	this->m_SPD		 = a->m_SPD;
	return this;
}


