#include "EnemyBulletBase.h"
#include "GlobalValueClass.h"
#include <EngineSetting.h>
int def = 0;
int daf = 0;
EnemyBulletBase::EnemyBulletBase()
{
	m_pos = glm::vec2(0.0f, 1200.0f);
}


EnemyBulletBase::~EnemyBulletBase()
{
	m_pos = glm::vec2(0.0f, 1200.0f);
	m_updateFunc = nullptr;
}

void EnemyBulletBase::setLifeTime(float lifeTime)
{
	m_lifeTime = lifeTime;
}

// void EnemyBulletBase::initLogic(b2World * world)
// {
// 	b2BodyDef bodyDef;
// 	bodyDef.type = b2_kinematicBody;
// 	bodyDef.position.Set(m_pos.x, m_pos.y);
// 	m_body = world->CreateBody(&bodyDef);
// 
// 	//b2Shape 
//  	b2CircleShape bulletShape;
// 	
// 	float radius = 0;
// 	radius = std::max(m_sprite.getDim().x, m_sprite.getDim().y) * 0.5f;
// 
// 	if (m_isAnim)
// 	{
// 		if (m_animObj.getCurrentAnimation())
// 		{
// 
// 			Feintgine::F_Sprite t_sprite = m_animObj.getCurrentAnimation()->getAnims()[m_animObj.getCurrentAnimation()->getCurrentIndex()].sprite;
// 			radius = std::max(t_sprite.getDim().x, t_sprite.getDim().y) * 0.5f;
// 		}
// 	}
// 
// 	bulletShape.m_radius = radius;
// 	bulletShape.m_p = b2Vec2(m_pos.x, m_pos.y);
// 
// 	b2FixtureDef fixtureDef;
// 	fixtureDef.shape = &bulletShape;
// 	//fixtureDef.
// 	m_fixture = m_body->CreateFixture(&fixtureDef);
// 
// 	m_body->SetUserData(this);
// }

void EnemyBulletBase::init(const glm::vec2 & pos, const glm::vec2 & scale,
	const Feintgine::F_Sprite & sprite, glm::vec2 vel, 
	std::function<void(float)> updateFunc, float depth)
{
	m_pos = pos;
	m_scale = scale;
	m_vel = vel;
	m_sprite = sprite;
	m_depth = depth;
	m_scale = glm::vec2(1.0f);

}

void EnemyBulletBase::init(const glm::vec2 & pos, const glm::vec2 & scale, 
	const Feintgine::F_AnimatedObject & animObj, glm::vec2 vel,
	std::function<void(float)> updateFunc, float depth)
{
	m_pos = pos;
	m_scale = scale;
	m_vel = vel;
	m_animObj = animObj;
	m_depth = depth;
	m_isAnim = true;
	m_animObj.setDepth(m_depth);
	m_animObj.setScale(m_scale);
}

void EnemyBulletBase::loadPattern(const std::string & pattern)
{

}



void EnemyBulletBase::addEvent(const Feintgine::oEvent::f_callback &cb, double when)
{
	event_queue.emplace(cb, when);
}

void EnemyBulletBase::timer()
{
	while (!event_queue.empty() &&
		(event_queue.top().when < ENGINE_current_tick))
	{
		event_queue.top()();
		event_queue.pop();
	}
}

void EnemyBulletBase::update(float deltaTime)
{
	if (m_updateFunc)
	{
		m_updateFunc(deltaTime);
	}
	else 
	{
		defaultUpdate(deltaTime);
	}
	m_color.a = m_lifeTime;
	timer();
	updateSpeedChange(deltaTime);
}

void EnemyBulletBase::setAngle(float angle)
{

	m_angle = angle;
	if (m_isAnim)
	{
		m_animObj.setAngle(m_angle);
	}
	
}

void EnemyBulletBase::rotate(float angle)
{
	m_angle += angle;
	if (m_isAnim)
	{
		m_animObj.setAngle(m_angle);
	}
}

void EnemyBulletBase::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void EnemyBulletBase::setColor(const Feintgine::Color & color)
{
	m_color = color;
}

void EnemyBulletBase::setSpeedChange(float speedWanted, float time)
{
	//way to calculate m_vel;
// 	glm::vec2 vel = glm::vec2(t_currentSpeed);
// 	m_vel = m_direction* vel;
	glm::vec2 vel = glm::vec2(m_vel / m_direction);
	t_currentSpeed = (vel.x + vel.y) * 0.5f;
	t_speed = speedWanted;
	m_speedChangeTime = time;
	t_deltaSpeed = (t_speed - t_currentSpeed);
	if (t_deltaSpeed > 0)
	{
		m_isSpeedPositive = 1;
	}
	else
	{
		//std::cout << "called \n";
		m_isSpeedPositive = -1;
	}
	m_firstChangeTime = time;

}

