
#ifndef _COLIDERBOX_H
#define _COLIDERBOX_H


#include "DragVertex.h"
#include <iostream>
#include "feint_common.h"

class ColiderBox
{
public:
	ColiderBox();
	~ColiderBox();

	bool checkInside(glm::vec2 mousePos);

	void draw(Feintgine::DebugRender & renderer);

	void init(glm::vec2 pos, glm::vec2 dim,int ID);

	glm::vec2 getPos() const { return m_pos; }

	glm::vec2 getDim() const { return m_dim; }

	void setPos(glm::vec2 pos);
	void setDim(glm::vec2 dim);

	void setSelected(bool value);

	bool isSelected() const { return selected; }

	int getID() const { return m_ID; }
	

private:
	glm::vec2 m_pos;
	glm::vec2 m_dim;

	
	Feintgine::Color m_color = Feintgine::Color(255, 0, 0, 255);
	Feintgine::Color m_selectedColor = Feintgine::Color(255, 0, 255, 255);
	Feintgine::Color color = m_color;
	DragVertex * point_pointer = nullptr;
	bool draged = false;

	bool modified = false;

	bool selected = false;
	
	int m_ID = 0;

	bool destroyed = false;

};

#endif
