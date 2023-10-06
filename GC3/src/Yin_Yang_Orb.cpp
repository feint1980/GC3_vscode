#include "Yin_Yang_Orb.h"

const float LIFE_TIME_RATE = 0.1f;
const float ALPHA_MULTIPLIER = 1.0f;

Yin_Yang_Orb::Yin_Yang_Orb()
{
	m_lightColor = glm::vec3(1.0f, 0.8f, 0.0f);
}


Yin_Yang_Orb::~Yin_Yang_Orb()
{
}

void Yin_Yang_Orb::init(const std::string & animationPath, const Feintgine::Color & color, float scale)
{
	m_animation.init(animationPath);
	m_animationFront.init(animationPath);
	m_color = color;
	m_scale = scale;
	//m_attentionua = glm::vec3(2.2f, 10.0f, 12.5f);
	m_afterImageParticle.init(&m_pos, &m_animation, &m_color, .15f, 10);
	//m_animation.setColor(m_color);
	m_afterImageParticle.setTraceLifeTime(2.65f);
	m_afterImageParticle.setAlphaRate(0.4f);
	m_isAlive = false;
	m_lifeTime = 0;
	//m_animation.playAnimation("idle");
	m_isVisible = false;
	isFinished = true;
}



void Yin_Yang_Orb::spawn(const glm::vec2 & pos, float lifeTime, const glm::vec2 & vel)
{
	m_pos = pos;
	m_lifeTime = lifeTime;
	m_vel = vel;
	m_animation.playAnimation("idle");
	m_animationFront.playAnimation("idle");
	m_isVisible = true;
	m_isPeak = false;
	m_isAlive = true;
	m_angle = 0.0f;
	m_animation.setAlpha(1.0f);
	m_animationFront.setAlpha(0.5f);
	m_attentionua = glm::vec3(3.4f, 10.0f, 12.5f);
	m_afterImageParticle.clear();
	colorRate = .5f;
	m_animationFront.setColor(Feintgine::Color(255,255,255,255));
	isFinished = false;
	m_loopSound.playInChannel(0, 2);
	
}

void Yin_Yang_Orb::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_isVisible)
	{
		m_animation.setPos(m_pos);
		m_animation.draw(spriteBatch);
		
	}
	if (m_isAlive)
	{
		m_afterImageParticle.draw(spriteBatch);
	}


}

void Yin_Yang_Orb::drawNoLight(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_isVisible)
	{
		m_animationFront.setPos(m_pos + offsetNolight);
		m_animationFront.draw(spriteBatch);

	}
}

void Yin_Yang_Orb::drawLight(Feintgine::LightBatch & lightBatch)
{
	if (m_isVisible)
	{
		glm::vec2 tPos = m_pos;
		//tPos.y -= 350;
		int numberOfLight = 1;
		t_attentionua = m_attentionua + abs(cos(m_lifeTime) + 1.0f);
		lightBatch.addLight(tPos, glm::vec4(m_lightColor, m_lifeTime),
			glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z));
	}
	
}

