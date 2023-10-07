#pragma once

#include <F_Sprite.h>
#include <SpritePacket.h>
#include <vector>
#include <map>

#include <DebugRender.h>

#include <SpriteManager.h>
#include <SpriteBatch.h>

struct SpriteProperty {

	std::string packetName;
	std::string spriteName;

};

class SpriteDisplayer
{
public:
	SpriteDisplayer();
	~SpriteDisplayer();
	void init(glm::vec2 pos, glm::vec2 dim, Feintgine::F_Sprite sprite);
	void calculateFitScale();

	void setSprite(Feintgine::F_Sprite sprite);


	bool checkInside(glm::vec2 mousePos);


	void draw(Feintgine::SpriteBatch &spriteBatch);

	void drawBorder(Feintgine::DebugRender & renderer);

	Feintgine::F_Sprite getSprite() const { return m_sprite; }


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
	Feintgine::F_Sprite m_sprite;

	Feintgine::Color idleColor = Feintgine::Color(255, 255, 255, 255);
	Feintgine::Color hoverColor = Feintgine::Color(100, 255, 100, 255);
	Feintgine::Color  currentColor = idleColor;

};

