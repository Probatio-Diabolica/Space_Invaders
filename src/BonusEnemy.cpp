#include "BonusEnemy.hpp"

SpecialEnemy::SpecialEnemy()
{
	m_Image = LoadTexture("Assets/Enemy/Mage.png");
	m_Alive = false;
}

SpecialEnemy::~SpecialEnemy()
{
	UnloadTexture(m_Image);
}

void SpecialEnemy::Draw()
{
	if (m_Alive)
	{
		DrawTextureV(m_Image, m_Position, WHITE);
	}
}

void SpecialEnemy::Update()
{
	if (m_Alive)
	{
		m_Position.x += m_Speed; 
		if (m_Position.x > GetScreenWidth() - m_Image.width -25 || m_Position.x < 25)
		{
			m_Alive = false;
		}
	}
}

void SpecialEnemy::Spawn()
{
	m_Position.y = 90;
	int side = GetRandomValue(0, 1);
	if (side == 0)
	{
		m_Position.x = 25;
		m_Speed = 3;
	}
	else
	{
		m_Position.x = GetScreenWidth() - m_Image.width-25;
		m_Speed = -3;
	}
	m_Alive = true;
}

Rectangle SpecialEnemy::getRect()
{	
	if(m_Alive) return {m_Position.x,m_Position.y,float(m_Image.width),float(m_Image.height)};
	return { m_Position.x,m_Position.y,0,0 };
}

bool SpecialEnemy::isAlive() const
{
	return m_Alive;
}

void SpecialEnemy::Kill()
{
	m_Alive = false;
}
