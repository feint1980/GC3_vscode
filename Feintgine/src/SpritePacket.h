#ifndef _SPRITEPACKET_H_
#define _SPRITEPACKET_H_

#include "F_Sprite.h"
#include <rapidxml.hpp>
#include <iostream>
#include <fstream>
#include "feint_common.h"
#include <rapidxml_print.hpp>
#include <sstream>
using namespace rapidxml;

namespace Feintgine {

	class SpritePacket
	{
	public:
		SpritePacket();
		~SpritePacket();
		SpritePacket(const std::string &filePath);
		void loadPacket(const std::string & filePath);

		void writeToImageset(const std::string & name);

		bool copyFile(const char *SRC, const char* DEST);

		std::string getName() const { return m_name; }

		Feintgine::F_Sprite getSpriteByName(const std::string & filePath);

		std::map<std::string, Feintgine::F_Sprite> getSpriteMap() const { return m_spriteMap; }

	private:

		Feintgine::F_Sprite templateSprite;

		std::string m_name;
		std::string m_texturePath;
		std::map<std::string, Feintgine::F_Sprite> m_spriteMap;
		bool isLoaded = false;

	};
}

#endif
