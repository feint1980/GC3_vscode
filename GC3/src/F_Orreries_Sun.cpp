#include "F_Orreries_Sun.h"



F_Orreries_Sun::F_Orreries_Sun()
{
}


F_Orreries_Sun::~F_Orreries_Sun()
{
}

void F_Orreries_Sun::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_animation.setColor(m_color);
	m_animation.setPos(m_pos);
	m_animation.setScale(glm::vec2(0.5f));
	m_animation.draw(spriteBatch);


// 	for (int i = 0; i < m_bullets.size(); i++)
// 	{
// 		m_bullets[i]->draw(spriteBatch);
// 	}
	m_nonDirectionLaser.draw(spriteBatch);
	m_laser.draw(spriteBatch);
}

void F_Orreries_Sun::setPos(const glm::vec2 & pos)
{

	//m_vector = pos - m_pos;
	m_pos = pos;
}

void F_Orreries_Sun::init(const std::string & animationPath, int id)
{

	m_bulletAnim.init("Assets/F_AObjects/marisa_effect.xml");
	m_animation.init(animationPath);
	m_id = id;
	m_attentionua = glm::vec3(15, 15, 8);
	m_animation.playAnimation("idle");
	m_dim = glm::vec2(36.0f);
	m_color = Feintgine::Color(0, 0,0,0);

	m_isVisible = true;
	m_isSwitchHappen = true;
	m_isALive = false;

	m_hitCount = 7;
	m_lifeTime = 0.0f;


	m_nonDirectionLaser.init(glm::vec2(3.6f, 0.8f),
		Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_master_spark.png"),
		getColor(m_id));

}

void F_Orreries_Sun::update(float deltaTime, std::vector<F_BaseEnemy *> enemies,
	std::vector<EnemyGuardian *> guardians,
	std::vector<EnemyAmplifier *> amplifiers,
	std::vector<EnemyBulletBase * > bullets)
{

	m_animation.update(deltaTime);
	m_time += 0.1f * deltaTime;
	t_attentionua = (m_attentionua + cos(m_time) * std::min(1.0f, m_color.a));
	for (int i = 0; i < bullets.size(); i++)
	{
		if (checkColliderWithEnemyBullet(*bullets[i]))
		{
			m_hitCount--;
			bullets[i]->setLifeTime(-1.0f);

		}
	}


	// handle colors

	if (!m_isDone)
	{


		if (m_hitCount < 0)
		{
			m_isDone = true;
			m_animation.playAnimation("destroy",1);
			m_isSwitchHappen = true;
			m_isVisible = false;
		}
	}
	else
	{
		if (!m_animation.isPlaying())
		{
			m_isALive = false;
		}
	}

	if (m_isSwitchHappen)
	{

		if (m_isVisible)
		{
			if (m_color.change(15, 0.025f, 1.3f))
			{
				m_isSwitchHappen = false;
			}
		}
		else
		{
			if (m_color.change(15, -0.025f, -0.01f))
			{
				//std::cout << "stop \n";
				m_isSwitchHappen = false;
				m_isALive = false;

			}

		}
	}

	updateState(deltaTime);

// 	for (int i = 0; i < m_bullets.size(); i++)
// 	{
// 		if (!m_bullets[i]->isAlive())
// 		{
// 			m_bullets.erase(m_bullets.begin() + i);
// 		}
// 		m_bullets[i]->update(deltaTime, enemies,guardians,amplifiers);
// 	}

	m_laser.update(deltaTime, m_pos, enemies, guardians, amplifiers,false);
	m_nonDirectionLaser.update(m_pos, m_angle,deltaTime, enemies, bullets);
	//updateMovement(deltaTime);
}

void F_Orreries_Sun::initLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos, 
	const glm::vec2 & dim, const Feintgine::Color & color, float depth, float angle, float dps, const Feintgine::F_Sprite & starSprite)
{
	m_laser.init(texture, pos, dim, Feintgine::Color(0,0,0,0), depth, angle, dps, starSprite, 0.1f);
	m_laser.setVisible(false);
	m_laser.setMaxMinColorVal(1.0f, -0.0001f);
	m_laser.setStarScale(0.7f);

	glm::vec4 tf_color = getLaserColor(m_id) * 0.5f;
	m_laser.setColorRate(glm::vec3(tf_color.x, tf_color.y, tf_color.z));
	m_laser.setAttenuation(glm::vec3(2.0f, 4.0f, 7.0f));
	m_laser.setSparkAttenuation(glm::vec3(4,2,4));
	//
}



void F_Orreries_Sun::setLifeTime(float lifeTime)
{
	m_lifeTime = lifeTime;
}

