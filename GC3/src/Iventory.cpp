// #include "Iventory.h"
// #include <iostream>

// Iventory::Iventory()
// {
// }


// Iventory::~Iventory()
// {
// }

// void Iventory::init(glm::vec2 & pos, glm::vec2 & dim, glm::vec2 slot_dims, Feintgine::GUI & gui)
// {
// 	m_pos = pos;
// 	m_dims = dim * 1.2f;
	
// 	item_info.init(gui);

// 	m_texture = Feintgine::ResourceManager::getTexture("Textures/inventory.png");

	
// 	m_mon = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);
	
// 	m_color = Feintgine::Color(255, 255, 255, 255);
// 	m_slotDim = slot_dims;

	
// 	int s_pos = 0;
// 	for (int i = 0; i < m_slotDim.y; i++)
// 	{
// 		for (int j = 0; j < m_slotDim.x; j++)
// 		{
// 			ItemSlot slot;
// 			slot.init(m_pos - glm::vec2(-j + 1.5, i - 1.5f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), s_pos);
// 			m_slots.push_back(slot);
// 			s_pos++;
// 		}
// 	}

// 	refreshItem();

// 	//std::cout << m_pos.x << "  " << m_pos.y << "\n";

	

// }

// void Iventory::draw(Feintgine::SpriteBatch & spriteBatch)
// {
// 	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);

// 	if (m_slots.size() > 0)
// 	{
// 		for (int i = 0; i < m_slots.size(); i++)
// 		{
// 			m_slots[i].draw(spriteBatch);
// 		}
// 	}

// 	glm::vec4 desRect;
// 	desRect.x = m_pos.x - m_dims.x / 2;
// 	desRect.y = m_pos.y - m_dims.y / 2;
// 	desRect.w = m_dims.x;
// 	desRect.z = m_dims.y;
// 	spriteBatch.draw(desRect, uvrect, m_texture.id, 0.0f, m_color,  1.0f);
// 	std::string tmp = "Mon : ";
// 	tmp.append(DataManager::Instance()->account_currency[0].c_str());
// 	mon_buffer = strdup(tmp.c_str());

// 	m_mon->draw(spriteBatch,
// 		mon_buffer, m_pos + glm::vec2(-m_dims.x / 2 + 0.4f, -3.2), glm::vec2(0.0085f),
// 		0.0f, Feintgine::Color(255, 255, 255, 255));	
// }

// void Iventory::setPos(glm::vec2 & pos)
// {
// 	m_pos = pos;
// }
// void Iventory::clear()
// {
// 	item_info.setup("", "", glm::vec2(-1));
// }

// void Iventory::update(Feintgine::InputManager & inputManager, QuickSlot &q)
// {
	
// 	dragItem();
// 	item_info.setup("", "", glm::vec2(-1));

// 	m_mouseWorldPos = glm::vec2(inputManager.getMouseCoords().x / 1000, inputManager.getMouseCoords().y / 600);
// 	m_mousePos = glm::vec2((inputManager.getMouseCoords().x - 500) / 35, (inputManager.getMouseCoords().y - 300) / 35);
	

// 	if (draging)
// 	{
// 		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
// 		{
// 			bool found = false;
// 			bool assign = false;
// 			int slotLocation = -100;
// 			for (int i = 0; i < m_slots.size(); i++)
// 			{
// 				if (m_slots[i].update(m_mousePos))
// 				{
// 					found = true;
// 					slotLocation = i;
// 					break;
// 				}
// 			}
			
// 				if (q.update(m_mousePos))
// 				{
					
// 						q.addItem(dragingItem->getID());
				
					
// 				}
			
			
			

// 			if (found)
// 			{

// 				if (m_slots[slotLocation].getItem() == nullptr)
// 				{
// 					std::string condition = "account_id = '";
// 					condition.append(DataManager::Instance()->getAccountID());
// 					condition.append("' AND item_id = '");
// 					condition.append(dragingItem->getID());
// 					condition.append("'");
// 					DataManager::Instance()->updateData("account_item", "position", strdup(::to_string(slotLocation).c_str()), strdup(condition.c_str()));

