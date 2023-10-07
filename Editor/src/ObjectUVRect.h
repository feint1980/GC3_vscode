#pragma once

#include <DebugRender.h>
#include <iostream>
#include <feint_common.h>
#include "DragVertex.h"

const int coliderWidth = 8;
class ObjectUVRect
{
public:
	ObjectUVRect();
	~ObjectUVRect();


	void create(glm::vec2 pos, glm::vec2 dim);
	void setPos(glm::vec2 pos) { m_pos = pos; updateVertices(); }
	void setDim(glm::vec2 dim);

	void draw(Feintgine::DebugRender &renderer);

	glm::vec2 getPos();
	glm::vec2 getDim();
	glm::vec2 getOffset() const { return m_offset; }

	void updateVertices();


	glm::vec4 getCalculatedUV(const glm::vec2 & spriteSheetDim);

	void calculateOffset( glm::vec2 mousePos);


	bool isMouseInside(const glm::vec2 & mousePos);

	void setDrag(bool value) { draged = value; }
	
	bool isDraged() const { return draged; }

	void checkPoint(const glm::vec2& mousePos, Feintgine::DebugRender &renderer);

	void dragPoint(const glm::vec2 &mousePos);

	DragVertex * getPoint() const { return point_pointer; }

	void recalculateDim();

protected:
	glm::vec2 m_pos;
	glm::vec2 m_dims;

	glm::vec2 m_offset;

	DragVertex tl;
	DragVertex bl;
	DragVertex br;
	DragVertex tr;

	DragVertex * point_pointer = nullptr; // pun 

	bool draged = false;
	
};

