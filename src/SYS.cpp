#include"SYS.hpp"
#include<raylib.h>
#include<string>
#include<chrono>
#include "GAME.hpp"
#include "Obstacles.hpp"
#include "Enemy.hpp"



static uint64_t getTimeNS()
{
	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

static uint64_t getTimeMS() {
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}


static std::string FormatWithLeadingZeros(int number,int width)
{
	std::string numberText = std::to_string(number);
	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}

const short int width=800;
const short int height=800;
const Color grey = { 29,29,27,255 };
const Color background = {155,155,155,255};
const int offset = 50;
Color yellow = { 243,216,63,255 };


void SpaceInvaders::run()
{
	InitWindow(	(width + offset), (height + offset * 2) , "SPACE INVADER TITLE");
	InitAudioDevice();
	Font font = LoadFontEx("Assets/Fonts/Font.ttf",64,0,0);
	//SetTargetFPS(60);
	Texture2D staticPlayer = LoadTexture("Assets/Player/player.png");
	GAME game;
	HeianAlien alien = HeianAlien(1, { 100,100 });

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//time
	uint64_t timer = getTimeMS();
	uint64_t initTime = getTimeNS();
	const double nano = 1000000000.0 / 60.0;
	double delta = 0;
	int frames = 0;
	int updates = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (!WindowShouldClose())
	{	////////////////////////////////////
		//Time calc
		uint64_t currentTime = getTimeNS();
		delta += (currentTime - initTime) / nano;
		initTime = currentTime;
		////////////////////////////////////////////////////
		
		while (delta >= 1)
		{
			UpdateMusicStream(game.music);
			game.inputs();
			game.update();
			++updates;
			--delta;
		}
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(background);
		
	
		DrawLineEx({ 25,730 }, { 775,730 }, 3, BLACK);

		game.forward ? DrawTextEx(font, "Level 01", { 570,740 }, 34, 2, yellow) : DrawTextEx(font, "GAME OVER", { 570,740 }, 34, 2, yellow);
		float x = 50.0;
		for (short int i = 0; i < game.playerLives; i++) 
		{
			DrawTextureV(staticPlayer, { x,745 }, WHITE);
			x += 50.0;
		}
		DrawTextEx(font,"Score",{50,15},34,2,yellow);
		std::string scoreText = FormatWithLeadingZeros(game.score,5);
		DrawTextEx(font, scoreText.c_str(), { 50,40 }, 34, 2, yellow);

		DrawTextEx(font, "High Score", { 570,15 }, 34, 2, yellow);
		std::string HighScoreText = FormatWithLeadingZeros(game.highscore, 5);
		DrawTextEx(font, HighScoreText.c_str(), { 655,40 }, 34, 2, yellow);
		game.draw();
		EndDrawing(); 
		
	}
	CloseWindow();
	CloseAudioDevice();
}