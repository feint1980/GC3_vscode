#pragma once
#include <glm/glm.hpp>
#include "GUI.h"

class EGUI_DrawElement
{
public:
	EGUI_DrawElement();
	~EGUI_DrawElement();

	void init(Feintgine::GUI & t_gui, 
		const std::string & name,
		const glm::vec2 pos, const glm::vec2 dim);

	void setText(const std::string & text);
	void setText(const std::wstring & text);

	void setPos(const glm::vec2 & pos, const glm::vec2 & aspect);

	void setPos(const glm::vec2 & pos);

	void setDim(const glm::vec2 & dim);

	void setColor(const std::string & colorRef);

	void setAlpha(float alpha);

	void setAlignment(int value);

	CEGUI::USize getDim() const { return m_label->getSize(); }
	
	CEGUI::String E_GUI_ws2s(const std::wstring& s)
	{
		size_t max_bytes = s.size() * 4 + 1;
		CHAR* buf = new CHAR[max_bytes];
		WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, buf, max_bytes, 0, 0);
		CEGUI::String ret((CEGUI::utf8*)buf);
		delete buf;
		return ret;
	}

	std::wstring E_GUI_s2ws(const CEGUI::String& s)
	{
		wchar_t* buf = new wchar_t[s.size()];
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buf, 1024);
		std::wstring ret(buf);
		delete buf;
		return ret;
	}
private:

	glm::vec2 m_pos;
	glm::vec2 m_dim;


	//CEGUI::TextComponent * m_label
	//CEGUI::Window
	CEGUI::Window * m_label = nullptr;
	CEGUI::DefaultWindow * m_label2 = nullptr;
};

