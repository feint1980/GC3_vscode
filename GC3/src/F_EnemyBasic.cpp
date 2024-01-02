#include "F_EnemyBasic.h"
#include "GlobalValueClass.h"
#include "F_Player.h"
#include <EngineSetting.h>

F_EnemyBasic::F_EnemyBasic()
{
	m_item = nullptr;
}


F_EnemyBasic::~F_EnemyBasic()
{
	event_queue = std::priority_queue<Feintgine::oEvent, std::vector<Feintgine::oEvent>, Feintgine::oEvent_less>();
}

void F_EnemyBasic::update(float deltaTime)
{
	
	m_pos += m_vel * deltaTime;
	
	if (isAnimated)
	{
		m_animation.update(deltaTime);
		m_animation.setPos(m_pos);
	}

	if (m_isDeath)
	{

		m_animation.rotate(0.9f * deltaTime);
		if (!m_animation.isPlaying())
		{
			m_isAlive = false;
		}
	}

	if (m_isMoveBerzier)
	{
		
			m_perc = berzierRate;
			berzierRate += 0.01f * deltaTime;
			m_vel = glm::normalize(getBerzierPos(m_start, m_inter, m_des, m_perc)) * m_berzierSpeed;
			m_vel.y = -m_vel.y;
		
	}
	if (m_shield)
	{
		m_shield->update(deltaTime);
		m_shield->setPos(m_pos);
	}

	timer();
}

void F_EnemyBasic::setVel(const glm::vec2 & vel)
{
	m_vel = vel;
	m_isMoveBerzier = false;
}

