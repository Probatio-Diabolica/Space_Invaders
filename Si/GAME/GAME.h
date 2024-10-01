#pragma once
#include<raylib.h>
#include"State/States.h"

class GAME
{
private:
	const short int m_windowWidth;
	const short int m_windowHeight;
	const char* m_Title = "trial";
	Home m_state;
public:
	GAME(short int width,short int height,Home state = Home());
	void run();
	void render();
	void update();
	void events();
	int getWidth() const;
	int getHeight() const;
};