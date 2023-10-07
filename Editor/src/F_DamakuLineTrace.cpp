#include "F_DamakuLineTrace.h"



F_DamakuLineTrace::F_DamakuLineTrace()
{
}


F_DamakuLineTrace::~F_DamakuLineTrace()
{
}

void F_DamakuLineTrace::update(float deltaTime)
{
	m_lifeTime -= m_lifeTimeRate * deltaTime;
	if (m_lifeTime < 0)
	{
		alive = false;
	}
}

void F_DamakuLineTrace::setLifeTime(float val)
{
	m_lifeTime = val;
}

