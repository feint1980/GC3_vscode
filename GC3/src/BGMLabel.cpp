#include "BGMLabel.h"



BGMLabel::BGMLabel()
{
	lifeTime = 4.0f;
	m_scale = 0.8f;
}


BGMLabel::~BGMLabel()
{
}

void BGMLabel::update(float deltaTime)
{
	if (lifeTime > 0)
	{
		lifeTime -= liveTime * deltaTime;
		m_pos += m_vel * deltaTime;
	}
	if (lifeTime < 2.0f)
	{
		m_vel.x = 9 ;
	}
	else
	{
		if (m_pos.x  < 0)
		{
			m_vel.x = 12 ;
		}
		else if (m_pos.x > 0)
		{
			m_vel.x = 0.05f ;
		}
	}
	

	
}
