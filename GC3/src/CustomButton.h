#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <string>

#include <feint_common.h>
#include <GUI.h>

class MainMenuScreen;
class CustomButton 
{
public:

	CustomButton();
	~CustomButton();
	void init(std::string text, const std::string & name,  Feintgine::GUI &gui,const glm::vec4 & guiPos, std::function<bool(const CEGUI::EventArgs & e)> setOnClick);
	void update(float delta);
	void hide();

	void setAlpha(float alpha);

	void setTextAlignment(const std::string & tProp, const std::string & val);
	
	CEGUI::DefaultWindow* getButton() const { return button; }

	void moveTo(const glm::vec2 & destination, 
		float delta, const glm::vec2 & moveSpeed);

	void updateHideEffect(float delta, glm::vec2 speed);

	void setReady(bool val);
	
private:

	//CEGUI::Colour green = CEGUI::Colour(0.0f, 1.0f, 0.15f, currentAlpha);
	//CEGUI::Colour white = CEGUI::Colour(1, 1.0f, 1, currentAlpha);

	int count = 0;
	bool m_hide = false;
	int stack;


	bool onHover(const CEGUI::EventArgs & e);
	bool notHover(const CEGUI::EventArgs & e);
	bool setClick(const  CEGUI::EventArgs & e);
	
	std::string m_text;
	CEGUI::DefaultWindow* button = nullptr;
	Feintgine::GUI m_gui;
	float m_alpha;
	bool b_isReady = false ;
	float currentAlpha;


};

