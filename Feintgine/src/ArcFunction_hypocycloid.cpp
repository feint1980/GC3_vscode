#include "ArcFunction_hypocycloid.h"



ArcFunction_hypocycloid::ArcFunction_hypocycloid()
{
	factorsCount = 2;
}


ArcFunction_hypocycloid::~ArcFunction_hypocycloid()
{
}

glm::vec2 ArcFunction_hypocycloid::getValue(float t)
{
	glm::vec2 returnVal;
	if (m_factors.size() < factorsCount)
	{
		std::cout << "Warning, incorrect expected factors \n";
		return returnVal;
	}
	returnVal.x = ((m_factors[0] - m_factors[1]) * cos(t) + \
		(m_factors[1] * cos(((m_factors[0] - m_factors[1]) / m_factors[1] ) *t))) * m_rad;

	returnVal.y = ((m_factors[0] - m_factors[1]) * sin(t) + \
		(m_factors[1] * sin(((m_factors[0] - m_factors[1]) / m_factors[1] ) *t))) * m_rad;

	return returnVal;
}
