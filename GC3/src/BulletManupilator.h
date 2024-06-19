#pragma once

#include "PaternBehaviorBase.h"
#include "PaternBehavior_Test.h"



enum PaternType
{
	PaternType_Test = 1
};

class BulletManupilator
{
public:
	BulletManupilator();
	~BulletManupilator();


	void update(float deltaTime);

	void addPatern(int ID, int type);

	void init(std::vector<EnemyBulletBase *> *bullets);

private : 
	std::vector<PaternBehaviorBase * > m_pattern;
	std::vector<EnemyBulletBase *> *m_bullets;

};

