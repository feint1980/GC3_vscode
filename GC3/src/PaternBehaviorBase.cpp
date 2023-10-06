#include "PaternBehaviorBase.h"






PaternBehaviorBase::PaternBehaviorBase()
{
}


PaternBehaviorBase::~PaternBehaviorBase()
{
}

void PaternBehaviorBase::init(std::vector<EnemyBulletBase *> bullets)
{
	m_bullets = bullets;
}
