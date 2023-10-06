#include "TestRender_ControllableObject.h"



TestRender_ControllableObject::TestRender_ControllableObject()
{
}


TestRender_ControllableObject::~TestRender_ControllableObject()
{
}

void TestRender_ControllableObject::update(float deltaTime)
{
	m_animation.update(deltaTime);


	m_pos += m_vel * deltaTime;
	calculateState();
}

void TestRender_ControllableObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_animation.setPos(m_pos);
	m_animation.draw(spriteBatch);
}

void TestRender_ControllableObject::drawLight(Feintgine::LightBatch & lightBatch)
{
	lightBatch.addLight(m_pos, glm::vec4(1.0f),
		(1.0f / f_attentionua));
}

void TestRender_ControllableObject::handleInput(Feintgine::InputManager & inputManager)
{

	m_vel = glm::vec2(0);
	if (inputManager.isKeyDown(SDLK_a))
	{
		m_vel.x = -tr_object_speed;
	}
	else if (inputManager.isKeyDown(SDLK_d))
	{
		m_vel.x = tr_object_speed;
	}

	if (inputManager.isKeyDown(SDLK_w))
	{
		m_vel.y = tr_object_speed;
	}
	else if (inputManager.isKeyDown(SDLK_s))
	{
		m_vel.y = -tr_object_speed;
	}

	
}

void TestRender_ControllableObject::init(const std::string & animationPath)
{
	m_animation.init(animationPath);
	m_animation.setDepth(10);
	m_animation.playAnimation("idle");

}

void TestRender_ControllableObject::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void TestRender_ControllableObject::calculateState()
{
	int decision = 0;
	if (m_vel.x < 0)
	{
		decision = 1;
	}
	if(m_vel.x > 0)
	{
		decision = 2;
	}
	if (m_currentAnimState != decision)
	{
		m_currentAnimState = decision;
		setAnimation(m_currentAnimState);
	}
}

void TestRender_ControllableObject::setAnimation(int value)
{
	switch (value)
	{
	case 0:
		m_animation.playAnimation("idle");
		break;
	case 1:
		m_animation.playAnimation("left");
		break;
	case 2:
		m_animation.playAnimation("right");
		break;
	default:
		break;
	}
}
