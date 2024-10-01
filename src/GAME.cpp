#include "GAME.h"
#include<fstream>
#include <iostream>
GAME::GAME()
{
	music = LoadMusicStream("Assets/Sounds/musicB.mp3");
	m_Explosion = LoadSound("Assets/Sounds/EnemyHit.wav");

	PlayMusicStream(music);
	m_InitGame();
}
void GAME::m_InitGame()
{
	score = 0;
	highscore = m_LoadHighScoreFromFile();
	m_enemyLastTimeShoot = 0;
	m_AlienDir = 1;
	m_createObstacles();
	m_createAliens();
	m_NueTimeLastSpawn = 0.0;
	m_NueSpawnInterval = GetRandomValue(10, 20);
	running = true;

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
	for (auto& bullet : m_Player.BulletList)
	{
		bullet.Draw();
	}
	for (auto& obstacle : m_ObstaclesList)
	{
		obstacle.Draw();
	}
	for (auto& alien : m_AliensList)
	{
		alien.Draw();
	}
	for (auto& bullet : m_enemyBullets)
	{
		bullet.Draw();
	}
	m_Nue.Draw();
}

void GAME::update()
{
	if (running == true)
	{
		double currentTime = GetTime();
		if (currentTime - m_NueTimeLastSpawn > m_NueSpawnInterval)
		{
			m_Nue.Spawn();
			m_NueTimeLastSpawn = GetTime();
			m_NueSpawnInterval = GetRandomValue(10, 20);
		}
		for (auto& bullet : m_Player.BulletList)
		{
			bullet.Update();
		}
		m_moveEnemy();
		m_alienShootLazer();
		for (auto& bullet : m_enemyBullets)
		{
			bullet.Update();
		}
		m_deleteInactiveBullets();
		m_Nue.Update();
		m_checkForCollisions();
	}
	else
	{
		if(IsKeyDown(KEY_ENTER)) m_Reset();
	}
	
}

void GAME::inputs()
{	
	if (running)
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



void GAME::m_deleteInactiveBullets()
{
	for (auto it = m_Player.BulletList.begin(); it != m_Player.BulletList.end();)
	{
		if (!it->IsActive())
		{
			it = m_Player.BulletList.erase(it);
		}
		else
		{
			++it;
		}
	}
	for (auto it = m_enemyBullets.begin(); it != m_enemyBullets.end();)
	{
		if (!it->IsActive())
		{
			it = m_enemyBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GAME::m_createObstacles()
{ 
	int obstacleWidth = Obstacle::grid[0].size()  * 3 ;
	float gap = float(GetScreenWidth() - (4 * obstacleWidth)) / 5;
	for (int temp = 0; temp < 4; temp++)
	{
		float oX = (temp + 1) * gap + temp * obstacleWidth;
		m_ObstaclesList.push_back(Obstacle({ oX,float(GetScreenHeight() - 200) }));
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
		m_enemyBullets.push_back(Bullet({ alien.Position.x + alien.alienImages[alien.GetType() - 1].width / 2,alien.Position.y + alien.alienImages[alien.GetType() - 1].height / 2 }, ENEMY_BULLET_SPD)); //Exception here
		m_enemyLastTimeShoot = GetTime();
	}
}

void GAME::m_checkForCollisions()
{
	//spaceship lazers
	for (auto& bullet : m_Player.BulletList)
	{
		auto it = m_AliensList.begin();
		while (it != m_AliensList.end())
		{
			if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
			{
				PlaySound(m_Explosion);
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
				bullet.Die();
				m_CheckforHighScore();
			}
			else
			{
				++it;
			}
		}

		//for obstacles

		for (auto& obstacle : m_ObstaclesList)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
				{
					it = obstacle.blocks.erase(it);
					bullet.Die();
				}
				else
				{
					++it;
				}
			}
		}
		if (CheckCollisionRecs(m_Nue.getRect(), bullet.getRect()))
		{
			m_Nue.Kill();
			bullet.Die();
			score += 1000;
			m_CheckforHighScore();
			PlaySound(m_Explosion);
		}
	}
	//enemy  bullets
	for (auto& bullet : m_enemyBullets)
	{
		if (CheckCollisionRecs(bullet.getRect(), m_Player.getRect()))
		{
			bullet.Die();
			playerLives--;
			if (playerLives == 0) m_GameOver();
		}
		for (auto& obstacle : m_ObstaclesList)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
				{
					it = obstacle.blocks.erase(it);
					bullet.Die();
				}
				else
				{
					++it;
				}
			}
		}
	}
	//Enemy colliding with obstacle
	for (auto& enemy : m_AliensList)
	{
		for (auto& shield : m_ObstaclesList)
		{
			auto it = shield.blocks.begin();
			while (it != shield.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), enemy.getRect()))
				{
					it = shield.blocks.erase(it);
				}
				else
				{
					it++;
				}
				
			}
		}
		if (CheckCollisionRecs(enemy.getRect(), m_Player.getRect()))
		{
			m_GameOver();
		}
	}
}

void GAME::m_GameOver()
{
	running = false;
}

void GAME::m_Reset()
{
	m_Player.Reset();
	m_AliensList.clear();
	m_enemyBullets.clear();
	m_ObstaclesList.clear();
	m_InitGame();
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
	else
	{
		std::cerr << "failed to load the file"<<std::endl;
	}
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
	else
	{
		std::cerr << "Failed to save file" << std::endl;
	}
}
