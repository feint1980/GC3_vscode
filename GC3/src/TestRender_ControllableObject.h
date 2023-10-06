#pragma once

#include "F_AnimatedObject.h"
#include <InputManager.h>
#include <LightBatch.h>

const float tr_object_speed = 5.0f;


class TestRender_ControllableObject
{
public:
	TestRender_ControllableObject();
	~TestRender_ControllableObject();


	void update(float deltaTime);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void handleInput(Feintgine::InputManager & inputManager);

	void init(const std::string & animationPath);

	void setPos(const glm::vec2 & pos);

	void calculateState();

	void setAnimation(int value);


	glm::vec2 getPos() const { return m_pos; }

protected:

	Feintgine::F_AnimatedObject m_animation;
	glm::vec2 m_pos;
	glm::vec2 m_vel;

	glm::vec3 f_attentionua = glm::vec3(14.0f, 14.0f, 25.0f);

	int m_currentAnimState = 0;
};

