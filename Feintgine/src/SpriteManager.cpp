#include "SpriteManager.h"


#ifdef _WIN32

#elif __linux__ 

#define _snprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__)

#endif



namespace Feintgine {

	SpriteManager *SpriteManager::p_Instance = 0;
	std::mutex SpriteManager::m_Mutex;

	SpriteManager::SpriteManager()
	{
	}


	SpriteManager::~SpriteManager()
	{
	}

	void SpriteManager::loadSpritePacket(const std::string & filePath)
	{
		//m_Mutex.lock();
		m_Mutex.lock();
		SpritePacket spritePacket;
		//spritePacket = new SpritePacket();
		
		spritePacket.loadPacket(filePath);
		//std::string packetKey = filePath;
		std::string packetKey = feint_common::Instance()->getFileNameFromPath(filePath);
		
		m_SpritePackets.insert(std::make_pair(packetKey.c_str(), spritePacket));
		std::cout << "inserted " << packetKey << "\n";
		std::cout << "size " << m_SpritePackets.size() << "\n";
		m_Mutex.unlock();
		//std::cout << "loaded packet !!!!!!!! " << packetKey << "\n";
	}

	void SpriteManager::printPacketList()
	{
		//std::cout << "************** PRINT SPRITE PACKET LIST ******************\n";
		//std::map<std::string, SpritePacket>::iterator it;
// 		for (it = m_SpritePackets.begin(); it != m_SpritePackets.end(); it++)
// 		{
// 			std::cout << it->first << "\n";
// 			std::cout << "with " << it->second.getSpriteMap().size() << "\n";
// 		}
	}

	void SpriteManager::executeReadData()
	{
		//std::cout << "thread size " << m_Threads.size() << "\n";
		// for(int i = 0; i < m_Threads.size(); i++)
		// {
		// 	m_Threads[i].join();
		// }
	}

	int SpriteManager::loadFromDirectory(const char * name, int level)
	{
		std::cout << "scan on " << name << "\n";
		DIR *dir;
		struct dirent *entry;


		
		if (!(dir = opendir(name)))
		{
			std::cout << "dir failed \n";
			return 0;
		}

		if (!(entry = readdir(dir)))
		{
			std::cout << "entry failed \n";
			return 0;
		}

		do {
			if (entry->d_type == DT_DIR) {
				char path[1024];
				int len = _snprintf_s(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
				path[len] = 0;
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
					continue;
					printf("%*s[%s]\n", level * 2, "", entry->d_name);
				loadFromDirectory(path, level + 1);
			}
			else
			{
				printf("%*s- %s\n", level * 2, "", entry->d_name);
				std::string texturePath = name;
				texturePath.append("/");
				texturePath.append(entry->d_name);

				if (texturePath.find("Packets/") != std::string::npos)
				{
					if (texturePath.find(".xml") != std::string::npos)
					{

						m_isDones[m_packetCount] = false;
						std::thread t = std::thread([&](){
							loadSpritePacket(texturePath.c_str());
							m_isDones[m_packetCount] = true;
						});
						m_packetCount++;
						m_Threads.push_back(std::move(t));

						//loadSpritePacket(texturePath.c_str()); // sync`
					}
				}

			}


		} while (entry = readdir(dir));



		if(level == 0) // end of stack
        {
            std::cout << "call \n";
            while(resolved_files < fileCount -1 )
            {
                for (int i = resolved_files ; i < resolved_files + limited_thread; ++i)
                {
                    if (i < m_Threads.size())
                    {
                        // std::cout <<"thread " << i << "\n";
                        if(m_Threads[i].joinable())
                        {
                            m_Threads[i].join();
                            //std::cout << "join thread " << i << "\n";
                        }
                    }
                }
                int result = 0;
                while (!isDoneBatch())
                {
                    std::cout << "wait \n";
                    std::cout << "resolved file \n";
                }

                resolved_files += limited_thread;
                if(resolved_files >= fileCount)
                {
                    resolved_files = fileCount -1;
                }
                

            // std::cout << "call \n";
            // for(int i = 0; i < m_Threads.size() -1; ++i)
            // {
            //     if(m_Threads[i].joinable())
            //     {
            //         m_Threads[i].join();
            //     }
            // }
            std::cout << "total threads " << m_Threads.size() << "\n";
        }

		closedir(dir);
		return 0;
	}
	}


	bool SpriteManager::isDoneBatch()
	{
		if(m_SpritePackets.size() >= resolved_files)
        {
            return true;
        }
        return false;
	}

	bool SpriteManager::isLoadingDone()
	{
		if(m_SpritePackets.size() >= m_Threads.size())
		{
			return true;
		}
		return false;
	}

	SpritePacket SpriteManager::getSpritePacketByFilePath(const std::string & filePath)
	{
		std::unordered_map<std::string, SpritePacket >::iterator it;

		it = m_SpritePackets.find(filePath);
		if (it != m_SpritePackets.end())
		{
		//	std::cout << "Found Packet : " << filePath << '\n';
			return m_SpritePackets.find(filePath)->second;
		}
		else
		{
			std::cout << "unable to find Packet " << filePath << " return null packet \n";
		SpritePacket pa;
		return pa;
		}

	}

	Feintgine::SpritePacket SpriteManager::getSpritePacketByName(const std::string & name)
	{
		std::unordered_map<std::string, SpritePacket >::iterator it;
		//std::cout << "data input " << name.c_str() << "\n ";

		it = m_SpritePackets.find(name);

		//std::cout << "look in " << m_SpritePackets.size() << " packet(s) \n";

		if (it != m_SpritePackets.end())
		{
			//std::cout << "Found Packet : " << name << '\n';
			return it->second;
		}
	
		// for (std::unordered_map<std::string, Feintgine::SpritePacket >::iterator sprite_it = m_SpritePackets.begin(); sprite_it != m_SpritePackets.end(); ++sprite_it)
		// {
		// 	if (sprite_it->first == name)
		// 	{
		// 		return sprite_it->second;
		// 	}
		// }
		std::cout << "unable to find Packet " << name << " return null packet \n";			
		SpritePacket pa;

		return pa;
	}

	F_Sprite SpriteManager::getSprite(const std::string & spritePacket_tt_name)
	{
		
		std::string packetName = spritePacket_tt_name.substr(0, spritePacket_tt_name.find("/"));
		std::string spriteName = spritePacket_tt_name.substr(spritePacket_tt_name.find("/") + 1);
		if (packetName.find(".xml") == std::string::npos)
		{
			packetName.append(".xml");
		}
		//std::cout << "><><><><>< looking for sprite "<< spriteName << " in packet " << packetName << "\n";
		return getSpritePacketByName(packetName).getSpriteByName(spriteName);
	}

}

