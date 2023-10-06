#include "Item.h"
#include <iostream>

Item::Item()
{
}


Item::Item(glm::vec2 & pos, glm::vec2 & dim, std::string & id)
{

	m_item_data.clear();
	m_item_num.clear();
	m_pos = pos;
	m_dim = dim;
	m_id = id;

	std::string tmp = "SELECT * FROM item WHERE ID = '";
	tmp.append(id);
	tmp.append("'");


	//std::cout << tmp;
	DataManager::Instance()->getTableData(strdup(tmp.c_str()), m_item_data);

	m_name = m_item_data[1];
	m_desciption = m_item_data[2];


	tmp = "SELECT number FROM account_item WHERE account_id = '";
	tmp.append(DataManager::Instance()->getAccountID());
	tmp.append("' AND item_id = '");
	tmp.append(id);
	tmp.append("'");

	DataManager::Instance()->getTableData(strdup(tmp.c_str()), m_item_num);

	m_num = std::stoi(m_item_num[0]);


	tileIndex = std::stoi(m_item_data[4]);

	m_texture.init(Feintgine::ResourceManager::getTexture("Textures/items.png"), glm::vec2(8));

	item_num = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);

	num_buffer = strdup(m_item_num[0].c_str());

	std::cout << "created item " << m_id << " tile Index = " << tileIndex <<"\n";
}

Item::~Item()
{

}

void Item::init(glm::vec2 & pos, glm::vec2 & dim, std::string & id)
{
	m_item_data.clear();
	m_item_num.clear();
	m_pos = pos;
	m_dim = dim;
	m_id = id;

	std::string tmp = "SELECT * FROM item WHERE ID = '";
	tmp.append(id);
	tmp.append("'");

	
	//std::cout << tmp;
	DataManager::Instance()->getTableData(strdup(tmp.c_str()), m_item_data);

	m_name = m_item_data[1];
	m_desciption = m_item_data[2];


	tmp = "SELECT number FROM account_item WHERE account_id = '";
	tmp.append(DataManager::Instance()->getAccountID());
	tmp.append("' AND item_id = '");
	tmp.append(id);
	tmp.append("'");

	DataManager::Instance()->getTableData(strdup(tmp.c_str()), m_item_num);

	if (m_item_num.size() > 0)
	{
		m_num = std::stoi(m_item_num[0]);
		m_texture.init(Feintgine::ResourceManager::getTexture("Textures/items.png"), glm::vec2(8));

		item_num = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);

		num_buffer = strdup(m_item_num[0].c_str());
		std::cout << "found data has item";
	}
	else

	{
		std::cout << " found data has no item ";
	}
	

	tileIndex = std::stoi(m_item_data[4]);
	
}

void Item::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_pos.x - m_dim.x / 2.0f;
	destRect.y = m_pos.y - m_dim.y / 2.0f;
	destRect.z = m_dim.x;
	destRect.w = m_dim.y;

	glm::vec4 uvRect = m_texture.getUVs(tileIndex);

	// Draw the sprite

	item_num->draw(spriteBatch,
		num_buffer, m_pos + glm::vec2(m_dim.x / 2 - 0.1f, -m_dim.y / 2), glm::vec2(0.0065f),
		0.0f, Feintgine::Color(255, 255, 255, 255), Feintgine::Justification::RIGHT);

	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 1.0f, white,  1.0f);
	//std::cout << "drawing with idex : " << tileIndex << "\n";


//	std::cout << top << " \n ";

}

void Item::setPos(glm::vec2 & newPos)
{
	m_pos = newPos;
}

bool Item::update(glm::vec2 & mousePos)
{
	float top = -m_pos.y + m_dim.y/2  ;
	float bot = -m_pos.y - m_dim.y/2 ;
	float left = m_pos.x - m_dim.x / 2;
	float right = m_pos.x + m_dim.x / 2;
	//std::cout << top << "  " << bot;
	
	if (mousePos.x > left && mousePos.x < right)
	{
		if (mousePos.y < top && mousePos.y > bot)
		{
			return true;
		}

		else
		{
			return false;
		}

	}
	{
		return false;
	}

}
