#include "TraceObject.h"



TraceObject::TraceObject()
{
}


TraceObject::~TraceObject()
{
}

void TraceObject::update(float deltaTime)
{
	m_lifeTime -= m_lifeTimeRate * deltaTime;
	if (m_lifeTime < 0)
	{
		alive = false;
	}
}

void TraceObject::setLifeTime(float val)
{
	m_lifeTime = val;
}
