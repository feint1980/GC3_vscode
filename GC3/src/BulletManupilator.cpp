#include "BulletManupilator.h"



BulletManupilator::BulletManupilator()
{
}


BulletManupilator::~BulletManupilator()
{
}

void BulletManupilator::update(float deltaTime)
{
	for (int i = 0; i < m_pattern.size(); i++)
	{
		m_pattern[i]->update(deltaTime);
	}
}

void BulletManupilator::addPatern(int ID, int type)
{
	switch (type)
	{
	case 0 :
	{
		PaternBehaviorBase * patern = new PaternBehavior_Test();

		std::vector<EnemyBulletBase * > bullets;
		for (int i = 0; i < m_bullets->size(); i++)
		{
			if (m_bullets->operator[](i)->getSpecialID() == ID)
			{
				bullets.push_back(m_bullets->operator[](i));

				//std::cout << "got " << i << "\n";
			}

		}
		patern->init(bullets);
		m_pattern.push_back(patern);
	}
		break;
	default:
		break;
	}
}

void BulletManupilator::init(std::vector<EnemyBulletBase *> *bullets)
{
	m_bullets = bullets;
}
