#include "F_Player_Sun_Manager.h"



#define MAX_ROTATION_RATE  0.175f
#define MIN_ROTATION_RATE  0.1f
#define LOWER_ROTATION_RATE 0.4f
#define LOWER_ROTATION_LASER_FOCUS_RATE 0.5f
#define LOWER_ROTATION_UNFOCUS_RATE 1.6f


F_Player_Sun_Manager::F_Player_Sun_Manager()
{

}


F_Player_Sun_Manager::~F_Player_Sun_Manager()
{
}

void F_Player_Sun_Manager::update(const glm::vec2 &  pos,float deltaTime,
	std::vector<F_BaseEnemy *> enemies, std::vector<EnemyGuardian *> guardians, 
	std::vector<EnemyAmplifier *> amplifiers, std::vector<EnemyBulletBase * > bullets)
{

	

	m_pos = pos;

	t_radius = m_radius + m_additionalRad * (cos(m_angle) +1.0F);
	m_angle += m_angleRate * deltaTime;
	if (m_lifeTime > 0.0f)
	{

		m_lifeTime -= 0.1f * deltaTime;
		
	}


	for (int i = 0; i < m_suns.size(); i++)
	{
		if (m_suns[i]->isAlive())
		{
			m_suns[i]->update(deltaTime, enemies, guardians, amplifiers, bullets);
		}
		else
		{
			m_suns.erase(m_suns.begin() + i);
		}
	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (!m_bullets[i]->isAlive())
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
		m_bullets[i]->update(deltaTime, enemies, guardians, amplifiers);
	}

	for (int i = 0; i < m_refSuns.size(); i++)
	{
		glm::vec2 t_pos;
		float calculatedAngle = m_angle + degreeToRad(360.0f / m_refSuns.size()) * i;
		t_pos.x = cos(calculatedAngle) * t_radius;
		t_pos.y = sin(calculatedAngle) * t_radius;

		if (!m_refSuns[i]->isDone())
		{
			m_refSuns[i]->setPos(m_pos + t_pos);
			m_refSuns[i]->setAngle(calculatedAngle);
		}
		else
		{
			m_refSuns.erase(m_refSuns.begin() + i);
		}
		if (!m_refSuns[i]->isAlive())
		{
			m_refSuns.erase(m_refSuns.begin() + i);
		}
	}

	if (m_isNonDirectionLaser)
	{
		m_angleRate_nonDirect = LOWER_ROTATION_RATE;
		if (m_suns.size() == 0)
		{
			m_isNonDirectionLaser = false;
			m_angleRate_nonDirect = 1.0f;
			m_balanceUnfocusRate = 1.0f;
		}
		//std::cout << m_angleRate << "\n";
	}
	else
	{
		if (m_isFire)
		{

			handleFire(deltaTime);
			handleBullets();

		}
		else
		{
			offLaser();
		}
		if (m_lifeTime <= 1.5f || !m_isFocus)
		{
			offLaser();
		}
	}
	

	if (m_isFocus)
	{
		if (m_additionalRad >= 10.0f)
		{
			m_additionalRad -= 1.25f * deltaTime;
		}
		else
		{
			m_additionalRad = 10.0f;
		}

		if (m_angleRate <= MAX_ROTATION_RATE * (m_angleRate_nonDirect * m_balancefocusRate))
		{
			m_angleRate += 0.01f * deltaTime;
		}
		else
		{
			m_angleRate = MAX_ROTATION_RATE * (m_angleRate_nonDirect  * m_balancefocusRate);
		}
	}
	else
	{
		if (m_additionalRad <= 40.0f)
		{
			m_additionalRad += 1.25f * deltaTime;
		}
		else
		{
			m_additionalRad = 40.0f;
		}
		if (m_angleRate >= MIN_ROTATION_RATE * (m_angleRate_nonDirect * m_balanceUnfocusRate ))
		{
			m_angleRate -= 0.01f * deltaTime;
		}
		else
		{
			m_angleRate = MIN_ROTATION_RATE * (m_angleRate_nonDirect * m_balanceUnfocusRate);
		}
	}

	


}

void F_Player_Sun_Manager::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_suns.size(); i++)
	{
		m_suns[i]->draw(spriteBatch);
	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
}

void F_Player_Sun_Manager::drawLight(Feintgine::LightBatch & lightBatch)
{
	for (int i = 0; i < m_suns.size(); i++)
	{
		m_suns[i]->drawLight(lightBatch);
	}
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->drawLight(lightBatch);
	}
}

void F_Player_Sun_Manager::setFocus(bool value)
{
	m_isFocus = value;
	
// 	for (int i = 0; i < m_suns.size(); i++)
// 	{
// 		//m_suns[i]->
// 	}
}

