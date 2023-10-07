#pragma once

#include <SpritePacket.h>
#include <vector>
#include <map>

#include <DebugRender.h>

#include <SpriteManager.h>
#include <SpriteBatch.h>

#include "EditObject.h"
class ObjectDisplayer
{
public:
	ObjectDisplayer();
	~ObjectDisplayer();
	void init(glm::vec2 pos, glm::vec2 dim, const EditObject & object);
	void calculateFitScale();

	void setObject(const EditObject & object);


	bool checkInside(glm::vec2 mousePos);


	void draw(Feintgine::SpriteBatch &spriteBatch);

	void drawBorder(Feintgine::DebugRender & renderer);

	EditObject getObject() const { return m_object; }


	void setHover(bool value);

	bool isHover() const { return m_isHover; }

	void update(glm::vec2 mousePos);

	glm::vec2 getPos() const { return m_pos; }

private:

	glm::vec2 m_pos;
	glm::vec2 m_dim;

	bool m_isHover = false;


	float enlargeSize = 1.35;
	float currentSize = 1.0f;

	float m_fitScale = 1;

	EditObject m_object;

	Feintgine::Color idleColor = Feintgine::Color(255, 255, 255, 255);
	Feintgine::Color hoverColor = Feintgine::Color(100, 255, 100, 255);
	Feintgine::Color  currentColor = idleColor;

};

