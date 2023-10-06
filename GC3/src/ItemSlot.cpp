// #include "ItemSlot.h"
// #include <iostream>

// ItemSlot::ItemSlot() :m_item(nullptr)
// {
// }


// ItemSlot::~ItemSlot()
// {
// }
// void ItemSlot::draw(Feintgine::SpriteBatch & spriteBatch)
// {
// 	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);
	

// 	glm::vec4 desRect;
// 	desRect.x = m_pos.x - m_dims.x / 2;
// 	desRect.y = m_pos.y - m_dims.y / 2;
// 	desRect.w = m_dims.x;
// 	desRect.z = m_dims.y;
// 	spriteBatch.draw(desRect, uvrect, m_texture.id, 0.0f, m_color,  1.0f);
// 	if (m_item != nullptr)
// 	{	
// 		m_item->draw(spriteBatch);
// 	}
// 	else
// 	{
		
// 	}
	
// }

// void ItemSlot::setPos(glm::vec2 & pos)
// {
// 	m_pos = pos;
// }

// void ItemSlot::addItem(std::string id)
// {
	
	
	


// 		m_item = new Item();
	
// 		m_item->init(m_pos, m_dims * .9f, id);
	
// 		if (m_item != nullptr)
// 		{
// 			std::cout << " adding new item with ID : " << id << " \n";
// 		}

// 	//m_listItem.push_back(m_item);
// 	//std::cout << m_item->getID();
// 	//hasItem = true;
	
// }

// bool ItemSlot::update(glm::vec2 &mousePos)
// {
	
// 		float top = -m_pos.y + m_dims.y / 2;
// 		float bot = -m_pos.y - m_dims.y / 2;
// 		float left = m_pos.x - m_dims.x / 2;
// 		float right = m_pos.x + m_dims.x / 2;
// 		//std::cout << top << "  " << bot;

// 		if (mousePos.x > left && mousePos.x < right)
// 		{
// 			if (mousePos.y < top && mousePos.y > bot)
// 			{
// 				return true;
// 			}

// 			else
// 			{
// 				return false;
// 			}

// 		}
// 		{
// 			return false;
// 		}
	
// }

// void ItemSlot::deleteItem()
// {
// 	delete m_item;
// 	//m_item = nullptr;
	
// 	//hasItem = false;
	
// }

// void ItemSlot::init(glm::vec2 pos, glm::vec2 dims, Feintgine::Color color, int slot)
// {
// 	m_texture = Feintgine::ResourceManager::getTexture("Textures/itemslot.png");
// 	m_pos = pos;
// 	m_dims = dims * 1.2f;
// 	m_color = color;
// 	slot_pos = slot;
// 	m_item = nullptr;

// }


