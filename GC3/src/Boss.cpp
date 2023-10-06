// #include "Boss.h"
// 
// 
// 
// void Boss::init(const glm::vec2 &positon, const glm::vec2 &dimentions, Feintgine::GLTexture texture, glm::vec2 sheetRes, Feintgine::Color &color, std::string name)
// {
// 	m_postion = positon;
// 	m_dimentions = dimentions;
// 	m_color = color;
// 	m_spriteSheet.init(texture, sheetRes);
// 	m_name = name;
// 	loadInfo();
// }
// 
// 
// 
// 
// void Boss::setColor(const Feintgine::Color &color)
// {
// 	m_color = color;
// }
// 
// void Boss::draw(Feintgine::SpriteBatch & spriteBatch)
// {
// 	glm::vec4 destRect;
// 	destRect.x = m_postion.x - m_dimentions.x / 2.0f;
// 	destRect.y = m_postion.y - m_dimentions.y / 2.0f;
// 	destRect.z = m_dimentions.x;
// 	destRect.w = m_dimentions.y;
// 
// 	glm::vec4 uvRect = m_spriteSheet.getUVs(m_tileIndex);
// 
// 	if (m_direction == -1) {
// 
// 		uvRect.x += 1.0f / m_spriteSheet.dims.x;
// 		uvRect.z *= -1;
// 	}
// 	spriteBatch.drawLight(destRect, uvRect, m_depth, m_color,  1.0f,1.0f);
// }
// 
// 
// 
// void Boss::playAnimation(std::string name, bool loop)
// {
// 	m_isPlayAnim = true;
// 	m_anim_name = name;
// 	currentTick = SDL_GetTicks();
// 	iterator = 0;
// 	m_isLoop = loop;
// }
// 
// void Boss::updateAnim()
// {
// 	
// 	if(m_isPlayAnim)
// 	{
// 	
// 		
// 		if (iterator >= m_animMap[m_anim_name].size())
// 		{
// 			if (!m_isLoop)
// 			{
// 				m_isPlayAnim = false;
// 				m_tileIndex = 0;
// 				m_anim_name = "";
// 			}
// 			else
// 			{
// 				playAnimation(m_anim_name);
// 			}
// 		
// 		}
// 		
// 		
// 	
// 		//	totalTick += m_animMap[m_anim_name][i].tick;
// 			
// 		else
// 		{
// 			if (SDL_GetTicks() < currentTick + m_animMap[m_anim_name][iterator].tick)
// 			{
// 				m_tileIndex = m_animMap[m_anim_name][iterator].tileIndex;
// 			}
// 			else
// 			{
// 				currentTick = SDL_GetTicks();
// 				iterator++;
// 			}
// 		}
// 	
// 	}
// 	
// 
// 	
// }
// 
// void Boss::loadInfo()
// {
// 	//std::cout << "Load character : " << m_name << "\n";
// 
// 	xml_document<> doc; 
// 	xml_node<> * animList = nullptr;
// 	string converted= "Data/bossInfo/";
// 	converted.append(m_name);
// 	converted.append(".xml");
// 
// 	ifstream theFile(converted);
// 	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
// 	buffer.push_back('\0');
// 	// Parse the buffer using the xml file parsing library into doc 
// 	doc.parse<0>(&buffer[0]);
// 	// Find our root node
// 	//root_node = doc.first_node("MyBeerJournal");
// 	
// 	animList = doc.first_node("AnimationList");
// 
// 	
// 	for (xml_node<> * anim_node = animList->first_node("Anim"); anim_node; anim_node = anim_node->next_sibling())
// 	{
// 		for (xml_node<> * key_node = anim_node->first_node("Key"); key_node; key_node = key_node->next_sibling())
// 		{
// 			int index = std::stoi(key_node->first_attribute("tileindex")->value());
// 			float t = std::stof(key_node->first_attribute("tick")->value());
// 
// 
// 			anim temp = anim(index, t);
// 			m_animMap[anim_node->first_attribute("name")->value()].push_back(temp);
// 		}
// 	}
// 	
// 
// 	//cout << m_animMap[ANIM->first_attribute("name")->value()].size();
// 	
// 
// 	//check debug anim read
// // 	for (it_type iterator = m_animMap.begin(); iterator != m_animMap.end(); iterator++) {
// // 		cout << iterator->first <<"\n";
// // 		
// //  		for (int i = 0; i < iterator->second.size(); i++)
// // 		{
// //  			cout << iterator->second[i].tileIndex << "\t" << iterator->second[i].tick << "\n";
// //  		}
// // 	}
// 
// 
// 	
// 
// 
// 
// }
// 
// void Boss::setDepth(float depth)
// {
// 	m_depth = depth;
// }
// 
// 
