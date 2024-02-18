#pragma once
#include "GUI.h"
#include "EGUI_DrawElement.h"




class CEGUI_TextRenderer
{
public:
	CEGUI_TextRenderer();
	~CEGUI_TextRenderer();

	//void init()

	void addFont(const std::string & fontPath);

	void addTextObject(const std::string & name, const std::string & text,
		const glm::vec2 & pos);

	void addTextObject(const std::string & name,const std::wstring & text,
		const glm::vec2 &pos);

	void draw();
	void update(float deltaTime);
private:

	
	//Feintgine::GUI m_gui2;
	std::map<std::string,EGUI_DrawElement > m_textMap;



};

