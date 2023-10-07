#include "EditObject.h"



EditObject::EditObject()
{
}


EditObject::~EditObject()
{
}





int EditObject::getLightIndexByID(int ID)
{
	for (int i = 0; i < m_lightListID.size(); i++)
	{
		if (m_lightListID[i] == ID)
		{
			return i;
		}
	}

	return -1;
}

int EditObject::getColiderIndexByID(int ID)
{
	for (int i = 0; i < m_coliders.size(); i++)
	{
		if (m_coliders[i].getID() == ID)
		{
			std::cout << "return " << i << "\n";
			return i;
		}
	}
	return -1;
}

void EditObject::setFitScale(float scale)
{
	m_fitScale = scale;
}

void EditObject::setEnlargeSize(float size)
{
	m_enlarger = size;
}




Feintgine::SelfSprite * EditObject::getSpriteByID(int ID)
{
	for (int i = 0; i < m_sprites.size(); i++)
	{
		if (m_sprites[i].m_ID == ID)
		{
			return &m_sprites[i];
		}
	}

	std::cout << "not found , return null \n";
	return nullptr;
}

void EditObject::deleteSpriteByID(int ID)
{
	for (int i = 0; i < m_sprites.size(); i++)
	{
		if (m_sprites[i].m_ID == ID)
		{
			std::cout << "delete index " << i << "\n";
			std::cout << "with ID " << m_sprites[i].m_ID << "\n";
			m_sprites.erase(m_sprites.begin() + i);
		}
	}
}

void EditObject::deleteColiderByID(int ID)
{
	for (int i = 0; i < m_coliders.size(); i++)
	{
		if (m_coliders[i].getID() == ID)
		{
			m_coliders.erase(m_coliders.begin() + i);
		}
	}
}

void EditObject::calculateOffset(const glm::vec2 & pos)
{
	savedOffset = m_pos - pos;
}

