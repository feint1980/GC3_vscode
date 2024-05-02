#include "F_Marisa_Luminous_Charge.h"
#include "GlobalValueClass.h"


F_Marisa_Luminous_Charge::F_Marisa_Luminous_Charge()
{
	m_lifeTime = 8.4f;
	m_isDestroy = false;

	m_attentionua = glm::vec3(5.0f, 7.5f, 9.0f);

	m_isRemove = false;
	m_audioEngine = nullptr;
}


F_Marisa_Luminous_Charge::~F_Marisa_Luminous_Charge()
{
}

void F_Marisa_Luminous_Charge::update(float deltaTime, std::vector<FairyBase *> enemy,
	std::vector<EnemyBulletBase * > bullets)
{
	glm::vec2 targetPos = GlobalValueClass::Instance()->getPlayer()->getPos();
	glm::vec2 halfDim = GlobalValueClass::Instance()->getPlayer()->getDim();

	direction = glm::normalize(targetPos - m_pos);

	//direction = glm::vec2(cos(m_lifeTime) * direction.x, sin(m_lifeTime) * direction.y) ;

	m_lifeTime -= 0.1f * deltaTime;
	m_angle += 0.12f * deltaTime;
	//m_acce += 0.025f * deltaTime;
	float distance = glm::length(targetPos - m_pos);
	//std::cout << distance << "\n";
	
	// = distance  * 0.01f;

	m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(), m_angle);
	m_animation.update(deltaTime);
	m_animation.setPos(m_pos);
	//updateColor(deltaTime);
	if (m_lifeTime < 0.0f)
	{
		
		destroy();

	}
	if (distance < 10)
	{
		//std::cout << "close \n";
		//std::cout << "global player " << feint_common::Instance()->convertiVec2toString(m_player->getPos()) << "\n";
		
		//glm::vec2 t_scale = glm::vec2(1.0f);
		//m_animation.setScale(glm::vec2(1.0f));
		m_scale = glm::vec2(1.0f);
		m_animation.setScale(m_scale);
		m_angle = 0.0f;
// 		t_scale.x -= m_scale.x;
// 		t_scale.y -= m_scale.y;
		m_pos = m_player->getPos();
	}
	else
	{
		m_pos += direction * ((0.04f * distance) + 4.5f) * deltaTime;
	}
	
	if (m_isDestroy)
	{
		//std::cout << "destroy \n";
		//m_pos = targetPos + m_animation.getDim() * 0.5f;
		m_color.a -= 0.25f * deltaTime;
		m_animation.setColor(m_color);
		
	}

	if (m_color.a < 0.0f)
	{
		m_isRemove = true;
	}

}

void F_Marisa_Luminous_Charge::destroy()
{
	//std::cout << "destroy \n";
	//m_vel = glm::vec2(0);
	//m_animation.playAnimation("destroy", 1);
	//m_animation.setScale(glm::vec2(1.2f));
	m_isDestroy = true;
}

void F_Marisa_Luminous_Charge::setFPlayer(F_Player * player)
{
	m_player = player;
}