void EnemyBulletBase::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;
	if (!m_isAnim)
	{	
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
	} 
	else
	{
		m_animObj.setPos(m_pos);
		m_animObj.draw(spriteBatch);	
	}
}

void EnemyBulletBase::drawHitbox(Feintgine::DebugRender & debugRenderer)
{
	float radius;
	if (m_isAnim)
	{
		radius = m_scale.x * m_animObj.getDim().x;
	}
	else
	{
		radius = m_scale.x * m_sprite.getDim().x;
	}
	
	debugRenderer.drawCircle(m_pos, m_hitboxColor, radius * 0.5f);
}

void EnemyBulletBase::setDestination(const glm::vec2 & val)
{
	m_destination = val;

	//std::cout << "destination " << m_destination.x << " " << m_destination.y << "\n";
	m_destinationState = Reaching;
	m_lifeTime = 2.0f;
	//if (m_isReachDestination == EnemyBulletBase::NotDefined)
	//{
	//	
	//}
	
}

void EnemyBulletBase::setDirection(const glm::vec2 & dir)
{
	m_direction = dir;	

}


void EnemyBulletBase::setVel(const glm::vec2 & vel)
{
	m_vel = vel;
}

void EnemyBulletBase::setGrazeable(bool val)
{
	m_isGrazeable = val;
}

void EnemyBulletBase::setDisabled(bool val)
{
	m_isDisabled = val;
}

void EnemyBulletBase::updateSpeedChange(float deltaTime)
{
	if (m_speedChangeTime > 0.0f)
	{
		m_speedChangeTime -=  0.1f * deltaTime;
		
		if (m_isSpeedPositive == 1)
		{


			if (abs(t_currentSpeed) <= abs(t_speed))
			{
				t_currentSpeed += t_deltaSpeed * (1.0f / (t_speed - t_currentSpeed)) * 0.01f * deltaTime;
				//std::cout << t_currentSpeed << " \n";
			}
		}
		else if(m_isSpeedPositive == -1)
		{
			if (abs(t_currentSpeed) >= abs(t_speed))
			{

				t_currentSpeed += t_deltaSpeed * (1.0f / (t_currentSpeed - t_speed)) * 0.01f * deltaTime;
				//std::cout << t_currentSpeed << " \n";
			}
		}
		
		glm::vec2 vel = glm::vec2(t_currentSpeed);
		m_vel = m_direction* vel;
	}
	
}

