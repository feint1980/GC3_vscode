#include "F_Marisa_Luminous_Strike.h"



F_Marisa_Luminous_Strike::F_Marisa_Luminous_Strike()
{
	m_isRemove = true;

	m_isDestroy = true;

	m_attentionua = glm::vec3(45.0f, 30.5f, 60.0f);

	m_pos = glm::vec2(-1000.0f);

	//glm::vec3(23.0f, 40.0f, 50.0f)
	m_sparkAttenua = glm::vec3(15.0f, 22.5f, 15.0f);

	m_color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	
}
Feintgine::Color F_Marisa_Luminous_Strike::getStarColor(int index)
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


F_Marisa_Luminous_Strike::~F_Marisa_Luminous_Strike()
{
}

void F_Marisa_Luminous_Strike::updateColor(float deltaTime)
{
	Feintgine::Color tColor = m_color;
// 	float t_val = GlobalValueClass::Instance()->getAmbientLight().x * 0.5f;
// 	tColor.r = std::min(0.75f + randomR * (sin(m_lifeTime) - t_val), 1.0f);
// 	tColor.g = std::min(0.75f + randomG * (cos(m_lifeTime) - t_val), 1.0f);
// 	tColor.b = std::min(0.75f + randomB * (cos(m_lifeTime) - t_val), 1.0f);

	tColor.a = m_alphaTime;
	// 
	// 
	// 	tColor.r = 0;
	// 	tColor.g =0;
	// 	tColor.b = 0;
	m_color = tColor;
}

void F_Marisa_Luminous_Strike::init(const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animation, const Feintgine::Color & color, const glm::vec2 & vel, const glm::vec2 & pos, int afterImageCount, float afterImageRate)
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
	if (count > 0)
	{


		if (m_audioEngine)
		{
			m_startSound.setVolume(15);
			m_startSound.playInChannel(0, 2);
		}
	}

	if (!m_hasInited)
	{


		m_afterImageParticle.init(p_pos, &m_animation, &m_animation.getColor(),
			afterImageRate, afterImageCount);
		m_hasInited = true;
	}
}

void F_Marisa_Luminous_Strike::destroy()
{
	
	if (!m_isDestroy)
	{
		m_vel = glm::vec2(0);

		m_animation.playAnimation("destroy", 1);

		if (count > 0)
		{

			if (m_audioEngine)
			{
				m_endSound.setVolume(10);
				m_endSound.playInChannel(2, 2);
			}
			if (m_hitParticleBatch)
			{
				//std::cout << "explod \n";
				int numberOfSpark = 20;
				for (int i = 0; i < numberOfSpark; i++)
				{
					float ranX = feint_common::Instance()->getRandomNum(-.5f, .5f);
					float ranY = feint_common::Instance()->getRandomNum(-.01f, -.4f);

					int colorIndex = i % 5;

					m_hitParticleBatch->addParticle(m_pos,
						glm::vec2(ranX, ranY), getStarColor(colorIndex), 1.1f, 34.0f, m_sparkAttenua);
				}
			}
		}

		m_isDestroy = true;
	}
	
}

void F_Marisa_Luminous_Strike::update(float deltaTime, std::vector<FairyBase *> enemy,
 std::vector<EnemyBulletBase * > bullets)
{

	if (!m_isRemove)
	{
		m_lifeTime -= 0.1f * deltaTime;
		m_angle += 0.325f * deltaTime;
		//m_acce += 0.025f * deltaTime;

		m_scale += 0.125f * deltaTime;
		m_pos += m_vel  * deltaTime;
		m_animation.update(deltaTime);
		m_animation.setScale(m_scale);
		m_animation.setAngle(m_angle);
		//std::cout << m_angle << "\n";
		updateColor(deltaTime);
		//m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(), 0);
		if (m_lifeTime < 0.0f || m_pos.y >= 350.0f)
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
					//std::cout << "deal dmg \n";
					enemy[i]->takeDamage(1.25f *deltaTime, false);

				}
			}

		}

		if (m_isDestroy)
		{
			//std::cout << "asrhhh \n";
			m_alphaTime -= 0.05f * deltaTime;
			if (!m_animation.isPlaying())
			{
				m_color.a = 0.0f;
				m_isRemove = true;
				count = 1;
			}
		}
	}
	
}
