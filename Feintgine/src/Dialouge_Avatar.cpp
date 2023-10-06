#include "Dialouge_Avatar.h"



Feintgine::Dialouge_Avatar::Dialouge_Avatar()
{
}


Feintgine::Dialouge_Avatar::~Dialouge_Avatar()
{
}

void Feintgine::Dialouge_Avatar::loadSpritePacket(const std::string & fileName)
{
	std::string locationPath = "Assets/Packets/";
	locationPath += fileName;
	m_spritePacket.loadPacket(locationPath);
	m_fileName = fileName;
}

Feintgine::F_Sprite Feintgine::Dialouge_Avatar::getSpriteByNum(int num)
{
	std::string ts = m_fileName.substr(0,m_fileName.size() - 4);
	ts += "_";
	if (num < 10)
	{
		ts += "0";
	}
	ts += std::to_string(num);
	ts += ".png";
	m_currentSprite  = m_spritePacket.getSpriteByName(ts);
	return m_currentSprite;
}
