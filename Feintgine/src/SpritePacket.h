#ifndef _SPRITEPACKET_H_
#define _SPRITEPACKET_H_

#include "F_Sprite.h"
#include <rapidxml.hpp>
#include <iostream>
#include <fstream>
#include "feint_common.h"
#include <rapidxml_print.hpp>
#include <sstream>
#include <unordered_map>
using namespace rapidxml;

namespace Feintgine {

	class SpritePacket
	{
	public:
		SpritePacket();
		~SpritePacket();
		SpritePacket(const std::string &filePath);
		SpritePacket fLoadPacket(std::string_view filePath);
		void loadPacket(const std::string & filePath);

		void writeToImageset(const std::string & name);

		bool copyFile(const char *SRC, const char* DEST);

		std::string getName() const { return m_name; }

		Feintgine::F_Sprite getSpriteByName(const std::string & filePath);

		void selfLoad();

		std::map<std::string, Feintgine::F_Sprite> getSpriteMap() const { return m_spriteMap; }

		std::string getFilePath() const { return m_filePath; }

		void setName(const std::string & name) { m_name = name; }

		void updateTexture();

		void setTexturePath(const std::string & texturePath) { m_texturePath = texturePath; }

		void insertSprite(const std::string & name, const Feintgine::F_Sprite & sprite) { m_spriteMap.insert({ name, sprite }); }

	private:

		Feintgine::F_Sprite templateSprite;



		std::string_view m_vFilePath;
		std::string m_filePath;
		std::string m_name;
		std::string m_texturePath;
		std::map<std::string, Feintgine::F_Sprite> m_spriteMap;
		bool isLoaded = false;
		static std::mutex m_t_mutex;

	};
}

#endif
