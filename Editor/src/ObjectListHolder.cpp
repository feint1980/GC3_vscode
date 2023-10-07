#include "ObjectListHolder.h"

ObjectListHolder::ObjectListHolder()
{

}


ObjectListHolder::~ObjectListHolder()
{
}



void ObjectListHolder::init(glm::vec2 pos, glm::vec2 dim, int col, int row, Feintgine::GUI *gui)
{
	m_pos = pos;
	m_dim = dim;
	m_col = col;
	m_row = row;
	m_gui = gui;
	totalSize = m_col * m_row;

	
	//m_textRenderder.init();

	filter_page = static_cast<CEGUI::Combobox*>
		(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.01, 0.58, 0.07, 0.22), glm::vec4(0), "sprite_holder_page_2"));
 
	page_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.01, 0.55, 0.1, 0.04), glm::vec4(0), "sprite_holder_page_label_2"));
	page_label->setText("Page");
// 
// 	filer_packet = static_cast<CEGUI::Combobox*>
// 		(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.917, 0.05, 0.082, 0.22), glm::vec4(0), "sprite_holder_packet"));
// 
// 	//packet filter even set 
// 	filer_packet->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&ObjectListHolder::packetFilterChanged, this));
// 
// 	filter_page->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&ObjectListHolder::pageValueChangedClick, this));
// 
// 	filter_page->subscribeEvent(CEGUI::Combobox::EventTextAccepted, CEGUI::Event::Subscriber(&ObjectListHolder::pageValueChangeText, this));
// 
// 	packet_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.93, 0.01, 0.1, 0.04), glm::vec4(0), "sprite_holder_packet_label"));
// 	packet_label->setText("Packet");
// 	packet_label->setProperty("HorzFormatting", "LeftAligned");
// 
 	filter_page->setHeight(CEGUI::UDim(0.2, 0.0));
 	page_label->setProperty("HorzFormatting", "LeftAligned");
// 
	filter_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.01, 0.445, 0.1, 0.12), glm::vec4(0), "sprite_filter_label_2"));
	filter_label->setText("Filter");
	filter_label->setProperty("HorzFormatting", "LeftAligned");
// 
	filter_page->setValidationString("\\d*");
	filter_page->setMaxTextLength(3);
// 
	filter_name = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.04, 0.485, 0.15, 0.04), glm::vec4(0), "sprite_filer_name_2"));
	filter_name->subscribeEvent(CEGUI::Combobox::EventTextChanged, CEGUI::Event::Subscriber(&ObjectListHolder::eventFilterNameTextChanged, this));
// 
	m_nextPage = static_cast<CEGUI::PushButton *>
		(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.09, 0.39, 0.04, 0.04), glm::vec4(0), "m_nextPage_2"));
	m_nextPage->setText(">>");
	m_nextPage->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&ObjectListHolder::nextPage, this));

	m_prevPage = static_cast<CEGUI::PushButton *>
		(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.04, 0.39, 0.04, 0.04), glm::vec4(0), "m_prevPage_2"));
	m_prevPage->setText("<<");
	m_prevPage->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&ObjectListHolder::prevPage, this));


	m_isInited = true;
 	loadList();
	
// 	updatePacket();
// 	initGUI();
// 	resetTheColor();
	


}

void ObjectListHolder::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_objects.size(); i++)
	{

		m_objects[i].draw(spriteBatch);
	}
}

void ObjectListHolder::drawBorder(Feintgine::DebugRender & renderer)
{
	for (int i = 0; i < m_objects.size(); i++)
	{		
		m_objects[i].drawBorder(renderer);
	}
}

void ObjectListHolder::update(glm::vec2 mousePos)
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i].update(mousePos);

	}
}

void ObjectListHolder::show()
{
	if (m_isInited)
	{
		filter_page->show();
		page_label->show();
		filter_label->show();
		filter_name->show();
		m_nextPage->show();
		m_prevPage->show();
		
	
	}
}

void ObjectListHolder::hide()
{
	if (m_isInited)
	{
		filter_page->hide();
		page_label->hide();
		filter_label->hide();
		filter_name->hide();
		m_nextPage->hide();
		m_prevPage->hide();
		
	}

}

bool ObjectListHolder::eventFilterNameTextChanged(const CEGUI::EventArgs &e)
{
	std::string keyword(filter_name->getText().c_str());
	filterList(keyword);
	return true;
}

bool ObjectListHolder::nextPage(const CEGUI::EventArgs &e)
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

bool ObjectListHolder::prevPage(const CEGUI::EventArgs &e)
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

void ObjectListHolder::clearTotalList()
{
	for (int i = 0; i < m_fullObjectList.size(); i++)
	{
		m_fullObjectList.erase(m_fullObjectList.begin() + i);
	}
	m_fullObjectList.clear();
}

void ObjectListHolder::clearFilterList()
{
	for (int i = 0; i < m_filteredList.size(); i++)
	{
		m_filteredList.erase(m_filteredList.begin() + i);
	}
	m_filteredList.clear();
}

void ObjectListHolder::clearObjectList()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects.erase(m_objects.begin() + i);
	}
	m_objects.clear();
}

void ObjectListHolder::loadList()
{


	std::cout << "start loading \n";
	clearTotalList();
	listdir("./Assets/F_Objects",0);

	filter_name->setText("");
	updateList(true);
	filterList("");

	
}


