#include "SpriteListHolder.h"

SpriteListHolder::SpriteListHolder()
{

}


SpriteListHolder::~SpriteListHolder()
{
}



void SpriteListHolder::init(glm::vec2 pos, glm::vec2 dim, int col, int row , Feintgine::GUI *gui )
{
	m_pos = pos;
	m_dim = dim;
	m_col = col;
	m_row = row;
	m_gui = gui;

	//m_textRenderder.init();
	
	filter_page = static_cast<CEGUI::Combobox*>
		(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.93, 0.2, 0.07, 0.22), glm::vec4(0), "sprite_holder_page"));
	
	page_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.93, 0.16, 0.1, 0.04), glm::vec4(0), "sprite_holder_page_label"));
	page_label->setText("Page");

	filer_packet = static_cast<CEGUI::Combobox*>
		(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.917, 0.05, 0.082, 0.22), glm::vec4(0), "sprite_holder_packet"));

	//packet filter even set 
	filer_packet->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&SpriteListHolder::packetFilterChanged, this));

	filter_page->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&SpriteListHolder::pageValueChangedClick, this));

	filter_page->subscribeEvent(CEGUI::Combobox::EventTextAccepted, CEGUI::Event::Subscriber(&SpriteListHolder::pageValueChangeText, this));

	packet_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.93, 0.01, 0.1, 0.04), glm::vec4(0), "sprite_holder_packet_label"));
	packet_label->setText("Packet");
	packet_label->setProperty("HorzFormatting", "LeftAligned");

	filter_page->setHeight(CEGUI::UDim(0.2, 0.0));
	page_label->setProperty("HorzFormatting", "LeftAligned");
	 
	filter_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.72, 0.395, 0.1, 0.12), glm::vec4(0), "sprite_filter_label"));
	filter_label->setText("Filter");
	filter_label->setProperty("HorzFormatting", "LeftAligned");

	filter_page->setValidationString("\\d*");
	filter_page->setMaxTextLength(3);

	filter_name = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.76, 0.435, 0.16, 0.04), glm::vec4(0), "sprite_filer_name"));
	filter_name->subscribeEvent(CEGUI::Combobox::EventTextChanged, CEGUI::Event::Subscriber(&SpriteListHolder::eventFilterNameTextChanged, this));

	m_nextPage = static_cast<CEGUI::PushButton *>
		(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.82, 0.38, 0.04, 0.04), glm::vec4(0), "m_nextPage"));
	m_nextPage->setText(">>");
	m_nextPage->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&SpriteListHolder::nextPage, this));

	m_prevPage = static_cast<CEGUI::PushButton *>
		(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.77, 0.38, 0.04, 0.04), glm::vec4(0), "m_prevPage"));
	m_prevPage->setText("<<");
	m_prevPage->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&SpriteListHolder::prevPage, this));

	sprite_name_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.605, 0.2275, 0.112, 0.04), glm::vec4(0), "sprite_name_label"));
	sprite_name_label->setProperty("HorzFormatting", "LeftAligned");
	


	//sprite_name_label->setFont(CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-8.font").getName());
	sprite_name_label->setText("Sprite Not selected");


	loadList();
	updatePacket();
	initGUI();
	resetTheColor();
	//filterList("");


}

void SpriteListHolder::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_spriteList.size(); i++)
	{
		//std::cout << "drawing " << i << " objects" << "\n";
		m_spriteList[i].draw(spriteBatch);
		
	}

}

void SpriteListHolder::drawBorder(Feintgine::DebugRender & renderer)
{
	for (int i = 0; i < m_spriteList.size(); i++)
	{
		m_spriteList[i].drawBorder(renderer);
			
	}
}

void SpriteListHolder::update(glm::vec2 mousePos)
{
	
	for (int i = 0; i < m_spriteList.size(); i++)
	{
		m_spriteList[i].update(mousePos);
		
	}
}

void SpriteListHolder::setPage(int page)
{
	m_currentPage = page;
}

void SpriteListHolder::show()
{
	if (filter_page && page_label)
	{
		filter_page->show();
		page_label->show();
		filer_packet->show();
		packet_label->show();
		filter_label->show();
		filter_name->show();
		sprite_name_label->show();
		m_nextPage->show();
		m_prevPage->show();
		
	}
	
}

void SpriteListHolder::hide()
{
	if (filter_page && page_label)
	{
		filter_page->hide();
		page_label->hide();
		filer_packet->hide();
		packet_label->hide();
		filter_label->hide();
		filter_name->hide();
		sprite_name_label->hide();
		m_nextPage->hide();
		m_prevPage->hide();
		
	}

}

