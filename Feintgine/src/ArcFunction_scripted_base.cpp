#include "ArcFunction_scripted_base.h"



ArcFunction_scripted_base::ArcFunction_scripted_base()
{

}


ArcFunction_scripted_base::~ArcFunction_scripted_base()
{
}

void ArcFunction_scripted_base::addScript(float radius, float rotationRate, float totalTime)
{
	m_factors.emplace_back(radius, degreeToRad(rotationRate), totalTime);

	//m_desTime = m_factors[currentIndex].totalTime;
	//if (m_ownTime >= m_desTime)
	//{
	//	currentIndex = 0;
	//	currentIndex %= m_factors.size();
	//	
	//}
}

void ArcFunction_scripted_base::update(float deltaTime)
{

	if (m_factors.size() > 0)
	{
		//std::cout << "yes \n";
		if (m_ownTime >  m_factors[currentIndex].totalTime)
		{
			currentIndex++;
			if (currentIndex >= m_factors.size())
			{
				currentIndex = 0;
			}
			//std::cout << currentIndex << " <---index \n";
			m_ownTime = 0;
		
			//m_desTime = m_factors[currentIndex].totalTime;
		}
		m_ownTime += abs(m_factors[currentIndex].rotationRate) * deltaTime;
		//std::cout << m_ownTime << "\n";
		m_pos.x = cos(m_ownTime) * m_factors[currentIndex].radius;
		m_pos.y = sin(m_ownTime) * m_factors[currentIndex].radius;
	}
	else
	{
		//std::cout << "no \n";
	}
	
	

}

void ArcFunction_scripted_base::clearScript()
{
	for (int i = 0; i < m_factors.size(); i++)
	{
		m_factors.erase(m_factors.begin() + i);
	}
	m_factors.clear();
}

void ArcFunction_scripted_base::setTime(float time)
{
	m_ownTime = time;
}
