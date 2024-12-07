#include "GAME.hpp"
#include<iostream>
#include<fstream>
#include <random> 
GAME::GAME()
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 

	// Define the range [0, 1] for the random number
	std::uniform_int_distribution<> distr(0, 1);

	// Generate the random number
	int randNum = distr(gen);

	const char* musicName;
	randNum == 0 ? musicName = "Assets/Sounds/musicA.mp3" : musicName = "Assets/Sounds/musicB.mp3";
	music = LoadMusicStream(musicName);
	m_Explosion = LoadSound("Assets/Sounds/EnemyHit.wav");

	PlayMusicStream(music);
	m_InitGame();
}
void GAME::m_InitGame()
{
	enemyBulletList = bulletList(200);
	score = 0;
	highscore = m_LoadHighScoreFromFile();
	m_enemyLastTimeShoot = 0;
	m_AlienDir = 1;
	m_createAliens();
	m_NueTimeLastSpawn = 0.0;
	m_NueSpawnInterval = GetRandomValue(10, 20);
	forward = true;

}

GAME::~GAME()
{
	UnloadMusicStream(music);
	UnloadSound(m_Explosion);
}

void GAME::draw()
{
	double currentTime = GetTime();
	if (currentTime - m_NueTimeLastSpawn > m_NueSpawnInterval)
	{
		m_Nue.Spawn();
		m_NueTimeLastSpawn = GetTime();
		m_NueSpawnInterval = GetRandomValue(10, 20);
	}
	m_Player.Draw();
	m_Player.playerBulletList.render();
	enemyBulletList.render();
	for (auto& alien : m_AliensList) alien.Draw();
	m_Nue.Draw();
}

void GAME::update()
{
	if (forward)
	{
		double currentTime = GetTime();
		if (currentTime - m_NueTimeLastSpawn > m_NueSpawnInterval)
		{
			m_Nue.Spawn();
			m_NueTimeLastSpawn = GetTime();
			m_NueSpawnInterval = GetRandomValue(10, 20);
		}
		m_moveEnemy();
		m_alienShootLazer();

		m_Player.playerBulletList.update();
		enemyBulletList.update();

		m_Nue.Update();
		m_checkForCollisions();
	}
	else if (IsKeyDown(KEY_ENTER)) m_Reset();
	
}

void GAME::inputs()
{	
	if (forward)
	{
		if (IsKeyDown(KEY_LEFT) or IsKeyDown(KEY_KP_4))
		{
			m_Player.MoveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT) or IsKeyDown(KEY_KP_6))
		{
			m_Player.moveRight();
		}
		if (IsKeyDown(KEY_UP) or IsKeyDown(KEY_KP_8))
		{
			m_Player.moveUp();
		}
		else if (IsKeyDown(KEY_DOWN) or IsKeyDown(KEY_KP_2))
		{
			m_Player.MoveDown();
		}
		if (IsKeyDown(KEY_Z))
		{
			m_Player.FireLaser();
		}
	}


}

//to do it later
void GAME::run()
{
	while (forward )
	{
		update();
		inputs();
		//draw();
	}
}


void GAME::m_createAliens()
{
	int cellSize = 55;
	int X_Offset = 75, Y_Offset = 110;
	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			float x = column * cellSize +X_Offset;
			float y = row * cellSize + Y_Offset ;

			if(row==0) m_AliensList.push_back(HeianAlien(DRAGON, { x,y }));

			else if( row==1 || row==2) m_AliensList.push_back(HeianAlien(SHIP, { x,y }));

			else m_AliensList.push_back(HeianAlien(ROCK, { x,y }));
			
		}
	}
}

void GAME::m_moveEnemy()
{
	for (auto& alien : m_AliensList)
	{
		if (alien.Position.x + alien.alienImages[alien.GetType() - 1].width > GetScreenWidth()-25)
		{
			m_AlienDir = -1;
			m_moveDownEnemy(4);
		}
		else if (alien.Position.x < 25)
		{
			m_AlienDir = 1;
			m_moveDownEnemy(4);
		}
		alien.Move(m_AlienDir);
	}
}

void GAME::m_moveDownEnemy(int distance)
{
	for (auto& alien : m_AliensList) alien.Position.y += distance;
	
}

void GAME::m_alienShootLazer()
{
	double currentTime = GetTime();
	if ( (currentTime - m_enemyLastTimeShoot >= m_enemyBTI) && !m_AliensList.empty())
	{
		// picking the aliens from the array ::NOTE:: rocks cannot shoot
		int randomIndex = GetRandomValue(0, m_AliensList.size() - 2);
		HeianAlien& alien = m_AliensList[randomIndex];
		if(m_AliensList.size()>0) enemyBulletList.push(Bullet({ alien.Position.x + alien.alienImages[alien.GetType() - 1].width / 2,alien.Position.y + alien.alienImages[alien.GetType() - 1].height / 2 }, ENEMY_BULLET_SPD));
		m_enemyLastTimeShoot = GetTime();
	}
}

void GAME::m_checkForCollisions()
{

	//player
	for (int i = 0; i < m_Player.getBulletTop(); i++)
	{

		auto it = m_AliensList.begin();
		while (it != m_AliensList.end())
		{
			if (CheckCollisionRecs(it->getRect(), m_Player.playerBulletList[i].getRect()) )
			{
				switch (it->GetType())
				{
				case DRAGON:
					score += 300;
					break;
				case ROCK:
					score += 100;
					break;
				case SHIP:
					score += 200;
					break;
				}
				it = m_AliensList.erase(it);
				m_Player.playerBulletList[i].Die();
				m_CheckforHighScore();
				PlaySound(m_Explosion);
			}
			else ++it;
		}

		if (CheckCollisionRecs(m_Nue.getRect(), m_Player.playerBulletList[i].getRect()))
		{
			m_Nue.Kill();
			m_Player.playerBulletList[i].Die();
			score += 1000;
			m_CheckforHighScore();
			PlaySound(m_Explosion);
		}
	}

	for (int i = 0; i < enemyBulletList.getTop(); i++)
	{
		//collision with player
		if (CheckCollisionRecs(enemyBulletList[i].getRect(), m_Player.getRect()))
		{
			enemyBulletList[i].Die();
			--playerLives;
			if (playerLives == 0) m_GameOver();
		}

	}


}

void GAME::m_GameOver()
{
	forward = false;
}

void GAME::m_Reset()
{
	m_Player.Reset();
	m_AliensList.clear();
	m_enemyBullets.clear();
	m_InitGame();
	playerLives = 3;
}

void GAME::m_CheckforHighScore()
{
	
	if (score > highscore) 
	{ 
		highscore = score;
		m_SaveScore();
	}
}
int GAME::m_LoadHighScoreFromFile()
{
	int hs = 0;
	std::ifstream hsFile("Assets/Scores.txt");
	if (hsFile.is_open())
	{
		hsFile >> hs;
		hsFile.close();
	}
	else std::cerr << "failed to load the file" << std::endl;
	return hs;
}

void GAME::m_SaveScore()
{
	std::ofstream ScoreFile("Assets/Scores.txt");
	if (ScoreFile.is_open())
	{
		ScoreFile << highscore;
		ScoreFile.close();
	}
	else std::cerr << "Failed to save file" << std::endl;
}
