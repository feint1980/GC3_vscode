#include "F_PlayerAccessory.h"
#include "GlobalValueClass.h"


F_PlayerAccessory::F_PlayerAccessory()
{

}


F_PlayerAccessory::~F_PlayerAccessory()
{

}

void F_PlayerAccessory::init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::F_Sprite & sprite, bool isLeft)
{
	m_pos = pos;
	m_dims = dim;
	m_sprite = sprite;
	if (isLeft)
	{
		m_isLeft = isLeft;
		offsetX = -offsetX;
		m_rotSpeed = -m_rotSpeed;
		destination = -destination;		
	}
	m_isRotate = true;
	savedOffset = offsetX;
	m_particleBatch = new Feintgine::ParticleBatch2D();
	m_particleBatch->init(150, 0.05f, Feintgine::SpriteManager::Instance()->getSprite("projectile/particle_red_4.png"),
		[](Feintgine::Particle2D& particles, float deltatime)
	{

		particles.position += particles.velocity * deltatime;
		particles.color.a = 1.0f * particles.life;
		particles.scale += 0.01f * deltatime;
		particles.angle += (0.1f * particles.velocity.x) * deltatime;

	});
	m_laser.setParticle(m_particleBatch);
	if (m_isLeft)
	{
		m_laserFocus.setParticle(m_particleBatch);
	}
	
	m_attentionua = glm::vec3(14.0f, 14.0f, 25.0f);
	t_attentionua = m_attentionua;
// 	m_laser.init(Feintgine::ResourceManager::getTexture("Assets/Textures/marisa_laser_small.png",
// 		m_pos, glm::vec2(256,13),)
}

void F_PlayerAccessory::draw(Feintgine::SpriteBatch & spriteBatch)
{
	
	float t_x = 0.0f;
		
	desRect.x = m_additionalPos.x +  m_pos.x + offsetX  - m_sprite.getDim().x  / 2.0f  ;
	desRect.y = m_additionalPos.y +  m_pos.y - m_sprite.getDim().y / 2.0f;
	desRect.z = m_sprite.getDim().x;
	desRect.w = m_sprite.getDim().y;
	spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, 5, m_color, m_angle);
	for (auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
	for (auto i = 0; i < m_bullets_a.size(); i++)
	{
		m_bullets_a[i]->draw(spriteBatch);
	}
	for (auto i = 0; i < m_bullets_b.size(); i++)
	{
		m_bullets_b[i]->draw(spriteBatch);
	}

	if (m_bulletType == BULLET_TYPE_MARISA_LASER)
	{
		m_laser.draw(spriteBatch);
		if (m_isLeft)
		{


			m_laserFocus.draw(spriteBatch);
		}
	}
}


void F_PlayerAccessory::drawLight(Feintgine::LightBatch & lightBatch)
{

	glm::vec2 tt;
	tt.x = m_additionalPos.x + m_pos.x + offsetX ;
	tt.y = m_additionalPos.y + m_pos.y ;

	f_attentionua = m_attentionua - (m_attentionua * 0.5f) *  GlobalValueClass::Instance()->getAmbientLight().x;
	lightBatch.addLight(tt,glm::vec4(1.0f), 
		(1.0f/ f_attentionua));

	for (int i = 0; i < m_bullets_a.size(); i++)
	{
		m_bullets_a[i]->drawLight(lightBatch);
	}

	if (m_bulletType == BULLET_TYPE_MARISA_LASER)
	{
		m_laser.drawRayLight(lightBatch);
		m_laserFocus.drawRayLight(lightBatch);
	}

}

void F_PlayerAccessory::drawDebug(Feintgine::DebugRender & renderer)
{
	m_laser.drawHitbox(renderer);
	m_laserFocus.drawHitbox(renderer);
}