// 					dragingItem = nullptr;
// 					draging = false;
// 					refreshItem();
// 					return;
// 				}
// 				else
// 				{
					
// 					std::vector<std::string> pos;

// 					std::string sql = "SELECT position from account_item WHERE account_id = '";
// 					sql.append(DataManager::Instance()->getAccountID());
// 					sql.append("' AND item_id = '");
// 					sql.append(dragingItem->getID());
// 					sql.append("'");

// 					DataManager::Instance()->getTableData(strdup(sql.c_str()), pos);



// 					std::string condition = "account_id = '";
// 					condition.append(DataManager::Instance()->getAccountID());
// 					condition.append("' AND item_id = '");
// 					condition.append(dragingItem->getID());
// 					condition.append("'");

// 					DataManager::Instance()->updateData("account_item", "position", strdup(std::to_string(slotLocation).c_str()), strdup(condition.c_str()));

// 					condition = "account_id = '";
// 					condition.append(DataManager::Instance()->getAccountID());
// 					condition.append("' AND item_id = '");
// 					condition.append(m_slots[slotLocation].getItem()->getID());
// 					condition.append("'");

// 					DataManager::Instance()->updateData("account_item", "position", strdup(pos[0].c_str()), strdup(condition.c_str()));


// 					dragingItem = nullptr;
// 					draging = false;
// 					refreshItem();
// 					return;
// 				}
				
			

				
// 			}
// 			else
// 			{
// 				dragingItem->setPos(returnPos);
// 				dragingItem = nullptr;
// 				draging = false;
// 			}
			
// 		}
// 	}

// 		for (int i = 0; i < m_slots.size(); i++)
// 		{
// 			if (m_slots[i].getItem() != nullptr)
// 			{


// 				if (m_slots[i].getItem()->update(m_mousePos))
// 				{
// 					if (!draging)
// 					{
// 						item_info.setup(m_slots[i].getItem()->getName(), m_slots[i].getItem()->getDes(), m_mouseWorldPos);

// 						if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
// 						{

// 							dragingItem = m_slots[i].getItem();
// 							returnPos = m_slots[i].getItem()->getPos();						
// 							draging = true;
// 						}
// 					}
				

					
					
					
// 					/*exit(1);*/

// 				}
				
					
				
				
// 			}
// 		}
	
	
// }
// void Iventory::dragItem()
// {

// 	if (dragingItem != nullptr )
// 	{
// 		dragingItem->setPos(glm::vec2(m_mousePos.x, -m_mousePos.y));
// 	}
// }

// void Iventory::refreshItem()
// {

// 	//m_slots.clear();

//  	for (int i = 0; i < item_pos.size(); i++)
//  	{
//  		 m_slots[std::stoi(item_pos[i])].deleteItem();
		 		
//  	}


// 	string tmp = "SELECT item_id from account_item WHERE account_id = '";
// 	tmp.append(DataManager::Instance()->getAccountID());
// 	tmp.append("'");
// 	DataManager::Instance()->getTableData(strdup(tmp.c_str()), item_id);

// 	tmp = "SELECT position from account_item WHERE account_id = '";
// 	tmp.append(DataManager::Instance()->getAccountID());
// 	tmp.append("'");
// 	DataManager::Instance()->getTableData(strdup(tmp.c_str()), item_pos);
	
// 	std::cout << "found " << item_pos.size() << "\n";

// 	for (int i = 0; i < item_pos.size(); i++)
// 	{
// 		m_slots[std::stoi(item_pos[i])].addItem(item_id[i]);
// 	}
// }

// int Iventory::getFirstFreeSlot()
// {
// 	for (int i = 0; i < m_slots.size(); i++)
// 	{
// 		if (m_slots[i].getItem() == nullptr)
// 		{
// 			return i;
// 		}
// 	}
// 	return -1;
// }

