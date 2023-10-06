#include "EGUI_TextRenderer.h"



CEGUI_TextRenderer::CEGUI_TextRenderer()
{
}


CEGUI_TextRenderer::~CEGUI_TextRenderer()
{
}

void CEGUI_TextRenderer::initFont(const std::string & fontName)
{
	std::string outlineFont = fontName + "_outline";
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("VanillaSkin.scheme");
	m_gui.loadScheme("WindowsLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont(fontName);

// 	m_gui2.init("GUI");
// 	m_gui2.loadScheme("TaharezLook.scheme");
// 	m_gui2.loadScheme("VanillaSkin.scheme");
// 	m_gui2.loadScheme("WindowsLook.scheme");
// 	m_gui2.loadScheme("AlfiskoSkin.scheme");
// 	m_gui2.setFont(outlineFont);


}



void CEGUI_TextRenderer::addTextObject(const std::string & name, 
	const glm::vec2 pos, const glm::vec2 dim, const std::string & content)
{
	EGUI_DrawElement * object = new EGUI_DrawElement();
	object->init(m_gui, name, pos, dim);
	object->setText(content);
	m_textobjects.push_back(object);
}

void CEGUI_TextRenderer::addTextObject(const std::string & name, const glm::vec2 pos, const glm::vec2 dim, const std::wstring & content)
{
	EGUI_DrawElement * object = new EGUI_DrawElement();
	object->init(m_gui,name, pos, dim);
	object->setText(content);
	
	m_textobjects.push_back(object);
}

void CEGUI_TextRenderer::draw()
{
	
	//m_gui2.draw();
	m_gui.draw();
}

