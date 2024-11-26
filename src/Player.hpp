#pragma once
#include"Utils/BulletList.hpp"
#include<raylib.h>
#include"Utils/Bullet.hpp"
#include<vector>
class Player
{
public:
	Player();
	~Player();
	void Draw();
	void Update();
	void FireLaser();
	Rectangle getRect();
	void Reset();
	void MoveLeft();
	void moveRight();
	void moveUp(); // just experimental
	void MoveDown(); // just experimental
	Vector2 getLocation();
	int getBulletTop() const;

public:
	////Maybe I'll remove this 
	//Rectangle rect;
	bulletList playerBulletList;

private:
	Texture2D m_Image;
	Vector2 m_Position;
	float m_SPD = 5;
	double lastFireTime=0.0;
	Sound m_bulletSound;
};