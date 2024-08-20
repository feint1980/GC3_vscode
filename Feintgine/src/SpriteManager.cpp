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


	int SpriteManager::scan_dir(const std::string & path, int level)
	{
        std::cout << "scan on " << path << "\n";
        //std::cout << "level start -----" << level << "\n";
        DIR *dir;
        struct dirent *entry;

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

                printf("%*s[%s]\n", level * 2, "", entry->d_name);
                //std::cout << "path -> " << sub_path << "\n";

                scan_dir(sub_path, level + 1);
            }
            else
            {
				std::string texturePath(path + "/" + entry->d_name);
				if (texturePath.find("Packets/") != std::string::npos)
				{
					if (texturePath.find(".xml") != std::string::npos)
					{
						std::string packetKey = feint_common::Instance()->getFileNameFromPath(texturePath);
						SpritePacket spritePacket(texturePath);
						m_SpritePackets.insert(std::make_pair(packetKey.c_str(),   std::move(spritePacket)));
						m_storedKey.push_back(packetKey);
						// std::thread t = std::thread([this, packetKey](){
					
						// 	m_SpritePackets[packetKey].selfLoad();
						// 	m_packetCount++;
						// });
						// if(t.joinable())
						// {
						// 	t.join();
						// }
						//t.detach();

						//m_Threads.push_back(std::move(t));

                		//files.push_back(file(texturePath));
               	 		//std::cout << "||||: " << texturePath << "\n";
					}
				}
            }
        } while (entry = readdir(dir));

        closedir(dir);
       // std::cout << "level end -----" << level << "\n";
        return 0;
    }


	void SpriteManager::loadSpritePacket(const std::string & filePath)
	{
		//m_Mutex.lock();

		SpritePacket spritePacket;
		//spritePacket = new SpritePacket();


		//m_Mutex.try_lock();
		//

		spritePacket.loadPacket(filePath);
		//std::string packetKey = filePath;
		std::string packetKey = feint_common::Instance()->getFileNameFromPath(filePath);

		//m_Mutex.lock();
		m_SpritePackets.insert(std::make_pair(packetKey.c_str(), std::move(spritePacket)));
		//m_Mutex.unlock();
		// std::cout << "inserted " << packetKey << "\n";
		// std::cout << "size " << m_SpritePackets.size() << "\n";
		//m_Mutex.unlock();
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



	int SpriteManager::loadFromDirectory(const char * name, int level)
	{

	 	scan_dir(name, level);
		int total_files = m_SpritePackets.size();
		int begin = 0;
		int end;
		int chunk;
		int redefinedMaxThreads = max_threads / 2;
		if(total_files > redefinedMaxThreads)
		{
			chunk = total_files / redefinedMaxThreads;

		}
		else
		{
			chunk = 1;
		}
       int remain_files = total_files % redefinedMaxThreads;

		for (int i = 0; i < std::min(redefinedMaxThreads, total_files); ++i)
        {
            end = begin + chunk - 1 +
			 (remain_files + (i + 1) * chunk == total_files ? remain_files : 0);

            std::thread t = std::thread([this, begin, end](){
			for(int i = begin; i <= end; ++i)
			{
                m_SpritePackets.find(m_storedKey[i].c_str())->second.selfLoad();
				//std::cout << "thread " << i << " " << m_storedKey[i].c_str() <<  " done \n";
				m_packetCount++;
			}
            });
            m_Threads.push_back(std::move(t));
            begin = end + 1;
        }

		for(int i = 0; i < m_Threads.size(); i++)
		{
			//m_Threads[i].detach();
			if(m_Threads[i].joinable())
			{
				m_Threads[i].join();
			}
		}

		// Solution 2, faster but cause crash in GC3

		// for(int i = 0 ; i < m_SpritePackets.size(); i++)
		// {
		// 	// m_SpritePackets.find(m_storedKey[i].c_str())->second.selfLoad();
		// 	// m_packetCount++;
		// 	// async::task<void> t = async::spawn([&,i]{
		// 	// 	m_SpritePackets.find(m_storedKey[i].c_str())->second.selfLoad();
		// 	// 	m_packetCount++;
		// 	// });

		// 	//m_tasks.push_back(std::move(t));
		// 	// std::thread t = std::thread([this,i](){
				
		// 	// 	m_SpritePackets.find(m_storedKey[i].c_str())->second.selfLoad();
		// 	// 	m_packetCount++;
		// 	// });
		// 	// if(t.joinable())
		// 	// {
		// 	// 	t.join();
		// 	// }
		// 	//m_Threads.push(std::move(t));
		// 	//m_Threads.push_back(t);
		// 	//if(t.)
		// 	// t.join();
		// 	//m_Threads.push_back(std::move(t));
		// }



		// while(!m_Threads.empty())
		// {
		// 	if(m_Threads.top().joinable())
		// 	{
		// 		m_Threads.top().join();
		// 		m_Threads.pop();
		// 	}
		// }
		// for(int i = 0; i < m_tasks.size(); i++)
		// {

		// 	m_tasks[i].wait();

		// }
		// async::when_all(m_tasks.begin(), m_tasks.end()).then([&]{
		// 	std::cout << "done \n";
		// });
		//}

		// while(!m_packetCount < m_SpritePackets.size())
		// {
		// 	//std::cout << "internal wait\n";
		// }

	
		// while(m_packetCount < m_Threads.size())
		// {
		// 	if(m_Threads[m_packetCount].joinable())
		// 	{
		// 		m_Threads[m_packetCount].join();
		// 		//m_packetCount++;
		// 	}
		// }


		while(m_packetCount < m_SpritePackets.size())
		{
			std::cout << "external wait\n";

		}

		// for(int i = 0; i < m_Threads.size(); i++)
		// {
		// 	//m_Threads[i].detach();
		// 	m_Threads[i].~thread();
		// 	m_Threads.erase(m_Threads.begin() + i);
		// }

		// back to main thread
		auto textureBuffers = A_Context_saver::getContext_saver()->getTextureBuffers();
		for(int i = 0; i < textureBuffers.size(); i++)
		{
			GLTexture t_texture =  ResourceManager::getTexture(textureBuffers[i].filePath);

			glGenTextures(1, &t_texture.id);
			auto out = textureBuffers[i].buffer;
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

		//loop in m_SpritePackets
		for(auto it = m_SpritePackets.begin(); it != m_SpritePackets.end(); it++)
		{

			it->second.updateTexture();
		}
		std::cout << "loaded using " << max_threads << " thread(s) \n";

		return 0;

		// ==============================================================

		// std::cout << "scan on " << name << "\n";
		// DIR *dir;
		// struct dirent *entry;

		// if (!(dir = opendir(name)))
		// {
		// 	std::cout << "dir failed \n";
		// 	return 0;
		// }

		// if (!(entry = readdir(dir)))
		// {
		// 	std::cout << "entry failed \n";
		// 	return 0;
		// }

		// do {
		// 	if (entry->d_type == DT_DIR) {
		// 		char path[1024];
		// 		int len = _snprintf_s(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
		// 		path[len] = 0;
		// 		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		// 			continue;
		// 			printf("%*s[%s]\n", level * 2, "", entry->d_name);
		// 		loadFromDirectory(path, level + 1);
		// 	}
		// 	else
		// 	{
		// 		printf("%*s- %s\n", level * 2, "", entry->d_name);
		// 		std::string texturePath = name;
		// 		texturePath.append("/");
		// 		texturePath.append(entry->d_name);

		// 		if (texturePath.find("Packets/") != std::string::npos)
		// 		{
		// 			if (texturePath.find(".xml") != std::string::npos)
		// 			{

		// 				//m_isDones[m_packetCount] = false;
		// 				//  std::thread t = std::thread([&](){
		// 				// 	loadSpritePacket(texturePath.c_str());
		// 				// 	//m_isDones[m_packetCount] = true;
		// 				// //	std::cout << "hahahaha \n";
		// 				// });
		// 				m_packetCount++;
		// 				m_texturePaths.push_back(texturePath);
		// 				//fileCount++;
		// 				// m_Threads.emplace_back([&](){
		// 				// 	this->loadSpritePacket(texturePath.c_str());
		// 				// });
		// 				// m_Threads.emplace_back([&](){
		// 				// 	this->loadSpritePacket(texturePath.c_str());
		// 				// });
		// 				// auto task = async::spawn([this, texturePath]
		// 				// {
		// 				// 	loadSpritePacket(texturePath.c_str()); // sync`
		// 				// });
		// 				loadSpritePacket(texturePath.c_str()); // sync`
		// 			}
		// 		}

		// 	}


		// } while (entry = readdir(dir));

		// if(level == 0) // end of stack
        // {
		// 	for(int i = 0; i < m_texturePaths.size(); i++)
		// 	{
		// 		m_isLoaded.push_back(false);
		// 	}

        //     std::cout << "call \n";
        //     while(resolved_files < m_packetCount -1  )
        //     {


		// 		for (int i = resolved_files ; i < resolved_files + limited_thread; ++i)
		// 		{

		// 			if (i < m_SpritePackets.size() + limited_thread)
		// 			{
		// 				//std::cout <<  "|i| " << i << "\n";
		// 				// if(!m_isLoaded[i])
		// 				// {
		// 					// std::string texturePath = m_texturePaths[i];
		// 					// std::thread t = std::thread([this, texturePath](){
		// 					// 	loadSpritePacket(texturePath);
		// 					// });
		// 					// std::cout << "create thread " << i << "\n";
		// 					// t.join();
		// 					// auto task = async::spawn([this, texturePath]()
		// 					// {
		// 					// 	this->loadSpritePacket(texturePath);
		// 					// });
		// 				// 	m_isLoaded[i] = true;
		// 				// }

		// 			}
		// 		}
		// 		while (!isDoneBatch())
		// 		{

		// 		}

		// 		std::cout << "|||||||||||||||||||||||||| next batch |||||||||||||||";
        //         resolved_files.fetch_add(limited_thread);
        //         if(resolved_files.load() >= m_packetCount)BackendRendererOpenGL
        //         {
        //             resolved_files.store(m_packetCount) ;
        //         }
		// 	}
		// 	std::cout << "enddddddd !!!!!!!!!!!!!!! \n";
		// }
		// closedir(dir);
		// return 0;
	}


	// bool SpriteManager::isDoneBatch()
	// {
	// 	if(m_SpritePackets.size() >= resolved_files)
    //     {
    //         return true;
    //     }
    //     return false;
	// }

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
			//std::cout << "Found Packet : " << name << '\n';
			//std::cout << it->second.
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

