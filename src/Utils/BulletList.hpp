#pragma once

#include"Bullet.hpp"

class bulletList
{
private:
	int m_size;
	Bullet *m_array;
	int m_top;
public:
	int removed = 0;

public:
	bulletList();
	bulletList(const bulletList& other);
	explicit bulletList(int size);
	~bulletList();
	int getTop()const;
	void push(Bullet item);
	void update();
	void render();
	void reset();
	Bullet& operator[](int index);
	bulletList& operator=(const bulletList& other);
};


