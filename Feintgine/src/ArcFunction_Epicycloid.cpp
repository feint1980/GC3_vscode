#include "ArcFunction_Epicycloid.h"



ArcFunction_Epicycloid::ArcFunction_Epicycloid()
{
	factorsCount = 2;
}


ArcFunction_Epicycloid::~ArcFunction_Epicycloid()
{
}

glm::vec2 ArcFunction_Epicycloid::getValue(float t)
{
	glm::vec2 retVal;
	if (m_factors.size() < factorsCount)
	{
		std::cout << "Warning, incorrect expected factors !!! expect " << factorsCount << " but get " << m_factors.size() << "\n";
		return retVal;
	}
	float amplification = 0.1f;
	float ft_t = t * amplification;

	retVal.x = (m_rad * (m_factors[0] + m_factors[1]) * cos(ft_t)) - (m_rad * cos((m_factors[0] + m_factors[1]) * ft_t));
	retVal.y = (m_rad * (m_factors[0] + m_factors[1]) * sin(ft_t)) - (m_rad * sin((m_factors[0] + m_factors[1]) * ft_t));

	return retVal;
}
