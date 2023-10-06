#include "F_MarisaRocket_small.h"
#include "GlobalValueClass.h"


F_MarisaRocket_small::F_MarisaRocket_small()
{
	m_vel = glm::vec2(0, 2.0f);
	m_dims = glm::vec2(8, 8);
	m_direction = glm::vec2(0, 1);
	m_attentionua = glm::vec3(5, 10, 15);
	m_particleNum = 1;
	m_particleType = 1;
	//m_animation.setPos(m_pos);
}
// 
// 
// F_MarisaRocket_small::F_MarisaRocket_small(const glm::vec2 & pos, const glm::vec2 & dim, 
// 	const Feintgine::Color & color, const std::string & animationPath, float depth, float dmg,
// 	Feintgine::ParticleBatch2D * hitParticleBatch /*= nullptr*/)
// {
// 	F_BulletStraight::F_BulletStraight(pos, dim, color, animationPath, depth, dmg, hitParticleBatch);
// }
// 
F_MarisaRocket_small::~F_MarisaRocket_small()
{

}

void F_MarisaRocket_small::update(float deltaTime, std::vector<F_BaseEnemy *> enemy,
	std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers)
{
	if (!m_isDone)
	{
	
		m_vel = m_direction * m_speed;
		if (m_vel.length() < MAX_SPEED)
		{
			m_speed += accelerateRate * deltaTime;
		}
	}
	else
	{
		m_color.a -= 0.1f * deltaTime;
	}
	m_lightPos = m_pos + t_additionPos;// globalRotatePoint(m_pos - (m_dims * 0.5f * m_scale.x), m_animation.getAngle() - RAD_90_DEGREE);

	F_BulletStraight::update(deltaTime, enemy,guardians,amplifiers);

}

void F_MarisaRocket_small::setIsFocus(bool val)
{
	m_isFocusRocket = val;

	
}

void F_MarisaRocket_small::setScale(float val)
{
	m_scale = glm::vec2(val);
	m_animation.setScale(m_scale);
}

void F_MarisaRocket_small::setDirection(const glm::vec2 & direction)
{
	m_direction = direction;
	m_angle = atan2(m_direction.y, m_direction.x);
	m_animation.setAngle(m_angle);
	m_calculatedAngle = m_animation.getAngle() - RAD_90_DEGREE;

}

void F_MarisaRocket_small::setLightColoFlag(int colorFlag)
{
	switch (colorFlag)
	{
	case 0 : 
		m_lightColor = glm::vec4(0.8,0,1.0,1.0);
		break;
	case 1:
		m_lightColor = glm::vec4(0.5, 0.5, 1.0, 1.0);
		m_attentionua = glm::vec3(25, 30, 45);
		m_particleNum = 10;
		break;
	default:
		m_lightColor = glm::vec4(1);
		break;
	}
}

void F_MarisaRocket_small::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!m_isAnimated)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
	}
	else
	{
		//glm::vec2 additionalPos;
		//if (radToDegree(m_animation.getAngle() == 90))
		//{
		t_additionPos.x = (m_animation.getDim().x * 0.5f * m_scale.x ) - (m_animation.getDim().y *  m_scale.x);
		//}


		m_animation.setPos(m_pos + t_additionPos);
		//m_animation.setScale(glm::vec2(1.0));
		m_animation.draw(spriteBatch);
	}
}

void F_MarisaRocket_small::drawLight(Feintgine::LightBatch & lightBatch)
{
	if (!m_isDone)
	{

		f_attentionua = m_attentionua - (m_attentionua * 0.5f) *  GlobalValueClass::Instance()->getAmbientLight().x;
		lightBatch.addLight(m_lightPos, m_lightColor,
			(1.0f / f_attentionua));
	}
}

void F_MarisaRocket_small::destroy()
{
	setScale(m_scale.x * 1.5f);
	m_pos.x += m_dims.x * m_scale.x;
	//m_animation.setAngle(0);
	F_BulletStraight::destroy();	
	accelerateRate = 0;
	//std::cout << "destroy called \n";
	//m_animation.setScale(glm::vec2(.0f));
	
	
	
}

void F_MarisaRocket_small::setParticleType(int type)
{
	m_particleType = type;

}