void F_PlayerAccessory::update(float deltaTime, std::vector<FairyBase *>  enemies)
{


	if (isParentColor)
	{
		for (auto i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i]->setAlpha(m_color.a);
			
		}
		for (auto i = 0; i < m_bullets_a.size(); i++)
		{
			m_bullets_a[i]->setAlpha(m_color.a);
			
		}
		for (auto i = 0; i < m_bullets_b.size(); i++)
		{
			m_bullets_b[i]->setAlpha(m_color.a);
			
		}
		m_laser.setAlpha(m_color.a);
		m_laserFocus.setAlpha(m_color.a);
	}

	if (m_isRotate)
	{
		m_angle -= m_rotSpeed * deltaTime;
	}
	if (m_bulletType == BULLET_TYPE_MARISA_LASER)
	{
		m_laser.update(deltaTime, getOffsetedPos(), enemies);
		m_laserFocus.update(deltaTime, getOffsetPosFocus(),enemies);
		
			
	}
	if (m_isFocus)
	{
		
		//std::cout << "focus \n";
		if (m_type == 2)
		{
			offsetX = 0;
			turnRate += m_rotSpeed * 0.5f;
			if (m_isLeft)
			{
				m_additionalPos.x = 0 + cos(turnRate)*24.0f;
				m_additionalPos.y = 0 + sin(turnRate)*24.0f;
			}
			else
			{
				m_additionalPos.x = 0 - cos(turnRate)*24.0f;
				m_additionalPos.y = 0 + sin(turnRate)*24.0f;
			}
		
		}
		
			if (m_stack < maxStack)
			{
				m_stack += 0.1f * deltaTime;
			}
			else
			{
				resetFirerate = true;
			}
		
	}
	else
	{
		//std::cout << "not focus \n";

		if (m_type == 2)
		{
			offsetX = savedOffset;
			m_additionalPos = glm::vec2(0);
			turnRate = 0.0f;
		}
		


		if (m_stack > 0.0f)
		{
			m_stack -= 0.1f * deltaTime;
		}
		else
		{
			m_stack = 0.0f;
			if (resetFirerate)
			{
				fireRate = 0.0f;
				resetFirerate = false;
			}

		}
		
	}
	if (m_type == 1 )
	{
		m_additionalPos.x = destination * m_stack ;
		m_additionalPos.y = 17.0f * m_stack ;
	}	
	if (m_isFire)
	{
		if (m_bulletType == BULLET_TYPE_MARISA_LASER)
		{
			isLaserOff = false;
			isFocusLaserOff = false;
			m_color = Feintgine::Color(255, 255, 255, 100);
		}
		
		fireRate += 0.1f * deltaTime;

		if (m_stack < maxStack)
		{
		
			if (isPeak)
			{
				fireRate = 0.0f;
				isPeak = false;
			}
			m_laserFocus.setVisible(false);
			if (fireRate >= delayBullet)
			{	
				switch (m_bulletType)
				{
				case BULLET_TYPE_REIMU_HOMING:
				{
					F_HomingBullet *bullet = new F_HomingBullet();
// 					bullet->init(glm::vec2(desRect.x, desRect.y)
// 						, glm::vec2(14, 16), Feintgine::Color(255, 100, 100, 255),
// 						Feintgine::SpriteManager::Instance()->getSprite("character/reimu_projectile_1.png"),
// 						2, 2.5f, m_particleBatch);

					bullet->init(glm::vec2(m_pos.x + offsetX, desRect.y), glm::vec2(14, 16),
						Feintgine::Color(255, 255, 255, 200),
						"Assets/F_AObjects/reimu_homing.xml", 2, 2.5, m_particleBatch);
					bullet->setBulletAnimationAction("default");
					bullet->setScale(glm::vec2(1.2f));
					//bullet.setVel(glm::vec2(0 + destination * -0.1f, 10));
					m_bullets.push_back(bullet);
					
				}
				break;
				case BULLET_TYPE_MARISA_ROCKET:
				{
					F_MarisaRocket_small * t_bullet = new F_MarisaRocket_small();
					t_bullet->init(glm::vec2(desRect.x , desRect.y), glm::vec2(16, 12),
						Feintgine::Color(255, 255, 255, 200),
						"Assets/F_AObjects/marisa_rocket_small.xml", 2, 4.0, m_particleBatch);
					t_bullet->setBulletAnimationAction("default");
					t_bullet->setDirection(getRocketDirection(enemies));
					t_bullet->setLightColoFlag(0);
					m_bullets_a.push_back(t_bullet);
				}
				break;
				
				case BULLET_TYPE_REIMU_NEEDLE:
				{
					F_ReimuWave * t_bullet = new F_ReimuWave();
					t_bullet->init(glm::vec2(m_pos.x + offsetX, desRect.y), glm::vec2(16, 12),
						Feintgine::Color(255, 255, 255, 200),
						"Assets/F_AObjects/reimu_wave.xml", 2, 4.0, m_particleBatch);
					t_bullet->setBulletAnimationAction("default");
					t_bullet->setBulletAnimationAngle(degreeToRad(90));
					m_bullets_b.push_back(t_bullet);
				}

				break;

				case BULLET_TYPE_MARISA_LASER:
					m_laser.setVisible(true);
					//syncLaser();
					break;
				default:
					break;
				}
				fireRate = 0.0f;
			}
			
		}
		else
		{
			isPeak = true;
			
// 			if (!isFocusLaserOff)
// 			{
// 				m_laserFocus.setVisible(false);
// 				isFocusLaserOff = true;
// 			}
			//fireRate += 0.1f * deltaTime;
			if (m_type == 1)
			{

				if (!isLaserOff)
				{
					m_laser.setVisible(false);
					isLaserOff = true;
					//syncLaser();

				}
				if (m_isLeft)
				{
					
					if (fireRate >= delayBullet)
					{
						switch (m_bulletType)
						{
						case BULLET_TYPE_REIMU_HOMING:
						{
// 							F_HomingBullet * bullet = new F_HomingBullet();
// 							bullet->init(glm::vec2(m_pos.x + offsetX, m_pos.y )
// 								, glm::vec2(18, 20), Feintgine::Color(255, 255, 255, 120),
// 								Feintgine::SpriteManager::Instance()->getSprite("character/reimu_focus_1.png"), 4, 7.5f, m_particleBatch);
							

							F_HomingBullet *bullet = new F_HomingBullet();
					
							bullet->init(glm::vec2(m_pos.x , m_pos.y), glm::vec2(14, 16),
								Feintgine::Color(255, 255, 255, 200),
								"Assets/F_AObjects/reimu_homing_big.xml", 2, 2.5, m_particleBatch);
							bullet->setBulletAnimationAction("default");
							bullet->setScale(glm::vec2(0.7f));
							//bullet.setVel(glm::vec2(0 + destination * -0.1f, 10));
							m_bullets.push_back(bullet);

		
						}
						break;
						case BULLET_TYPE_MARISA_ROCKET:
						{
							F_MarisaRocket_small * t_bullet = new F_MarisaRocket_small();
							t_bullet->init(glm::vec2(desRect.x , desRect.y + 7), glm::vec2(24, 12),
								Feintgine::Color(255, 255, 255, 200),
								"Assets/F_AObjects/marisa_rocket_big.xml", 2, 10.0f, m_particleBatch);
							t_bullet->setBulletAnimationAction("default");
							t_bullet->setLightColoFlag(1);
							t_bullet->setDirection(getRocketDirection(enemies));
							t_bullet->setScale(1.3f);
							t_bullet->setParticleType(2);
							m_bullets_a.push_back(t_bullet);
						}
						break;
						case BULLET_TYPE_REIMU_NEEDLE:
						{
							F_ReimuWave * t_bullet = new F_ReimuWave();
							t_bullet->init(glm::vec2(desRect.x +7.0f, desRect.y + 7), glm::vec2(30, 8),
								Feintgine::Color(255, 255, 255, 255),
								"Assets/F_AObjects/reimu_wave.xml", 2, 4.0, m_particleBatch);
							t_bullet->setBulletAnimationAction("default");
							t_bullet->setScale(glm::vec2(1.7f));
							t_bullet->setBulletAnimationAngle(degreeToRad(90));
							m_bullets_b.push_back(t_bullet);
						}

						break;
						case BULLET_TYPE_MARISA_LASER:
						{

							m_laserFocus.setVisible(true);
							//syncLaser(deltaTime);
						}
						break;
						
						default:
							break;
						}
						
						fireRate = 0.0f;
					}
				}
			}
			if (m_type == 2) 
			{
				if (m_isFocus)
				{
					//fireRate += 0.1f * deltaTime;
					if (fireRate >= delayBullet)
					{
						switch (m_bulletType)
						{
						case BULLET_TYPE_REIMU_HOMING:
						{
							F_HomingBullet *bullet = new F_HomingBullet();
							// 					bullet->init(glm::vec2(desRect.x, desRect.y)
							// 						, glm::vec2(14, 16), Feintgine::Color(255, 100, 100, 255),
							// 						Feintgine::SpriteManager::Instance()->getSprite("character/reimu_projectile_1.png"),
							// 						2, 2.5f, m_particleBatch);

							bullet->init(glm::vec2(desRect.x, desRect.y), glm::vec2(14, 16),
								Feintgine::Color(255, 255, 255, 200),
								"Assets/F_AObjects/reimu_homing.xml", 2, 2.5, m_particleBatch);
							bullet->setBulletAnimationAction("default");
							bullet->setScale(glm::vec2(1.2f));
							//bullet.setVel(glm::vec2(0 + destination * -0.1f, 10));
							m_bullets.push_back(bullet);
						}
						break;
						case BULLET_TYPE_MARISA_ROCKET:
						{
							F_MarisaRocket_small * t_bullet = new F_MarisaRocket_small();
							t_bullet->init(glm::vec2(desRect.x, desRect.y), glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 200),
								"Assets/F_AObjects/marisa_rocket_small.xml", 2, 4.0, m_particleBatch);
							t_bullet->setBulletAnimationAction("default");
							t_bullet->setLightColoFlag(0);
							t_bullet->setDirection(getRocketDirection(enemies));
							//t_bullet->setBulletAnimationAngle(degreeToRad(90));
							m_bullets_a.push_back(t_bullet);
						}
						break;
						case BULLET_TYPE_REIMU_NEEDLE:
						{
							F_ReimuWave * t_bullet = new F_ReimuWave();
							t_bullet->init(glm::vec2(desRect.x, desRect.y), glm::vec2(16, 12),
								Feintgine::Color(255, 255, 255, 200),
								"Assets/F_AObjects/reimu_double_projectile.xml", 2, 4.0, m_particleBatch);
							t_bullet->setBulletAnimationAction("default");
							t_bullet->setBulletAnimationAngle(degreeToRad(90));
							m_bullets_b.push_back(t_bullet);
						}

						break;
						case BULLET_TYPE_MARISA_LASER:
						{
							m_laser.setVisible(true);
							//syncLaser();
							//isLaserOff = false;
						}
						break;

						default:
							break;
						}

						fireRate = 0.0f;
					}
				}
			}
		}		
	}
	else
	{
		if (m_bulletType == BULLET_TYPE_MARISA_LASER)
		{
			
			m_color = Feintgine::Color(255, 255, 255, 255);
			if (!isLaserOff)
			{
				m_laser.setVisible(false);
				isLaserOff = true;
				//syncLaser();

			}
			if (!isFocusLaserOff)
			{
				m_laserFocus.setVisible(false);
				isFocusLaserOff = true;
				//syncLaser();
			}
		}
		
	}
	for (auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(deltaTime,enemies);
		if (!m_bullets[i]->isAlive())
		{
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
		}	
	}
	for (auto i = 0; i < m_bullets_a.size(); i++)
	{
		m_bullets_a[i]->update(deltaTime, enemies);
		if (!m_bullets_a[i]->isAlive())
		{
			delete m_bullets_a[i];
			m_bullets_a.erase(m_bullets_a.begin() + i);
		}
	}
	for (auto i = 0; i < m_bullets_b.size(); i++)
	{
		m_bullets_b[i]->update(deltaTime, enemies);
		if (!m_bullets_b[i]->isAlive())
		{
			delete m_bullets_b[i];
			m_bullets_b.erase(m_bullets_b.begin() + i);
		}
	}
	m_attentionua = t_attentionua * (m_stack + 1.0f);
}


