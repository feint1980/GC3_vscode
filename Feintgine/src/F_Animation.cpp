#include "F_Animation.h"

namespace Feintgine 
{



	F_Animation::F_Animation()
	{
		m_curIndex = 0;
		//m_currentSprite = new f_anim();//m_anims[0];
		//m_currentSpriteGuard = std::shared_ptr<f_anim>(m_currentSprite);
		//m_currentSpriteGuard = m_currentSprite;
		//m_currentSprite = nullptr;

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
		//m_currentSprite = nullptr;
		//std::cout << "the last control was " << m_currentSprite << "\n";
		
// 		for (int i = 0; i < m_anims.size(); i++)
// 		{
// 			m_anims.erase(m_anims.begin() + i);
// 		}
// 		m_anims.clear();
		
		//delete
// 		if (m_currentSprite)
// 		{
// 			delete m_currentSprite;
// 		}
		
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
		if (m_anims.size() > 1)
		{	
			//std::cout << "data " << m_animName << " " << m_anims.size() << "\n";
			/*I don't know why, I don't want to know why, I wonder how I got here is the first place, but it will
			cause problem that animation on 60hz monitor will be slower than 144hz monitor unless I do this horrible thing */
			if (deltaTime > 0.95f)
			{
				deltaTime = 1.0f;
			}
			// End of work around 
			if (m_currentSprite)
			{
				if (m_time > 0)
				{
					if (m_playing)
					{

						m_animTime += (m_animSpeed * deltaTime);
						//std::cout << m_animTime << "\n";
						if (m_animTime >= m_currentSprite->time)
						{
							m_curIndex++;
							m_animTime = 0.0f;
							if (m_curIndex >= m_anims.size())
							{
								m_curIndex = m_loop;
								m_time--;
								if (m_time == 0)
								{
									m_playing = false;
								}
							}

						}
						if (m_curIndex >= 0 && m_curIndex <= m_anims.size())
						{
							m_currentSprite = &m_anims[m_curIndex];
						}
					}
					else if (m_time == 0)
					{
						m_playing = false;
					}
				}
				else if (m_time < 0)
				{
					if (m_playing)
					{
						if (m_currentSprite)
						{
							m_animTime += (m_animSpeed  * deltaTime);
							//std::cout << m_animTime << "\n";
							if (m_animTime >= m_currentSprite->time)
							{
								m_animTime = 0.0f;
								m_curIndex++;
								if (m_curIndex >= m_anims.size())
								{
									m_curIndex = m_loop;
								}
							}
							if (m_curIndex >= 0 && m_curIndex <= m_anims.size())
							{
								m_currentSprite = &m_anims[m_curIndex];
							}
							else
							{
								m_currentSprite = nullptr;
							}
						}
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
		if (index == m_loop)
		{
			m_loop = 0;
		}
	}

	void F_Animation::playAnimation(int time, int index)
	{
		m_time = time;
		m_playing = true;
		//resetAnim();
		m_curIndex = index;
		if (m_curIndex < 0)
		{
			return;
		}
		if (m_anims.size() > 0)
		{
			m_curIndex = 0;
			
			m_currentSprite = &m_anims[m_curIndex];
			//currentSpriteGuard = std::make_shared<f_anim>(*m_currentSprite);
		}
		else
		{
			m_currentSprite = nullptr;
		}
	}

	void F_Animation::setAnimation()
	{
		m_currentSprite = &m_anims[m_curIndex];
	}

	void F_Animation::stop()
	{
		m_playing = false;
	}

	void F_Animation::setCurrentAnimTime(float value)
	{
		if (m_currentSprite)
		{
			m_currentSprite->time = value;
		}
	}

	void F_Animation::setLoopAnim(int val)
	{
		m_loop = val;
	}

	void F_Animation::setAnimIndex(int index)
	{
		if (index >= 0 && index <= m_anims.size())
		{
			m_curIndex = index;
			m_currentSprite = &m_anims[m_curIndex];
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
