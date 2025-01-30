//void GAME::m_checkForCollisions()
//{
//
//	//maybe I'll move it to another place
//	// let's do it this way
//	//FOr now it is as it is
//	//but I will move the collision part to the entities's respective files
//	/*m_Player.tes__bullet[i].getRect()
//	for (int i = 0; i < m_Player.tes__bullet.top; i++)
//	{
//		auto it = m_AliensList.begin();
//		if(CheckCollisionRecs(it->getRect(), m_Player.tes__bullet[i].getRect());
//	}*/
//	//spaceship lazers
//	for (int i = 0; i < m_Player.getBulletTop(); i++)
//	{
//		//aliens
//		auto it = m_AliensList.begin();
//		while (it != m_AliensList.end())
//		{
//			if (CheckCollisionRecs(it->getRect(), m_Player.tes__bullet[i].getRect()))
//			{
//				PlaySound(m_Explosion);
//				switch (it->GetType())
//				{
//				case DRAGON:
//					score += 300;
//					break;
//				case ROCK:
//					score += 100;
//					break;
//				case SHIP:
//					score += 200;
//					break;
//				}
//				it = m_AliensList.erase(it);
//				m_Player.tes__bullet[i].Die();
//				m_CheckforHighScore();
//			}
//			else ++it;
//		}
//
//		//for obstacles
//		for (auto& obstacle : m_ObstaclesList)
//		{
//			auto it = obstacle.blocks.begin();
//			while (it != obstacle.blocks.end())
//			{
//				if (CheckCollisionRecs(it->getRect(), m_Player.tes__bullet[i].getRect()))
//				{
//					it = obstacle.blocks.erase(it);
//					m_Player.tes__bullet[i].Die();
//				}
//				else ++it;
//			}
//		}
//		//For nue
//		if (CheckCollisionRecs(m_Nue.getRect(), m_Player.tes__bullet[i].getRect()))
//		{
//			m_Nue.Kill();
//			m_Player.tes__bullet[i].Die();
//			score += 1000;
//			m_CheckforHighScore();
//			PlaySound(m_Explosion);
//		}
//	}
//
//	//for (auto& bullet : m_Player.BulletList)
//	//{
//	//	auto it = m_AliensList.begin();
//	//	/*while (it != m_AliensList.end())
//	//	{
//	//		if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
//	//		{
//	//			PlaySound(m_Explosion);
//	//			switch (it->GetType())
//	//			{
//	//			case DRAGON:
//	//				score += 300;
//	//				break;
//	//			case ROCK:
//	//				score += 100;
//	//				break;
//	//			case SHIP:
//	//				score += 200;
//	//				break;
//	//			}
//	//			it = m_AliensList.erase(it);
//	//			bullet.Die();
//	//			m_CheckforHighScore();
//	//		}
//	//		else ++it;
//	//	}*/
//
//	////	//for obstacles
//
//	//	for (auto& obstacle : m_ObstaclesList)
//	//	{
//	//		auto it = obstacle.blocks.begin();
//	//		while (it != obstacle.blocks.end())
//	//		{
//	//			if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
//	//			{
//	//				it = obstacle.blocks.erase(it);
//	//				bullet.Die();
//	//			}
//	//			else ++it;
//	//		}
//	//	}
//	//	if (CheckCollisionRecs(m_Nue.getRect(), bullet.getRect()))
//	//	{
//	//		m_Nue.Kill();
//	//		bullet.Die();
//	//		score += 1000;
//	//		m_CheckforHighScore();
//	//		PlaySound(m_Explosion);
//	//	}
//	//}
//
//
//
//	//enemy  bullets
//	for (auto& bullet : m_enemyBullets)
//	{
//		if (CheckCollisionRecs(bullet.getRect(), m_Player.getRect()))
//		{
//			bullet.Die();
//			--playerLives;
//			if (playerLives == 0) m_GameOver();
//		}
//		for (auto& obstacle : m_ObstaclesList)
//		{
//			auto it = obstacle.blocks.begin();
//			while (it != obstacle.blocks.end())
//			{
//				if (CheckCollisionRecs(it->getRect(), bullet.getRect()))
//				{
//					it = obstacle.blocks.erase(it);
//					bullet.Die();
//				}
//				else ++it;
//			}
//		}
//	}
//	//Enemy colliding with obstacle
//	for (auto& enemy : m_AliensList)
//	{
//		for (auto& shield : m_ObstaclesList)
//		{
//			auto it = shield.blocks.begin();
//			while (it != shield.blocks.end())
//			{
//				if (CheckCollisionRecs(it->getRect(), enemy.getRect())) it = shield.blocks.erase(it);
//				else ++it;
//			}
//		}
//		if (CheckCollisionRecs(enemy.getRect(), m_Player.getRect())) m_GameOver();
//
//	}
//}
