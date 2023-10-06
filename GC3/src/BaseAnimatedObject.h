#pragma once
#include <F_AnimatedObject.h>

class BaseAnimatedObject
{
public:
	BaseAnimatedObject();
	~BaseAnimatedObject();
	
	BaseAnimatedObject(const glm::vec2 & pos, const std::string & animationPath);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float delta);

protected:

	Feintgine::F_AnimatedObject m_animation;

	glm::vec2 m_pos;

	glm::vec2 m_vel = glm::vec2(0, 1.0f);
};

