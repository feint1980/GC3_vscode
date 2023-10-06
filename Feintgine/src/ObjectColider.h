
#ifndef _OBJECTCOLIDER_H_
#define _OBJECTCOLIDER_H_

#include "DebugRender.h"
#include <iostream>
#include "feint_common.h"
class ObjectColider 
{
public:
	ObjectColider();
	~ObjectColider();

	void init(const glm::vec2 & pos, const glm::vec2 & dim);
	
	void draw(Feintgine::DebugRender & renderer);

	void setPos(const glm::vec2 &pos);

	glm::vec2 getPos() const { return m_pos;}

	glm::vec2 getDim() const { return m_dim; }

	void setDim(const glm::vec2 &dim);


private:
	glm::vec2 m_pos;
	glm::vec2 m_dim;

	Feintgine::Color m_color;

	
};

#endif