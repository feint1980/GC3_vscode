#include "LinkAmplifier.h"



LinkAmplifier::LinkAmplifier()
{
}


LinkAmplifier::~LinkAmplifier()
{
}

void LinkAmplifier::init(const std::string & animationPath, const glm::vec2 & pos, EnemyAmplifier * leftAmplifier)
{
	m_animation.init(animationPath);
	m_pos = pos - glm::vec2(10, 0);

	m_animation.update(1.0f);
	m_animation.playAnimation("effect_2", 1);
	m_animation.setPos(m_pos);

	m_animation.setDepth(30);
	m_leftAmplifier = leftAmplifier;

	m_animation.setScale(glm::vec2(0.7f));

	m_isAlive = true;


	m_rightAmplifier = leftAmplifier->getLinkPartner();

	m_iceWall.init();
}


void LinkAmplifier::update(float deltaTime, std::vector<EnemyBulletBase *> & enemies_bullets, F_Player & player)
{
	m_animation.update(deltaTime);
	m_iceWall.update(deltaTime,player);
	if (m_isAlive)
	{

		updateAmplifyEffect(enemies_bullets, player);

		handlingState(deltaTime);

		handleLinker();
	}
	else 
	{
	
		m_alpha -= 0.1f * deltaTime;
		
		m_animation.setScale(glm::vec2(1.0f,m_alpha));
		if (m_alpha <= 0.0f)
		{
			m_isRemoved = true;
		}
	}



}

void LinkAmplifier::updateAmplifyEffect(std::vector<EnemyBulletBase *> & enemies_bullets, F_Player & player)
{

	switch (m_type)
	{
	case LINK_EFFECT_LIGHTNING:
	{
		if (isCollisionWithPlayer(player))
		{
			player.die();
		}
		for (int i = 0; i < player.getBullets().size(); i++)
		{
			if (!player.getBullets()[i]->isDone())
			{
				if (isCollisionWithPlayerBullets(*player.getBullets()[i]))
				{
					// if difficult is hard or lunatic
					player.getBullets()[i]->destroy();

				}
			}
		}

		for (int i = 0; i < player.getLeftAccessosry().getBullets().size(); i++)
		{
			//std::cout << "accessory left \n";
			if (player.getLeftAccessosry().getBullets()[i])
			{
				if (!player.getLeftAccessosry().getBullets()[i]->isDone())
				{
					if (isCollisionWithPlayerBullets(*player.getLeftAccessosry().getBullets()[i]))
					{
						// if difficult is hard or lunatic
						//std::cout << "left hit \n";
						player.getLeftAccessosry().getBullets()[i]->destroy();

					}
				}
			}
		}
		for (int i = 0; i < player.getRightAccesory().getBullets().size(); i++)
		{
			//std::cout << "accessory right \n";
			if (player.getRightAccesory().getBullets()[i])
			{
				if (!player.getRightAccesory().getBullets()[i]->isDone())
				{
					if (isCollisionWithPlayerBullets(*player.getRightAccesory().getBullets()[i]))
					{
						// if difficult is hard or lunatic
						//std::cout << "left hit \n";
						player.getRightAccesory().getBullets()[i]->destroy();

					}
				}
			}
		}

		for (int i = 0; i < enemies_bullets.size(); i++)
		{
			if (isCollisionWithAllyBullets(*enemies_bullets[i]))
			{
				//enemies_bullets[i]->
				// if difficult is hard or lunatic
				//player.getBullets()[i]->destroy();
				enemies_bullets[i]->setVel(enemies_bullets[i]->getVel() * 1.03f);
			}
		}

	}
	
	break;

	case LINK_EFFECT_FROST:
	{
		if (isCollisionWithPlayer(player))
		{
			player.die();
		}
		for (int i = 0; i < player.getBullets().size(); i++)
		{
			if (!player.getBullets()[i]->isDone())
			{
				if (isCollisionWithPlayerBullets(*player.getBullets()[i]))
				{
					//m_iceWall
					// if difficult is hard or lunatic
					//player.getBullets()[i]->destroy();
					m_iceWall.freezeBullet(player.getBullets()[i]);

				}
			}

		}
		for (int i = 0; i < enemies_bullets.size(); i++)
		{
			if (isCollisionWithAllyBullets(*enemies_bullets[i]))
			{
				//enemies_bullets[i]->
				// if difficult is hard or lunatic
				//player.getBullets()[i]->destroy();
				enemies_bullets[i]->setVel(enemies_bullets[i]->getVel() * 1.03f);
			}
		}
	}
	break;
	default:

		break;
	}
}

