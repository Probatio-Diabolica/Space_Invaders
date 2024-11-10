#include<raylib.h>
#include<string>
#include "GAME.hpp"
#include "Obstacles.hpp"
#include "Enemy.hpp"

std::string FormatWithLeadingZeros(int number,int width)
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


int main()
{
	InitWindow(	(width + offset), (height + offset * 2) , "SPACE INVADER TITLE");
	InitAudioDevice();
	Font font = LoadFontEx("Assets/Fonts/Font.ttf",64,0,0);
	SetTargetFPS(60);
	Texture2D staticPlayer = LoadTexture("Assets/Player/player.png");
	GAME game;
	Obstacle o = Obstacle({ 200,300 });
	HeianAlien alien = HeianAlien(1, { 100,100 });
	while (!WindowShouldClose())
	{
		UpdateMusicStream(game.music);
		game.inputs();
		game.update(); 
		BeginDrawing();
		ClearBackground(background);
		DrawFPS(0,0);
	
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