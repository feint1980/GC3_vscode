#include "MainGUI.h"

MainGUI *MainGUI::p_Instance = 0;
#pragma execution_character_set("utf-8")

MainGUI::MainGUI()
{
}


MainGUI::~MainGUI()
{
}

void MainGUI::destroyGUI()
{
	m_gui.destroy();
}

void MainGUI::loadGUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("VanillaSkin.scheme");
	m_gui.loadScheme("WindowsLook.scheme");

// 	m_chatLog = static_cast<CEGUI::MultiLineEditbox * > 
// 		(m_gui.createWidget("TaharezLook/MultiLineEditbox",
// 			glm::vec4(0.01f, 0.5f, 0.38, 0.4f), glm::vec4(0.0f), "chatLog"));
 	
// 	m_chatLog->disable();
	m_chatTab = static_cast<CEGUI::TabControl*>
		(m_gui.createWidget("TaharezLook/TabControl",
			glm::vec4(0.01f, 0.5f, 0.38f, 0.4f), glm::vec4(0.0f), "chatlog"));

// 	m_chatTab_clone = static_cast<CEGUI::TabControl*>
// 		(m_gui.createWidget("TaharezLook/TabControl",
// 			glm::vec4(0.01f, 0.5f, 0.38f, 0.04f), glm::vec4(0.0f), "clone"));

	chatAllTab = static_cast<CEGUI::DefaultWindow*>
		(m_gui.createWidget("TaharezLook/TabContentPane",
			glm::vec4(0, 0, 1.0f, 1.0f), glm::vec4(0.0f), "bg_chatlog"));

	chatAllAlginment = static_cast<CEGUI::Listbox*>
		(m_gui.createWidget("TaharezLook/Listbox",
			glm::vec4(0, 0, 1, 1), glm::vec4(0.0f), "alginment"));


	systemTab = static_cast<CEGUI::DefaultWindow*>
		(m_gui.createWidget("TaharezLook/TabContentPane",
			glm::vec4(0, 0, 1.0f, 1.0f), glm::vec4(0.0f), "bg_chatlog1"));

// 	testText = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/StaticText", glm::vec4(0.5, 0.5, 0.1, 0.1), glm::vec4(0.0f), "testText"));
// 	testText->setText((CEGUI::utf8*)"thặc là \n vcl đó mà" );
	//testText->set
	m_chatTab->setAlwaysOnTop(false);
	m_chatTab->setAlpha(.5f);
	m_chatTab->addTab(chatAllTab);
	m_chatTab->addTab(systemTab);
// 
// 	m_chatTab_clone->addTab(chatAllTab);
// 	m_chatTab_clone->addTab(systemTab);

	chatAllTab->setText((CEGUI::utf8*)"Tất cả ");
	systemTab->setText((CEGUI::utf8*)"Hệ thống ");
	
	chatAllTab->setInheritsAlpha(false);
	chatAllTab->setAlpha(0.5f);
	systemTab->setInheritsAlpha(false);
	systemTab->setAlpha(0.5f);

	chatAllTab->addChild(chatAllAlginment);
	chatAllAlginment->setInheritsAlpha(false);
	chatAllAlginment->setAlpha(1.0f);
	

	//text->setSelectionBrushImage("MultiListSelectionBrush");
	

}

void MainGUI::drawGUI()
{
	if (isShow)
	{
		m_gui.draw();
	}
	

}

void MainGUI::addTextToChatLog(const std::string name , const std::string & content)
{
	//m_chatLog->appendText("\n");

	std::wstring wcontent = feint_common::Instance()->convertStringtoWstring(content);
	feint_common::Instance()->testPrintUtf8(wcontent);
	//std::cout << "added text \n";
	//std::string coloredText = "[colour='FFFF0000']" + content;

	std::wstring finalString = L"[colour='FF16F0F0']" + 
		feint_common::Instance()->convertStringtoWstring(name)
		+ L"[colour='FFFFFFFF'] : " + wcontent;

	LBWrapText wraptext;

	std::vector<CEGUI::ListboxTextItem *> chatitemlist;

	chatitemlist = wraptext.strToItemList(chatAllAlginment, feint_common::Instance()->convertWstringToString(finalString));


	
	for (size_t i= 0; i < chatitemlist.size(); i++)
	{	
		
		chatAllAlginment->addItem(chatitemlist[i]);
	}
	chatAllAlginment->getVertScrollbar()->setScrollPosition(
		chatAllAlginment->getVertScrollbar()->getDocumentSize() -
		chatAllAlginment->getVertScrollbar()->getPageSize());
//	chatAllAlginment->addItem(text);
	//chatAllAlginment->insertItem()
	//chatAllAlginment->addChild(text);
	//chatAllAlginment->addChildToPosition(chatAllAlginment->getChildAtIdx(0), 0);
	//m_chatLog->appendText("[colour='FFFF0000']");
	//m_chatLog->setText(m_chatLog->getText() + "\n"+ coloredContent);
	//m_chatLog->appendText("[colour='FFFF0000']");



}

void MainGUI::handleKey(Feintgine::InputManager &inputManager)
{
	if (inputManager.isKeyPressed(SDLK_F12))
	{
		if (!isShow)
		{
			isShow = true;
		}
		else
		{
			isShow = false;
		}
	}
}

void MainGUI::updataGUI()
{
// 	if (m_chatLog->isMouseContainedInArea())
// 	{
// 		m_chatLog->setAlpha(1.0f);
// 	}
// 	else
// 	{
// 		m_chatLog->setAlpha(0.75f);
// 	}
}

void MainGUI::updateChatLog()
{

}