bool SpriteListHolder::packetFilterChanged(const CEGUI::EventArgs &e)
{
	
	updatePacket();

	return true;
}

bool SpriteListHolder::pageValueChangedClick(const CEGUI::EventArgs &e)
{
	
	m_currentPage = std::stoi(filter_page->getSelectedItem()->getText().c_str());
	updateList();
	return true;
}

bool SpriteListHolder::pageValueChangeText(const CEGUI::EventArgs &e)
{

	int selection = std::stoi(filter_page->getText().c_str());
	if (selection > m_maxPageSize)
	{
		selection = m_maxPageSize;
		filter_page->setItemSelectState(selection, true);
	}


	m_currentPage = selection;
		//if(selection  )
	updateList();
	

	return true;
}

bool SpriteListHolder::eventFilterNameTextChanged(const CEGUI::EventArgs &e)
{

	std::string keyword(filter_name->getText().c_str());
	filterList(keyword);
	
	return true;
}

bool SpriteListHolder::nextPage(const CEGUI::EventArgs &e)
{
	int selection = std::stoi(filter_page->getText().c_str());
	selection += 1;
	if (selection > m_maxPageSize)
	{
		selection = m_maxPageSize;
		
	}
	filter_page->setItemSelectState(selection, true);

	m_currentPage = selection;
	updateList();
	return true;
}

bool SpriteListHolder::prevPage(const CEGUI::EventArgs &e)
{
	int selection = std::stoi(filter_page->getText().c_str());
	selection -= 1;
	if (selection < 0)
	{
		selection = 0;

	}
	filter_page->setItemSelectState(selection, true);

	m_currentPage = selection;
	updateList();
	return true;
}

void SpriteListHolder::clearTotalList()
{
	for (int i = 0; i < m_fullSpriteList.size(); i++)
	{
		m_fullSpriteList.erase(m_fullSpriteList.begin() + i);
	}
	m_fullSpriteList.clear();


}

void SpriteListHolder::clearFilterList()
{
	for (int i = 0; i < m_filteredList.size(); i++)
	{
		m_filteredList.erase(m_filteredList.begin() + i);
	}
	m_filteredList.clear();
}

void SpriteListHolder::clearSpriteList()
{
	for (int i = 0; i < m_spriteList.size(); i++)
	{
		m_spriteList.erase(m_spriteList.begin() + i);
	}
	m_spriteList.clear();
}

void SpriteListHolder::loadList()
{
	

	std::cout << "SpriteListHolder load start \n ";
	
	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
	CEGUI::ListboxTextItem * item;
	item = new CEGUI::ListboxTextItem("All", 0);
	item->setSelectionBrushImage(sel_img);
	filer_packet->addItem(item);
	std::map<std::string, Feintgine::SpritePacket > packetMap = Feintgine::SpriteManager::Instance()->getPacketMap();
	for (std::map<std::string, Feintgine::SpritePacket >::iterator it = packetMap.begin(); it != packetMap.end(); ++it)
	{
	
		
		item = new CEGUI::ListboxTextItem(it->first, packetId++);
		item->setSelectionBrushImage(sel_img);
		filer_packet->addItem(item);
		
// 		std::map<std::string, Feintgine::F_Sprite > packetSpriteMap = it->second.getSpriteMap();
// 		for (std::map<std::string, Feintgine::F_Sprite >::iterator sprite_it = packetSpriteMap.begin(); sprite_it != packetSpriteMap.end(); ++sprite_it)
// 		{
// 			SpriteProperty spriteProp;
// 			spriteProp.packetName = it->first;
// 			spriteProp.spriteName = sprite_it->first;
// 			m_fullSpriteList.push_back(spriteProp);
// 		}
		
	}

	filer_packet->setSortingEnabled(false);
	filer_packet->setReadOnly(true);
	if (CEGUI::ListboxItem* skinItem = filer_packet->getListboxItemFromIndex(0))
	{
		filer_packet->setItemSelectState(skinItem, true);
		

	}
	//filer_packet->setsel
	

	updateList(true);


	
}

bool SpriteListHolder::checkInside(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x / 2.0f && mousePos.x < m_pos.x + m_dim.x / 2.0f &&
		mousePos.y > m_pos.y - m_dim.y / 2.0f && mousePos.y < m_pos.y + m_dim.y / 2.0f)
	{
	
		return true;
	}
	return false;
}



