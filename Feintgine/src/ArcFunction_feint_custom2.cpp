#include "ArcFunction_feint_custom2.h"



ArcFunction_feint_custom2::ArcFunction_feint_custom2()
{
	factorsCount = 4;
	
}


ArcFunction_feint_custom2::~ArcFunction_feint_custom2()
{
}

glm::vec2 ArcFunction_feint_custom2::getValue(float t)
{
	glm::vec2 retVal;
	if (m_factors.size() < factorsCount)
	{
		std::cout << "Warning, incorrect expected factors !!! expect " << factorsCount << " but get " << m_factors.size() << "\n";
		return retVal;
	}
	retVal.x = (((m_factors[0] + m_factors[1]) / m_factors[2]) * cos(t)+ m_factors[3]  + ((m_factors[2] - m_factors[0]) / m_factors[1]) * sin(t) - m_factors[3]) * m_rad;
	retVal.y = (((m_factors[0] / m_factors[1]) - m_factors[2]) * sin(t) * m_factors[3] + ((m_factors[2] * m_factors[0]) - m_factors[1]) * cos(t) + m_factors[3]) * m_rad;
	return retVal;
}
