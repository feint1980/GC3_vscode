#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <string>

#include <GUI.h>

class CustomMessageBox
{
public:
	CustomMessageBox(Feintgine::GUI & gui, std::string name, std::string name2, std::string name3, std::string name4, std::string message, glm::vec4 rect);
	~CustomMessageBox();
	void init(Feintgine::GUI &gui, std::string name, std::string name2, std::string name3, std::string name4, std::string message, glm::vec4 rect);
	void show();
	bool hide(const CEGUI::EventArgs & e);
	void update();
	bool onDestroy() const { return isDestroy; }
	void addEvent(std::function<bool(const CEGUI::EventArgs & e)> setOnClick);
	void destroy();
	private:
		CEGUI::GroupBox *border = nullptr;
		CEGUI::DefaultWindow * bg = nullptr;
		CEGUI::DefaultWindow * msg = nullptr;
		CEGUI::PushButton * button = nullptr;
		float m_alpha = 0.0f;
		bool isShowed = true;
		bool isDestroy = false;

};

