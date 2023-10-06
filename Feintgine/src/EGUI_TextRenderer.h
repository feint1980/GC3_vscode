#pragma once
#include "GUI.h"
#include "EGUI_DrawElement.h"


class CEGUI_TextRenderer
{
public:
	CEGUI_TextRenderer();
	~CEGUI_TextRenderer();

	void initFont(const std::string & fontName);

	void addTextObject(const std::string & name,
		const glm::vec2 pos, const glm::vec2 dim, const std::string & content);

	void addTextObject(const std::string & name,
		const glm::vec2 pos, const glm::vec2 dim, const std::wstring & content);

	void draw();

	Feintgine::GUI getGUI() const { return m_gui; }
	Feintgine::GUI getGUI_non_const() { return m_gui; }
	Feintgine::GUI m_gui;
private:

	
	//Feintgine::GUI m_gui2;
	std::vector<EGUI_DrawElement * > m_textobjects;



};

