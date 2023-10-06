#include "IceWall.h"



IceWall::IceWall()
{
}


IceWall::~IceWall()
{
}



void IceWall::init()
{
	for (int i = 1; i <= 4; i++)
	{
		std::string strSearch = "effect_iced/effect_ice_bullet_0";
		strSearch.append(std::to_string(i));
		strSearch.append(".png");
		Feintgine::F_Sprite sprite = Feintgine::SpriteManager::Instance()->getSprite(strSearch);
		m_sprites.push_back(sprite);
	}


}



void IceWall::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{

	for (int i = 1; i <= 3; i++) // total has 3 sound effects, start with 1
	{
		
		std::string loadFile = "Sounds/sfx/ice_effect/ice_eff_" + std::to_string(i) + ".wav";

		//std::cout << "check load file " << loadFile << "\n";

		Feintgine::SoundEffect iceSFX = audioEngine->loadSoundEffect(loadFile);
		iceSFX.setVolume(75);
		m_iceSoundEffects.push_back(iceSFX);
	}
	
	//std::cout << "ice sound " << m_iceSoundEffects.size() << "\n";
}

void IceWall::update(float deltaTime, F_Player & player)
{
// 	for (int i = 0; i < m_iceObjects.size(); i++)
// 	{
// 		for (int j = 0; j < player.getBullets().size(); j++)
// 		{
// 			if (m_iceObjects[i].isCollisionWithPlayerBullets(*player.getBullets()[j]))
// 			{
// 				freezeBullet((player.getBullets()[j]));
// 			}
// 		}
// 	}
	 //too slow
	for (unsigned int i = 0; i < m_iceObjects.size(); i++)
	{
		if (m_iceObjects[i].isDone())
		{
			m_iceObjects.erase(m_iceObjects.begin() + i);
			break;
		}
		m_iceObjects[i].update(deltaTime,player,this);
	}
}

void IceWall::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void IceWall::setDim(const glm::vec2 & dim)
{
	m_dim = dim;
}





void IceWall::freezeBullet(F_BulletBase * bullet)
{
	if (bullet)
	{

		if (!bullet->isFreezed())
		{

			bullet->setVel(glm::vec2(0));
			bullet->setLifeTime(50.0f);

			// 

			glm::vec2 spawnIce = bullet->getPos();

			spawnIce.y += bullet->getDim().x * 0.5f;
			IcedObject iceObj;
			float angle = feint_common::Instance()->randomFloat(0, 3.14);
			int index = feint_common::Instance()->getRandomNum(0, 4);
			float randomScale = feint_common::Instance()->randomFloat(0.5,1.0f);
			iceObj.init(spawnIce, glm::vec2(50,50) , m_sprites[index], angle, glm::vec2(randomScale));
			m_iceObjects.push_back(iceObj);
			bullet->setFreeze(true);
			bullet->destroy();

			m_iceSoundEffects[feint_common::Instance()->radndomInt(0, 3)].play(0);
			//std::cout << "total count " << m_iceObjects.size() << "\n";
		}
	}
}

void IceWall::drawDebug(Feintgine::DebugRender & debugRenderer)
{
	//debugRenderer.drawBox_center()
}

void IceWall::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (unsigned int i = 0; i < m_iceObjects.size(); i++)
	{
		m_iceObjects[i].draw(spriteBatch);
	}
}
