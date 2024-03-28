#include "F_AnimatedObject.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iostream>
//#include <>
namespace Feintgine
{



	F_AnimatedObject::F_AnimatedObject()
	{
		m_animations.clear();
		//std::cout << "called \n";
		m_currentAnimation = nullptr;
	}


	F_AnimatedObject::~F_AnimatedObject()
	{
		m_animations.clear();
		m_currentAnimation = nullptr;
	}

	void F_AnimatedObject::init(const std::string & filePath,const glm::vec2 & scaleFactor)
	{
		//std::cout << "init animate object " << filePath << " \n";
		m_filePath = filePath;
		m_animations.clear();
		m_currentAnimation = nullptr;
		m_scale = scaleFactor;
		xml_document<> doc;

// 		std::ifstream file(m_filePath.c_str());
// 		if (!file)
// 		{
// 			std::cout << "nothing found \n";
// 			return;
// 		}
		
// 		std::vector<char> buffer(std::istreambuf_iterator<char>(filePath),
// 			std::istreambuf_iterator<char>());
		//std::ifstream file(filePath.c_str());
		//std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		//buffer.push_back('\0');
		std::vector<char> buffer = ResourceManager::getPreloadedFile(m_filePath.c_str());  //((std::istreambuf_iterator<char>(filePath)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		//ResourceManager::getPreloadedFile(m_filePath.c_str());
		doc.parse<0>(&buffer[0]);

		xml_node<> * F_AObj_node = nullptr;
		F_AObj_node = doc.first_node("F_AObj");
		
		if (!F_AObj_node)
		{
			std::cout << "Error while parsing value F_AnimatedObject.cpp \n";
		}
		m_name = F_AObj_node->first_attribute("name")->value();

		xml_node<> * animations_node = F_AObj_node->first_node("animations");

		for (xml_node<> * animation_node = animations_node->first_node("animation");
			animation_node; animation_node = animation_node->next_sibling())
			{
				F_Animation t_animation;
				t_animation.create(animation_node->first_attribute("name")->value());
			
				xml_node<> * anims_node = animation_node->first_node("anims");
				for (xml_node<> * anim_node = anims_node->first_node("anim");
					anim_node; anim_node = anim_node->next_sibling())
				{
					f_anim anim;
					anim.sprite = SpriteManager::Instance()->getSprite(anim_node->first_attribute("name")->value());
					std::cout << "anim "  << anim.sprite.getTexture().id << "\n";
					anim.time = std::stof(anim_node->first_attribute("time")->value());
					glm::vec2 offset;
					bool isLoop = false;
					if (anim_node->first_attribute("loop"))
					{
					//	std::cout << "found loop \n";
					
						isLoop = true;
						
					}
					if (anim_node->first_attribute("inverted"))
					{
						//	std::cout << "found loop \n";

						anim.sprite.setInvert(true);

					}
					if (anim_node->first_attribute("offset_x"))
					{
						offset.x = std::stof(anim_node->first_attribute("offset_x")->value());
					}
					if (anim_node->first_attribute("offset_y"))
					{
						offset.y = std::stof(anim_node->first_attribute("offset_y")->value());
					}
					anim.offset = offset;
					t_animation.addAnim(anim,isLoop);
					//std::cout << t_animation.getAnimName() << "\n";
				}
			//m_testAnims.push_back(t_animation);
			//std::cout << "loading " << t_animation.getAnimName() << "\n";
			m_animations.insert(std::pair<std::string, F_Animation>(t_animation.getAnimName(), t_animation));
//  			{
//  				//std::cout << "added animation " << t_animation.getAnimName() << " successfully \n";
//  			}
//  			else
//  			{
//  				//std::cout << "failed to add animation " << t_animation.getAnimName() << " \n";
//  			}
		}
		m_isInited = true;

		// if(m_animations.size() > 0)
		// {
		// 	std::string animName = m_animations.begin()->first;
		// 	playAnimation(animName);
		// }
		//std::cout << "loaded " << m_name << "with " << m_testAnims.size() << " anims \n";
		//m_currentAnimation = &m_animations.begin()->second;

	}