void F_EnemyBasic::loadState(const std::string & name, bool preloaded)
{
	xml_document<> doc;
	// if(name == "Disabled_sealed")
	// {
	// 	std::cout << "disabled sealed \n";
	// }
	std::string fileLocation = "./Data/stageData/enemyState/fairyState.est";
	std::vector<char> buffer;
	if (preloaded)
	{
		buffer = Feintgine::ResourceManager::getPreloadedFile(fileLocation);
	}
	else
	{
		std::ifstream  file(fileLocation);
		buffer = std::vector<char>((std::istreambuf_iterator<char>(file)),\
			std::istreambuf_iterator<char>());
		buffer.push_back('\0');
	}
	
	//std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	
	doc.parse<0>(&buffer[0]);

	xml_node<> * EnemyStates_node = nullptr;
	auto now = std::chrono::system_clock::now();
	EnemyStates_node = doc.first_node("EnemyStates");
	if (!EnemyStates_node)
	{
		std::cout << "Error while parsing value action for Enemy BaseEnemy.cpp \n";
	}
	else
	{
		for (xml_node<> * ComboState_node = EnemyStates_node->first_node("ComboState");
			ComboState_node; ComboState_node = ComboState_node->next_sibling())
		{
			std::string found = ComboState_node->first_attribute("name")->value();
			//std::cout << "get " << found << "\n";
			//std::cout << "targeting " << name << "\n";
			if (found == name)
			{
				//std::cout << "we cool \n";

				for (xml_node<> * State_node = ComboState_node->first_node("State");
					State_node; State_node = State_node->next_sibling())
				{
					std::string t_type = State_node->first_attribute("name")->value();
					unsigned t_time = std::stoi(State_node->first_attribute("time")->value());
					if (t_type == "playAnim")
					{
						//std::cout << "yes play Anim \n";
						std::string valueAnim = State_node->first_attribute("value")->value();
						//std::cout << "play anim << " << valueAnim << " \n";
						addEvent([=] {
							playAnim(valueAnim);
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));

					}
					else if (t_type == "move")
					{
						//std::cout << "yes move\n";
						glm::vec2 vel = glm::vec2(std::stof(State_node->first_attribute("vel_x")->value()),
							std::stof(State_node->first_attribute("vel_y")->value()));
						//std::cout << "move as vel " << feint_common::Instance()->convertVec2toString(vel) << "\n";
						addEvent([=] {

							setVel(vel);
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));

					}
					else if (t_type == "moveBerzier")
					{
						glm::vec2 inter = glm::vec2(std::stof(State_node->first_attribute("inter_x")->value()),
							std::stof(State_node->first_attribute("inter_y")->value()));
						glm::vec2 des = glm::vec2(std::stof(State_node->first_attribute("des_x")->value()),
							std::stof(State_node->first_attribute("des_y")->value()));

						float speed = std::stof(State_node->first_attribute("speed")->value());
						//std::cout << "move as vel " << feint_common::Instance()->convertVec2toString(vel) << "\n";
						addEvent([=] {

							moveBerzier(m_pos, inter, des, speed);
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));
					}
					else if (t_type == "selfDestroy")
					{
						addEvent([=] {

							m_isAlive = false;
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));
						
					}
					else if (t_type == "fire")
					{

						std::string t_pattern;
						int count = 0;

						bool staged = false;

						std::string eventName = "";

						if (State_node->first_attribute("event"))
						{
							staged = true;
							eventName = State_node->first_attribute("event")->value();

						}

						if (State_node->first_attribute("pattern"))
						{
							t_pattern = State_node->first_attribute("pattern")->value();


						}
						if (State_node->first_attribute("count"))
						{
							count = std::stoi(State_node->first_attribute("count")->value());

						}
						if (t_pattern == "normal")
						{
							//xml_node<> * Prop_node = State_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float vel_x = std::stof(State_node->first_attribute("vel_x")->value());
							float vel_y = std::stof(State_node->first_attribute("vel_y")->value());
							float spread_x = std::stof(State_node->first_attribute("spread_x")->value());
							float spread_y = std::stof(State_node->first_attribute("spread_y")->value());

							addEvent([=]
							{
								int spreadCount = 0;
								for (int i = 0; i < count; i++)
								{
									EnemyBulletBase * bullet = new EnemyBulletBase();
									int direction = -1;
									if (i % 2)
									{
										direction = 1;
										spreadCount++;
									}

									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), glm::vec2(vel_x + (spreadCount * spread_x * direction), vel_y + (spreadCount * spread_y)), nullptr, 5);
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
									//spreadCount++;
								}

							}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));
						}
						if (t_pattern == "ring")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float spread = std::stof(State_node->first_attribute("spread")->value());
							glm::vec2 vel = glm::vec2(speed);
							addEvent([=]
							{
								//int spreadCount = 0;
								for (int i = 0; i < count; i++)
								{
									EnemyBulletBase * bullet = new EnemyBulletBase();

									bullet->setDirection(vel);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), glm::rotate(vel, i * spread), nullptr, 5);
									bullet->setAngle(i * spread);
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
									//spreadCount++;
								}

							}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));
						}
						if (t_pattern == "atPlayer_1")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float random = std::stof(State_node->first_attribute("randomness")->value());
							glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);

							glm::vec2 vel = glm::vec2(speed) *direction;
							addEvent([=]
							{
								//int spreadCount = 0;
								for (int i = 0; i < count; i++)
								{
									EnemyBulletBase * bullet = new EnemyBulletBase();
									float t_random = feint_common::Instance()->getRandomNum(random, -random);
									bullet->setDirection(vel);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), glm::rotate(vel, t_random), nullptr, 5);
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
									//spreadCount++;
								}

							}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time));
						}
						if (t_pattern == "atPlayer_2")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float random = std::stof(State_node->first_attribute("randomness")->value());
							int interval = std::stoi(State_node->first_attribute("interval")->value());
							glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);

							glm::vec2 vel = glm::vec2(speed) *direction;
							for (int i = 0; i < count; i++)
							{
								addEvent([=]
								{
									//int spreadCount = 0;

									EnemyBulletBase * bullet = new EnemyBulletBase();
									float t_random = feint_common::Instance()->getRandomNum(random, -random);
									bullet->setDirection(vel);
									bullet->setLifeTime(8.0f);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), glm::rotate(vel, t_random), nullptr, 5);
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
									//spreadCount++;


								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * i)));
							}
						}
						if (t_pattern == "atPlayer_offset")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							//float random = std::stof(State_node->first_attribute("randomness")->value());

							float offset_x = std::stof(State_node->first_attribute("offset_x")->value());
							float offset_y = std::stof(State_node->first_attribute("offset_y")->value());

							int interval = 0;
							interval = std::stoi(State_node->first_attribute("interval")->value());
							glm::vec2 offsetDir = glm::vec2(offset_x, offset_y);
							//glm::vec2 direction = glm::normalize(GlobalValueClass::Instance()->getPlayer()->getPos() - m_pos);
						
							
							
							for (int i = 0; i < count; i++)
							{
								addEvent([=]
								{
									//int spreadCount = 0;

									EnemyBulletBase * bullet = new EnemyBulletBase();
									glm::vec2 direction = glm::normalize((GlobalValueClass::Instance()->getPlayer()->getPos() + offsetDir) - m_pos);
									glm::vec2 vel = glm::vec2(speed) * direction;
									//float t_random = feint_common::Instance()->getRandomNum(random, -random);
									bullet->setDirection(vel);
									bullet->setLifeTime(8.0f);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), vel, nullptr, 5);
									//bullet->setVel(vel);
									if (staged)
									{
										bullet->loadEvent(eventName, preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
									//spreadCount++;


								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * i)));
							}
						}

						if (t_pattern == "PE_Rose_cos")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float range = std::stof(State_node->first_attribute("start_range")->value());

							//float petal_x = std::stof(State_node->first_attribute("petal_x")->value());
							//float petal_y = std::stof(State_node->first_attribute("petal_y")->value());
							float range_cover = std::stof(State_node->first_attribute("range_cover")->value());
							float angle_step = std::stof(State_node->first_attribute("angle_step")->value());
							float petal_count = std::stof(State_node->first_attribute("petal_count")->value());
							float angle = 0;
							float tRotation = 0;
							int interval = 0;
							if (State_node->first_attribute("interval"))
							{
								interval = std::stoi(State_node->first_attribute("interval")->value());
							}
							if (State_node->first_attribute("start_angle"))
							{
								angle = std::stof(State_node->first_attribute("start_angle")->value()) / 57.2957795f;
							}
							if (State_node->first_attribute("rotation"))
							{
								tRotation = std::stof(State_node->first_attribute("start_angle")->value());
								tRotation /= 57.2957795f;
							}

							for (int i = 0; i < count; i++)
							{

								addEvent([=]
								{

									float range1 = range *  cos(angle * petal_count);
									//float range2 = sin(angle * petal_y);
									EnemyBulletBase * bullet = new EnemyBulletBase();
									bullet->m_lifeTime = 6.0f;
									float x = range1 * cos(angle);
									float y = range1  * sin(angle);
									// 									float x = range * cos(angle);
									// 									float y = range * sin(angle);
									glm::vec2 vel = glm::vec2(x, y) * speed;
									vel = globalRotatePoint(glm::vec2(vel.x, vel.y), tRotation);
									bullet->setDirection(vel);

									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), glm::rotate(vel, angle), nullptr, 5);
									//bullet->setAngle(atan2(y, x) + degreeToRad(90));
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);


								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval *i)));
								//std::cout << "INTERVAL value : " << ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval *i)) << "\n";

								angle += angle_step;
							}
						}
						if (t_pattern == "PE_Rose_sin")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float range = std::stof(State_node->first_attribute("start_range")->value());

							//float petal_x = std::stof(State_node->first_attribute("petal_x")->value());
							//float petal_y = std::stof(State_node->first_attribute("petal_y")->value());
							float range_cover = std::stof(State_node->first_attribute("range_cover")->value());
							float angle_step = std::stof(State_node->first_attribute("angle_step")->value());
							float petal_count = std::stof(State_node->first_attribute("petal_count")->value());
							float angle = 0;
							float tRotation = 0;

							int interval = 0;
							if (State_node->first_attribute("interval"))
							{
								interval = std::stoi(State_node->first_attribute("interval")->value());
							}
							if (State_node->first_attribute("start_angle"))
							{
								angle = std::stof(State_node->first_attribute("start_angle")->value()) / 57.2957795f;
							}
							if (State_node->first_attribute("rotation"))
							{
								tRotation = std::stof(State_node->first_attribute("start_angle")->value());
								tRotation /= 57.2957795f;
							}

							for (int i = 0; i < count; i++)
							{
								addEvent([=]
								{
									float range1 = range *  sin(angle * petal_count);
									//float range2 = sin(angle * petal_y);
									EnemyBulletBase * bullet = new EnemyBulletBase();
									bullet->m_lifeTime = 6.0f;
									float x = range1 * cos(angle);
									float y = range1  * sin(angle);
									// 									float x = range * cos(angle);
									// 									float y = range * sin(angle);
									//bullet->setAngle(atan2(y, x) + degreeToRad(90));
									glm::vec2 vel = glm::vec2(x, y) * speed;
									vel = globalRotatePoint(glm::vec2(x, y), tRotation);
									bullet->setDirection(vel);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), glm::rotate(vel, angle), nullptr, 5);
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);


								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * i)));

								angle += angle_step;
							}
						}
						if (t_pattern == "PE_Circle")
						{
							//xml_node<> * Prop_node = ComboState_node->first_node("Prop");

							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float range = std::stof(State_node->first_attribute("start_range")->value());
							float angle_step = std::stof(State_node->first_attribute("angle_step")->value());
							float angle = 0;
							int interval = 0;
							if (State_node->first_attribute("interval"))
							{
								interval = std::stoi(State_node->first_attribute("interval")->value());
							}
							if (State_node->first_attribute("start_angle"))
							{
								angle = std::stof(State_node->first_attribute("start_angle")->value()) / 57.2957795f;
							}

							for (int i = 0; i < count; i++)
							{
								addEvent([=]
								{
									EnemyBulletBase * bullet = new EnemyBulletBase();
									bullet->m_lifeTime = 6.0f;
									float x = cos(angle);
									float y = sin(angle);
									glm::vec2 vel = glm::vec2(x, y) * speed;
									bullet->setDirection(vel);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), vel, nullptr, 5);


									//std::cout << "angle " << radToDegree(angle) << "\n";
									//std::cout << "atan2 " << radToDegree(atan2(y, x)) << "\n";

									//bullet->setAngle(atan2(y, x) + degreeToRad(90));

									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * i)));

								angle += angle_step;
							}
						}
						if (t_pattern == "MA_hypotrochoid")
						{
							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float fA = std::stof(State_node->first_attribute("a")->value());
							float fB = std::stof(State_node->first_attribute("b")->value());
							float fC = std::stof(State_node->first_attribute("c")->value());
							float fR = std::stof(State_node->first_attribute("r")->value());
							float lifeTime = std::stof(State_node->first_attribute("life_time")->value());
							fR = fR * 0.01f;
							float angle_step = std::stof(State_node->first_attribute("angle_step")->value());
							float angle = 0;
							int interval = 0;
							if (State_node->first_attribute("interval"))
							{
								interval = std::stoi(State_node->first_attribute("interval")->value());
							}
							if (State_node->first_attribute("start_angle"))
							{
								angle = std::stof(State_node->first_attribute("start_angle")->value()) / 57.2957795f;
							}
							float tRotation = 0;
							if (State_node->first_attribute("rotation"))
							{
								tRotation = std::stof(State_node->first_attribute("rotation")->value()) / 57.2957795f;
							}
							for (int i = 0; i < count; i++)
							{
								addEvent([=]
								{
									EnemyBulletBase * bullet = new EnemyBulletBase();
									bullet->m_lifeTime = lifeTime;
									// 									float x = ((fA - fB) * cos(angle) +
									// 										(fC * cos((fA/fB - 1)*angle))) *fR;
									// 									float y = ((fA - fB) * sin(angle)
									// 										- (fC * sin((fA/ fB- 1)*angle))) *fR;;
									// 									glm::vec2 vel = glm::vec2(x, y) * speed;

									ArcFunction_hypotrochoid arc;
									std::vector<float> factor;
									factor.push_back(fA);
									factor.push_back(fB);
									factor.push_back(fC);
									arc.init(fR, factor);
									// 									float x = ((fA - fB) * cos(angle) +
									// 										(fC * cos((fA / fB - 1)*angle))) *fR;
									// 									float y = ((fA - fB) * sin(angle)
									// 										- (fC * sin((fA / fB - 1)*angle))) *fR;;
									// 									
									float x = arc.getValue(angle).x;
									float y = arc.getValue(angle).y;

									glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), tRotation);

									glm::vec2 vel = tVel * speed;
									bullet->setDirection(tVel);
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), vel, nullptr, 5);
									//bullet->setAngle(atan2(vel.x, vel.y));
									//std::cout << "angle is " << (atan2(x + m_pos.x, y + m_pos.y)) << "\n";
									//bullet->setAngle(atan2(y , x) + degreeToRad(90));
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * i)));
								angle += angle_step;
							}


						}
						if (t_pattern == "MA_hypocycloid")
						{
							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float fA = std::stof(State_node->first_attribute("a")->value());
							float fB = std::stof(State_node->first_attribute("b")->value());
							float fR = std::stof(State_node->first_attribute("r")->value());
							float lifeTime = std::stof(State_node->first_attribute("life_time")->value());
							fR = fR * 0.01f;
							float angle_step = std::stof(State_node->first_attribute("angle_step")->value());
							float angle = 0;
							int interval = 0;
							if (State_node->first_attribute("interval"))
							{
								interval = std::stoi(State_node->first_attribute("interval")->value());
							}
							if (State_node->first_attribute("start_angle"))
							{
								angle = std::stof(State_node->first_attribute("start_angle")->value()) / 57.2957795f;
							}
							float tRotation = 0;
							if (State_node->first_attribute("rotation"))
							{
								tRotation = std::stof(State_node->first_attribute("rotation")->value()) / 57.2957795f;
							}
							for (int i = 0; i < count; i++)
							{
								addEvent([=]
								{
									EnemyBulletBase * bullet = new EnemyBulletBase();
									bullet->m_lifeTime = lifeTime;
									ArcFunction_hypocycloid arc;
									std::vector<float> factor;
									factor.push_back(fA);
									factor.push_back(fB);

									arc.init(fR, factor);
									// 									float x = ((fA - fB) * cos(angle) +
									// 										(fC * cos((fA / fB - 1)*angle))) *fR;
									// 									float y = ((fA - fB) * sin(angle)
									// 										- (fC * sin((fA / fB - 1)*angle))) *fR;;
									// 									
									float x = arc.getValue(angle).x;
									float y = arc.getValue(angle).y;
									glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), tRotation);
									bullet->setDirection(tVel);
									glm::vec2 vel = tVel * speed;
									bullet->init(m_pos, glm::vec2(1),
										Feintgine::SpriteManager::Instance()->getSprite(t_asset), vel, nullptr, 5);
									//bullet->setAngle(atan2(vel.x, vel.y));

									//std::cout << "angle is " << (atan2(x + m_pos.x, y + m_pos.y)) << "\n";
									//bullet->setAngle(atan2(y , x) + degreeToRad(90));
									if (staged)
									{
										bullet->loadEvent(eventName,preloaded);
									}
									//bullet->initLogic(m_world);
									m_bullets.push_back(bullet);
								}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * i)));
								angle += angle_step;
							}


						}
						if (t_pattern == "MA_custom_aff")
						{
							std::string t_asset = State_node->first_attribute("asset")->value();
							float speed = std::stof(State_node->first_attribute("speed")->value());
							float fA = std::stof(State_node->first_attribute("a")->value());
							float fB = std::stof(State_node->first_attribute("b")->value());

							float fR = std::stof(State_node->first_attribute("r")->value());
							float lifeTime = std::stof(State_node->first_attribute("life_time")->value());
							fR = fR * 0.01f;
							float angle_step = std::stof(State_node->first_attribute("angle_step")->value());
							float angle = 0;
							int interval = 0;
							if (State_node->first_attribute("interval"))
							{
								interval = std::stoi(State_node->first_attribute("interval")->value());
							}
							if (State_node->first_attribute("start_angle"))
							{
								angle = std::stof(State_node->first_attribute("start_angle")->value()) / 57.2957795f;
							}
							float tRotation = 0;
							if (State_node->first_attribute("rotation"))
							{
								tRotation = std::stof(State_node->first_attribute("rotation")->value()) / 57.2957795f;
							}


							//int c = 0;
							int n = std::stoi(State_node->first_attribute("n")->value());
							//int nn = 22;
							int n2 = std::stoi(State_node->first_attribute("n2")->value());

							//float cosin = 0.0f;
							//int t1 = 4;
							//int t2 = n2 * t1;
							//float ap = 17.0f / n2;

							int t_l1 = std::stoi(State_node->first_attribute("l1")->value());
							int t_l2 = std::stoi(State_node->first_attribute("l2")->value());

							float posneg = std::stof(State_node->first_attribute("posneg")->value());
							
							f_angle = angle;
							//t_angle = angle;
							for (int k = 0; k < 1; k++)
							{
								for (int l1 = 0; l1 < t_l1; l1++)
								{
									f_angle += angle_step;
									for (int l2 = 0; l2 < t_l2; l2++)
									{
																
										f_angle += angle_step;
										//f_angle = t_angle;
										for (int f = 0; f < n2; f++)
										{
											
											f_angle += angle_step;
											for (int c = 0; c < n; c++)
											{

												addEvent([=]
												{
													EnemyBulletBase * bullet = new EnemyBulletBase();
													bullet->m_lifeTime = lifeTime;
													ArcFunction_hypocycloid arc;
													std::vector<float> factor;
													//factor.push_back(fA);
													//factor.push_back(fB);

													//arc.init(fR, factor);
													//float f_angle = t_angle;
													 ;
													float x =  cos(f_angle * posneg);
													float y =  sin(f_angle * posneg);
													f_angle += degreeToRad((360 / n ));
														
								
													glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), f_angle * posneg);

													glm::vec2 vel = tVel * speed;
													bullet->init(m_pos, glm::vec2(1),
														Feintgine::SpriteManager::Instance()->getSprite(t_asset), vel, nullptr, 5);
													bullet->setDirection(tVel);
													//bullet->setAngle(atan2(vel.x, vel.y));

													//std::cout << "angle is " << (atan2(x + m_pos.x, y + m_pos.y)) << "\n";
													//bullet->setAngle(atan2(y , x) + degreeToRad(90));
													if (staged)
													{
														bullet->loadEvent(eventName,preloaded);
													}
													//bullet->initLogic(m_world);
													m_bullets.push_back(bullet);
												}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(t_time + (interval * c )));
												//t_angle += angle_step;
												//cosin += 0.001f;
												
											}
											f_angle += angle_step;
											//f_angle += degreeToRad(0.1f * posneg);
											//cosin += 0.01f;
											//t_angle += degreeToRad(0.1f * posneg);
										}
										//cosin += 0.01f;
									}
									
								}
							}
						}
					}
				}
				break;
			}

		}
		initSound();
	}
	
}



