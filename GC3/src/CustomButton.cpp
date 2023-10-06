#include "CustomButton.h"
#include <iostream>
#pragma execution_character_set("utf-8")
CustomButton::CustomButton()
{
	currentAlpha = 1.0f;
}


CustomButton::~CustomButton()
{
}


void CustomButton::init(std::string text,const std::string & name, Feintgine::GUI &gui, const glm::vec4 & guiPos, std::function<bool(const CEGUI::EventArgs & e)> setOnClick)
{
	
	m_gui = gui;
	button = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/Label", guiPos, glm::vec4(0.0f), name));
	button->setText((CEGUI::utf8*) text.c_str());
	button->setProperty("HorzFormatting", "LeftAligned");
	button->subscribeEvent(CEGUI::DefaultWindow::EventMouseEntersArea, CEGUI::Event::Subscriber(&CustomButton::onHover, this));
	button->subscribeEvent(CEGUI::DefaultWindow::EventMouseLeavesArea, CEGUI::Event::Subscriber(&CustomButton::notHover, this));
	button->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, setOnClick);
	button->setAlwaysOnTop(true);
	

}

void CustomButton::update(float delta)
{
	if (m_hide)
	{
		if (count >= stack)
		{
			button->setPosition(button->getPosition() + CEGUI::UVector2(CEGUI::UDim(-0.025f, 0.1f), CEGUI::UDim(0.0f, 0.0f)));
			count++;
		}
	}
		
	else
	{
		if (count >= stack)
		{
			button->setPosition(button->getPosition() + CEGUI::UVector2(CEGUI::UDim(0.025f, 0.1f), CEGUI::UDim(0.0f, 0.0f)));
			count--;
		}
	}

	


//	std::cout << count << "\t "<< stack << "\n";

}




void CustomButton::hide()
{
	m_hide = true;
}

void CustomButton::setAlpha(float alpha)
{
	CEGUI::Colour total(1, 1.0f, 1, alpha);
	button->setProperty("NormalTextColour", ::CEGUI::PropertyHelper<::CEGUI::Colour>::toString(total));
}


void CustomButton::setTextAlignment(const std::string & tProp, const std::string & val)
{
	button->setProperty(tProp, val);
}



void CustomButton::moveTo(const glm::vec2 & destination, float delta, const glm::vec2 & moveSpeed)
{
	// todo , save the position from init function then move it 

	//glm::vec2 currentPos = glm::vec2(button->getPosition().d_x.percent(), button->getPosition().d_y.percent());
	//std::cout << feint_common::Instance()->convertiVec2toString(currentPos) << "\n";
}



void CustomButton::updateHideEffect(float delta, glm::vec2 speed)
{

}


void CustomButton::setReady(bool val)
{
	b_isReady = val;
}

bool CustomButton::onHover(const CEGUI::EventArgs & e)
{
	if (b_isReady)
	{
		CEGUI::Colour green = CEGUI::Colour(0.0f, 1.0f, 0.15f, currentAlpha);
		button->setProperty("NormalTextColour", ::CEGUI::PropertyHelper<::CEGUI::Colour>::toString(green));
		
	}
	return true;
}

bool CustomButton::notHover(const CEGUI::EventArgs & e)
{
	if (b_isReady)
	{
		CEGUI::Colour white = CEGUI::Colour(1, 1.0f, 1, currentAlpha);
		button->setProperty("NormalTextColour", ::CEGUI::PropertyHelper<::CEGUI::Colour>::toString(white));
	}
	return true;
}
bool CustomButton::setClick(const CEGUI::EventArgs & e)
{
	
	return true;
}