bool SpriteListHolder::resetColor(const CEGUI::EventArgs &e)
{
	resetTheColor();
	return true;
}

bool SpriteListHolder::updateColor(const CEGUI::EventArgs &e)
{


	return true;
}

void SpriteListHolder::resetTheColor()
{

}

void SpriteListHolder::handleInput(Feintgine::InputManager & inputManager, glm::vec2 mousePos)
{
	update(mousePos);

	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		// clear sample when click escape
		if (m_displaySample)
		{
			sprite_name_label->setText("Sprite Not selected");
			delete m_displaySample;
			m_displaySample = nullptr;
		}
		
	}
	
	if (checkInside(mousePos))
	{

		for (int i = 0; i < m_spriteList.size(); i++)
		{
			
			if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
			{

				if (m_spriteList[i].isHover())
				{
					if (m_selectSpriteCallback)
					{
						m_selectSpriteCallback();
					}
					
					if (!m_displaySample)
					{
						

						m_selectSpriteCallback;
						m_displaySample = new DisplaySample();
						m_displaySample->init(m_spriteList[i].getSprite(), glm::vec2(0), glm::vec2(1), Feintgine::Color(255,255,255,255));
					}
					else
					{
						m_displaySample->init(m_spriteList[i].getSprite(), glm::vec2(0), glm::vec2(1), Feintgine::Color(255, 255, 255, 255));
					}
					sprite_name_label->setText(m_spriteList[i].getSprite().getName());
				}
			}
		}
	
	}
}

void SpriteListHolder::updatePacket()
{
	clearTotalList();
	if (CEGUI::ListboxItem * item = filer_packet->getSelectedItem())
	{
		if (item->getText() == "All")
		{
			std::cout << "reach\n";
			std::map<std::string, Feintgine::SpritePacket > packetMap = Feintgine::SpriteManager::Instance()->getPacketMap();
			for (std::map<std::string, Feintgine::SpritePacket >::iterator it = packetMap.begin(); it != packetMap.end(); ++it)
			{

				std::map<std::string, Feintgine::F_Sprite > packetSpriteMap = it->second.getSpriteMap();
				for (std::map<std::string, Feintgine::F_Sprite >::iterator sprite_it = packetSpriteMap.begin(); sprite_it != packetSpriteMap.end(); ++sprite_it)
				{
					SpriteProperty spriteProp;
					spriteProp.packetName = it->first;
					spriteProp.spriteName = sprite_it->first;
					m_fullSpriteList.push_back(spriteProp);
				}
			}
		}
		else
		{
			std::string packetName = std::string(item->getText().c_str());
			std::cout << "look for packet " << packetName << "\n";
			Feintgine::SpritePacket packetMap = Feintgine::SpriteManager::Instance()->getSpritePacketByName(packetName);

			if (packetMap.getName() != "")
			{
				std::map<std::string, Feintgine::F_Sprite > packetSpriteMap = packetMap.getSpriteMap();
				for (std::map<std::string, Feintgine::F_Sprite >::iterator sprite_it = packetSpriteMap.begin(); sprite_it != packetSpriteMap.end(); ++sprite_it)
				{
					SpriteProperty spriteProp;
					spriteProp.packetName = packetMap.getName();
					spriteProp.spriteName = sprite_it->first;
					m_fullSpriteList.push_back(spriteProp);
				}
			}
		}
	}

	filterList(filter_name->getText().c_str());
	//updateList();
}

void SpriteListHolder::filterList(const std::string & keyword)
{
	clearFilterList();
	
	if (keyword == "")
	{
		m_filteredList = m_fullSpriteList;
	}
	else
	{
		for (int i = 0; i < m_fullSpriteList.size(); i++)
		{
			if (m_fullSpriteList[i].spriteName.find(keyword) != std::string::npos)
			{
				//std::cout << "push back " << m_fullSpriteList[i].spriteName << "\n";
				m_filteredList.push_back(m_fullSpriteList[i]);
			}			
		}		
	}
	updateList(true);
}