void F_EnemyBasic::takeDamage(float damage, bool playSound)
{
	m_heath = m_heath - damage;
	if (m_heath < 0)
	{
		death();
		F_Player * player = GlobalValueClass::Instance()->getPlayer();
		player->addScoreSilence(m_scoreValue);
	}
	else
	{
		if (playSound)
		{
			m_hitSoundEffect.play(0);
		}
			
	}
	
}

void F_EnemyBasic::initSound()
{
	if (m_audioEngine)
	{
		m_deadSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/fairy_dead_sound.wav");
		m_hitSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/damage00.wav");
		//m_fireSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/plst00.wav");
	}
	else
	{
		feint_common::Instance()->showMessageBox("Error", "EnemyBasic audio engine is null ");
	}
}

void F_EnemyBasic::death()
{
	if (!m_isDeath)
	{
		//std::cout << "dead \n";
		m_animation.setAlpha(0.5f);
		m_animation.setScale(glm::vec2(2));
		playAnim("death", 1);
		m_deadSoundEffect.play(0);
		setVel(glm::vec2(0));
		m_isDeath = true;
		
		if (m_item)
		{
			m_item->create(m_pos);
			m_item->bump(12);			
			onDrop(GlobalValueClass::Instance()->getPlayer());
		}
		event_queue = std::priority_queue<Feintgine::oEvent, std::vector<Feintgine::oEvent>, Feintgine::oEvent_less>();
	}
}

