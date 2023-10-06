#pragma once
#include "SpriteBatch.h"
#include "GLTexture.h"
#include "AudioEngine.h"
#include <iostream>
#include "Camera2D.h"
#include "TextRenderer.h"
#include "feint_common.h"
#include "EGUI_DrawElement.h"


class F_SpellcardBase
{
public:
	F_SpellcardBase();
	~F_SpellcardBase();

	void init(const Feintgine::GLTexture & texture, const glm::vec2 & pos,
	const glm::vec2 & intendPos,const glm::vec2 & dim, const Feintgine::Color & color,\
		float depth ,bool isLeft = true );

	void loadDesciption(const std::string & signName,
		const std::string & spellName, int id);

	void loadSound(Feintgine::AudioEngine * audioEngine,\
		const std::string & filePath);

	void loadDesciption(const std::wstring & signName,
		const std::wstring & spellName, int id);

	void registerText(Feintgine::GUI & gui, const std::string & name,
		const glm::vec2 & pos, const glm::vec2 & dim);

	void update(float deltaTime);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void setTextPos(const glm::vec2 & pos);
	
	void drawText(const Feintgine::Camera2D & camera, TextRenderer & renderer);

	bool isAlive() const { return m_isAlive; }

	std::wstring colorCode(int id);
	

protected:

	glm::vec2 m_pos;
	glm::vec2 m_intendedPos;
	glm::vec2 m_dim;

	bool m_isLeft = true;

	float m_firstDistance;

	glm::vec2 textOffset;
	glm::vec2 textOffset2;

	Feintgine::Color m_color;
	float m_depth;

	bool m_isAlive = true;

	float m_lifeTime = 10.0f;

	float m_lifeTimeRate = 0.1f;

	Feintgine::GLTexture m_texture;
	
	Feintgine::AudioEngine * m_audioEngine = nullptr;

	std::wstring m_signName;
	std::wstring m_spellName;

	EGUI_DrawElement m_cegui_text;

};

