#ifndef _DRAGVERTEX_H_
#define _DRAGVERTEX_H_
#include "DebugRender.h"
class DragVertex
{
public:
	DragVertex();
	~DragVertex();

	void setPos( const glm::vec2 & pos);
	void setPoswithTrack(const glm::vec2 & pos);
	void setDim( const glm::vec2 & dim);

	void init(glm::vec2 pos, glm::vec2 dim);

	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDim() const { return m_dim; }
	glm::vec2 getLastPos() const { return m_lastPos; }

	void add(glm::vec2 val);

	void setX(float x) { m_pos.x = x; }
	void setY(float y) { m_pos.y = y; }

	void draw(Feintgine::DebugRender & renderer);

	bool checkInside(const glm::vec2 & mousePos);
	
	bool isDraged() const { return draged; }

	void setDrag(bool val) { draged = val; }

private:

	bool draged = false;
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	glm::vec2 m_lastPos;
};

#endif 
