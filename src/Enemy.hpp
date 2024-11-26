#pragma once
#include<raylib.h>

static const char* pathA = "Assets/Enemy/dragon.png";
static const char* pathB = "Assets/Enemy/rock.png";
static const char* pathC = "Assets/Enemy/ship.png";

class HeianAlien
{
public:
	HeianAlien(int type, Vector2 position);
	void Draw();
	void Update();
	int GetType() const ;
	void Move(int direction);
	Rectangle getRect();
	
private:
public:
	Vector2 Position;
	static Texture2D alienImages[3];
	Texture2D Image;
private:
	int m_Type;
};