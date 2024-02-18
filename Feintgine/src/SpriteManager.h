#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

#include "SpritePacket.h"
#include <iostream>
#include <dirent.h>
#include <thread>
#include <vector>
#include <async++.h>
namespace Feintgine {

	class SpriteManager
	{
	public:
		SpriteManager();
		~SpriteManager();

		void loadSpritePacket(const std::string & filePath);

		void printPacketList();

		int loadFromDirectory(const char * name, int level);

		SpritePacket getSpritePacketByFilePath(const std::string & filePath);

		SpritePacket getSpritePacketByName( std::string  name);

		F_Sprite getSprite(const std::string & spritePacket_tt_name);

		static SpriteManager *Instance()
		{
			if (p_Instance == 0)
			{
				p_Instance = new SpriteManager;
				return p_Instance;
			}
			return p_Instance;
		}

		std::map<std::string, SpritePacket > getPacketMap() const { return m_SpritePackets; }

		void executeReadData();

	private:

		static SpriteManager *p_Instance;

		std::map<std::string, SpritePacket > m_SpritePackets;
		std::vector<std::thread> m_Threads;
		std::mutex m_Mutex;

	};
}

#endif 