void Yin_Yang_Orb::update(float deltaTime ,std::vector<F_BaseEnemy *>  enemy, std::vector<EnemyBulletBase * > bullets)
{
	m_lifeTime -= LIFE_TIME_RATE * deltaTime;
	
	m_pos += m_vel * deltaTime;


	suckScale = 1.2f;

	if (m_lifeTime < 8.0f)
	{
		suckScale = 1.6f;
	}
	if (m_lifeTime < 4.0f)
	{
		suckScale = 0.1f;
	}

	if (m_lifeTime > 4.0f)
	{
		if (m_animation.getCurrentAnimation())
		{
			m_dim = m_animation.getCurrentAnimation()->getAnims()[m_animation.getCurrentAnimation()->getCurrentIndex()].sprite.getDim();
		}
	}
	else
	{
		m_dim *= m_lifeTime * deltaTime *0.25f;
	}

	


	if (m_isVisible)
	{
		for (auto i = 0; i < bullets.size(); i++)
		{

			if (checkColliderWithEnemyBulletOuter(*bullets[i]))
			{
				glm::vec2 direction = glm::normalize(bullets[i]->getPos() - m_pos);
				if (m_lifeTime > 8.0f)
				{
					bullets[i]->setVel(-direction * 1.4f);
				}
				else if(m_lifeTime > 1.0f)
				{
					
					bullets[i]->setVel(-direction * 9.4f);
					bullets[i]->setDisabled(true);
					bullets[i]->setLifeTime(m_lifeTime * 0.05f);
				}
				
			}

			if (checkColliderWithEnemyBullet(*bullets[i]))
			{
				bullets[i]->setLifeTime(-1.0f);

			}
		}
	}

	if (m_isAlive)
	{
		
	
		for (auto i = 0; i < enemy.size(); i++)
		{

			if (checkColliderWithEnemy(*enemy[i]))
			{
				//std::cout << "deal dmg \n";
				enemy[i]->takeDamage(m_dmg *deltaTime, false);
			}
		}

		if (m_lifeTime < 29.0f)
		{
			m_angle -= 0.025f * deltaTime;
			m_animation.setAngle(m_angle);		
			m_animationFront.setAngle(m_angle);
		}
		if (m_lifeTime < 8.0f)
		{
			m_isAlive = false;
			//std::cout << "is out \n";
			m_animation.playAnimation("end", 1);
			m_animationFront.playAnimation("end", 1);
			m_vel *= 0.1f * deltaTime;
		}

		if (m_lifeTime > 25.0f)
		{

			m_attentionua += 2.5f * deltaTime;

		}

	}
	else
	{
		if (!m_animation.isPlaying())
		{
			
			m_isVisible = false;
			//m_endSound.stahp();
			//std::cout << "is off \n";
			m_isPeak = false;
			m_afterImageParticle.clear();
// 			if (m_animation.getCurrentAnimation())
// 			{
// 				std::cout << "end\n";
// 				
// 			}
			
			
		}
		if (m_lifeTime < 5.0f)
		{
			if (!isFinished)
			{
				if (m_deathCallback)
				{
					m_deathCallback();
				}
				//std::cout << "finished \n";
				m_endSound.playInChannel(0, 2);
				isFinished = true;
			}
		}
	}

	
// 	if (m_lifeTime > 10.0f && m_lifeTime < 25.0f )
// 	{
// 		//colorRate -= 0.1f * deltaTime;
// 		t_color = glm::vec4(-10, -10, -10, 1.0f);
// 		m_animation.setColor(Feintgine::Color(-2555, -2555, -2555, 255));
// 	}
// 	else 
// 	{
// 		m_animation.setColor(Feintgine::Color(255, 255, 255, 255));
// 	}

	if (m_isVisible)
	{
		if (m_lifeTime < 7.0f)
		{
			m_attentionua -= 2.5f * deltaTime;
			colorRate -= 0.05f * deltaTime;
			t_color = glm::vec4(colorRate, colorRate, colorRate, colorRate);
			//m_animationFront.setColor(t_color);
		}
		if (m_lifeTime < 4.5f)
		{
			
			m_animation.setAlpha(m_lifeTime * ALPHA_MULTIPLIER);

			//m_attentionua *= m_lifeTime + .2f;
		}
		if (m_lifeTime < 29 && m_lifeTime > 8.0f)
		{
			if (m_animation.getCurrentAnimation())
			{
				if (m_animation.getCurrentAnimation()->getCurrentIndex() != -1)
				{
					m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(), m_angle);
				}
			}
		}
		if (m_lifeTime > 3.5f)
		{
			m_animation.update(deltaTime);
			m_animationFront.update(deltaTime);
		}
		else
		{
			m_animation.getCurrentAnimation()->stop();
			m_animationFront.getCurrentAnimation()->stop();
		}
	

		
	}
}

void Yin_Yang_Orb::setDeathCallback(const std::function <void(void)>& f)
{
	m_deathCallback = f;
}

void Yin_Yang_Orb::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	//m_castSound = audioEngine->loadSoundEffect("Sounds/sfx/se_tan00.wav");
	m_loopSound = audioEngine->loadSoundEffect("Sounds/sfx/hover.wav");
	m_loopSound.setVolume(24);
	m_endSound = audioEngine->loadSoundEffect("Sounds/sfx/demon_binding_end.wav");
	m_endSound.setVolume(20);
	//std::cout << "Yin_Yang_Orb \n";
}

void Yin_Yang_Orb::setOffsetNoLight(const glm::vec2 & offset)
{
	offsetNolight = offset;
}



bool Yin_Yang_Orb::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();

	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;


	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim * m_scale * 0.35f);

	glm::vec2 halfDims(desRect.z / 2.0f, desRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl = glm::vec2(-halfDims.x, halfDims.y) + m_pos;
	glm::vec2 bl = glm::vec2(-halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDims.x, halfDims.y) + m_pos;

	// Rotate the points


	if (pos.x > tl.x && pos.x < tr.x
		&& pos.y < tl.y && pos.y > br.y)
	{
		//std::cout << "collide \n";
		return true;
	}
	return false;
}

bool Yin_Yang_Orb::checkColliderWithEnemyBulletOuter(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();

	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;

	

	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim * m_scale * suckScale);

	glm::vec2 halfDims(desRect.z / 2.0f, desRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl = glm::vec2(-halfDims.x, halfDims.y) + m_pos;
	glm::vec2 bl = glm::vec2(-halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDims.x, halfDims.y) + m_pos;

	// Rotate the points


	if (pos.x > tl.x && pos.x < tr.x
		&& pos.y < tl.y && pos.y > br.y)
	{
		return true;
	}
	return false;
}

bool Yin_Yang_Orb::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dim * 0.5f;
	glm::vec2 t_halfDim = m_dim * 0.35f * m_scale;


	if (m_pos.x > pos.x - t_halfDim.x &&
		m_pos.y < pos.y + t_halfDim.y &&
		m_pos.x  < pos.x + t_halfDim.x &&
		m_pos.y > pos.y - t_halfDim.y)
	{
		//std::cout << "conecct \n";
		return true;
	}

	return false;
}

void Yin_Yang_Orb::setDMG(float val)
{
	m_dmg = val;
}