void SpriteListHolder::updateList(bool needUpdatePage)
{
	
	clearSpriteList();
	
	glm::vec2 boxSize = glm::vec2(m_dim.x / m_row, m_dim.y / m_col);
	glm::vec2 startPosition = glm::vec2(0 - m_dim.x / 2.0f, -boxSize.y + m_dim.y / 2.0f) + glm::vec2(boxSize.x / 2.0f, boxSize.y / 2.0f);
	totalSize = m_col * m_row;

	m_maxPageSize = (m_filteredList.size() / totalSize );

	filter_page->resetList();
	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
	for (int i = 0; i <= m_maxPageSize; i++)
	{
		CEGUI::ListboxItem * item = new CEGUI::ListboxTextItem(std::to_string(i).c_str(), i);
		item->setSelectionBrushImage(sel_img);
		filter_page->addItem(item);
	}
	if (needUpdatePage)
	{
		if (CEGUI::ListboxItem* page = filter_page->getListboxItemFromIndex(0))
		{
			filter_page->setItemSelectState(page, true);
			m_currentPage = 0;
		}
	}

	if (m_filteredList.size() > 0)
	{
		for (int i = 0; i < m_col; i++)
		{
			for (int j = 0; j < m_row; j++)
			{
				SpriteDisplayer spriteDisplayer;

				int spriteIndex = ((i * m_col) + j) + (totalSize * m_currentPage);

				if (spriteIndex < m_filteredList.size())
				{
					std::string spriteItem = m_filteredList[spriteIndex].packetName + "/" + m_filteredList[spriteIndex].spriteName;

					spriteDisplayer.init(glm::vec2(startPosition.x + boxSize.x * i, startPosition.y - boxSize.y * j), boxSize, Feintgine::SpriteManager::Instance()->getSprite(spriteItem));
					m_spriteList.push_back(spriteDisplayer);
				}
			}
		}
	}
	//std::cout << "total " << m_fullSpriteList.size() << " sprite(s) loaded \n";
	//std::cout << "SpriteListHolder load end dddddddddddddddddddddddddB\n ";
}

void SpriteListHolder::setClickSpriteEvent(std::function<bool()> setOnClick)
{
	m_selectSpriteCallback = setOnClick;
}