void LinkAmplifier::handlingState(float deltaTime)
{
	switch (m_state)
	{
	case 0:
	{
		if (!m_animation.isPlaying())
		{
			m_animation.setScale(glm::vec2(1.0f, calculateLinkScale()));
			
			m_state = 1;

			switch (m_type)
			{
			case LINK_EFFECT_LIGHTNING :
			{
				m_animation.playAnimation("effect_3");
				m_animation.setAngle(degreeToRad(90));
				m_isIvertXY = true;
			}
				break;

			case LINK_EFFECT_FLAME:
			{
				//m_animation.playAnimation("fire_link");

				m_animation.playAnimation("effect_3");
				m_animation.setAngle(degreeToRad(90));
				m_isIvertXY = true;
			}
			break;

			case LINK_EFFECT_FROST:
			{
				//m_animation.playAnimation("frost_link");
				m_animation.playAnimation("effect_3");
				m_animation.setAngle(degreeToRad(90));
				m_isIvertXY = true;
			}
			break;

			default:
				break;
			}
			
		}
	}
		break;
	case 1 :
	{
		// calculate between 2 amplifier 
		float tDistanceX = m_leftAmplifier->getLinkPartner()->getPos().x - m_leftAmplifier->getPos().x;
		m_pos.x = m_leftAmplifier->getPos().x + (tDistanceX * 0.5f);
		m_pos.y = m_leftAmplifier->getPos().y;

		if (m_isIvertXY)
		{
			m_animation.setScale(glm::vec2(1.0f, calculateLinkScale()));
		}
		else
		{
			m_animation.setScale(glm::vec2( calculateLinkScale(),1.0f));
		}
		

	
	}
	break;
	case 2 :
	{
		
	}
	break;
	default:
		break;
	}


}

void LinkAmplifier::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_animation.setPos(m_pos);
	m_animation.draw(spriteBatch);
	m_iceWall.draw(spriteBatch);
}

void LinkAmplifier::drawDebug(Feintgine::DebugRender & debugRenderer)
{
	m_iceWall.drawDebug(debugRenderer);
}

float LinkAmplifier::calculateLinkScale()
{
	float returnVal;

	/*
		Formula be like 
		scale is 1.0f 
		real pixel is m_texture.dim * scale;

	*/


	float tDistanceX = m_leftAmplifier->getLinkPartner()->getPos().x - m_leftAmplifier->getPos().x;

	float t_texutreHeigh = m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim().y;

	float t_texutreWidth = m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim().x;

	//m_dim = glm::vec2(1000, 40);
	if (m_isIvertXY)
	{
		m_dim = glm::vec2(t_texutreHeigh, m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim().x * 0.5f);
		returnVal = tDistanceX / t_texutreHeigh;

	}
	else
	{
		m_dim = glm::vec2(m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim().x * 0.5f, t_texutreHeigh);
		returnVal = tDistanceX / (t_texutreWidth *0.9f);
	}
	
	m_iceWall.setPos(m_pos);

	float dist = glm::distance(m_leftAmplifier->getLinkPartner()->getPos(), m_leftAmplifier->getPos());
	m_iceWall.setDim(glm::vec2(dist * 0.5f,5));


	return returnVal;
}

bool LinkAmplifier::isCollisionWithPlayer(const F_Player & player)
{
	glm::vec2 pos = player.getPos();
	glm::vec2 dim = player.getDim();

 	glm::vec2 halfDim = m_dim * calculateLinkScale() * 0.5f;
 	glm::vec2 t_halfDim = dim * 0.5f;

	if (pos.x + t_halfDim.x > m_pos.x - halfDim.x &&
		pos.y + t_halfDim.y < m_pos.y + halfDim.y &&
		pos.x - t_halfDim.x < m_pos.x + halfDim.x &&
		pos.y - t_halfDim.y > m_pos.y - halfDim.y)
	{
		//std::cout << "hit \n";
		return true;
	}

	return false;
}


void LinkAmplifier::handleLinker()
{
	if (!m_leftAmplifier->isAlive() || !m_rightAmplifier->isAlive())
	{
		m_isAlive = false;
	}
}

void LinkAmplifier::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	//std::cout << "register for ice wall \n";
	m_iceWall.registerAudioEngine(audioEngine);
}

bool LinkAmplifier::isCollisionWithPlayerBullets(const F_BulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim();

	glm::vec2 halfDim = m_dim * calculateLinkScale() * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	if (pos.x + t_halfDim.x > m_pos.x - halfDim.x &&
		pos.y + t_halfDim.y < m_pos.y + halfDim.y &&
		pos.x - t_halfDim.x < m_pos.x + halfDim.x &&
		pos.y - t_halfDim.y > m_pos.y - halfDim.y)
	{
		//std::cout << "hit \n";
		return true;
	}

	return false;
}

bool LinkAmplifier::isCollisionWithAllyBullets(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim();

	glm::vec2 halfDim = m_dim * calculateLinkScale() * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	if (pos.x + t_halfDim.x > m_pos.x - halfDim.x &&
		pos.y + t_halfDim.y < m_pos.y + halfDim.y &&
		pos.x - t_halfDim.x < m_pos.x + halfDim.x &&
		pos.y - t_halfDim.y > m_pos.y - halfDim.y)
	{
		//std::cout << "hit \n";
		return true;
	}

	return false;
}

