#pragma once
#include <DebugRender.h>

#include "TemplateObject.h"
#include <SpriteBatch.h>
class ObjectSlot
{
public:
	ObjectSlot();
	~ObjectSlot();

	void draw(Feintgine::DebugRender & renderer);

	void setPos(glm::vec2 pos);

	void setDim(glm::vec2 dim);

	bool onHover(const glm::vec2 & mousePos);

	

	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDim() const { return m_dim; }

	glm::vec2 getOffsetPos();

	void addObject(TemplateObject object);

	void clearObject();

	void drawObject(Feintgine::SpriteBatch & spriteBatch);

	bool hasObject() const { return m_object; }

	void init(glm::vec2 pos, glm::vec2 dim);

	TemplateObject * getObject() const { return m_object; }

	TemplateObject getCopyObject() { return v_object; }
	
private:
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	
	float enlargeSize = 1.35;
	float currentSize = 1.0f;

	bool show = false;

	TemplateObject v_object;

	TemplateObject * m_object = nullptr;


	Feintgine::Color m_color;
};

