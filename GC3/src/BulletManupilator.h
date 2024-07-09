#pragma once

#include "PaternBehaviorBase.h"
#include "PaternBehavior_Test.h"
#include "PaternBehavior_from_lua.h"



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

	void addPatern(PaternBehaviorBase * pattern, int ID);

	void init(std::vector<EnemyBulletBase *> *bullets);

private : 
	std::vector<PaternBehaviorBase * > m_pattern;
	std::vector<EnemyBulletBase *> *m_bullets;

};

