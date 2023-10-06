#include "CustomMessageBox.h"


CustomMessageBox::CustomMessageBox(Feintgine::GUI & gui, std::string name, std::string name2, std::string name3, std::string name4, std::string message, glm::vec4 rect)
{
	border = static_cast<CEGUI::GroupBox*>(gui.createWidget("TaharezLook/GroupBox", rect, glm::vec4(0.0f), name));
	msg = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/Label", glm::vec4(0.2f, 0.2f, 0.6, 0.2f), glm::vec4(0.0f), name2));
	msg->setText((CEGUI::utf8*)message.c_str());
	msg->setAlwaysOnTop(true);
	bg = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/StaticImage", glm::vec4(0.0f, 0.0f, 1.0, 1.0f), glm::vec4(0.0f), name3));
	bg->setAlwaysOnTop(false);
	button = static_cast<CEGUI::PushButton*>(gui.createWidget("Vanilla/Button", glm::vec4(0.35f, 0.6f, 0.3f, 0.2f), glm::vec4(0.0f), name4));
	button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CustomMessageBox::hide, this));
	button->setAlwaysOnTop(true);
	button->setText("OK");
	border->addChild(msg);
	border->addChild(bg);
	border->addChild(button);

	msg->setDestroyedByParent(true);
	bg->setDestroyedByParent(true);
	button->setDestroyedByParent(true);
	border->setDestroyedByParent(true);
	border->setAlpha(0);
	isShowed = true;

}


CustomMessageBox::~CustomMessageBox()
{




}

void CustomMessageBox::init(Feintgine::GUI & gui, std::string name, std::string name2, std::string name3, std::string name4, std::string message, glm::vec4 rect)
{
	border = static_cast<CEGUI::GroupBox*>(gui.createWidget("TaharezLook/GroupBox", rect, glm::vec4(0.0f), name));
	msg = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/Label", glm::vec4(0.2f, 0.2f, 0.6, 0.2f), glm::vec4(0.0f), name2));
	msg->setText(message);
	msg->setAlwaysOnTop(true);
	bg = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/StaticImage", glm::vec4(0.0f, 0.0f, 1.0, 1.0f), glm::vec4(0.0f), name3));
	bg->setAlwaysOnTop(false);
	button = static_cast<CEGUI::PushButton*>(gui.createWidget("Vanilla/Button", glm::vec4(0.35f, 0.6f, 0.3f, 0.2f), glm::vec4(0.0f), name4));
	button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CustomMessageBox::hide, this));
	button->setAlwaysOnTop(true);
	button->setText("OK");
	border->addChild(msg);
	border->addChild(bg);
	border->addChild(button);

	msg->setDestroyedByParent(true);
	bg->setDestroyedByParent(true);
	button->setDestroyedByParent(true);
	border->setDestroyedByParent(true);
	isShowed = true;
	
}

void CustomMessageBox::show()
{
	if (!isShowed)
	{
		isShowed = true;
	}
}

bool CustomMessageBox::hide(const CEGUI::EventArgs & e)
{
	if (isShowed)
	{
		isShowed = false;
	}
	return true;
}

void CustomMessageBox::update()
{
	if (isShowed)
	{
		if (m_alpha <= 1)
		{
			m_alpha += 0.05f;
			border->setAlpha(m_alpha);
		}
	}
	else
	{
		if (m_alpha >= 0)
		{
			m_alpha -= 0.05f;
			border->setAlpha(m_alpha);
		}
		else
		{
			border->hide();		
			
			
			destroy();
		}
	}
}

void CustomMessageBox::destroy()
{
	msg->setText("");
	bg->destroy();
	msg->destroy();
	button->destroy();
	border->destroy();
	free(bg);
	free(msg);
	free(button);
	free(border);


	isDestroy = true;
}

void CustomMessageBox::addEvent(std::function<bool(const CEGUI::EventArgs & e)> setOnClick)
{
	button->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, setOnClick);
}