bool ObjectListHolder::checkInside(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x / 2.0f && mousePos.x < m_pos.x + m_dim.x / 2.0f &&
		mousePos.y > m_pos.y - m_dim.y / 2.0f && mousePos.y < m_pos.y + m_dim.y / 2.0f)
	{

		return true;
	}
	return false;
}

void ObjectListHolder::handleInput(Feintgine::InputManager & inputManager, glm::vec2 mousePos)
{
	update(mousePos);

	
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		
		if (m_displaySample)
		{
			m_displaySample->clearLightAfterward();
			m_displaySample = nullptr;
			if (m_onCancelObjectCallback)
			{
				m_onCancelObjectCallback();
			 }
		}

	}

	if (checkInside(mousePos))
	{
		
		for (int i = 0; i < m_objects.size(); i++)
		{

			if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
			{
				
				if (m_objects[i].isHover())
				{
					if (m_selectSpriteCallback)
					{
						m_selectSpriteCallback();
					}
					if (m_selectObjectCallback)
					{
						m_selectObjectCallback();
					}
					if (!m_displaySample)
					{
					
						m_displaySample = new EditObject();
						m_displaySample->loadFromFile(m_objects[i].getObject().getFilePath());
						//m_displaySample->init();
						std::cout << "select new \n";
					
						if (m_displaySample)
						{
							m_selectObjectCallback();
						}						
					}
					else
					{
						delete m_displaySample;
						m_displaySample = new EditObject();
						m_displaySample->loadFromFile(m_objects[i].getObject().getFilePath());
						
						std::cout << "re-select \n";
						if (m_displaySample)
						{
							m_selectObjectCallback();
						}
					
					}
					//sprite_name_label->setText(m_spriteList[i].getSprite().getName());
				}
			}
		}

	}

}

void ObjectListHolder::filterList(const std::string & keyword)
{
	clearFilterList();

	if (keyword == "")
	{
		m_filteredList = m_fullObjectList;
	}
	else
	{
		for (int i = 0; i < m_fullObjectList.size(); i++)
		{
			
			if (m_fullObjectList[i].getName().find(keyword) != std::string::npos)
			{
				//std::cout << "push back " << m_fullSpriteList[i].spriteName << "\n";
				m_filteredList.push_back(m_fullObjectList[i]);
			}
		}
	}
	updateList(true);

}

void ObjectListHolder::updateList(bool needUpdatePage /*= false*/)
{

	clearObjectList();
	
	m_maxPageSize = (m_filteredList.size() / totalSize);
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

	glm::vec2 boxSize = glm::vec2(m_dim.x / m_row, m_dim.y / m_col);
	glm::vec2 startPosition = glm::vec2(0 - m_dim.x / 2.0f, -boxSize.y + m_dim.y / 2.0f) + glm::vec2(boxSize.x / 2.0f, boxSize.y / 2.0f);
	totalSize = m_col * m_row;

	//if (m_objects.size() > 0)
	//{
		for (int i = 0; i < m_col; i++)
		{
			for (int j = 0; j < m_row; j++)
			{
				

				int objectIndex = ((i * m_col) + j) + (totalSize * m_currentPage);

				if (objectIndex < m_filteredList.size())
				{
					
					ObjectDisplayer objectDisplayer;
					
					objectDisplayer.init(glm::vec2(startPosition.x + boxSize.x * i, startPosition.y - boxSize.y * j), boxSize, m_filteredList[objectIndex]);
					objectDisplayer.calculateFitScale();
					m_objects.push_back(objectDisplayer);
				}
			}
		}
	//}
	//std::cout << "total " << m_objects.size() << " object(s) loaded \n";
	//std::cout << "SpriteListHolder load end dddddddddddddddddddddddddB\n ";
}

void ObjectListHolder::clearCurrentObject()
{
	if (m_displaySample)
	{
		m_displaySample->clearLightAfterward();

		m_displaySample = nullptr;
	}
	delete m_displaySample;
	
}

void ObjectListHolder::setClickSpriteEvent(std::function<bool()> setOnClick)
{
	m_selectSpriteCallback = setOnClick;
}

void ObjectListHolder::setClickObjectEvent(std::function<bool()> setOnClick)
{
	m_selectObjectCallback = setOnClick;
}

void ObjectListHolder::setOnCancelObject(std::function<bool()> setCallback)
{
	m_onCancelObjectCallback = setCallback;
}

int ObjectListHolder::listdir(const char *name, int level)
{
	//std::cout << "scan on " << name << "\n";
	DIR *dir;
	struct dirent *entry;

	if (!(dir = opendir(name)))
	{
		std::cout << "dir failed \n";
		return 0;
	}

	if (!(entry = readdir(dir)))
	{
		std::cout << "entry failed \n";
		return 0;
	}


	do {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			int len = _snprintf_s(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
			path[len] = 0;
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			//	printf("%*s[%s]\n", level * 2, "", entry->d_name);
			listdir(path, level + 1);
		}
		else
		{
			//printf("%*s- %s\n", level * 2, "", entry->d_name);
			std::string texturePath = name;
			texturePath.append("/");
			texturePath.append(entry->d_name);



			if (texturePath.find("F_Objects/") != std::string::npos)
			{
				if (texturePath.find(".fob") != std::string::npos)
				{
					std::cout << "object " << entry->d_name << " found \n";
					EditObject object;
					object.loadFromFile(texturePath);
					
					std::cout << "loaded " << object.getName() << " object \n";
					m_fullObjectList.push_back(object);
					
				}
			}

		}
	} while (entry = readdir(dir));

	closedir(dir);
	return 0;

}


