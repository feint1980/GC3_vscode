#include "SpriteManager.h"


#ifdef _WIN32

#elif __linux__

#define _snprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__)

#endif



namespace Feintgine {

	 inline std::string t_getFileNameFromPath(const std::string & str)
	{

		// std::cout << "scan on " << str << "\n";
		char sep = '/';


		size_t i = str.rfind(sep, str.length());
		if (i != std::string::npos) {
		
			return(str.substr(i + 1, str.length() - i));
		}
		return("");
	}

	template<typename R>
	bool is_ready(std::future<R> const& f)
	{ return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }

	bool t_isFloat(const std::string & s)
	{
		std::istringstream iss(s);
		float f;
		iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
							// Check the entire string was consumed and if either failbit or badbit is set
		return iss.eof() && !iss.fail();
	}
	inline std::string t_getPathName(const std::string & str)
	{

		// std::cout << "scan on " << str << "\n";
			char sep = '/';

	// #ifdef _WIN32
	// 		 sep = '\\';
	// #endif

			size_t i = str.rfind(sep, str.length());
			if (i != std::string::npos) {
				// std::cout << "cliped " << str << "\n";
				return(str.substr(0, i));
			}
			return("");	 
	}

	inline glm::vec2 t_convertStringToVec2(const std::string & x_string, const std::string & y_string)
	{
		if (t_isFloat(x_string) && t_isFloat(y_string))
		{
			return glm::vec2(std::stof(x_string.c_str()), std::stof(y_string.c_str()));
		}	
		return glm::vec2(-1);
	}

	SpritePacket readFile(std::string_view vFilePath) {
		SpritePacket retVal;
		xml_document <> t_packet;
		xml_node<> * t_TextureAtlas = nullptr;


		std::string filePath = vFilePath.data();

		//std::cout << "TEST :::::: " << filePath << "\n";

		std::ifstream theFile(filePath.c_str());

		retVal.setName(t_getFileNameFromPath(filePath));

		if (!theFile.fail())
		{
			std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), 
			std::istreambuf_iterator<char>());

			buffer.push_back('\0');
			// Parse the buffer using the xml file parsing library into doc 
			t_packet.parse<0>(buffer.data());

			std::string packetTexturePath = t_getPathName(filePath);
			packetTexturePath.append("/");

			t_TextureAtlas = t_packet.first_node("TextureAtlas");
			packetTexturePath.append(t_TextureAtlas->first_attribute("imagePath")->value());
			//std::cout << "Image path is " << packetTexturePath << "\n";
			
			retVal.setTexturePath(packetTexturePath);
			