	void F_AnimatedObject::saveToFile(const std::string & name)
	{
		std::string finalName = "Assets/F_AObjects/" + name + ".xml";
		if (feint_common::Instance()->isFileExist(finalName))
		{
			std::cout << "file exist \n";
		}
		else
		{
			std::cout << "file does not exist \n";
		}
		xml_document<> doc;
		xml_node<> * F_AObj_node = doc.allocate_node(node_element,"F_AObj");
		F_AObj_node->append_attribute(doc.allocate_attribute("name", name.c_str()));
		xml_node<> * animations_node = doc.allocate_node(node_element,"animations");
		F_AObj_node->append_node(animations_node);

		
		for (auto it = m_animations.begin(); it != m_animations.end(); it++)
		{
		
			xml_node<> * animation_node = doc.allocate_node(node_element,"animation");
			animation_node->append_attribute(doc.allocate_attribute("name", it->first.c_str()));
			xml_node<> * anims_node = doc.allocate_node(node_element,"anims");
			animation_node->append_node(anims_node);
			std::string nameValue = "";
			std::string timeValue = "";	
			std::string oXValue = "";
			std::string oYValue = "";
			for (auto i = 0; i < it->second.getAnims().size(); i++)
			{
			//	std::cout << "write loop " << i << "\n";
				
				std::string packetName = it->second.getAnims()[i].sprite.getPacketName().c_str();
				size_t lastindex = packetName.find_last_of(".");
				std::string rawname = packetName.substr(0, lastindex);
				std::string spriteName = it->second.getAnims()[i].sprite.getName().c_str();


				nameValue = rawname +"/"+ spriteName;
				const std::string::size_type size = nameValue.size();
				char *buffer = new char[size + 1];   //we need extra char for NUL
				
				memcpy(buffer, nameValue.c_str(), size + 1);
				xml_node<> * anim_node = doc.allocate_node(node_element,"anim");
				//std::string trimedPacket = feint_common::Instance()->getFileNameFromPath(it->second.getAnims()[i].sprite.getPacketName());
				
				
				anim_node->append_attribute(doc.allocate_attribute("name", buffer));
				
				timeValue = feint_common::Instance()->convertPreciousFloatToString(it->second.getAnims()[i].time);
				const std::string::size_type size2 = timeValue.size();
				char *buffer2 = new char[size2 + 1];   //we need extra char for NUL
				
				memcpy(buffer2, timeValue.c_str(), size2 + 1);
				

 				anim_node->append_attribute(doc.allocate_attribute("time",
					buffer2));


				 oXValue = feint_common::Instance()->convertPreciousFloatToString(it->second.getAnims()[i].offset.x);
				 oYValue = feint_common::Instance()->convertPreciousFloatToString(it->second.getAnims()[i].offset.y);
				//oXValue = std::to_string(it->second.getAnims()[i].offset.x);
				//oYValue = std::to_string(it->second.getAnims()[i].offset.y);

				const std::string::size_type size3 = oXValue.size();
				char *buffer3 = new char[size3 + 1];   //we need extra char for NUL

				memcpy(buffer3, oXValue.c_str(), size3 + 1);
				
				anim_node->append_attribute(doc.allocate_attribute("offset_x",
					buffer3));
				
				const std::string::size_type size4 = oYValue.size();
				char *buffer4 = new char[size4 + 1];   //we need extra char for NUL

				memcpy(buffer4, oYValue.c_str(), size4 + 1);

				anim_node->append_attribute(doc.allocate_attribute("offset_y",
					buffer4));
				
				if (i == it->second.getLoopAnim())
				{
					anim_node->append_attribute(doc.allocate_attribute("loop",
						"1"));
				}
				if (it->second.getAnims()[i].sprite.isInverted())
				{
					anim_node->append_attribute(doc.allocate_attribute("inverted",
						"1"));
				}


 				anims_node->append_node(anim_node);
			}
			
			animations_node->append_node(animation_node);
		}
		doc.append_node(F_AObj_node);
		std::cout << "write " << m_name << " to " << finalName << "\n";
		std::ofstream fileSave(finalName);
		fileSave << doc;
		fileSave.close();
		doc.clear();
		std::cout << "process done\n";
	}

	void F_AnimatedObject::addNewAnimation(const std::string & name)
	{
		F_Animation t_animation;
		if (m_animations.insert(std::pair<std::string, F_Animation>(name, t_animation)).second)
		{

			std::cout << "successfuly added animation " << name << "\n";
		}
		
	}

	void F_AnimatedObject::removeAnimation(const std::string & name)
	{
		auto it = m_animations.find(name);
		if (it != m_animations.end())
		{
			m_animations.erase(it->first);
		}
	}

	void F_AnimatedObject::playAnimation(const std::string & name, int time)
	{
		//std::cout << "play animation " << name << "\n";
		if (m_currentAnimation)
		{
			m_currentAnimation->stop();
		//	m_currentAnimation->resetAnim();
		}
		
		auto it = m_animations.find(name);
		if (it != m_animations.end())
		{
			m_currentAnimation = &it->second;
			if (m_currentAnimation)
			{
				m_currentAnimation->playAnimation(time);
				m_currentAnimationGuard = std::make_shared<F_Animation>(*m_currentAnimation);
			}
			//else
			//{
			//	m_currentAnimation->stop();
				//m_currentAnimation->resetAnim();
				//std::cout << "not play \n";
			//}
		}
	//	else
	//	{
			//m_currentAnimation->stop();
			//m_currentAnimation->resetAnim();
			//std::cout << "animation " << name << " not found !\n";
	//	}

	
	}

	void F_AnimatedObject::setAnimation(const std::string & name)
	{
		m_currentAnimation = nullptr;
		auto it = m_animations.find(name);
		
		if (it != m_animations.end())
		{
			m_currentAnimation = &it->second;
			if (m_currentAnimation)
			{
				//std::cout << "animation found \n";
				m_currentAnimation->setAnimation();
			}
			else
			{
			
				m_currentAnimation = nullptr;
				std::cout << "setAnimation failed, cannot find the animation " + name << "\n";
			}
		}
		else
		{
			std::cout << "animation " << name << " not found !\n";
		}
	}
	
