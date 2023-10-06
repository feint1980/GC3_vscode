#include "ArcFunction_hypotrochoid.h"



ArcFunction_hypotrochoid::ArcFunction_hypotrochoid()
{
	factorsCount = 3;
}


ArcFunction_hypotrochoid::~ArcFunction_hypotrochoid()
{
}


glm::vec2 ArcFunction_hypotrochoid::getValue(float t)
{
	glm::vec2 returnVal;
	if (m_factors.size() < factorsCount)
	{
		std::cout << "Warning, incorrect expected factors \n";
		return returnVal;
	}
	returnVal.x = ((m_factors[0] - m_factors[1]) * cos(t) +
		(m_factors[2] * cos((m_factors[0] / m_factors[1] - 1)*t))) *m_rad;

	returnVal.y = ((m_factors[0] - m_factors[1]) * sin(t)
		- (m_factors[2] * sin((m_factors[0] / m_factors[1] - 1)*t))) *m_rad;
	return returnVal;
}
