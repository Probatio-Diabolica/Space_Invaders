#pragma once
#include<raylib.h>
class SpecialEnemy
{
public:
	SpecialEnemy();
	~SpecialEnemy();
	void Draw();
	void Update();
	void Spawn();
	Rectangle getRect();
	bool isAlive()const;
	void Kill();
private:
	Vector2 m_Position;
	Texture2D m_Image;
	int m_Speed;
	bool m_Alive;
};