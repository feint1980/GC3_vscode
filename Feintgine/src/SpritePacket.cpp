#include "SpritePacket.h"


namespace Feintgine {



	SpritePacket::SpritePacket()
	{
	}


	SpritePacket::SpritePacket(const std::string &filePath)
	{
		loadPacket(filePath);
	}

	SpritePacket::~SpritePacket()
	{
	}

	void SpritePacket::loadPacket(const std::string & filePath)
	{
		//TODO : load sprite from XML (note, each sprite does not save their name, this packet ( key of map ) does )
		xml_document <> t_packet;
		xml_node<> * t_TextureAtlas;

		//std::cout << "TEST :::::: " << filePath << "\n";

		std::ifstream theFile(filePath.c_str());

		m_name = feint_common::Instance()->getFileNameFromPath(filePath);

		if (!theFile.fail())
		{



			std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');
			// Parse the buffer using the xml file parsing library into doc 
			t_packet.parse<0>(buffer.data());

			std::string packetTexturePath = feint_common::Instance()->getPathName(filePath);
			packetTexturePath.append("/");



			t_TextureAtlas = t_packet.first_node("TextureAtlas");
			packetTexturePath.append(t_TextureAtlas->first_attribute("imagePath")->value());
			//std::cout << "Image path is " << packetTexturePath << "\n";
			m_texturePath = packetTexturePath;
			for (xml_node<> * sprite_node = t_TextureAtlas->first_node("sprite"); sprite_node; sprite_node = sprite_node->next_sibling())
			{
				//std::cout << "creating sprite ..... \n";

				Feintgine::F_Sprite t_sprite;
				//t_sprite = new F_Sprite();
				//std::cout << "loading sprite " << sprite_node->first_attribute("n")->value() << "\n";
				//std::cout << "pos X " << sprite_node->first_attribute("x")->value() << "\n";
				//std::cout << "pos Y " << sprite_node->first_attribute("y")->value() << "\n";
				//std::cout << "total " << feint_common::Instance()->convertVec2toString(feint_common::Instance()->convertStringToVec2(sprite_node->first_attribute("x")->value(), sprite_node->first_attribute("y")->value()));
				glm::vec2 anchor = glm::vec2(0.5f);
				if (sprite_node->first_attribute("pX") && sprite_node->first_attribute("pX"))
				{
					anchor = feint_common::Instance()->convertStringToVec2(sprite_node->first_attribute("pX")->value(), sprite_node->first_attribute("pY")->value());
				}

				 
				t_sprite.init(feint_common::Instance()->convertStringToVec2(sprite_node->first_attribute("x")->value(), sprite_node->first_attribute("y")->value()),
					feint_common::Instance()->convertStringToVec2(sprite_node->first_attribute("w")->value(), sprite_node->first_attribute("h")->value()),
					anchor,
					packetTexturePath.c_str(), m_name, sprite_node->first_attribute("n")->value());
				m_spriteMap.insert(std::make_pair(sprite_node->first_attribute("n")->value(), t_sprite));
				// 		m_sprites.push_back(t_sprite);
			}

			//std::cout << " total " << m_spriteMap.size() << " loaded \n";
			//std::cout << " here are the list >>>>>> \n";

// 			std::map<std::string, Feintgine::F_Sprite>::iterator it;
// 			for (it = m_spriteMap.begin(); it != m_spriteMap.end(); it++)
// 			{
// 				std::cout << it->second.getName() << "\n";
// 
// 			}
		}
		else
		{
			std::cout << "Error ! File " << filePath << "not exist \n";
		}


	}

