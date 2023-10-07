#pragma once
#include "F_EmptyObject.h"
class F_DamakuLineTrace : public Feintgine::F_EmptyObject
{
public:
	F_DamakuLineTrace();
	~F_DamakuLineTrace();

	void update(float deltaTime);
	void setLifeTime(float val);
	bool isAlive() const { return alive; }

private : 
	bool alive = true;
	float m_lifeTime = 5;
	float m_lifeTimeRate = 0.125f;
};

