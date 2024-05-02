#include "F_MarisaStar.h"
#include "GlobalValueClass.h"


F_MarisaStar::F_MarisaStar()
{
	randomScale = 0.9;
	randomR = feint_common::Instance()->randomFloat(0, randomScale);
	randomG = feint_common::Instance()->randomFloat(0, randomScale);
	randomB = feint_common::Instance()->randomFloat(0, randomScale);
	//glm::vec3(15.0f, 30.5f, 24.0f);
	m_attentionua = glm::vec3(7.5f, 15.5f, 12.0f);
	m_numberOfSpark = 8;
	m_sparkAttenua = glm::vec3(9.5f, 5.5f, 10.0f);
}


F_MarisaStar::~F_MarisaStar()
{
}

void F_MarisaStar::init(const glm::vec2 & scale,
	const Feintgine::F_AnimatedObject & animation,
	const Feintgine::Color & color, const glm::vec2 & vel,
	const glm::vec2 &  pos, int afterImageCount, float afterImageRate)
{
	m_scale = scale;
	m_color = color;
	m_animation = animation;
	m_animation.setPos(m_pos);
	m_vel = vel;
	m_animation.playAnimation("idle");
	m_pos = pos;
	m_alphaTime = 1.0f;

	m_lifeTime = 6.2f;

	m_animation.setScale(m_scale);
	m_acce = glm::vec2(1);

	m_isRemove = false;

	m_isDestroy = false;

	p_pos = &m_pos;
	if (m_audioEngine)
	{
		m_startSound.setVolume(10);
		m_startSound.playInChannel(0, 2);
	}

	if (!m_hasInited)
	{


		m_afterImageParticle.init(p_pos, &m_animation, &m_animation.getColor(),
			afterImageRate, afterImageCount);
		m_hasInited = true;
	}
}

void F_MarisaStar::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
}

void F_MarisaStar::loadStarSound(const std::string & filePath)
{
	m_startSound =  m_audioEngine->loadSoundEffect(filePath);
	m_startSound.stahp();
}

void F_MarisaStar::loadEndSound(const std::string & filePath)
{
	m_endSound = m_audioEngine->loadSoundEffect(filePath);
	m_endSound.stahp();
}

void F_MarisaStar::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_animation.draw(spriteBatch);
	m_afterImageParticle.draw(spriteBatch);
}

void F_MarisaStar::drawLight(Feintgine::LightBatch & lightBatch)
{
	if (!m_isDestroy)
	{


		float randomScale = 4.4;
		float randomR = feint_common::Instance()->randomFloat(0, randomScale);
		float randomG = feint_common::Instance()->randomFloat(0, randomScale);
		float randomB = feint_common::Instance()->randomFloat(0, randomScale);
		t_attentionua = m_attentionua - (m_attentionua * 0.5f) * GlobalValueClass::Instance()->getAmbientLight().x;
		Feintgine::Color tColor = m_color;
		lightBatch.addLight(m_pos, glm::vec4(tColor.r * 2.0f /* * sin(m_lifeTime)*/,
			tColor.g * 2.0f /** cos(m_lifeTime)*/,
			tColor.b  * 2.0f/* * sin(m_lifeTime)*/, m_color.a),1.0f / t_attentionua);
	}
}

void F_MarisaStar::update(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets)
{


	m_lifeTime -= 0.1f * deltaTime;
	m_angle += 0.125f * deltaTime;
	m_acce += 0.025f * deltaTime;
	
	m_scale += 0.025f * deltaTime;
	m_pos += m_vel * m_acce * deltaTime;
	m_animation.update(deltaTime);
	m_animation.setScale(m_scale);
	m_animation.setPos(m_pos);
	m_animation.setColor(m_color);
	m_animation.setAngle(m_angle);

	updateColor(deltaTime);
	
	m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(), m_angle);
	if (m_lifeTime < 0.0f)
	{
		destroy();

	}
	else
	{
		//
		for (auto i = 0; i < bullets.size(); i++)
		{

			if (checkColliderWithEnemyBullet(*bullets[i]))
			{
				bullets[i]->setLifeTime(-1.0f);
			}
		}

		for (auto i = 0; i < enemy.size(); i++)
		{

			if (checkColliderWithEnemy(*enemy[i]))
			{
				enemy[i]->takeDamage(1.25f *deltaTime, false);
			}
		}

	}
	
	if (m_isDestroy)
	{
		
		m_alphaTime -= 0.05f * deltaTime;
 		if (!m_animation.isPlaying())
 		{
 			m_isRemove = true;
 		}
	}

}

