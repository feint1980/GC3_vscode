#include "SpriteManager.h"


#ifdef _WIN32

#elif __linux__ 

#define _snprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__)

#endif


namespace Feintgine {

	SpriteManager *SpriteManager::p_Instance = 0;

	SpriteManager::SpriteManager()
	{
	}


	SpriteManager::~SpriteManager()
	{
	}

	void SpriteManager::loadSpritePacket(const std::string & filePath)
	{
		SpritePacket spritePacket;
		//spritePacket = new SpritePacket();
		spritePacket.loadPacket(filePath);
		std::string packetKey = filePath;
		packetKey = feint_common::Instance()->getFileNameFromPath(packetKey);
		m_SpritePackets.insert(std::make_pair(packetKey.c_str(), spritePacket));
		//std::cout << "loaded packet !!!!!!!! " << packetKey << "\n";
	}

	void SpriteManager::printPacketList()
	{
		//std::cout << "************** PRINT SPRITE PACKET LIST ******************\n";
		std::map<std::string, SpritePacket>::iterator it;
// 		for (it = m_SpritePackets.begin(); it != m_SpritePackets.end(); it++)
// 		{
// 			std::cout << it->first << "\n";
// 			std::cout << "with " << it->second.getSpriteMap().size() << "\n";
// 		}
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
				//	printf("%*s[%s]\n", level * 2, "", entry->d_name);
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
						//std::cout << "packet " << entry->d_name << " found \n";
						loadSpritePacket(texturePath.c_str());
					}
				}

			}


		} while (entry = readdir(dir));

		closedir(dir);
		return 0;
	}

	SpritePacket SpriteManager::getSpritePacketByFilePath(const std::string & filePath)
	{
		std::map<std::string, SpritePacket >::iterator it;

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

	Feintgine::SpritePacket SpriteManager::getSpritePacketByName( std::string name)
	{
		std::map<std::string, SpritePacket >::iterator it;
		//std::cout << "data input " << name.c_str() << "\n ";

		it = m_SpritePackets.find(name);

		//std::cout << "look in " << m_SpritePackets.size() << " packet(s) \n";

		for (std::map<std::string, Feintgine::SpritePacket >::iterator sprite_it = m_SpritePackets.begin(); sprite_it != m_SpritePackets.end(); ++sprite_it)
		{
			if (sprite_it->first == name)
			{
				return sprite_it->second;
			}
		}
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