void SpriteListHolder::initGUI()
{

// 	 	name_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.72, 0.51, 0.1, 0.12), glm::vec4(0), "name_label"));
// 	 	name_label->setText("Object name");
// 	 	name_label->setProperty("HorzFormatting", "LeftAligned");
	 
// 	 	type_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.875, 0.575, 0.1, 0.1), glm::vec4(0), "type_label"));
// 	 	type_label->setText("Object type");
// 	 	type_label->setProperty("HorzFormatting", "LeftAligned");
	 
	 
// 	 	width_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.725, 0.565, 0.08, 0.12), glm::vec4(0), "width_label"));
// 	 	width_label->setText("Width");
// 	 	width_label->setProperty("HorzFormatting", "LeftAligned");
// 	 
// 	 
// 	 
// 	 	heigh_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.725, 0.615, 0.08, 0.12), glm::vec4(0), "heigh_label"));
// 	 	heigh_label->setText("Heigh");
// 	 	heigh_label->setProperty("HorzFormatting", "LeftAligned");



// 	 	 red_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.725, 0.86, 0.08, 0.12), glm::vec4(0), "red_label"));
// 	 	red_label->setText("Red");
// 	 	red_label->setProperty("HorzFormatting", "LeftAligned");
// 
// 
// 
// 	 	green_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.725, 0.91, 0.08, 0.12), glm::vec4(0), "green_label"));
// 	 	green_label->setText("Green");
// 	 	green_label->setProperty("HorzFormatting", "LeftAligned");
// 
// 
// 
// 	 	blue_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.81, 0.86, 0.08, 0.12), glm::vec4(0), "blue_label"));
// 	 	blue_label->setText("Blue");
// 	 	blue_label->setProperty("HorzFormatting", "LeftAligned");
// 
// 
// 	 
// 	 	alpha_label = static_cast<CEGUI::DefaultWindow*>
// 	 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.81, 0.91, 0.08, 0.12), glm::vec4(0), "alpha_label"));
// 	 	alpha_label->setText("Alpha");
// 	 	alpha_label->setProperty("HorzFormatting", "LeftAligned");



// 	 	object_edit_name = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.815, 0.55, 0.13, 0.04), glm::vec4(0), "name_edit"));
// 	 
// 	 	object_combo_type = static_cast<CEGUI::Combobox*>
// 	 		(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.875, 0.655, 0.085, 0.18), glm::vec4(0), "type_combo"));
// 	 
// 	 	object_edit_width = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.775, 0.605, 0.09, 0.04), glm::vec4(0), "width_edit"));
// 	 
// 
// 	 
// 	 	object_edit_heigh = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.775, 0.655, 0.09, 0.04), glm::vec4(0), "heigh_edit"));
// 	 
// 	 
	 
// 	 	object_button_create = static_cast<CEGUI::PushButton*>(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.895, 0.95, 0.1, 0.05), glm::vec4(0),
// 	 		"create_button"));
// 	 	object_button_create->setText("Save Object");
	 
	 	

//  	 	object_resetColor = static_cast<CEGUI::PushButton*> (m_gui->createWidget("TaharezLook/Button", glm::vec4(0.895, 0.895, 0.1, 0.05), glm::vec4(0),
//  	 		"object_resetColor"));
//  	 	object_resetColor->setText("Reset Color");
// 		object_resetColor->subscribeEvent(CEGUI::FrameWindow::EventMouseClick, CEGUI::Event::Subscriber(&SpriteListHolder::resetColor, this));
// 
// 	 
// 	 	color_red_value = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.77, 0.895, 0.035, 0.04), glm::vec4(0), "color_red_value"));
// 	 	color_red_value->setMaxTextLength(3);
// 	 
// 
// 	 
// 	 	color_green_value = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.77, 0.945, 0.035, 0.04), glm::vec4(0), "color_green_value"));
// 	 	color_green_value->setMaxTextLength(3);
// 	 
// 
// 	 	color_blue_value = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.855, 0.895, 0.035, 0.04), glm::vec4(0), "color_blue_value"));
// 	 	color_blue_value->setMaxTextLength(3);
// 	 
// 	 	color_alpha_value = static_cast<CEGUI::Editbox *>
// 	 		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.855, 0.945, 0.035, 0.04), glm::vec4(0), "color_alpha_value"));
// 	 	color_alpha_value->setMaxTextLength(3);
// 
// 		color_red_value->setText("255");
// 		color_green_value->setText("255");
// 		color_blue_value->setText("255");
// 		color_alpha_value->setText("255");
// 	 
// 	 	color_red_value->setValidationString("\\d*");
// 	 	color_green_value->setValidationString("\\d*");
// 	 	color_blue_value->setValidationString("\\d*");
// 	 	color_alpha_value->setValidationString("\\d*");
	 






	//Combobox Item
	//type_combo->getEditbox()->disable();

// 	 	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
// 	 
// 	 	CEGUI::ListboxTextItem * item;
// 	 	item = new CEGUI::ListboxTextItem("Terrain", TYPE_TERRIAN);
// 	 	item->setSelectionBrushImage(sel_img);
// 	 	object_combo_type->addItem(item);
// 	 	item = new CEGUI::ListboxTextItem("Object", TYPE_OBJECT);
// 	 	item->setSelectionBrushImage(sel_img);
// 	 	object_combo_type->addItem(item);
// 	 	item = new CEGUI::ListboxTextItem("Tree", TYPE_TREE);
// 	 	item->setSelectionBrushImage(sel_img);
// 	 	object_combo_type->addItem(item);
// 	 	item = new CEGUI::ListboxTextItem("Plant", TYPE_PLANT);
// 	 	item->setSelectionBrushImage(sel_img);
// 	 	object_combo_type->addItem(item);
// 	 	item = new CEGUI::ListboxTextItem("Decal", TYPE_DECAL);
// 	 	item->setSelectionBrushImage(sel_img);
// 	 	object_combo_type->addItem(item);
// 	 	object_combo_type->setSortingEnabled(false);
// 	 	
	 	
// 	 	object_combo_type->setReadOnly(true);
// 	 	
	 	
	 
// 	 	if (CEGUI::ListboxItem* skinItem = object_combo_type->getListboxItemFromIndex(0))
// 	 	{
// 	 		object_combo_type->setItemSelectState(skinItem, true);
// 	 			
// 	 	}
	 
	  
	 
// 	 	object_edit_width->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::recalculateDimforSample, this));
// 	 	object_edit_heigh->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::recalculateDimforSample, this));
// 	 	object_button_addColider->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::createColider, this));
// 	 
 	 	//color_red_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&SpriteListHolder::updateColor, this));
 	 //	color_green_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&SpriteListHolder::updateColor, this));
 	 	//color_blue_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&SpriteListHolder::updateColor, this));
 	 	//color_alpha_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&SpriteListHolder::updateColor, this));
 	 	//object_button_create->subscribeEvent(CEGUI::FrameWindow::EventMouseClick, CEGUI::Event::Subscriber(&SpriteListHolder::writeFile, this));

}
