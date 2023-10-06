#pragma once

#include <SpriteBatch.h>
#include <TextRenderer.h>
#include <GLTexture.h>


const float AVATAR_FADE_SPEED = 0.045f;
class CharacterAvatar
{
public:
	CharacterAvatar();
	~CharacterAvatar();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawDescription(Feintgine::SpriteBatch & spriteBatch);


	void init(const Feintgine::GLTexture & texture, const glm::vec2 & pos,
		const glm::vec2 & dim, const glm::vec4 & color, float depth);


	void initDescription(const std::string & japName, const std::string &engName,
		const std::string & title );

	void addDesciptionTexture(const Feintgine::GLTexture & texture, const glm::vec2 & pos);

	void getTextRenderer(const TextRenderer & txtrd);

	bool handleMouseInput(const glm::vec2 & mousePos);



	void setAlpha(float alphaVal);

	void setSelected(bool val);

	void update(float delta);
	void show(float delta);

	void setVisible(bool val);

	void selecting(float delta);
	void unSelecting(float delta);

	void hide(float delta);

private:

	TextRenderer m_textRenderer;

	Feintgine::GLTexture m_texture;
	Feintgine::GLTexture m_desTexture;

	glm::vec2 m_pos;
	glm::vec2 m_dim;
	glm::vec4 m_color;

	std::string m_japName;
	std::string m_engName;

	glm::vec2 m_desPos; 
	glm::vec2 m_desDim;
	glm::vec4 m_desColor;

	glm::vec2 m_originalPos;
	glm::vec2 selectionOffset;
	float m_depth;

	bool m_isSelected = false; 

	bool m_isVisible;
	float m_speed;


};