void F_EnemyBasic::setCollectableItem(const std::string & itemName)
{
	
	if (itemName == "score")
	{
		m_item = new ScoreItem();
		m_item->init(Feintgine::SpriteManager::Instance()->getSprite("projectile/score.png"), glm::vec2(15), Feintgine::Color(255, 255, 255, 255), 4);
		return;
	}
	if (itemName == "power_small")
	{
		m_item = new PowerItem();
		m_item->setPowerValue(1);
		m_item->init(Feintgine::SpriteManager::Instance()->getSprite("projectile/power_big.png"), glm::vec2(15), Feintgine::Color(255, 255, 255, 255), 4);
		return;
	}
	if (itemName == "power_big")
	{
		m_item = new PowerItem();
		m_item->setPowerValue(8);
		m_item->init(Feintgine::SpriteManager::Instance()->getSprite("projectile/power_big.png"), glm::vec2(22), Feintgine::Color(255, 255, 255, 255), 4);
		return;
	}
}



void F_EnemyBasic::onDrop(F_Player * player)
{
	player->addDropItem(m_item);
}

glm::vec2 F_EnemyBasic::getBerzierPos(const glm::vec2 & start, const glm::vec2 & interotation, const glm::vec2 & destination, float perc)
{

	float xa = getPt(start.x, interotation.x, perc);
	float ya = getPt(start.y, interotation.y, perc);
	float xb = getPt(interotation.x, destination.x, perc);
	float yb = getPt(interotation.y, destination.y, perc);

	// The Black Dot
	float x = getPt(xa, xb, perc);
	float y = getPt(ya, yb, perc);

	return glm::vec2(x, y);
}