	void F_AnimatedObject::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		//std::cout << "step 1 \n";
		if (m_currentAnimation)
		{
			//std::cout << "step 2 \n";
			if (m_currentAnimation->getCurrentIndex() != -1)
			{
				//std::cout << "step 3 \n";
				if (&m_currentAnimation->getAnims()[m_currentAnimation->getCurrentIndex()])
				{
					//std::cout << "step 4 \n";
					glm::vec4 desRect;// (0, 0, 50, 50);

					int t_index = m_currentAnimation->getCurrentIndex();
					glm::vec2 totalPos = m_pos +m_currentAnimation->getAnims()[t_index].offset * m_scale;
					//std::cout << m_currentAnimation->getCurrentAnim()->sprite.getName() << "\n";

					F_Sprite tSprite = m_currentAnimation->getAnims()[t_index].sprite;
					desRect.x = totalPos.x - tSprite.getDim().x * m_scale.x / 2.0f;
					desRect.y = totalPos.y - tSprite.getDim().y * m_scale.y / 2.0f;
					desRect.z = m_scale.x * tSprite.getDim().x ;
					desRect.w = m_scale.y * tSprite.getDim().y ;

					spriteBatch.draw(desRect, tSprite.getUV(),
						tSprite.getTexture().id, m_depth, m_color, m_angle);
					//std::cout << "draw function \n";
					//std::cout << m_currentAnimation->getAnims()[m_currentAnimation->getCurrentIndex()].sprite.getName() << "\n";
				}
			}
		}
	}

	void F_AnimatedObject::update(float deltaTime)
	{
		if (m_currentAnimation)
		{
			m_currentAnimation->updateAnim(deltaTime);
		}
	}

	void F_AnimatedObject::setDepth(float depth)
	{
		m_depth = depth;
	}

	void F_AnimatedObject::setAngle(float angle)
	{
		m_angle = angle;
	}

	void F_AnimatedObject::rotate(float angle)
	{
		m_angle += angle;
	}

	void F_AnimatedObject::setAlpha(float alpha)
	{
		m_color.a = alpha;
	}

	void F_AnimatedObject::setScale(const glm::vec2 & scale)
	{
		m_scale = scale;
	}

	void F_AnimatedObject::setPos(const glm::vec2 & pos)
	{
		m_pos = pos;
	}

	void F_AnimatedObject::setVisisble(bool val)
	{
		m_isVisible = val;
	}


	void F_AnimatedObject::setColor(const Feintgine::Color & color)
	{
		m_color = color;
	}

	bool F_AnimatedObject::changeColor(int channel, float rate, float maxVal)
	{
		return m_color.change(channel, rate, maxVal);
	}

	// 	void f_animation::updateAnim(float deltaTime)
// 	{
// 
// 		
// 		if (m_anims.size() > 1)
// 		{
// 			//std::cout << "data " << m_animName << " " << m_anims.size() << "\n";
// 			/*I don't know why, I don't want to know why, I wonder how I got here is the first place, but it will
// 			cause problem that animation on 60hz monitor will be slower than 144hz monitor unless I do this horrible thing */
// 			if (deltaTime > 0.95f)
// 			{
// 				deltaTime = 1.0f;
// 			}
// 			// End of work around 
// 			if (m_currentSprite)
// 			{
// 				if (m_currentSprite->sprite.getTexture().id > 0)
// 				{
// 
// 
// 					if (m_time > 0)
// 					{
// 						if (m_playing)
// 						{
// 
// 							m_animTime += (m_animSpeed * deltaTime);
// 							//std::cout << m_animTime << "\n";
// 							if (m_animTime >= m_currentSprite->time)
// 							{
// 								m_curIndex++;
// 								m_animTime = 0.0f;
// 								if (m_curIndex >= m_anims.size())
// 								{
// 									m_curIndex = m_loop;
// 									m_time--;
// 									if (m_time == 0)
// 									{
// 										m_playing = false;
// 									}
// 								}
// 
// 							}
// 							if (m_curIndex >= 0)
// 							{
// 
// 								if (m_curIndex <= m_anims.size())
// 								{
// 									m_currentSprite = &m_anims[m_curIndex];
// 								}
// 
// 							}
// 
// 						}
// 
// 					}
// 					else if (m_time < 0)
// 					{
// 						if (m_playing)
// 						{
// 							if (m_currentSprite)
// 							{
// 								m_animTime += (m_animSpeed  * deltaTime);
// 								//std::cout << m_animTime << "\n";
// 								if (m_animTime >= m_currentSprite->time)
// 								{
// 									m_animTime = 0.0f;
// 									m_curIndex++;
// 									if (m_curIndex >= m_anims.size())
// 									{
// 										m_curIndex = m_loop;
// 									}
// 
// 								}
// 								if (m_curIndex <= m_anims.size())
// 								{
// 									m_currentSprite = &m_anims[m_curIndex];
// 								}
// 							}
// 						}
// 
// 						//davai
// 					}
// 				}
// 			}
// 		}
// 		
// 
// 		//davai2
// 	}
}
