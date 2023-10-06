#ifndef _F_ANIMATEDOBJECT_H_
#define _F_ANIMATEDOBJECT_H_


#include "F_Sprite.h"
#include <rapidxml.hpp>
#include <fstream>
#include "Error.h"
#include <map>
#include "F_Animation.h"
#include "SpriteManager.h"
#include <memory.h>
using namespace rapidxml;

namespace Feintgine
{

// 	struct f_anim
// 	{
// 		F_Sprite sprite;
// 		float time;
// 		glm::vec2 offset;
// 	};
// 
// 	struct f_animation
// 	{
// 	public:
// 		f_animation()
// 		{
// 			m_curIndex = 0;
// 			m_currentSprite = nullptr; //= new f_anim();//m_anims[0];
// 		}
// 		~f_animation()
// 		{
// 			//m_currentSprite = nullptr;
// 			m_curIndex = 0;
// 			m_playing = false;
// 			m_animTime = 0;
// 			m_loopSet = false;
// 			m_animName = "";
// 			
// 			//delete
// 			m_currentSprite = nullptr;
// 		}
// 
// 		void create(const std::string & animationName)
// 		{
// 			m_animName = animationName;
// 
// 			//std::cout << "adding animation " << m_animName << "\n";
// 		}
// 		
// 		void addAnim(const f_anim & tsprite, bool isLoop )
// 		{
// 			m_anims.push_back(tsprite);
// 			if (!m_loopSet)
// 			{
// 				if (isLoop)
// 				{
// 
// 					m_loop = m_anims.size() - 1;
// 					m_loopSet = true;
// 				}
// 			}
// 		}
// 		void updateAnim(float deltaTime)
// 		{
// 			if (m_anims.size() > 1)
// 			{
// 				//std::cout << "data " << m_animName << " " << m_anims.size() << "\n";
// 				/*I don't know why, I don't want to know why, I wonder how I got here is the first place, but it will
// 				cause problem that animation on 60hz monitor will be slower than 144hz monitor unless I do this horrible thing */
// 				if (deltaTime > 0.95f)
// 				{
// 					deltaTime = 1.0f;
// 				}
// 				// End of work around 
// 				if (m_currentSprite)
// 				{
// 					if (m_time > 0)
// 					{
// 						if (m_playing)
// 						{
// 
// 							m_animTime += (m_animSpeed * deltaTime);
// 							//std::cout << m_animTime << "\n";
// 							if (m_animTime >= m_currentSprite->time)
// 							{
// 								m_curIndex++;
// 								m_animTime = 0.0f;
// 								if (m_curIndex >= m_anims.size())
// 								{
// 									m_curIndex = m_loop;
// 									m_time--;
// 									if (m_time == 0)
// 									{
// 										m_playing = false;
// 									}
// 								}
// 
// 							}
// 							if (m_curIndex >= 0 && m_curIndex <= m_anims.size())
// 							{								
// 								m_currentSprite = &m_anims[m_curIndex];
// 							}
// 						}
// 					}
// 					else if (m_time < 0)
// 					{
// 						if (m_playing)
// 						{
// 							if (m_currentSprite->sprite.getTexture().id > 0)
// 							{
// 								m_animTime += (m_animSpeed  * deltaTime);
// 								//std::cout << m_animTime << "\n";
// 								if (m_animTime >= m_currentSprite->time)
// 								{
// 									m_animTime = 0.0f;
// 									m_curIndex++;
// 									if (m_curIndex >= m_anims.size())
// 									{
// 										m_curIndex = m_loop;
// 									}
// 								}
// 								if (m_curIndex >= 0 && m_curIndex <= m_anims.size())
// 								{
// 									m_currentSprite = &m_anims[m_curIndex];
// 								}
// 							}
// 						}
// 
// 					}
// 				}
// 				
// 			}
// 
// 		}
// 		void assignSpriteToCurrentAnim(const F_Sprite &sprite)
// 		{
// 			m_anims[m_curIndex].sprite = sprite;		
// 		}
// 
// 		void insertAnim()
// 		{
// 			f_anim aNew;
// 			m_anims.insert(m_anims.begin() + m_curIndex +1, aNew);
// 			m_curIndex++;
// 		}
// 
// 		void removeAnimAt(int index)
// 		{
// 
// 			m_anims.erase(m_anims.begin() + index);
// 			if (index == m_loop)
// 			{
// 				m_loop = 0;
// 			}
// 		}
// 
// 
// 		void playAnimation(int time )
// 		{
// 			
// 			m_time = time;
// 			m_playing = true;
// 			//resetAnim();
// 			if (m_curIndex < 0)
// 			{
// 				return;
// 			}
// 			if (m_anims.size() > 0)
// 			{
// 				m_curIndex = 0;
// 				m_currentSprite = &m_anims[m_curIndex];
// 			}
// 			else
// 			{
// 				m_currentSprite = nullptr;
// 			}
// 
// 		}
// 
// 		void setAnimation()
// 		{
// 			m_currentSprite = &m_anims[m_curIndex];
// 		}
// 
// 		void stop()
// 		{
// 			m_playing = false;
// 		}
// 
// 		bool isPlaying() const { return m_playing; }
// 
// 		
// 		std::vector<f_anim> getAnims() { return m_anims; }
// 		std::string getAnimName() const { return m_animName; }
// 
// 		f_anim * getCurrentAnim() const {
// 			return m_currentSprite;
// 		}
// 
// 		void setCurrentAnimTime(float value)
// 		{
// 			if (m_currentSprite)
// 			{
// 				m_currentSprite->time = value;
// 			}
// 		}
// 
// 		int getLoopAnim() const { return m_loop; }
// 
// 		void setLoopAnim(int val)
// 		{
// 			m_loop = val;
// 		}
// 
// 		int getCurrentIndex() const { return m_curIndex; }
// 
// 		size_t getSize() const { return m_anims.size(); }
// 		
// 		void setAnimIndex(int index)
// 		{
// 			if (index >= 0 && index <= m_anims.size())
// 			{
// 				m_curIndex = index;
// 				m_currentSprite = &m_anims[m_curIndex];
// 			}
// 
// 		}
// 
// 		void resetAnim() {
// 		//m_currentSprite;// = nullptr;
// 		m_curIndex = 0;
// 		m_playing = false;
// 		m_animTime = 0;
// 		m_loopSet = false;
// 		}
// 		
// 	private :
// 
// 		std::vector<f_anim> m_anims;
// 		f_anim * m_currentSprite;// = nullptr;
// 		std::string m_animName;
// 		int loopIndex = 0;
// 
// 		bool m_loopSet = false;
// 
// 		int m_curIndex = 0;
// 		float m_animTime = 0.0f;
// 		float m_animSpeed = 1.0f;
// 
// 		int m_time = -1;
// 
// 		int m_loop = 0;
// 
// 		bool m_playing = false;
// 	};

