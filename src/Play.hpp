#pragma once
#include "Utils/BulletList.hpp"
#include "Utils/Bullet.hpp"
#include "Spaceship.hpp"
#include "Obstacles.hpp"
#include "Enemy.hpp"
#include "BonusEnemy.hpp"
#define ENEMY_BULLET_SPD -6
#define DRAGON 1
#define ROCK   2
#define SHIP 3 
class Play
{

public:
	Play();
	~Play();
	void draw();
	void update();
	void inputs();
public:
	//test cases i need to implenent run for better
	void run();

private:
	void m_InitGame();
	void m_deleteInactiveBullets();
	void m_createObstacles();
	void m_createAliens();
	void m_moveEnemy();
	void m_moveDownEnemy(int distance);
	void m_alienShootLazer();
	void m_checkForCollisions();
	void m_GameOver();
	void m_Reset();
	void m_CheckforHighScore();
	int m_LoadHighScoreFromFile();
	void m_SaveScore();

public:
	Music music;
	int playerLives = 3;
	int score;
	int highscore;
	bool funtioning;

private:
	Player m_Player;
	std::vector<Obstacle> m_ObstaclesList;
	std::vector<HeianAlien> m_AliensList;
	std::vector<Bullet> m_enemyBullets;
	bulletList enemyBulletList;
	int m_AlienDir;
	constexpr static float m_enemyBTI = 0.35;
	float m_enemyLastTimeShoot;
	SpecialEnemy m_Nue;
	float m_NueSpawnInterval;
	float m_NueTimeLastSpawn;
	Sound m_Explosion;
};