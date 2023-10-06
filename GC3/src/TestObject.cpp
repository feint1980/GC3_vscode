#include "TestObject.h"
#include "EngineSetting.h"


TestObject::TestObject()
{
	
	
	
}


TestObject::~TestObject()
{
}

void TestObject::setInitialTime(float val_t)
{
	m_t = val_t;
}

void TestObject::update(float deltaTime)
{
	m_t += PATERN_SPEED * deltaTime;

	m_counter += 1 * deltaTime;
	glm::vec2 newPos = /*(m_pos + glm::vec2(1.0f * deltaTime, 0)) +*/ hypotrochoid(m_pos);
	m_pos = newPos;

	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].update(deltaTime);
		if (!m_traces[i].isAlive())
		{
			m_traces.erase(m_traces.begin() + i);
		}
	}

	genTrace(1,50);
}

glm::vec2 TestObject::astroid(const glm::vec2 & pos)
{
	glm::vec2 val; 
	float rad = 50.0f;
	float a = 2;
	val.x = (a * pow(cos(m_t),3)) *rad ;
	val.y = (a * pow(sin(m_t),3)) *rad ; 

	return val;
}

glm::vec2 TestObject::calculate(const glm::vec2 & pos)
{
	
	glm::vec2 val;

	int a = 9;
	int b = 3;
	float rad = 25.0f;

	val.x = ((a - b) * cos(m_t) + (b * cos((a / b - 1)*m_t))) * rad;
	val.y = ((a - b) * sin(m_t) - (b * cos((a / b - 1)*m_t))) * rad;

	return val;
	

}

glm::vec2 TestObject::hypotrochoid(const glm::vec2 & pos)
{
	glm::vec2 val;

	float a = 2.5;
	float b = 1;
	float c = 3;
	float rad = 75.0f;
	val.x = ((a - b) * cos(m_t) + (c * cos((a / b - 1)*m_t))) *rad;
	val.y = ((a - b) * sin(m_t) - (c * sin((a / b - 1)*m_t))) *rad;
	return val;
}

void TestObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	EmptyObject::draw(spriteBatch);
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].draw(spriteBatch);
	}
}

void TestObject::genTrace(float interval, float lifeTime)
{

	if (m_tracerCounter < m_counter)
	{
	
		TraceObject bg;
		bg.init(Feintgine::ResourceManager::getTexture("Textures/particle2.png"),
			m_pos, glm::vec2(40.0f, 40.0f), Feintgine::Color(255, 0, 255, 200));
		bg.setLifeTime(lifeTime);
		m_traces.push_back(bg);
		m_tracerCounter = m_counter + interval;
		
	}

}
