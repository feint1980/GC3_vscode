#pragma once
#include "PaternBehaviorBase.h"
class PaternBehavior_Test : public PaternBehaviorBase
{
public:
	PaternBehavior_Test();
	~PaternBehavior_Test();
	virtual void update(float deltaTime)override;

	float reArc(float t);

	void randomizeValue();


private:

	glm::vec2 calculatePos(float t,float additionalAngle);

	float customVal;

	std::vector<float>m_factors;

	float m_rad = 40;

	float m_threshold;
};

