#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include "feint_common.h"
struct arcFactor {

	arcFactor(float r, float ro, float t)
	{
		radius = r;
		rotationRate = ro;
		totalTime = t;
	}

	float radius;
	float rotationRate;
	float totalTime;
};

class ArcFunction_scripted_base
{
public:
	ArcFunction_scripted_base();
	~ArcFunction_scripted_base();

	void addScript(float radius, float rotationRate, float totalTime);

	void update(float deltaTime);

	void clearScript();

	glm::vec2 getData() const { return m_pos; }

	void setTime(float time);
protected:

	std::vector<arcFactor> m_factors;

	float m_ownTime = 0.0f;

	float updateSpeed = 1.0f;
	int currentIndex = 0;
	float m_desTime = 0.0f;


	glm::vec2 m_pos;
};

