#pragma once


#include <F_AnimatedObject.h>
#include <feint_common.h>
class GuardianShield 
{
public:

	GuardianShield();
	GuardianShield(const std::string & animationPath, const glm::vec2 & pos, float scale);
	
	~GuardianShield();

	void init(const std::string & animationPath, const glm::vec2 & pos, float scale);

	void update(float delta);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void setPos(const glm::vec2 & pos);

	void setOffsetPos(const glm::vec2 & pos);

	void playAnimation(const std::string & animationName);

private:

	Feintgine::F_AnimatedObject m_animations;

	glm::vec2 m_pos;
	glm::vec2 m_offsetPos;
	glm::vec2 m_dim;
	float m_scale;



};

