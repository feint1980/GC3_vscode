#pragma once

#include "SpritePacket.h"
namespace Feintgine
{
	class Dialouge_Avatar
	{
	public:
		Dialouge_Avatar();
		~Dialouge_Avatar();

		void loadSpritePacket(const std::string & fileName);

		F_Sprite getCurrentSprite()const { return m_currentSprite; }
		F_Sprite getSpriteByNum(int num);

		std::string getFileName() const { return m_fileName; }

	private:
		SpritePacket m_spritePacket;
		F_Sprite m_currentSprite;
		std::string m_fileName;
	};
}

