#ifndef FL_OBJECT_H
#define FL_OBJECT_H


#include "F_AnimatedObject.h"

#include "SpriteBatch.h"
#include "F_Sprite.h"

namespace Feintgine
{

class FL_Object
{
public:
	FL_Object();

	~FL_Object();

	void init(const Feintgine::F_Sprite & sprite ,const glm::vec2 & pos, const glm::vec2 & scale);
	void init(const Feintgine::F_AnimatedObject & animObj, const glm::vec2 & pos, const glm::vec2 & scale);

	void setVel(const glm::vec2 & vel)
	{
		m_vel = vel;
	}

	void setPos(const glm::vec2 & pos)
	{
		m_pos = pos;
	}

	void setScale(const glm::vec2 & scale)
	{
		m_scale = scale;
	}

	void setDestination(const glm::vec2 & destination)
	{
		m_destination = destination;
		m_isReachDestination = false;
		m_hasTarget = true;
	}


	void setDepth(float depth)
	{
		m_depth = depth;
	
	}
	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDim() const { return m_dim; }
	glm::vec2 getScale() const { return m_scale; }
	glm::vec2 getVel() const { return m_vel; }
	glm::vec2 getDestination() const { return m_destination; }
	float getDepth() const { return m_depth; }
	float getAngle() const { return m_angle; }
	bool isReachDestination() const { return m_isReachDestination; }

	void defaultUpdate(float deltaTime);
	void setID(unsigned int id)
	{
		m_id = id;
	}

	unsigned int getID() const { return m_id; }

//	virtual void update(float deltaTime) = 0; this was my plan but i changed my mind

	void setUpdateFunc(std::function<void(float)> func)
	{
		m_updateFunc = func;
	}

	void setManipulatedFunc(std::function<void(float)> func, float duration, float delayTime);

	void update(float deltaTime);
	void draw(Feintgine::SpriteBatch & spriteBatch);


protected:
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	glm::vec2 m_scale;
	glm::vec2 m_vel;
	glm::vec2 m_destination;
	Feintgine::Color m_color;
	Feintgine::F_Sprite m_sprite;
	Feintgine::F_AnimatedObject m_animation;

	bool m_isAnimated = false;

	glm::vec2 m_direction;
	float m_depth = 0.0f;
	float m_angle = 0.0f;

	float m_speed = 2.5;

	unsigned int m_id = 0;
	bool m_isReachDestination = true;
	bool m_hasTarget = false;

	std::function<void(float)> m_updateFunc  = nullptr;
	std::function<void(float)> m_malipulatedFunc = nullptr;
	float m_manipulateDuration = 0.0f;
	float m_manipulateDelayTime = 0.0f;

};

}
#endif