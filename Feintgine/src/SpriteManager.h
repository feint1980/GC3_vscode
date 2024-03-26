#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

#include "SpritePacket.h"
#include <iostream>
#include <dirent.h>
#include <thread>
#include <vector>
#include <async++.h>
#include <unordered_map> // replace map with hash table to test if it's faster
#include <atomic>
#include <mutex>

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

		SpritePacket getSpritePacketByName(const std::string  & name);

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


		std::unordered_map<std::string, SpritePacket > getPacketMap() const { return m_SpritePackets; }

		void executeReadData();

		bool isLoadingDone();

		bool isDoneBatch();

	private:

		static SpriteManager *p_Instance;

		std::unordered_map<std::string, SpritePacket > m_SpritePackets;
		std::vector<std::thread> m_Threads;
		static std::mutex m_Mutex;
		std::atomic<bool> m_isDones[2000]; // let just cache 2000 packets
		int m_packetCount = 0;

		// test ||
		int fileCount = 0;

		int limited_thread = 8;
		int resolved_files = 0;
		int total_result = 0;

	};
}

#endif 
