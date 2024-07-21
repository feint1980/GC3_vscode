#include "F_MarisaStarSpawner.h"
#include "GlobalValueClass.h"


F_MarisaStarSpawner::F_MarisaStarSpawner()
{

}


F_MarisaStarSpawner::~F_MarisaStarSpawner()
{

}

void F_MarisaStarSpawner::spawn(int count, float rotationCurve, float spawnRate1)
{
	m_count = count;
	m_angleDelta = rotationCurve;
	m_spawnRate = spawnRate1;
	m_spawnCounter = m_spawnRate;
	m_index = 0;

}

void F_MarisaStarSpawner::loadStar(const Feintgine::F_AnimatedObject & animation)
{
	m_starAnim = animation;
}

void F_MarisaStarSpawner::loadStar(const std::string & animationPath)
{
	m_starAnim.init(animationPath);
}

Feintgine::Color F_MarisaStarSpawner::getStarColor(int index)
{
	Feintgine::Color returnVal;

	float intensity =  255.0f;
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
		returnVal = Feintgine::Color(intensity, t_offset, intensity,255);
		break;
	case 5:
		returnVal = Feintgine::Color(t_offset, intensity, intensity, 255);
		break;

	default:
		returnVal = glm::vec4(255,255,255,255);
		break;
	}

	return returnVal;
}

void F_MarisaStarSpawner::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_stars.size(); i++)
	{
		m_stars[i]->draw(spriteBatch);
	}
}

void F_MarisaStarSpawner::update(float deltaTime ,std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets, const glm::vec2 & pos)
{
	updateSpawn(deltaTime,pos);
	
	for (int i = 0; i < m_stars.size(); i++)
	{	
		if (m_stars[i]->isRemoved())
		{

			m_stars.erase(m_stars.begin() + i);
		}
		else
		{
			m_stars[i]->update(deltaTime,enemy,bullets);
			
		}
		
	}
}

void F_MarisaStarSpawner::drawLight(Feintgine::LightBatch & lightBatch)
{
	for (int i = 0; i < m_stars.size(); i++)
	{
		m_stars[i]->drawLight(lightBatch);
	}
}

void F_MarisaStarSpawner::updateSpawn(float deltaTime, const glm::vec2 & pos)
{
	//std::cout << m_spawnCounter << "\n";
	if (m_count > 0)
	{
		m_spawnCounter += 0.1f * deltaTime;
		if (m_spawnCounter > m_spawnRate)
		{
			glm::vec2 vel = glm::vec2(0, 6.0f);
			// glm::vec2 pos = GlobalValueClass::Instance()->getPlayer()->getPos();
			pos.y + 5.0f;
			F_MarisaStar * star = new F_MarisaStar();

			int colorIndex = m_count % 5;
			//getStarColor(colorIndex)

			float t_angle = getAngleSpawn(m_index);

			vel.x = vel.x * cos(t_angle) - vel.y * sin(t_angle);
			vel.y = vel.x * sin(t_angle) + vel.y * cos(t_angle);
			star->registerAudioEngine(m_audioEngine);
			star->loadStarSound("Sounds/sfx/star_start.wav");
			star->loadEndSound("Sounds/sfx/star_end.wav");
			star->init(glm::vec2(1.0f), m_starAnim, 
				getStarColor(m_index %5), vel, pos,10, 0.3f);
			star->registerParticleBatch(m_hitParticleBatch);
			
			m_stars.push_back(star);
			m_count--;
			m_spawnCounter = 0;
			m_index++;
			//std::cout  << "spawn \n";
		}
	
	}
}



void F_MarisaStarSpawner::addStar(const F_MarisaStar & star)
{
	//m_stars.push_back(star);
}

float F_MarisaStarSpawner::getAngleSpawn(int index)
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

void F_MarisaStarSpawner::registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch)
{
	m_hitParticleBatch = particleBatch;
}

void F_MarisaStarSpawner::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
}


