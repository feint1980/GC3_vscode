#pragma once
#include <GUI.h>
#include <InputManager.h>
#include <iostream>
#include <lbwraptext.h>
#include <feint_common.h>
class MainGUI
{
public:
	MainGUI();
	~MainGUI();

	void destroyGUI();
	void loadGUI();
	void drawGUI();
	

	static MainGUI * Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new MainGUI;
			return p_Instance;
		}
		return p_Instance;
	}

	

	void addTextToChatLog(const std::string name,const std::string & content);

	Feintgine::GUI getGUI() const { return m_gui; }
	
	void handleKey(Feintgine::InputManager &inputManager);

	void updataGUI();

	void updateChatLog();

	//void removeAllLog();

	//CEGUI::MultiLineEditbox * getBox() const { return m_chatLog; }
	
private :

	CEGUI::DefaultWindow * testText = nullptr;

	CEGUI::MultiLineEditbox * m_chatLog = nullptr;

	CEGUI::TabControl *m_chatTab = nullptr;
	CEGUI::TabControl *m_chatTab_clone = nullptr;

	CEGUI::DefaultWindow * chatAllTab = nullptr;
	CEGUI::Listbox * chatAllAlginment = nullptr;

	CEGUI::DefaultWindow * systemTab = nullptr;
	

	unsigned long attemp = 0;

	bool isShow = true;

	Feintgine::GUI m_gui;
	static MainGUI * p_Instance ;
};

