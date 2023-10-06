#include "PaternBehavior_Test.h"



PaternBehavior_Test::PaternBehavior_Test()
{

	m_factors.push_back(7);
	m_factors.push_back(4);
	m_factors.push_back(2);
}


PaternBehavior_Test::~PaternBehavior_Test()
{
}

void PaternBehavior_Test::update(float deltaTime)
{
	m_threshold += deltaTime;
	customVal += 0.1f*  deltaTime;

	float calculateAngle = degreeToRad(360.0f / m_bullets.size());
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->setDestination(calculatePos( customVal + (float) i, calculateAngle * i));

	}
	if (m_threshold >= 150.0f)
	{
		m_threshold = 0;
		randomizeValue();
	}


// 	float modifier = (1 / m_bullets.size()) * 10.0f;
// 	for (int i = 0; i < m_bullets.size(); i++)
// 	{
// 		m_bullets[i]->setPos(calculatePos((float)i + deltaTime));
// 
// 	}
}


float PaternBehavior_Test::reArc(float t)
{
	float returnVal;
	float t_limit = 5;
	float minLimit = -2.0;
	return returnVal = -minLimit / pow(t_limit, 2) * pow(t, 2) + 2 * minLimit / t_limit * t;
	
}

void PaternBehavior_Test::randomizeValue()
{
	for (int i = 0; i < m_factors.size(); i++)
	{
		m_factors[i] -= (rand() % 4 - 3) ;
	}
}

glm::vec2 PaternBehavior_Test::calculatePos(float t, float additionalAngle)
{
	glm::vec2 returnVal;

	returnVal.x = ((m_factors[0] - m_factors[1]) * cos(t ) +
		(m_factors[2] * cos((m_factors[0] / m_factors[1] - 1)*t))) *m_rad;

	returnVal.y = ((m_factors[0] - m_factors[1]) * sin(t )
		- (m_factors[2] * sin((m_factors[0] / m_factors[1] - 1)*t))) *m_rad;
	return returnVal;


}
