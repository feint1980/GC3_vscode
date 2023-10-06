#include "F_Marisa_Star_Trail_Manager.h"



F_Marisa_Star_Trail_Manager::F_Marisa_Star_Trail_Manager()
{

}


F_Marisa_Star_Trail_Manager::~F_Marisa_Star_Trail_Manager()
{
}

void F_Marisa_Star_Trail_Manager::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_trails.size(); i++)
	{
	
		m_trails[i]->draw(spriteBatch);
			
	}
}

void F_Marisa_Star_Trail_Manager::drawLight(Feintgine::LightBatch & lightBatch)
{
	for (int i = 0; i < m_trails.size(); i++)
	{
		m_trails[i]->drawLight(lightBatch);
	}
	for (int i = 0; i < m_laserTrails.size(); i++)
	{
		m_laserTrails[i]->drawLight(lightBatch);
	}
}

void F_Marisa_Star_Trail_Manager::update(const glm::vec2 & pos, float deltaTime, std::vector<F_BaseEnemy *> enemy, std::vector<EnemyBulletBase * > bullets)
{

	if (m_isLeaveTrail)
	{
		m_currentTrailCounter += 0.1f * deltaTime;
 		if (m_currentTrailCounter > m_trailThreshold)
 		{
			glm::vec2 vel = glm::vec2(0, 6.0f);
			pos.y + 5.0f;
			F_Marisa_Star_Trail * star = new F_Marisa_Star_Trail();

			int colorIndex = m_count % 5;
			//getStarColor(colorIndex)

			float t_angle = getAngleSpawn(m_count);

			vel.x = feint_common::Instance()->randomFloat(-3.5,3.5);
			vel.y = feint_common::Instance()->randomFloat(-3.5, 3.5);
			//star->registerAudioEngine(m_audioEngine);
			//star->loadStarSound("Sounds/sfx/star_start.wav");
			//star->loadEndSound("Sounds/sfx/star_end.wav");
			
			star->init(glm::vec2(0.1f), m_starAnim,
				getStarColor(m_count % 5), vel, pos, 10, 0.3f);
			star->setLifeTime(4.0f);
			//star->setN
			//star->setA
			//star->setNumberOfParticle(1);
			star->registerParticleBatch(m_hitParticleBatch);

			m_trails.push_back(star);
			m_count++;
			m_currentTrailCounter = 0;

		}
	}

	for (int i = 0; i < m_trails.size(); i++)
	{
		if (m_trails[i]->isRemoved())
		{

			m_trails.erase(m_trails.begin() + i);
		}
		else
		{
			m_trails[i]->update(deltaTime, enemy, bullets);

		}
	}

	for (int i = 0; i < m_laserTrails.size(); i++)
	{
		if (m_laserTrails[i]->isRemoved())
		{

			m_laserTrails.erase(m_laserTrails.begin() + i);
		}
		else
		{
			m_laserTrails[i]->update(deltaTime, enemy, bullets);

		}
	}
}

void F_Marisa_Star_Trail_Manager::init(const Feintgine::F_AnimatedObject & starAnim, float trailThreshold)
{
	m_starAnim = starAnim;
	m_trailThreshold = trailThreshold;
}

void F_Marisa_Star_Trail_Manager::setTrailThreshold(float val)
{
	m_trailThreshold = val;
}

void F_Marisa_Star_Trail_Manager::registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch)
{
	m_hitParticleBatch = particleBatch;
}

void F_Marisa_Star_Trail_Manager::spawnLaserTrait(const glm::vec2 & pos, const glm::vec3 & attenuation,
	int colorFlag, Feintgine::Color color,float angle)
{
	F_Marisa_Laser_trail * laserTrail = new F_Marisa_Laser_trail();
	laserTrail->spawn(pos, attenuation, colorFlag, color);
	laserTrail->setAngle(angle);
	m_laserTrails.push_back(laserTrail);
}

Feintgine::Color F_Marisa_Star_Trail_Manager::getStarColor(int index)
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
		returnVal = Feintgine::Color(255, 255, 255, 255);
		break;
	}

	return returnVal;
}

void F_Marisa_Star_Trail_Manager::setLeaveTrail(bool val)
{
	m_isLeaveTrail = val;
}

float F_Marisa_Star_Trail_Manager::getAngleSpawn(int index)
{
	float returnAngle = 0.0f;
	float angleScale = degreeToRad(12);

	int cIndex = index % 5;

	int tIndex = ((float)cIndex * 0.5f) + 0.9f;

	returnAngle = returnAngle + angleScale * tIndex;
	if (cIndex % 2)
	{
		returnAngle = -returnAngle;
	}

	return returnAngle;
}
