#pragma once
#include "TraceObject.h"
#include <math.h>
#include <ResourceManager.h>
#include <F_oEvent.h>

const float PATERN_SPEED = 0.1f;
class TestObject : public EmptyObject
{
public:
	TestObject();
	~TestObject();
	void setInitialTime(float val_t);

	void update(float deltaTime);

	glm::vec2 astroid(const glm::vec2 & pos);

	glm::vec2 calculate(const glm::vec2 & pos);

	glm::vec2 hypotrochoid(const glm::vec2 & pos);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void genTrace(float interval,float lifeTime);
private : 
	float m_t;
	bool gened = false;
	float m_counter = 0; 
	float m_tracerCounter = 0;

	std::vector<TraceObject> m_traces;
};

