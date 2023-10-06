#pragma once
#include <TextRenderer.h>
#include <Camera2D.h>
const float TEXT_DECAY_RATE = 0.025f;
const float TEXT_DEFAULT_TIME = 2.5f;
class LabelItem
{
public:
	LabelItem();
	~LabelItem();

	void init(const glm::vec2 & pos, const std::string & text, Feintgine::Color color, float scale, int alignment);
	void draw(TextRenderer & textRenderer, const Feintgine::Camera2D cam );
	void update(float deltaTime);

	bool isExpired() const { return m_isExpired; }

private:
	glm::vec2 m_pos;
	std::string m_text;
	Feintgine::Color m_color;
	float m_scale;
	int m_alignment;
	bool m_isExpired = false;
	float m_lifeTime;

};

