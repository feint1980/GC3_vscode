#ifndef _F_ANIMATEDOBJECT_H_
#define _F_ANIMATEDOBJECT_H_


#include "F_Sprite.h"
#include <rapidxml.hpp>
#include <fstream>
#include "Error.h"
#include <map>
#include <string>
#include <iostream>
#include "F_Animation.h"
#include "SpriteManager.h"
#include <memory.h>
using namespace rapidxml;

namespace Feintgine
{

	class F_AnimatedObject
	{
	public:
		F_AnimatedObject();
		~F_AnimatedObject();
		F_AnimatedObject(const F_AnimatedObject& other): m_animations(other.m_animations),
		m_pos(other.m_pos), m_scale(other.m_scale), /* etc */
		m_currentAnimation(nullptr)
		{
			if (other.m_currentAnimation) 
			{
				auto it = m_animations.find(other.m_currentAnimation->getAnimName());
				if (it != m_animations.end())
				{
					m_currentAnimation = &it->second;
				}
			}
		}

		void init(const std::string & filePath, const glm::vec2 & scaleFactor = glm::vec2(1),bool loadOnce = true);

		void saveToFile(const std::string & name);
		
		void addNewAnimation(const std::string & name);

		void removeAnimation(const std::string & name);

		void playAnimation(const std::string & name,int time = -1);

		void setAnimation(const std::string & name);

		void draw(Feintgine::SpriteBatch & spriteBatch);

		void update(float deltaTime);

		void setDepth(float depth);

		void setAngle(float angle);

		void setSpeed(float speed);

		void rotate(float angle);

		float getAngle() const { return m_angle; }

		void setAlpha(float alpha);

		std::string getName() const { return m_name; }

		bool isPlaying() const { 
			
			if(m_currentAnimation)
			{
				return m_currentAnimation->isPlaying();
			}
			return false;
		}

		void setScale(const glm::vec2 & scale);

		glm::vec2 getScale() const { return m_scale; }

		void setPos(const glm::vec2 & pos);

		glm::vec2 getDim() const { 

			if (m_currentAnimation)
			{
				return (m_scale * m_currentAnimation->getCurrentAnim()->sprite.getDim());
			}
			else
			{
				return glm::vec2(-223);
			}
			
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

		void setInvertAnimation();

	private:

		std::string m_filePath = "";
		std::string m_name = "";
		glm::vec2 m_pos = glm::vec2(0);
		glm::vec2 m_scale = glm::vec2(1);

		//bool m_isInverted = false;

		bool m_isInited = false;
		bool m_isVisible = false;

		float m_depth = 4;
		float m_angle = 0.0;
		Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);
		std::map<std::string, F_Animation> m_animations ;
		F_Animation * m_currentAnimation = nullptr;
		std::deque<std::string> stringPool;	
	};

}

#endif