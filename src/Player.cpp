#include "Player.hpp"
#include<iostream>
Player::Player()
{
	m_Image = LoadTexture("Assets/player/player.png"); //path to the image 
	m_Position = { (GetScreenWidth() - float(m_Image.width))/ 2,GetScreenHeight() - float(m_Image.height) - 100 };
	m_bulletSound = LoadSound("Assets/Sounds/Bullet.wav");
	playerBulletList = bulletList(35);
	
}

Player::~Player()
{
	UnloadTexture(m_Image);
	UnloadSound(m_bulletSound);
	playerBulletList.~bulletList();
}


void Player::Draw()
{
	DrawTextureV(m_Image,m_Position,WHITE);
}

void Player::Update()
{
	
}

void Player::MoveLeft()
{
	if ((m_Position.x-7) >= 25)
	m_Position.x -= m_SPD;
}

void Player::moveRight()
{
	if ((m_Position.x + 32+m_SPD) <= GetScreenWidth()-25)
	m_Position.x += m_SPD;
}

void Player::moveUp()
{
	if ((m_Position.y -m_SPD) >= 0)
		m_Position.y -= m_SPD;
}

void Player::MoveDown()
{
	if ((m_Position.y +32+ m_SPD) <= GetScreenHeight()-100)
		m_Position.y += m_SPD;
}

Vector2 Player::getLocation()
{
	return m_Position;
}

int Player::getBulletTop() const
{
	return playerBulletList.getTop();
}


void Player::FireLaser()
{
	if (GetTime() - lastFireTime >= 0.2)
	{
		playerBulletList.push(Bullet(Vector2(m_Position.x + 14, m_Position.y), 4));
		lastFireTime = GetTime();
		PlaySound(m_bulletSound);
	}
}

Rectangle Player::getRect()
{
	return {m_Position.x,m_Position.y,float(m_Image.width),float(m_Image.height)}; //Rect={XPos,Ypos,float(Rect_Width),float(Rect_Height)}
}

void Player::Reset()
{
	m_Position.x = (GetScreenWidth() - m_Image.width)/2.0f;
	m_Position.y = (GetScreenHeight() - m_Image.height);
	playerBulletList.reset();;
}
