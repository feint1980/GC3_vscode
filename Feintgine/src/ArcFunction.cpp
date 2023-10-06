#include "ArcFunction.h"



ArcFunction::ArcFunction()
{
}


ArcFunction::~ArcFunction()
{
}

void ArcFunction::init(float rad, std::vector<float> factors)
{
	m_rad = rad; 
	m_factors = factors;
	factorsCount = m_factors.size();
}