void F_PlayerAccessory::setBoolRotate(bool val)
{
	m_isRotate = val;
}

void F_PlayerAccessory::setBoolFocus(bool val)
{
	m_isFocus = val;
}

void F_PlayerAccessory::setPos(const glm::vec2 & pos)
{

	m_pos = pos;

}

void F_PlayerAccessory::setType(int val)
{
	m_type = val;
}

void F_PlayerAccessory::setFire(bool val)
{
	m_isFire = val;
}

glm::vec2 F_PlayerAccessory::getOffsetedPos()
{
	glm::vec2 retPos;
	retPos = m_pos + m_additionalPos;
	retPos.x = retPos.x + offsetX;
	return retPos;
}

glm::vec2 F_PlayerAccessory::getOffsetPosFocus()
{
	glm::vec2 retPos;
	retPos = m_pos + m_additionalPos;
	retPos.x = retPos.x + offsetX + 8.0f;
	retPos.y = retPos.y ;
	return retPos;
}

void F_PlayerAccessory::setBulletType(int val)
{
	m_bulletType = val;
	switch (m_bulletType)
	{
	case 1:
		delayBullet = 0.75f;
		break;
	case 2:
		delayBullet = 1.25f;
		break;
	default:
		break;
	}
}

void F_PlayerAccessory::clearBullet()
{
	m_bullets.clear();
}

