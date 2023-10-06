#include "ArcFunction_feint_custom1.h"



ArcFunction_feint_custom1::ArcFunction_feint_custom1()
{

	factorsCount = 3;

}


ArcFunction_feint_custom1::~ArcFunction_feint_custom1()
{
}

glm::vec2 ArcFunction_feint_custom1::getValue(float t)
{
	glm::vec2 retVal;
	if (m_factors.size() < factorsCount)
	{
		std::cout << "Warning, incorrect expected factors !!! expect " << factorsCount << " but get " << m_factors.size() << "\n";
		return retVal;
	}
	retVal.x = (((m_factors[0] - m_factors[1]) / m_factors[2]) * cos(t) + ((m_factors[2] - m_factors[0]) / m_factors[1]) * sin(t)) * m_rad;
	retVal.y = (((m_factors[0] - m_factors[1]) / m_factors[2]) * sin(t) + ((m_factors[2] - m_factors[0]) / m_factors[1]) * cos(t)) * m_rad;
	return retVal;
}
