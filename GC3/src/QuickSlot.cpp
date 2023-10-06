// #include "QuickSlot.h"
// #include <iostream>

// QuickSlot::QuickSlot()
// {
// }


// QuickSlot::~QuickSlot()
// {
// }

// void QuickSlot::init(glm::vec2 & pos, glm::vec2 & dim)
// {
// 	m_pos = pos; 
// 	m_dim = dim;
// 	m_texture = Feintgine::ResourceManager::getTexture("Textures/itemslot.png");
// }

// void QuickSlot::draw(Feintgine::SpriteBatch & spriteBatch)
// {
// 	glm::vec4 destRect;
// 	destRect.x = m_pos.x - m_dim.x / 2.0f;
// 	destRect.y = m_pos.y - m_dim.y / 2.0f;
// 	destRect.z = m_dim.x;
// 	destRect.w = m_dim.y;

// 	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);


// 	// Draw the sprite
// 	spriteBatch.draw(destRect, uvrect, m_texture.id, 1.0f, m_color,  1.0f);

// 	if (m_item != nullptr)
// 	{
// 		m_item->draw(spriteBatch);
// 	}
// }

// void QuickSlot::addItem(std::string id)
// {
// 	m_item = new Item();
// 	m_item->init(m_pos, m_dim * .9f, id);
// }
// bool QuickSlot::update(glm::vec2 &mousePos)
// {
// 	float top = -m_pos.y + m_dim.y / 2;
// 	float bot = -m_pos.y - m_dim.y / 2;
// 	float left = m_pos.x - m_dim.x / 2;
// 	float right = m_pos.x + m_dim.x / 2;
// 	//std::cout << top << "  " << bot;

// 	if (mousePos.x > left && mousePos.x < right)
// 	{
// 		if (mousePos.y < top && mousePos.y > bot)
// 		{
		
// 			hover = true;
// 			return true;
// 		}

// 		else
// 		{
// 			hover = false;
// 			return false;
// 		}

// 	}
// 	{
// 		hover = false;
// 		return false;
// 	}
// }

// void QuickSlot::remove()
// {
	
// 	delete m_item;
// 	m_item = nullptr;
// }

// float QuickSlot::use()
// {

// 	std::vector<std::string> recover;
// 	if (m_item != nullptr)
// 	{
// 		std::vector<std::string> num;
// 		std::string tmp = "SELECT number FROM account_item WHERE account_id = '";
// 		tmp.append(DataManager::Instance()->getAccountID());
// 		tmp.append("' AND item_id ='");
// 		tmp.append(m_item->getID());
// 		tmp.append("'");
// 		DataManager::Instance()->getTableData(strdup(tmp.c_str()), num);
// 		if (std::stoi(num[0]) > 1)
// 		{
// 			int s = std::stoi(num[0]);
// 			s--;
// 			tmp = "account_id = '";
// 			tmp.append(DataManager::Instance()->getAccountID());
// 			tmp.append("' AND item_id ='");
// 			tmp.append(m_item->getID());
// 			tmp.append("'");
// 			DataManager::Instance()->updateData("account_item", "number", strdup(std::to_string(s).c_str()), strdup(tmp.c_str()));
// 			addItem(m_item->getID());

// 			tmp = "SELECT recover FROM item WHERE ID = '";
// 			tmp.append(m_item->getID());
// 			tmp.append("'");
// 			DataManager::Instance()->getTableData(strdup(tmp.c_str()), recover);
			
// 		}
// 		else
// 		{

// 			tmp = "SELECT recover FROM item WHERE ID = '";
// 			tmp.append(m_item->getID());
// 			tmp.append("'");
// 			DataManager::Instance()->getTableData(strdup(tmp.c_str()), recover);

// 			tmp = "account_id = '";
// 			tmp.append(DataManager::Instance()->getAccountID());
// 			tmp.append("' AND item_id ='");
// 			tmp.append(m_item->getID());
// 			tmp.append("'");
// 			DataManager::Instance()->deleteData("account_item", strdup(tmp.c_str()));

// 			remove();
			

// 		}
// 		return std::stof(recover[0]);	
// 	}
// 	return -1;
// }