void F_PlayerAccessory::initLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos,
	const glm::vec2 & dim, const Feintgine::Color & color, float depth, float angle, float dps,
	const Feintgine::F_Sprite & starSprite)
{
	m_laser.init(texture, pos, dim, color, depth, angle, dps,starSprite,0.8f);
	m_laser.setMaxMinColorVal(1.0f, -0.0001f);
	m_laser.setStarScale(0.7f);
}

void F_PlayerAccessory::initFocusLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos,
	const glm::vec2 & dim, const Feintgine::Color & color, float depth, float angle, float dps, 
	const Feintgine::F_Sprite & starSprite)
{
	m_laserFocus.init(texture, pos, dim, color, depth, angle, dps,starSprite,0.69f);
	m_laserFocus.setAttenuation(glm::vec3(9.0f, 15.0f, 35.0f));
	m_laserFocus.setMaxMinColorVal(1.0f, -0.0001f);
}

bool F_PlayerAccessory::changeColor(int channel, float rate, float maxVal)
{
	return m_color.change(channel, rate, maxVal);
}

void F_PlayerAccessory::resetStack()
{
	m_stack = 0;
	fireRate = 0.0f;
}

void F_PlayerAccessory::setParentColor(bool val)
{
	isParentColor = val;
}

std::vector<F_BulletBase *> F_PlayerAccessory::getBullets()
{
	//std::cout << "called " << m_type << "\n";
	std::vector<F_BulletBase *> returnVal;
	switch (m_bulletType)
	{
	case BULLET_TYPE_REIMU_HOMING:
		for (int i = 0; i < m_bullets.size(); i++)
		{
			returnVal.push_back(static_cast<F_BulletBase*>(m_bullets[i]));
		}
		break;

	case BULLET_TYPE_MARISA_ROCKET:
		//std::cout << "hit \n";
		for (int i = 0; i < m_bullets_a.size(); i++)
		{
			//std::cout << "test \n";
			returnVal.push_back(static_cast<F_BulletBase*>(m_bullets_a[i]));
		}
		break;

	case BULLET_TYPE_REIMU_NEEDLE:
		for (int i = 0; i < m_bullets_b.size(); i++)
		{
			returnVal.push_back(static_cast<F_BulletBase*>(m_bullets_b[i]));
		}
		break;

	case BULLET_TYPE_MARISA_LASER:
		{	
			// do nothing
		}
		break;
		default:
			break;
	}
	
	//std::cout << "return state \n";
	return returnVal;

	
}

