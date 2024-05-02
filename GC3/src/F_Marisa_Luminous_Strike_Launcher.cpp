#include "F_Marisa_Luminous_Strike_Launcher.h"
#include "GlobalValueClass.h"


F_Marisa_Luminous_Strike_Launcher::F_Marisa_Luminous_Strike_Launcher()
{
	m_mainStrike = new F_Marisa_Luminous_Strike();
	m_count = 0;

	m_totalCount;

	m_spawnCounter = 0.0f;

	m_launchCounter = 0.0f;
	m_launchTime = 0.0f;

	m_launched = false;
}


F_Marisa_Luminous_Strike_Launcher::~F_Marisa_Luminous_Strike_Launcher()
{
}

void F_Marisa_Luminous_Strike_Launcher::chargeStar(int count)
{
	m_count = count;
	m_totalCount = count;

	m_launchTime = m_count * 0.1f + 6.4f;
	m_launched = false;
	m_launchCounter = 0.0f;

	if (m_audioEngine)
	{
		m_chargeSound.setVolume(10);
		m_chargeSound.playInChannel(0,2);
	}

	
	//std::cout << "called \n";

// 	glm::vec2 targetPos = GlobalValueClass::Instance()->getPlayer()->getPos();
// 	for (int i = 0; i < count; i++)
// 	{
// 		float radius = feint_common::Instance()->randomFloat(200, 400);
// 
// 		float splitAngle = degreeToRad(360.0f / count) * i ;
// 		glm::vec2 spawnPos = glm::vec2(cos(splitAngle ) * radius, sin(splitAngle ) * radius) + targetPos;
// 		//glm::vec2 spawnPos(100);
// 		F_Marisa_Luminous_Charge * chargePoint = new F_Marisa_Luminous_Charge();
// 		chargePoint->init(glm::vec2(1.5f), m_chargeAnimation, Feintgine::Color(255, 255, 100, 200),
// 			glm::vec2(1), spawnPos);
// 		m_chargeStar.push_back(chargePoint);
// 
// 	}
 }

void F_Marisa_Luminous_Strike_Launcher::draw(Feintgine::SpriteBatch & spriteBatch)
{
	//mainStrike.draw(spriteBatch);
	for (int i = 0; i < m_chargeStar.size(); i++)
	{
		m_chargeStar[i]->draw(spriteBatch);
	}
	if (m_mainStrike )
	{
		m_mainStrike->draw(spriteBatch);
	}
}

void F_Marisa_Luminous_Strike_Launcher::update(float deltaTime,std::vector<FairyBase *> enemy, std::vector<EnemyBulletBase * > bullets)
{
 	//m_mainStrike.update(deltaTime, enemy, bullets);
// 
	updateSpawn(deltaTime);
	for (int i = 0; i < m_chargeStar.size(); i++)
	{
		if (m_chargeStar[i]->isRemoved())
		{
			//std::cout << "remove " << i << "\n";
			m_chargeStar.erase(m_chargeStar.begin() + i);
		}
		m_chargeStar[i]->update(deltaTime, enemy, bullets);
	}
	if (m_mainStrike)
	{
// 		if (m_mainStrike->isRemoved())
// 		{
// 			//delete m_mainStrike;
// 			m_mainStrike = nullptr;
// 		}
		m_mainStrike->update(deltaTime, enemy, bullets);
	}

}

void F_Marisa_Luminous_Strike_Launcher::drawLight(Feintgine::LightBatch & lightBatch)
{
	
	if (m_mainStrike )
	{
		m_mainStrike->drawLight(lightBatch);
	}
	for (int i = 0; i < m_chargeStar.size(); i++)
	{
		m_chargeStar[i]->drawLight(lightBatch);
	}
}

void F_Marisa_Luminous_Strike_Launcher::updateSpawn(float deltaTime)
{
	//float radius = 0.0f;
	if (m_count > 0)
	{
		m_spawnCounter += 0.1f * deltaTime;
		if (m_spawnCounter > 0.1f)
		{

			float radius = feint_common::Instance()->getRandomNum(300, 500);
			float splitAngle = degreeToRad(feint_common::Instance()->getRandomNum(0, 360));
			glm::vec2 spawnPos = glm::vec2(cos(splitAngle) * radius, sin(splitAngle) * radius) + GlobalValueClass::Instance()->getPlayer()->getPos();
			//glm::vec2 spawnPos(100);
			F_Marisa_Luminous_Charge * chargePoint = new F_Marisa_Luminous_Charge();
			Feintgine::Color tColor = getStarColor(m_count % 5);
			tColor.a = 0.3f;
			chargePoint->init(glm::vec2(feint_common::Instance()->randomFloat(0.3f, 0.8f)), m_chargeAnimation, tColor/*Feintgine::Color(255, 255, 100, 150)*/,
				glm::vec2(1), spawnPos, 2, 0.3f);
			chargePoint->setFPlayer(GlobalValueClass::Instance()->getPlayer());
			m_chargeStar.push_back(chargePoint);
			m_count--;
			m_spawnCounter = 0;
		}

		
		}
	if (!m_launched)
	{
		m_launchCounter += 0.1f * deltaTime;
		if (m_launchCounter > m_launchTime)
		{
			//std::cout << "launch \n";
			m_launched = true;
			glm::vec2 vel = glm::vec2(0, 21.0f);
			glm::vec2 pos = GlobalValueClass::Instance()->getPlayer()->getPos();
			pos.y + 5.0f;
			//m_mainStrike = new F_Marisa_Luminous_Strike();

			int colorIndex = m_count % 5;
			//getStarColor(colorIndex)

			m_mainStrike->init(glm::vec2(1.0f), m_chargeAnimation,
				Feintgine::Color(255, 255, 255, 200), vel, pos, 10, 0.3f);
			//m_mainStrike->registerParticleBatch(m_hitParticleBatch);
			//m_mainStrike->setLifeTime(3.0f);
		}
	}


}

void F_Marisa_Luminous_Strike_Launcher::loadAnimation(const std::string & animationPath)
{

	m_chargeAnimation.init(animationPath);

}

void F_Marisa_Luminous_Strike_Launcher::registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch)
{
	m_hitParticleBatch = particleBatch;
	m_mainStrike->registerParticleBatch(m_hitParticleBatch);
}

Feintgine::Color F_Marisa_Luminous_Strike_Launcher::getStarColor(int index)
{
	Feintgine::Color returnVal;

	float intensity = 255.0f;
	float t_offset = intensity * 0.3f;
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

void F_Marisa_Luminous_Strike_Launcher::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
	m_chargeSound = m_audioEngine->loadSoundEffect("Sounds/sfx/luminous_charge.wav");
	m_chargeSound.setVolume(10);
	m_chargeSound.stahp();
	m_mainStrike->registerAudioEngine(m_audioEngine);
	m_mainStrike->loadStarSound("Sounds/sfx/luminous_cast.wav");
	m_mainStrike->loadEndSound("Sounds/sfx/luminous_luminating.wav");

}



