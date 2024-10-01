#pragma once
#include<raylib.h>

class Bullet
{
public:
	Bullet(Vector2 position, short  int spd);
	void Update();
	void Draw() const ;
	bool IsActive() const ;
	void Die();
	Rectangle getRect();
private:
	bool m_Active;
	Vector2 m_Position;
	short int m_SPD; 
};