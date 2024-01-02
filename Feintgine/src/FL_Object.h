#ifndef FL_OBJECT_H
#define FL_OBJECT_H


#include "F_AnimatedObject.h"

#include "SpriteBatch.h"
#include "F_Sprite.h"

namespace Feintgine
{

class FL_OBject
{
public:
	FL_OBject();

	~FL_OBject();

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

	virtual void update(float deltaTime) = 0;
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

	unsigned int m_id = 0;
	bool m_isReachDestination = true;



};



}
#endif