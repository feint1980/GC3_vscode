// #include "DropIcon.h"
// #include <iostream>

// DropIcon::DropIcon()
// {
// }


// DropIcon::~DropIcon()
// {
// }

// void DropIcon::init(glm::vec2 & pos, glm::vec2 & dim, char *id)
// {
// 	m_pos = pos;
// 	m_dim = dim;
// 	m_id = id;

// 	std::string tmp = "SELECT item.";
// 	tmp += '"';
// 	tmp.append("index");
// 	tmp += '"';
// 	tmp.append(" from item where ID = '");
// 	tmp.append(id);
// 	tmp.append("'");
// 	//std::cout << tmp;

// 	//std::cout << std::stoi(mm[0]);
// 	std::vector<std::string> mm;
// 	DataManager::Instance()->getTableData(strdup(tmp.c_str()), mm);

// 	m_texture.init(Feintgine::ResourceManager::getTexture("Textures/items.png"), glm::vec2(8));
	
// 	tileIndex = std::stoi(mm[0]);


// }

// void DropIcon::draw(Feintgine::SpriteBatch & spriteBatch)
// {
// 	glm::vec4 destRect;
// 	destRect.x = m_pos.x - m_dim.x / 2.0f;
// 	destRect.y = m_pos.y - m_dim.y / 2.0f;
// 	destRect.z = m_dim.x;
// 	destRect.w = m_dim.y;

// 	glm::vec4 uvRect = m_texture.getUVs(tileIndex);

// 	// Draw the sprite

// 	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 1.0f, m_color ,  1.0f);
// }

// void DropIcon::update(Player & player)
// {
// 	if (checkColide(player))// hit player
// 	{
// 		// check if player has already has this kind of item 
// 		std::string tmp = "SELECT number from account_item WHERE account_id = '";
// 		tmp.append(DataManager::Instance()->getAccountID());
// 		tmp.append("' AND item_id = '");
// 		tmp.append(m_id);
// 		tmp.append("'");
		

// 		std::vector<std::string> mm;
// 		DataManager::Instance()->getTableData(strdup(tmp.c_str()), mm);

// 		if (mm.size() > 0)
// 		{
// 			// if player has this item 
// 			int num = std::stoi(mm[0]);
// 			num++;
// 			tmp = "account_id = '";
// 			tmp.append(DataManager::Instance()->getAccountID());
// 			tmp.append("' AND item_id = '");
// 			tmp.append(m_id);
// 			tmp.append("'");
// 			DataManager::Instance()->updateData("account_item", "number", strdup(std::to_string(num).c_str()), strdup(tmp.c_str()));
// 		// increase the number of item 	
// 		}
// 		else
// 		{
// 			// if player doesn't have item like this 
// 			std::string tmp = "'";
// 			tmp.append(DataManager::Instance()->getAccountID());
// 			tmp.append("','");
// 			tmp.append(m_id);
// 			tmp.append("',");
// 			tmp.append(std::to_string(1));
// 			tmp.append(",");
// 			tmp.append(std::to_string(player.m_inventory.getFirstFreeSlot()));
// 			DataManager::Instance()->insertData("account_item", "account_id , item_id , number , position", strdup(tmp.c_str()));
// 			// create new one 
			
// 		}
// 		// they both gonna refresh item 
// 		player.m_inventory.refreshItem();
// 		//collected is flag to delete the item 
// 		collected = true;
// 	}

// }
// bool DropIcon::checkColide(Player & obj)
// {


// 	float leftSideA = m_pos.x - m_dim.x / 3.0f;
// 	float rightSideA = m_pos.x + m_dim.x / 3.0f;
// 	float upperSideA = m_pos.y + m_dim.y / 3.0f;
// 	float downSideA = m_pos.y - m_dim.y / 3.0f;

// 	float leftSideB = obj.getPos().x - obj.getDims().x / 2.0f;
// 	float rightSideB = obj.getPos().x + obj.getDims().x / 2.0f;
// 	float upperSideB = obj.getPos().y + obj.getDims().y / 2.0f;
// 	float downSideB = obj.getPos().y - obj.getDims().y / 2.0f;



// 	if (leftSideA > leftSideB && leftSideA < rightSideB || rightSideA > leftSideB && rightSideA < rightSideB)
// 	{
// 		if (upperSideA >= downSideB && upperSideA <= upperSideB || downSideA <= upperSideB && downSideA >= downSideB)
// 		{
// 			return true;
// 		}

// 	}
// 	if (upperSideA > downSideB && upperSideA < upperSideB || downSideA < upperSideB && downSideA > downSideB)
// 	{
// 		if (leftSideA >= leftSideB && leftSideA <= rightSideB || rightSideA >= leftSideB && rightSideA <= rightSideB)
// 		{
// 			return true;
// 		}
// 	}
// 	else
// 	{
// 		return false;
// 	}
// 	return false;
// }
