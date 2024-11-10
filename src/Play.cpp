#include "Play.hpp"
#include<iostream>
#include<fstream>
#include <random> 

Play::Play()
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

Play::~Play()
{
}

void Play::draw()
{
}

void Play::update()
{
}

void Play::inputs()
{
}

void Play::run()
{
}

void Play::m_InitGame()
{

	enemyBulletList = bulletList(200);
	score = 0;
	highscore = m_LoadHighScoreFromFile();
	m_enemyLastTimeShoot = 0;
	m_AlienDir = 1;
	m_createObstacles();
	m_createAliens();
	m_NueTimeLastSpawn = 0.0;
	m_NueSpawnInterval = GetRandomValue(10, 20);
	funtioning = true;
}

void Play::m_deleteInactiveBullets()
{
}

void Play::m_createObstacles()
{
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = float(GetScreenWidth() - (4 * obstacleWidth)) / 5;
	for (int temp = 0; temp < 4; temp++)
	{
		float oX = (temp + 1) * gap + temp * obstacleWidth;
		m_ObstaclesList.push_back(Obstacle({ oX,float(GetScreenHeight() - 200) }));
	}
}

void Play::m_createAliens()
{
	int cellSize = 55;
	int X_Offset = 75, Y_Offset = 110;
	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			float x = column * cellSize + X_Offset;
			float y = row * cellSize + Y_Offset;

			if (row == 0) m_AliensList.push_back(HeianAlien(DRAGON, { x,y }));

			else if (row == 1 || row == 2) m_AliensList.push_back(HeianAlien(SHIP, { x,y }));

			else m_AliensList.push_back(HeianAlien(ROCK, { x,y }));

		}
	}
}

void Play::m_moveEnemy()
{
	for (auto& alien : m_AliensList)
	{
		if (alien.Position.x + alien.alienImages[alien.GetType() - 1].width > GetScreenWidth() - 25)
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

void Play::m_moveDownEnemy(int distance)
{
	for (auto& alien : m_AliensList) alien.Position.y += distance;
}

void Play::m_alienShootLazer()
{
	double currentTime = GetTime();
	if ((currentTime - m_enemyLastTimeShoot >= m_enemyBTI) && !m_AliensList.empty())
	{
		// picking the aliens from the array ::NOTE:: rocks cannot shoot
		int randomIndex = GetRandomValue(0, m_AliensList.size() - 2);
		HeianAlien& alien = m_AliensList[randomIndex];
		if (m_AliensList.size() > 0) enemyBulletList.push(Bullet({ alien.Position.x + alien.alienImages[alien.GetType() - 1].width / 2,alien.Position.y + alien.alienImages[alien.GetType() - 1].height / 2 }, ENEMY_BULLET_SPD));
		m_enemyLastTimeShoot = GetTime();
	}
}

void Play::m_checkForCollisions()
{


		//spaceship lazers
		for (int i = 0; i < m_Player.getBulletTop(); i++)
		{
			//aliens
			auto it = m_AliensList.begin();
			while (it != m_AliensList.end())
			{
				if (CheckCollisionRecs(it->getRect(), m_Player.playerBulletList[i].getRect()))
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
					m_Player.playerBulletList[i].Die();
					m_CheckforHighScore();
				}
				else ++it;
			}

			//for obstacles
			for (auto& obstacle : m_ObstaclesList)
			{
				auto it = obstacle.blocks.begin();
				while (it != obstacle.blocks.end())
				{
					if (CheckCollisionRecs(it->getRect(), m_Player.playerBulletList[i].getRect()))
					{
						it = obstacle.blocks.erase(it);
						m_Player.playerBulletList[i].Die();
					}
					else ++it;
				}
			}
			//For nue
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
			// collision with obstacles
			for (auto& obstacle : m_ObstaclesList)
			{
				auto it = obstacle.blocks.begin();
				while (it != obstacle.blocks.end())
				{
					if (CheckCollisionRecs(it->getRect(), enemyBulletList[i].getRect()))
					{
						it = obstacle.blocks.erase(it);
						enemyBulletList[i].Die();
					}
					else ++it;
				}
			}

		}


		////enemy  bullets
		//for (auto& bullet : m_enemyBullets)
		//{
		//	if (CheckCollisionRecs(bullet.getRect(), m_Player.getRect()))
		//	{
		//		bullet.Die();
		//		--playerLives;
		//		if (playerLives == 0) m_GameOver();
		//	}
		//	for (auto& obstacle : m_ObstaclesList)
		//	{
		//		auto it = obstacle.blocks.begin();
		//		while (it != obstacle.blocks.end())
		//		{
		//			if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
		//			{
		//				it = obstacle.blocks.erase(it);
		//				bullet.Die();
		//			}
		//			else ++it;
		//		}
		//	}
		//}
		//Enemy colliding with obstacle
		for (auto& enemy : m_AliensList)
		{
			for (auto& shield : m_ObstaclesList)
			{
				auto it = shield.blocks.begin();
				while (it != shield.blocks.end())
				{
					if (CheckCollisionRecs(it->getRect(), enemy.getRect())) it = shield.blocks.erase(it);
					else ++it;
				}
			}
			if (CheckCollisionRecs(enemy.getRect(), m_Player.getRect())) m_GameOver();

		}
	

}

void Play::m_GameOver()
{
	funtioning = false;
}

void Play::m_Reset()
{
	m_Player.Reset();
	m_AliensList.clear();
	m_enemyBullets.clear();
	m_ObstaclesList.clear();
	m_InitGame();
}

void Play::m_CheckforHighScore()
{
	if (score > highscore)
	{
		highscore = score;
		m_SaveScore();
	}
}

int Play::m_LoadHighScoreFromFile()
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

void Play::m_SaveScore()
{
	std::ofstream ScoreFile("Assets/Scores.txt");
	if (ScoreFile.is_open())
	{
		ScoreFile << highscore;
		ScoreFile.close();
	}
	else std::cerr << "Failed to save file" << std::endl;
}
