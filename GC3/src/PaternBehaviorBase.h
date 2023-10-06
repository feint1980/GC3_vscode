#pragma once

#include "EnemyBulletBase.h"

class PaternBehaviorBase
{
public:
	PaternBehaviorBase();
	~PaternBehaviorBase();

	virtual void update(float deltaTime) = 0;

	void init(std::vector<EnemyBulletBase *>  bullets);

	bool isActive() const { return m_bullets.size() > 0; }
	
protected:
	std::vector<EnemyBulletBase *>  m_bullets;




};