void F_PlayerAccessory::syncLaser(float deltaTime)
{
	
	
	//GlobalValueClass::Instance()->setLaserEnergy(m_energy);



}

void F_PlayerAccessory::setLaserEnergy(float value)
{
 	if (m_bulletType == BULLET_TYPE_MARISA_LASER)
 	{
		m_laser.setEnergy(value);
		if (m_isLeft)
		{
			m_laserFocus.setEnergy(value);
		}
		
	}
	
}

float F_PlayerAccessory::getLaserEnergy()
{
	 return m_laser.getEnergy(); 
}

glm::vec2 F_PlayerAccessory::getRocketDirection(std::vector<FairyBase *> enemies)
{
	glm::vec2 returnVec = glm::vec2(0, 1.0f);
	F_BaseEnemy * enemy = getNearstEnemy(m_pos, enemies);

	if (enemy)
	{
		returnVec = glm::normalize(enemy->getPos() - m_pos);
	}
	
	return returnVec;
}

F_BaseEnemy * F_PlayerAccessory::getNearstEnemy(const glm::vec2 & pos, std::vector<FairyBase *> enemy)
{
	F_BaseEnemy * nearstEnemy = nullptr;

	float nearest = 1000.0f;

	for (int i = 0; i < enemy.size(); i++)
	{
		glm::vec2 disVec = enemy[i]->getPos() - pos;
		float distance = glm::length(disVec);
		if (!enemy[i]->isDeath())
		{
			if (distance < nearest)
			{
				nearest = distance;
				nearstEnemy = enemy[i];

			}
		}
	}

	return nearstEnemy;
}

EnemyAmplifier * F_PlayerAccessory::getNearstAmplifier(const glm::vec2 & pos, std::vector<EnemyAmplifier *> enemy)
{
	EnemyAmplifier * nearstEnemy = nullptr;

	float nearest = 1000.0f;

	for (int i = 0; i < enemy.size(); i++)
	{
		glm::vec2 disVec = enemy[i]->getPos() - pos;
		float distance = glm::length(disVec);
		if (!enemy[i]->isDeath())
		{
			if (distance < nearest)
			{
				nearest = distance;
				nearstEnemy = enemy[i];

			}
		}
	}

	return nearstEnemy;
}

