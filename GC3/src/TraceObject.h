#pragma once
#include "EmptyObject.h"
class TraceObject : public EmptyObject
{
public:
	TraceObject();
	~TraceObject();

	void update(float deltaTime);
	void setLifeTime(float val);
	bool isAlive() const { return alive; }

private :


	bool alive = true;
	float m_lifeTime = 5;
	float m_lifeTimeRate = 0.125f;

};