void F_EnemyBasic::moveBerzier(const glm::vec2 & start, const glm::vec2 & interotation, const glm::vec2 & destination, float speed)
{

	
	//setVel(glm::vec2(0));
	m_isMoveBerzier = true;
	m_start = start;
	m_inter = interotation;
	m_des = destination;
	m_berzierSpeed = speed;

}

void F_EnemyBasic::loadPatern(const std::string & name,int count, int p_time)
{
	xml_document<> doc;
	//std::cout << "start state \n";

	//std::string filePath = ;
	std::ifstream file("Data/stageData/pattern/common.pat");
	if (!file)
	{
		std::cout << "nothing found \n";
		return;
	}
	else
	{
		xml_node<> * Patterns_node = doc.first_node("Patterns");
		if (Patterns_node)
		{
			for (xml_node<> * Pattern_node = Patterns_node->first_node("ComboState");
				Pattern_node; Pattern_node = Pattern_node->next_sibling())
			{

				std::string pt_name = Pattern_node->first_attribute("name")->value();
				if (name == "normal_1" && pt_name == "normal_1")
				{
					xml_node<> * Prop_node = Pattern_node->first_node("Prop");
					if (Prop_node)
					{
						
						Feintgine::F_Sprite sprite = Feintgine::SpriteManager::Instance()->getSprite(
							Prop_node->first_attribute("asset")->value());
						float x = std::stof(Prop_node->first_attribute("vel_x")->value());
						float y = std::stof(Prop_node->first_attribute("vel_y")->value());
						float s_x = std::stof(Prop_node->first_attribute("spread_x")->value());
						float s_y = std::stof(Prop_node->first_attribute("spread_y")->value());
						glm::vec2 vel = glm::vec2(x, y);
						glm::vec2 spread = glm::vec2(s_x, s_y);
						
							for (int i = 0; i < count; i++)
							{
								glm::vec2 t_vel = vel + (spread * glm::vec2(i));
								EnemyBulletBase * bullet = new EnemyBulletBase();
								bullet->init(m_pos, glm::vec2(1), sprite, t_vel, [&](float deltatime) {
								}, 4);
								m_bullets.push_back(bullet);
							}						
					}				
					break;
				}
			}			
		}
	}

}


