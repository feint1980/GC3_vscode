#pragma once

#include <glm\glm.hpp>
#include <Feintgine.h>
#include <Vertex.h>
#include <GLTexture.h>
#include <TileSheet.h>
#include <SpriteBatch.h>
#include <DebugRender.h>

class SimpleObject
{
public:
	SimpleObject();
	~SimpleObject();

	virtual void update() = 0;
	virtual void destroy() = 0;
	glm::vec2 getPos()const { return m_pos; }
	glm::vec2 getDims() const {return m_dims; }
	void draw(Feintgine::SpriteBatch &spriteBatch);
	void drawDebug(Feintgine::DebugRender & renderer);
	void setPos(const glm::vec2 & pos);
	void changeColor(Feintgine::Color & color);
	void setDirection(const int d);

	void setDepth(float depth);
	void init(const glm::vec2 & pos , const glm::vec2 & dimentions ,Feintgine::GLTexture & texture, Feintgine::Color color ,const glm::vec2 & tileDims);
protected:
	int tileIndex = 0;
	int numTiles = 1;

	float m_animTime = 0.0f;
	
	int m_direction = 1;
	glm::vec2 m_pos;
	glm::vec2 m_dims;
	Feintgine::TileSheet m_texture;
	Feintgine::Color m_color;
	float m_depth = 1.0f;

};

