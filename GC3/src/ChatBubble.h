#pragma once

#include <SpriteFont.h>
#include <SpriteBatch.h>
#include <glm/glm.hpp>
#include <GLTexture.h>
#include <iostream>
#include <ResourceManager.h>
#include <feint_common.h>
#include <GUI.h>
class ChatBubble 
{
public:
	ChatBubble();
	~ChatBubble();

	void update(glm::vec2 pos);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void loadTexture(const std::string & filePath);

	void say(const std::string & msg);
	//void loadFont()

	//void drawText();

	int getnearst(const std::string & ts);

	int getMax(int t1,  int t2);

private :
	int lifeTime;
	int limitTime;
	int basicTime = 80;
	
	Feintgine::GLTexture m_texture;
	glm::vec2 m_pos; 
	glm::vec2 m_dims;
	glm::vec2 basicDim = glm::vec2(1.0f,0); 

	bool isShow = false;
	bool isClean = false;

	int line = 1;
	glm::vec2 pos1, pos2;
	Feintgine::SpriteFont *m_spriteFont;
	std::string m_content;
	std::string m_secondContent;
	Feintgine::Color m_textColor;
	Feintgine::Color m_color;
	glm::vec4 uvrect;
};