			for (xml_node<> * sprite_node = t_TextureAtlas->first_node("sprite"); sprite_node; sprite_node = sprite_node->next_sibling())
			{
				//std::cout << "creating sprite ..... \n";

				Feintgine::F_Sprite t_sprite;
				
				glm::vec2 anchor = glm::vec2(0.5f);
				if (sprite_node->first_attribute("pX") && sprite_node->first_attribute("pX"))
				{
					anchor = t_convertStringToVec2(sprite_node->first_attribute("pX")->value(), sprite_node->first_attribute("pY")->value());
				}
			
				t_sprite.init(t_convertStringToVec2(sprite_node->first_attribute("x")->value(), sprite_node->first_attribute("y")->value()),
					t_convertStringToVec2(sprite_node->first_attribute("w")->value(), sprite_node->first_attribute("h")->value()),
					anchor,
					packetTexturePath.c_str(), retVal.getName(), sprite_node->first_attribute("n")->value());


				// retVal.m_spriteMap.insert(std::make_pair(sprite_node->first_attribute("n")->value(),  std::move(t_sprite)));

				retVal.insertSprite(sprite_node->first_attribute("n")->value(), t_sprite);
				
				// 		m_sprites.push_back(t_sprite);
			}
			
		}
		else
		{
			std::cout << "Error ! File " << filePath << "not exist \n";
		}

		theFile.close();
		return retVal;
	}

	SpriteManager *SpriteManager::p_Instance = 0;

	SpriteManager::SpriteManager()
	{
		half_threads = std::thread::hardware_concurrency() / 2;
		target_threads = max_threads;
		//m_FutureMap.
	}


	SpriteManager::~SpriteManager()
	{
	}


	int SpriteManager::scan_dir(const std::string & path, int level)
	{
        //std::cout << "scan on " << path << "\n";
        //std::cout << "level start -----" << level << "\n";
        DIR *dir = nullptr;
        struct dirent *entry = nullptr;

        if (!(dir = opendir(path.c_str())))
        {
            std::cout << "dir failed \n";
            return 0;
        }

        if (!(entry = readdir(dir)))
        {
            std::cout << "entry failed \n";
            return 0;
        }
        do
        {
            if (entry->d_type == DT_DIR)
            {
                std::string sub_path = path + "/" + entry->d_name;
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                {
                    continue;
                }

                scan_dir(sub_path, level + 1);
            }
            else
            {
				std::string texturePath(path + "/" + entry->d_name);
				if (texturePath.find("Packets/") != std::string::npos)
				{
					if (texturePath.find(".xml") != std::string::npos)
					{
						std::string packetKey = t_getFileNameFromPath(texturePath);

						m_storedPaths[m_indexCount].emplace(texturePath);
						m_indexCount++;
						if(m_indexCount == target_threads)
						{
							m_indexCount = 0;
						}
						m_storedKey.emplace_back(packetKey);
						m_storedPacketCount++;
					}
				}
            }
        } while (entry = readdir(dir));

        closedir(dir);
       // std::cout << "level end -----" << level << "\n";
        return 0;
    }


	void SpriteManager::loadTStoredPackets(int index)
	{
		while(m_storedPaths[index].size() > 0)
		{
			SpritePacket spritePacket;
		
			spritePacket.loadPacket(m_storedPaths[index].front());
			std::string packetKey = t_getFileNameFromPath(m_storedPaths[index].front());

			m_SpritePackets.insert(std::make_pair(packetKey.c_str(), std::move(spritePacket)));
			m_packetCount++;
			m_storedPaths[index].pop();
			std::cout << "loaded " << m_packetCount << "/" << m_storedPacketCount << "(thread " << index << ")\n";

		}
	}

	void SpriteManager::loadSpritePacket(const std::string & filePath)
	{
		SpritePacket spritePacket;
		
		spritePacket.loadPacket(filePath);
		
		std::string packetKey = t_getFileNameFromPath(filePath);

		m_SpritePackets.insert(std::make_pair(packetKey.c_str(), std::move(spritePacket)));
	}


	void SpriteManager::printPacketList()
	{
		std::cout << "************** PRINT SPRITE PACKET LIST ******************\n";
		std::map<std::string, SpritePacket>::iterator it;
		for (it = m_SpritePackets.begin(); it != m_SpritePackets.end(); it++)
		{
			std::cout << it->first << "\n";
			std::cout << "with " << it->second.getSpriteMap().size() << "\n";
		}
	}

	int SpriteManager::loadFromDirectory(const char * name, int level)
	{

		// m_FutureMap.reserve(MAX_PACKET_SIZE); old way
		m_storedKey.reserve(MAX_PACKET_SIZE);
		for(int i = 0 ; i < target_threads ; i++)
		{
			m_storedPaths.push_back(std::queue<std::string>());
		}
		scan_dir(name, level);

		for(int i = 0 ; i < target_threads ; i++)
		{
			std::thread loader(std::bind(&SpriteManager::loadTStoredPackets, this,i));
			m_threads.push_back(std::move(loader));

		}

		for(int i = 0 ; i < m_threads.size() ; i++)	
		{
			m_threads[i].join();
		}

		std::cout << "back to main thread \n";

		// back to main thread
		auto textureBuffers = A_Context_saver::getContext_saver()->getTextureBuffers();
		GLTexture t_texture;
		for(int i = 0; i < textureBuffers.size(); i++)
		{
			
			t_texture =  ResourceManager::getTexture(textureBuffers[i].filePath);


			glGenTextures(1, &t_texture.id);
			auto out = std::move(textureBuffers[i].buffer);
			glBindTexture(GL_TEXTURE_2D, t_texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,t_texture.width, t_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			ResourceManager::rewriteTexture(textureBuffers[i].filePath, t_texture);
		}

		std::cout << "update buffer texture OK \n";
		for(int i = 0 ; i < m_storedPacketCount; i++)
		{
			m_SpritePackets[m_storedKey[i]].updateTexture();
		}
		std::cout << "loaded using " << target_threads << " thread(s) \n";

		return 0;
	}

	bool SpriteManager::isLoadingDone()
	{
		return m_packetCount >= m_SpritePackets.size();

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

	Feintgine::SpritePacket SpriteManager::getSpritePacketByName(const std::string & name)
	{
		std::map<std::string, SpritePacket >::iterator it;
		//std::cout << "data input " << name.c_str() << "\n ";

		it = m_SpritePackets.find(name);

		//std::cout << "look in " << m_SpritePackets.size() << " packet(s) \n";

		if (it != m_SpritePackets.end())
		{
			return it->second;
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
		return getSpritePacketByName(packetName).getSpriteByName(spriteName);
	}

}

