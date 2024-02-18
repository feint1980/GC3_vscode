#include "EGUI_TextRenderer.h"



CEGUI_TextRenderer::CEGUI_TextRenderer()
{
}


CEGUI_TextRenderer::~CEGUI_TextRenderer()
{
}

void CEGUI_TextRenderer::addFont(const std::string & fontPath)
{
	// todo 
}


void CEGUI_TextRenderer::addTextObject(const std::string & name,
const std::string & text,
		const glm::vec2 & pos)
{
	EGUI_DrawElement element;
	element.init(text.c_str(), pos);
	m_textMap[name] = element;

}

void CEGUI_TextRenderer::addTextObject(const std::string & name,
const std::wstring & text,
		const glm::vec2 &pos)
{
	EGUI_DrawElement element;
	element.init(feint_common::Instance()->convertWstringToString(text).c_str(), pos);
	m_textMap[name] = element;
}

void CEGUI_TextRenderer::draw()
{
	for (auto & it : m_textMap)
	{
		it.second.render();
	}
}

void CEGUI_TextRenderer::update(float deltaTime)
{
	for (auto & it : m_textMap)
	{
		it.second.update(deltaTime);
	}
}