void F_MarisaStar::updateColor(float deltaTime)
{
	//m_color

	Feintgine::Color tColor = m_color;
	float t_val = GlobalValueClass::Instance()->getAmbientLight().x * 0.1f;
	float scale = 0.7f;
	tColor.r = scale * randomR;//std::min(scale * randomR /** (sin(m_lifeTime) + 0.8f)*/,1.0f);
	tColor.g = scale * randomG;//std::min(scale * randomG /** (cos(m_lifeTime) + 0.8f)*/,1.0f);
	tColor.b = scale * randomB;//std::min(scale * randomB /** (cos(m_lifeTime) + 0.8f)*/,1.0f);

	tColor.a = m_alphaTime;
// 
// 
// 	tColor.r = 0;
// 	tColor.g =0;
// 	tColor.b = 0;
	m_color = tColor ;
	//m_animation.setColor(tColor);
}

void F_MarisaStar::setVel(const glm::vec2 & vel)
{
	m_vel = vel;
}

void F_MarisaStar::destroy()
{
	if (!m_isDestroy)
	{
		m_vel = glm::vec2(0);
		m_animation.playAnimation("destroy", 1);
		if (m_audioEngine)
		{
			m_endSound.setVolume(10);
			m_endSound.playInChannel(0, 2);
		}
		
		if (m_hitParticleBatch)
		{
			//std::cout << "explod \n";
			//int numberOfSpark = 8;
			t_sparkAttenua = m_sparkAttenua - (m_sparkAttenua * 0.2f) * GlobalValueClass::Instance()->getAmbientLight().x;
			for (int i = 0; i < m_numberOfSpark; i++)
			{
				float ranX = feint_common::Instance()->getRandomNum(-2.5f, 2.5f);
				float ranY = feint_common::Instance()->getRandomNum(-2.5f, 2.5f);
				glm::vec2 halfDim = glm::vec2(25);
// 				m_hitParticleBatch->addParticle(m_pos,
// 					glm::vec2(ranX, ranY),m_color, 0.4f,3.4f, t_sparkAttenua);

				m_hitParticleBatch->addParticle(m_pos, glm::vec2(ranX, ranY),
					Feintgine::Color(255 * randomR, 255 * randomG, 255 * randomB, 255),
					0.5f, 6.2f, t_sparkAttenua);
			}
		}

		m_isDestroy = true;
	}
}

void F_MarisaStar::registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch)
{
	m_hitParticleBatch = particleBatch;
}

void F_MarisaStar::setNumberOfParticle(int val)
{
	m_numberOfSpark = val;
}

bool F_MarisaStar::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	//glm::vec2 dim = bullet.getDim() * bullet.getScale();

	glm::vec4 desRect(m_pos - m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim() * 0.5f, 
		m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim() * m_scale);

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

void F_MarisaStar::setLifeTime(float val)
{
	m_lifeTime = val;
}

bool F_MarisaStar::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	//glm::vec2 halfDim = m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim() * m_scale * 0.5f;
	glm::vec2 t_halfDim = m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim() * m_scale * 0.5f * m_scale;


	if (m_pos.x > pos.x - t_halfDim.x &&
		m_pos.y < pos.y + t_halfDim.y &&
		m_pos.x  < pos.x + t_halfDim.x &&
		m_pos.y > pos.y - t_halfDim.y)
	{
		return true;
	}

	return false;
}