	void SpritePacket::writeToImageset(const std::string & name)
	{
		const std::string GUIPath = "E:/template/my_last/GC3/Gansokyo/GUI/";

		size_t lastindex = name.find_last_of(".");
		std::string rawname = name.substr(0, lastindex);

		std::string textureFile = feint_common::Instance()->getFileNameFromPath(m_texturePath);
		std::string textureFullpath = GUIPath + textureFile;

		xml_document<> doc;
		xml_node<> * root_node = doc.allocate_node(node_declaration);
		root_node->append_attribute(doc.allocate_attribute("version", "1.0"));
		root_node->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
		doc.append_node(root_node);

		xml_node<>* Imageset_node = doc.allocate_node(node_element, "Imageset");
		Imageset_node->append_attribute(doc.allocate_attribute("version", "2"));
		Imageset_node->append_attribute(doc.allocate_attribute("name", rawname.c_str()));
		Imageset_node->append_attribute(doc.allocate_attribute("imagefile", textureFile.c_str()));
		Imageset_node->append_attribute(doc.allocate_attribute("nativeHorzRes", "800"));
		Imageset_node->append_attribute(doc.allocate_attribute("nativeVertRes", "600"));
		Imageset_node->append_attribute(doc.allocate_attribute("autoScaled", "vertical"));


		std::map<std::string, Feintgine::F_Sprite>::iterator it;
		for (it = m_spriteMap.begin(); it != m_spriteMap.end(); it++)
		{

			xml_node<>* image_node = doc.allocate_node(node_element, "Image");
			image_node->append_attribute(doc.allocate_attribute("name", it->first.c_str()));
			std::string fs;
			char* cstr;
			fs = std::to_string((int)it->second.getDim().y);
			cstr = new char[fs.size() + 1];
			strcpy(cstr, fs.c_str());
			image_node->append_attribute(doc.allocate_attribute("height", cstr));


			fs = std::to_string((int)it->second.getPos().x);
			cstr = new char[fs.size() + 1];
			strcpy(cstr, fs.c_str());
			image_node->append_attribute(doc.allocate_attribute("xPos", cstr));

			fs = std::to_string((int)it->second.getPos().y);
			cstr = new char[fs.size() + 1];
			strcpy(cstr, fs.c_str());
			image_node->append_attribute(doc.allocate_attribute("yPos", cstr));

			fs = std::to_string((int)it->second.getDim().x);
			cstr = new char[fs.size() + 1];
			strcpy(cstr, fs.c_str());
			image_node->append_attribute(doc.allocate_attribute("width", cstr));

			

			// 		image_node->append_attribute(doc.allocate_attribute("yPos", std::to_string(sprite.getPos().y).c_str()));
			// 		image_node->append_attribute(doc.allocate_attribute("width", std::to_string(sprite.getDim().x).c_str()));
			// 		image_node->append_attribute(doc.allocate_attribute("height", std::to_string(sprite.getDim().y).c_str()));



			Imageset_node->append_node(image_node);
		}


		doc.append_node(Imageset_node);

		// Convert doc to string if needed
		std::string xml_as_string;
		rapidxml::print(std::back_inserter(xml_as_string), doc);



		std::string t_imagesetFile = GUIPath + name;
		// Save to file
		std::ofstream file_stored(t_imagesetFile);
		file_stored << doc;
		file_stored.close();
		doc.clear();


		if (copyFile(m_texturePath.c_str(), textureFullpath.c_str()))
		{
			std::cout << "copy successfully ! \n";
		}
		else
		{
			std::cout << "copy failed \n";
		}

	}

	bool SpritePacket::copyFile(const char *SRC, const char* DEST)
	{
		std::ifstream src(SRC, std::ios::binary);
		std::ofstream dest(DEST, std::ios::binary);
		dest << src.rdbuf();
		return src && dest;
	}

	Feintgine::F_Sprite  SpritePacket::getSpriteByName(const std::string & filePath)
	{

		std::map<std::string, Feintgine::F_Sprite >::iterator it;
		Feintgine::F_Sprite returnone;
		it = m_spriteMap.find(filePath);
		if (it != m_spriteMap.end())
		{
			returnone = it->second;
			//std::cout << "Found Sprite : " << filePath << '\n';
			
		}
		else
		{
			std::cout << "Warning : unable to find sprite " << filePath << " return null sprite ";
		}
		return returnone;
	}

}
