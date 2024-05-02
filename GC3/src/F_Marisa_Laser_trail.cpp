#include "F_Marisa_Laser_trail.h"
#include "GlobalValueClass.h"


F_Marisa_Laser_trail::F_Marisa_Laser_trail()
{
	m_attenuationScale = 0.0f;

}


F_Marisa_Laser_trail::~F_Marisa_Laser_trail()
{
}

void F_Marisa_Laser_trail::drawLight(Feintgine::LightBatch & lightBatch)
{
	t_attenuation = (m_attenuation - (m_attenuation * 0.12f) * GlobalValueClass::Instance()->getAmbientLight().x) * m_attenuationScale;

	glm::vec2 lightPos = m_pos + glm::vec2(0, 5);
	//lightPos.y -= m_dim.x * 0.5f;
	//float m_rotation = 
//	float randomScale = 0.6;
// 	float randomR = feint_common::Instance()->randomFloat(0.5, randomScale);
// 	float randomG = feint_common::Instance()->randomFloat(0.5, randomScale);
// 	float randomB = feint_common::Instance()->randomFloat(0.5, randomScale);
	Feintgine::Color tColor = m_color;
	tColor.r *= 1.4f;
 	tColor.g *= 1.4f;
 	tColor.b *= 1.4f;
	lightBatch.addRayLight(lightPos, glm::vec4(tColor.r ,
		tColor.g ,
		tColor.b, m_color.a)
		, 1.0f / t_attenuation, m_angle - degreeToRad(90));
}

void F_Marisa_Laser_trail::update(float deltaTime, std::vector<FairyBase *> enemy, std::vector<EnemyBulletBase * > bullets)
{
	//m_angle += 0.05f;
	updateState(deltaTime);

}

void F_Marisa_Laser_trail::updateState(float deltaTime)
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

	if (m_isSwitchHappen)
	{

		if (m_isVisible)
		{
			if (m_color.change(m_colorFlag, 0.025f, maxColorVal))
			{
				m_isSwitchHappen = false;
			}
			if (m_attenuationScale < 2.0f)
			{
				m_attenuationScale += 0.25f * deltaTime;
			}
		}
		else
		{
			if (m_color.change(m_colorFlag, -0.025f, minColorVal))
			{
				m_isSwitchHappen = false;			
			}
			if (m_attenuationScale > 0.0f)
			{
				m_attenuationScale -= 0.01f * deltaTime;
			}
			else
			{
				m_isRemoved = true;
			}


		}
	}
}

void F_Marisa_Laser_trail::spawn(const glm::vec2 & pos,
	const glm::vec3 & attenuation, int colorFlag, Feintgine::Color color)
{
	m_pos = pos;
	m_attenuation = attenuation;
	m_colorFlag = colorFlag;
	m_color = color;
	m_isSwitchHappen = true;
	m_isVisible = true;
	m_isRemoved = false;
	m_lifeTime = 12.0f;

}

void F_Marisa_Laser_trail::setAngle(float angle)
{
	m_angle = angle;
}