void EnemyBulletBase::loadEvent(const std::string & eventName, bool preloaded)
{
	xml_document<> doc;
	//std::cout << "load state " << def++ <<  "\n";

	//std::string filePath = ;
	// 	std::ifstream  file("Data/stageData/enemyState/fairyState.est");
	// 
	// 
	// 	if (!file)
	// 	{
	// 		std::cout << "nothing found \n";
	// 		return;
	// 	}
	std::string fileLocation = "Data/stageData/pattern/bulletState.bls";
	std::vector<char> buffer;
	if (preloaded)
	{
		buffer = Feintgine::ResourceManager::getPreloadedFile(fileLocation);
	}
	else
	{
		std::ifstream  file(fileLocation);
		buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), \
			std::istreambuf_iterator<char>());
		buffer.push_back('\0');
	}
	
	/* = Feintgine::ResourceManager::getPreloadedFile("Data/stageData/pattern/bulletState.bls");*/
	//std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	//buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	xml_node<> * Scripts_node = nullptr;
	auto now = std::chrono::system_clock::now();
	Scripts_node = doc.first_node("Scripts");
	unsigned int time = 0;
	if (!Scripts_node)
	{
		std::cout << "Error while parsing value action for Enemy \n" << __FILE__ << " with " << __LINE__ << "\n";
	}
	else
	{
		//std::cout << "reading " + eventName + " \n";
		for (xml_node<> * Events_node = Scripts_node->first_node("Events");
			Events_node; Events_node = Events_node->next_sibling())
		{
			
			if (eventName == Events_node->first_attribute("name")->value())
			{
				
				for (xml_node<> * Event_node = Events_node->first_node("Event");
					Event_node; Event_node = Event_node->next_sibling())
				{

					//std::cout << "match " << Event_node->first_attribute("name")->value() << "\n";
					std::string t_name = Event_node->first_attribute("name")->value();
					if (Event_node->first_attribute("time"))
					{
						time = std::stoi(Event_node->first_attribute("time")->value());
						
					}
					//std::cout << "time is  " << time << "\n";
					if (t_name == "atPlayer")
					{
						//std::cout << " name match " << eventName << "\n";
						float speed = 1.0f;
						if (Event_node->first_attribute("speed"))
						{
							speed = std::stof(Event_node->first_attribute("speed")->value());
						}
						addEvent([=]
						{
						//	std::cout << "add Event " << daf++ << "\n";
							glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);
							glm::vec2 vel = glm::vec2(speed) *direction;
							m_vel = vel;
						}, ENGINE_current_tick  + Feintgine::F_oEvent::convertMSToS(time));
					
					}
					if (t_name == "atPlayer_v1")
					{
						//std::cout << " name match " << eventName << "\n";
						float speed = 1.0f;
						float transit_time = 0.0f;
						if (Event_node->first_attribute("speed"))
						{
							speed = std::stof(Event_node->first_attribute("speed")->value());
							if (Event_node->first_attribute("transit_time"))
							{
								transit_time = std::stof(Event_node->first_attribute("transit_time")->value());
							}
						}
						addEvent([=]
						{
							//	std::cout << "add Event " << daf++ << "\n";
							//glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);
// 							glm::vec2 vel = glm::vec2(speed) *direction;
// 							m_vel = vel;
							
							setSpeedChange(speed, transit_time);
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time));

					}
					if (t_name == "speedChange")
					{
						//std::cout << "speedChange time is " << time << "\n";
						float speed = 1.0f;
						float transit_time = 0.0f;
						if (Event_node->first_attribute("speed"))
						{
							speed = std::stof(Event_node->first_attribute("speed")->value());
							if (Event_node->first_attribute("transit_time"))
							{
								transit_time = std::stof(Event_node->first_attribute("transit_time")->value());
							}
							

						}
						addEvent([=]
						{
							//	std::cout << "add Event " << daf++ << "\n";
							//glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);
							/*glm::vec2 vel = glm::vec2(speed);
							m_vel = m_direction* vel;*/
							//
							setSpeedChange(speed, transit_time);
							
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time));
					}
					if (t_name == "maxSpeed")
					{
						//std::cout << "maxSpeed time is " << time << "\n";
						float value = 0.0f;
						if (Event_node->first_attribute("value"))
						{
							value = std::stof(Event_node->first_attribute("value")->value());
						}
						addEvent([=]
						{
							//	std::cout << "add Event " << daf++ << "\n";
							//glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);
							//glm::vec2 vel = glm::vec2(speed);
							//m_vel = m_direction* vel;
											
							m_vel = glm::normalize(m_vel) * value;
			
								
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time));
					}
					// if(t_name == "minSpeed")
					// {
					// 	//std::cout << "minSpeed time is " << time << "\n";
					// 	float value = 0.0f;
					// 	if (Event_node->first_attribute("value"))
					// 	{
					// 		value = std::stof(Event_node->first_attribute("value")->value());
					// 	}
					// 	addEvent([=]
					// 	{
					// 		//	std::cout << "add Event " << daf++ << "\n";
					// 		//glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);
					// 		//glm::vec2 vel = glm::vec2(speed);
					// 		//m_vel = m_direction* vel;
											
					// 		m_vel = glm::normalize(m_vel) * value;
			
								
					// 	}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time));
					// }
					if (t_name == "cos")
					{
						float startAngle = 0.0f;
						if (Event_node->first_attribute("startAngle"))
						{
							startAngle = std::stof(Event_node->first_attribute("startAngle")->value());
						}
						float endAngle = 0;
						if (Event_node->first_attribute("endAngle"))
						{
							endAngle = std::stof(Event_node->first_attribute("endAngle")->value());
						}
						float angleStep = 0;
						if (Event_node->first_attribute("angleStep"))
						{
							angleStep = std::stof(Event_node->first_attribute("angleStep")->value());
						}
						addEvent([=]
						{
							
							//glm::vec2 direction = glm::vec2(cos(angle), sin(angle));
							setRotateVec(startAngle, endAngle, angleStep);
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time));

					}
				}
			}
	
		}
	}

}

void EnemyBulletBase::setRotateVec(float angleStart, float angleEnd, float step)
{
	m_isRotate = true;
	m_startAngle = angleStart;
	m_currentAngle = m_startAngle;
	m_endAngle = angleEnd;
	m_rotateStep = step;
}

void EnemyBulletBase::updateRotateVec(float deltaTime)
{

		if (m_isRotate)
		{
			m_rotateVec = ((glm::vec2(cos(m_currentAngle), sin(m_currentAngle))) *deltaTime) + m_pos ;
			m_currentAngle += m_rotateStep *deltaTime;
			if (m_currentAngle > m_endAngle)
			{
				m_isRotate = false;
				m_rotateVec = glm::vec2(1);
			}
		}
	
}