	class F_AnimatedObject
	{
	public:
		F_AnimatedObject();
		~F_AnimatedObject();

		void init(const std::string & filePath, const glm::vec2 & scaleFactor = glm::vec2(1));

		void saveToFile(const std::string & name);
		
		void addNewAnimation(const std::string & name);

		void removeAnimation(const std::string & name);

		void playAnimation(const std::string & name,int time = -1);

		void setAnimation(const std::string & name);

		void draw(Feintgine::SpriteBatch & spriteBatch);

		void update(float deltaTime);

		void setDepth(float depth);

		void setAngle(float angle);

		void rotate(float angle);

		float getAngle() const { return m_angle; }

		void setAlpha(float alpha);

		std::string getName() const { return m_name; }

		bool isPlaying() const { 
			
			if(m_currentAnimation)
			return m_currentAnimation->isPlaying(); }

		void setScale(const glm::vec2 & scale);

		glm::vec2 getScale() const { return m_scale; }

		void setPos(const glm::vec2 & pos);

		glm::vec2 getDim() const { 
			return (m_scale * m_currentAnimation->getCurrentAnim()->sprite.getDim());
		}

		glm::vec2 getPos() const { return m_pos; }

		bool isInited() const { return m_isInited; }

		F_Animation * getCurrentAnimation() const { return m_currentAnimation; }

		std::map<std::string, F_Animation> getMap() const { return m_animations; }

		void setVisisble(bool val);

		bool isVisible() const { return m_isVisible; }

		void setColor(const Feintgine::Color & color);

		Feintgine::Color getColor() const { return m_color; }

		bool changeColor(int channel, float rate, float maxVal);

	private:

		std::string m_filePath;
		std::string m_name;
		glm::vec2 m_pos;
		glm::vec2 m_scale = glm::vec2(1);

		bool m_isInited = false;
		bool m_isVisible = false;

		float m_depth = 4;
		float m_angle = 0.0;
		Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);
		std::map<std::string, F_Animation> m_animations ;
		F_Animation * m_currentAnimation = nullptr;
		std::shared_ptr<F_Animation> m_currentAnimationGuard;

		std::vector<F_Animation> m_testAnims;
	};

}

#endif