void F_Orreries_Sun::drawLight(Feintgine::LightBatch & lightBatch)
{

	if (!m_laser.isVisible() || !m_nonDirectionLaser.isVisible())
	{


		lightBatch.addLight(m_pos, glm::vec4(1.0f),
			1.0f / t_attentionua);
	}
	m_laser.drawRayLight(lightBatch);
	m_nonDirectionLaser.drawRayLight(lightBatch);

// 	for (int i = 0; i < m_bullets.size(); i++)
// 	{
// 		m_bullets[i]->drawLight(lightBatch);
// 	}


}

void F_Orreries_Sun::fireNonDirectionLaser()
{
	m_lifeTime = 30.0f;
	m_nonDirectionLaser.spawn(m_lifeTime);
	m_hitCount = 999;
}

bool F_Orreries_Sun::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	//glm::vec2 dim = bullet.getDim() * bullet.getScale();

	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim );

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

bool F_Orreries_Sun::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dim * 0.5f;
	//glm::vec2 t_halfDim = m_sprite.getDim() * 0.5f * m_scale;


	if (m_pos.x > pos.x - halfDim.x &&
		m_pos.y < pos.y + halfDim.y &&
		m_pos.x  < pos.x + halfDim.x &&
		m_pos.y > pos.y - halfDim.y)
	{
		return true;
	}

	return false;
}

void F_Orreries_Sun::updateState(float deltaTime)
{
	if (m_lifeTime > 0.0f)
	{
		m_lifeTime -= 0.1f * deltaTime;


	}
	else
	{
		m_isVisible = false;
		m_isSwitchHappen = true;
		

	}
}

void F_Orreries_Sun::spawn(float time)
{
	m_lifeTime = time;
	m_isVisible = true;
	m_isSwitchHappen = true;
	m_isALive = true;

	m_time = 0.0f;
	
}

void F_Orreries_Sun::updateMovement(float deltaTime)
{
	m_pos += m_vector * 0.01f * glm::distance(m_pos, t_pos) * deltaTime;
// 	if (glm::distance(m_pos, t_pos) < 0.1f)
// 	{
// 		m_pos = t_pos;
// 		//m_isMoving = false;
// 		m_vector = glm::vec2(0);
// 		//m_prevPos = m_pos;
// 	}
}

void F_Orreries_Sun::fireNormal()
{
	F_BulletStraight  * t_bullet = new F_BulletStraight();
	t_bullet->init(m_pos, glm::vec2(16, 12), getColor(m_id),
		m_bulletAnim, 2,2.5f,m_particleBatch);
	t_bullet->setBulletAnimationAction("common_1");
	t_bullet->setBulletAnimationAngle(degreeToRad(90));
	t_bullet->setVel(glm::vec2(0, 8.0f));
	t_bullet->setDestroyAnimName("common_1_destroy");
	t_bullet->setAttenuation(glm::vec3(6, 6, 6));
	m_bullets.push_back(t_bullet);
}

void F_Orreries_Sun::showLaser(bool val)
{
	m_laser.setVisible(val);
}

void F_Orreries_Sun::registerParticle(Feintgine::ParticleBatch2D * particleBatch)
{
	m_particleBatch = particleBatch;
	m_laser.setParticle(m_particleBatch);
}

glm::vec4 F_Orreries_Sun::getLaserColor(int num)
{
	glm::vec4 returnVal;

	float intensity = 4.6f;
	float t_offset = intensity * 0.01f;
	switch (num)
	{
	case 0:
		returnVal = glm::vec4(intensity, t_offset, t_offset, 1.0f);
		break;
	case 1:
		returnVal = glm::vec4(t_offset, intensity, t_offset, 1.0f);
		break;
	case 2:
		returnVal = glm::vec4(t_offset, t_offset, intensity, 1.0f);
		break;
	case 3:
		returnVal = glm::vec4(intensity, intensity, t_offset, 1.0f);
		break;
	case 4:
		returnVal = glm::vec4(intensity, t_offset, intensity, 1.0f);
		break;
	case 5:
		returnVal = glm::vec4(t_offset, intensity, intensity, 1.0f);
		break;

	default:
		returnVal = glm::vec4(1.0f);
		break;
	}

	return returnVal;
}

Feintgine::Color F_Orreries_Sun::getColor(int index)
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

void F_Orreries_Sun::setAngle(float angle)
{
	m_angle = angle;
	//m_nonDirectionLaser.
}

void F_Orreries_Sun::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
	m_nonDirectionLaser.registerAudioEngine(m_audioEngine);
	
}
