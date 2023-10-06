#include "F_BaseEnemy.h"
#include <EngineSetting.h>


F_BaseEnemy::F_BaseEnemy()
{
}


F_BaseEnemy::~F_BaseEnemy()
{
}

void F_BaseEnemy::init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::GLTexture & texture)
{
	m_pos = pos;
	m_dim = dim;
	m_texture = texture;
}

void F_BaseEnemy::init(const glm::vec2 & pos, const glm::vec2 & dim, const std::string & animationPath , float heath)
{
	m_pos = pos;
	m_dim = dim;
	isAnimated = true;
	m_animation.init(animationPath);
	m_heath = heath;

}



glm::vec2 F_BaseEnemy::getRotatedVec(const glm::vec2 & t_vel, float angle)
{
	float cs = cos(angle);
	float sn = sin(angle);

	float x = t_vel.x;
	float y = t_vel.y;
	float px = 0;
	float py = 0;
	x = x * cs - y * sn;
	y = x * sn + y * cs;

	x = x * cs - y * sn;
	y = x * sn + y * cs;


	px = x * cs - y * sn;
	py = x * sn + y * cs;

	return glm::vec2(px, py);
}

void F_BaseEnemy::loadLighting(const std::string & name)
{

	xml_document<> doc;
	std::vector<char> buffer = Feintgine::ResourceManager::getPreloadedFile("Data/stageData/lightSet/light.xml");
	doc.parse<0>(&buffer[0]);
	xml_node<> * Lights_node = nullptr;
	Lights_node = doc.first_node("Lights");
	if (!Lights_node)
	{
		std::cout << "Error while parsing light value from F_BaseEnemy.cpp \n";
	}
	else
	{
		for (xml_node<> * Light_node = Lights_node->first_node("Light");
			Light_node; Light_node = Light_node->next_sibling())
		{
			std::string found = Light_node->first_attribute("name")->value();
			
			if (found == name)
			{
				for (xml_node<> * Prop_node = Light_node->first_node("Prop");
					Prop_node; Prop_node = Prop_node->next_sibling())
				{
					//parse offset 
					glm::vec2 offset;
					offset = feint_common::Instance()->convertStringToVec2(Prop_node->first_attribute("offsetX")->value(), Prop_node->first_attribute("offsetY")->value());
					glm::vec3 color;
					color = feint_common::Instance()->convertStringToVec3(Prop_node->first_attribute("cR")->value(), Prop_node->first_attribute("cG")->value(), Prop_node->first_attribute("cB")->value());
					glm::vec3 attenuation;
					attenuation = feint_common::Instance()->convertStringToVec3(Prop_node->first_attribute("aX")->value(), Prop_node->first_attribute("aY")->value(), Prop_node->first_attribute("aZ")->value());
					addLight(offset, color, attenuation);

				}

			}
		}
	}

}

void F_BaseEnemy::drawLight(Feintgine::LightBatch & lightBatch)
{
	for (auto i = 0; i < m_lights.size(); i++)
	{
		lightBatch.addLight(m_pos + m_lights[i].pos, m_lights[i].color , m_lights[i].attenuation);
	}
	
}

void F_BaseEnemy::addLight(const glm::vec2 & offset, const glm::vec3 & color, const glm::vec3 & attenuation)
{

	glm::vec4 t_color = glm::vec4(color.r, color.g, color.b, 1.0f);
	Feintgine::Light light(offset, t_color, attenuation);
	m_lights.push_back(light);

}


void F_BaseEnemy::initShield(const std::string & animationPath, const glm::vec2 & pos, float scale)
{
	if (!m_shield)
	{
		// only create once ( no re-init)
		m_shield = new GuardianShield(animationPath, pos, scale);
		//m_shield->init(animationPath, pos, scale);
		
		
	}
	
}

void F_BaseEnemy::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

float F_BaseEnemy::getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;

	return n1 + (diff * perc);
}

void F_BaseEnemy::playAnim(const std::string & animName, int time)
{
	if (isAnimated)
	{
		m_animation.playAnimation(animName,time);
	}
}

void F_BaseEnemy::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!isAnimated)
	{
		const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);

		float t_x = 0.0f;
		glm::vec4 desRect;
		desRect.x = m_pos.x - m_dim.x / 2.0f;
		desRect.y = m_pos.y - m_dim.y / 2.0f;
		desRect.z = m_dim.x;
		desRect.w = m_dim.y;
		spriteBatch.draw(desRect, uvrect, m_texture.id, m_depth, m_color, m_angle);
	}
	else
	{
		//std::cout << "this is why \n";
		m_animation.draw(spriteBatch);
	}
	if (m_shield)
	{
		m_shield->draw(spriteBatch);
	}
// 	for (int i = 0; i < m_bullets.size(); i++)
// 	{
// 		m_bullets[i]->draw(spriteBatch);
// 	}
}

void F_BaseEnemy::takeDamage(float dmg, bool playSound)
{
	m_heath = m_heath - dmg;
	
	if (m_heath < 0)
	{
		m_isAlive = false;
		
	}
}

void F_BaseEnemy::addEvent(const Feintgine::oEvent::f_callback &cb,  double when)
{
	//double real_when = Feintgine::F_oEvent::convertMSToS(when);
	event_queue.emplace(cb, when);
}



void F_BaseEnemy::clearEvent()
{
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
}

void F_BaseEnemy::timer()
{
	while (!event_queue.empty() &&
		(event_queue.top().when < ENGINE_current_tick))
	{
		//std::cout << "exccute event at " << event_queue.top().when << "\n";
		event_queue.top()();
		event_queue.pop();
	}
}

void F_BaseEnemy::registerAudio(Feintgine::AudioEngine * engine)
{
	m_audioEngine = engine;
}

void F_BaseEnemy::drawBullet(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
}

void F_BaseEnemy::updateBullet(float deltaTime)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(deltaTime);
	}

}

void F_BaseEnemy::setPriority(int val)
{
	m_priority = val;
}

