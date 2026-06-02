#include "F_Animation.h"

namespace Feintgine 
{



	F_Animation::F_Animation()
	{
		m_curIndex = 0;
	}

	void F_Animation::setInverseAnimation()
	{
		for(int i = 0; i < m_anims.size(); i++)
		{
			m_anims[i].sprite.setInvert( ! m_anims[i].sprite.isInverted() );
			m_anims[i].offset.x = -m_anims[i].offset.x;
		}
	}
	F_Animation::~F_Animation()
	{
		m_curIndex = 0;
		m_playing = false;
		m_animTime = 0;
		m_loopSet = false;
		m_animName = "";
		
	}

	void F_Animation::addAnim(const f_anim & tsprite, bool isLoop)
	{
		m_anims.push_back(tsprite);
		if (!m_loopSet)
		{
			if (isLoop)
			{
				m_loop = m_anims.size() - 1;
				m_loopSet = true;
			}
		}
	}

	void F_Animation::setAnimationSpeed(float speed)
	{
		m_animSpeed = speed;
	}

	void F_Animation::updateAnim(float deltaTime)
	{
			
		if (m_anims.size() <= 1 || !m_playing)
		{
			return;
		} 
		if (m_curIndex < 0 || m_curIndex >= (int)m_anims.size())
		{
			return;
		} 

		if (deltaTime > 0.95f && deltaTime < 1.0f)
		{
			deltaTime = 1.0f;
			/*I don't know why, I don't want to know why, I wonder how I got here is the first place. This will
			cause problem that animation on 60hz monitor will be slower than 144hz monitor unless I do this horrible thing */
		}  
		m_animTime += m_animSpeed * deltaTime;
		if (m_animTime >= m_anims[m_curIndex].time)
		{
			m_animTime = 0.0f;
			m_curIndex++;
			if (m_curIndex >= (int)m_anims.size())
			{
				m_curIndex = m_loop;
				if (m_time > 0)
				{
					m_time--;
					if (m_time == 0)
					{
						m_playing = false;
					}
				}
			}
		}
	}

	void F_Animation::assignSpriteToCurrentAnim(const F_Sprite &sprite)
	{
		m_anims[m_curIndex].sprite = sprite;
	}

	void F_Animation::insertAnim()
	{
		f_anim aNew;
		m_anims.insert(m_anims.begin() + m_curIndex + 1, aNew);
		m_curIndex++;
	}

	void F_Animation::removeAnimAt(int index)
	{
		m_anims.erase(m_anims.begin() + index);
		if(m_curIndex == index)
		{
			m_curIndex--;
		}
		if (m_curIndex < 0)
		{
			m_curIndex = 0;
		}
		if (index == m_loop)
		{
			m_loop = 0;
		}
	}

	void F_Animation::playAnimation(int time, int index)
	{
		
		if (index < 0)
		{
			return;
		}
		m_curIndex = index;
		m_time = time;
		m_playing = true;
		
		if (m_anims.size() > 0)
		{
			m_curIndex = 0;			
		}
	}

	void F_Animation::setAnimation()
	{
		if(m_anims.size() > 0 && m_curIndex >= 0 && m_curIndex <= m_anims.size())
		{
			if (m_curIndex < 0 || m_curIndex >= (int)m_anims.size())
			{
				m_curIndex = 0;
			}
		}
	}

	void F_Animation::stop()
	{
		m_playing = false;
	}

	void F_Animation::setCurrentAnimTime(float value)
	{
		if (m_curIndex >= 0 && m_curIndex < (int)m_anims.size())
		{
			m_anims[m_curIndex].time = value;
		}
	}

	void F_Animation::setLoopAnim(int val)
	{
		m_loop = val;
	}

	void F_Animation::setAnimIndex(int index)
	{
		if (index >= 0 && index < (int)m_anims.size())
		{
			m_curIndex = index;
		}
	}

	void F_Animation::resetAnim()
	{
		m_curIndex = 0;
		m_playing = false;
		m_animTime = 0;
		m_loopSet = false;
	}

	void Feintgine::F_Animation::create(const std::string & animationName)
	{
		m_animName = animationName;
	}
}