void F_Player_Sun_Manager::setFire(bool value)
{
	m_isFire = value;

}

void F_Player_Sun_Manager::init(const glm::vec2 & pos)
{
	m_pos = pos;
	
}

Feintgine::Color F_Player_Sun_Manager::getSunColor(int index)
{
	Feintgine::Color returnVal;

	float intensity = 255.0f;
	float t_offset = intensity * 0.1f;
	switch (index)
	{
	case 0:
		returnVal = Feintgine::Color(intensity, t_offset, t_offset, 255);
		break;
	case 1:
		returnVal = Feintgine::Color(t_offset, intensity, t_offset, 255);
		break;
	case 2:
		returnVal = Feintgine::Color(t_offset, t_offset, intensity, 255);
		break;
	case 3:
		returnVal = Feintgine::Color(intensity, intensity, t_offset, 255);
		break;
	case 4:
		returnVal = Feintgine::Color(intensity, t_offset, intensity, 255);
		break;
	case 5:
		returnVal = Feintgine::Color(t_offset, intensity, intensity, 255);
		break;

	default:
		returnVal = glm::vec4(255, 255, 255, 255);
		break;
	}

	return returnVal;
}

void F_Player_Sun_Manager::handleFire(float deltaTime)
{

	if (!m_isFocus)
	{


		m_fireCount += m_fireRate * deltaTime;

		if (m_fireCount >= m_fireThreshold)
		{
			// fire here
			for (int i = 0; i < m_suns.size(); i++)
			{
				m_suns[i]->fireNormal();
			}
			m_fireCount = 0.0f;
		}
	}
	else 
	{
		for (int i = 0; i < m_suns.size(); i++)
		{
			m_suns[i]->showLaser(true);
		}
		//m_fireCount = 0.0f;
		//m_laser.setVisible(true);
	}
}

void F_Player_Sun_Manager::handleBullets()
{
	for (int i = 0; i < m_suns.size(); i++)
	{
		if (m_suns[i]->m_bullets.size() > 0)
		{
			for (int c = 0; c < m_suns[i]->m_bullets.size(); c++)
			{
				//m_enemies[i]->m_bullets[c]->initLogic(m_world.get());
				m_bullets.push_back(m_suns[i]->m_bullets[c]);
			}
			m_suns[i]->m_bullets.clear();
		}
	}
}

void F_Player_Sun_Manager::offLaser()
{
	for (int i = 0; i < m_suns.size(); i++)
	{
		m_suns[i]->showLaser(false);
	}
}

void F_Player_Sun_Manager::setParticle(Feintgine::ParticleBatch2D * particleBatch)
{
	m_particleBatch = particleBatch;
}

void F_Player_Sun_Manager::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
	m_startSound = audioEngine->loadSoundEffect("Sounds/sfx/master_spark.wav");

}

void F_Player_Sun_Manager::spawn(int count, float lifeTime)
{
	m_isNonDirectionLaser = false;
	m_lifeTime = lifeTime;
	for (int i = 0; i < count; i++)
	{

		int d = (i % 6) +1;
		std::string loadPath = "Assets/F_AObjects/marisa_sun_";
		loadPath.append(std::to_string(d));
		loadPath.append(".xml");

		F_Orreries_Sun * sun = new F_Orreries_Sun();
		sun->init(loadPath, i);
		sun->spawn(lifeTime);
		sun->initLaser(Feintgine::ResourceManager::getTexture("Assets/Textures/marisa_laser_small.png"),
			m_pos, glm::vec2(1280, 13), Feintgine::Color(0, 0, 0, 0), 10, degreeToRad(-90), 5.0f,
			Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_projectile_star_2.png"));
		sun->registerParticle(m_particleBatch);
		//sun->registerAudioEngine(m_audioEngine);
		m_suns.push_back(sun);
		m_refSuns.push_back(sun);
	}
}

void F_Player_Sun_Manager::activeNondirectionLaser()
{

	
	m_balanceUnfocusRate = 2.5f;
	m_balancefocusRate = 0.6f;
	m_startSound.play();
	
	for (int i = 0; i < m_suns.size(); i++)
	{
		m_suns.erase(m_suns.begin() + i);

		m_refSuns.erase(m_refSuns.begin() + i);

	}
	m_suns.clear();
	m_refSuns.clear();
	//int total = 6 - m_suns.size();		
	spawn(6, 10.0f);
	m_isNonDirectionLaser = true;
	for (int i = 0; i < m_suns.size(); i++)
	{
		m_suns[i]->fireNonDirectionLaser();
	}
}

