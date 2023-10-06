#include "F_Player_Reimu.h"



F_Player_Reimu::F_Player_Reimu()
{
}


F_Player_Reimu::~F_Player_Reimu()
{
}

// void F_Player_Reimu::fire()
// {
// 	m_fireSoundEffect.playInChannel(1, 5);
// 	glm::vec2 t_pos = m_pos;
// 	t_pos.y += 5.5f;
// 	switch (m_powerLevel)
// 	{
// 	case 0:
// 	case 1:
// 	{
// 		//bullet.setVel(glm::vec2(0, 10));
// 		std::string path = "Assets/F_AObjects/marisa_normal_projectile.xml";
// 		F_BulletStraight  * t_bullet = new F_BulletStraight();
// 		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
// 			path, 2, 5.0f, m_hitParticleBatch);
// 		t_bullet->setBulletAnimationAction("default");
// 		t_bullet->setBulletAnimationAngle(degreeToRad(90));
// 		m_bullets.push_back(t_bullet);
// 		//delete t_bullet;
// 		break;
// 	}
// 	case 2:
// 	case 3:
// 		bullet.setVel(glm::vec2(-0.6, 10));
// 		//m_bullets.push_back(t_bullet);
// 		bullet.setVel(glm::vec2(0.6, 10));
// 		//m_bullets.push_back(t_bullet);
// 		break;
// 	case 4:
// 		bullet.setVel(glm::vec2(-1.2, 10));
// 		//m_bullets.push_back(bullet);
// 		bullet.setVel(glm::vec2(0, 10));
// 		//m_bullets.push_back(bullet);
// 		bullet.setVel(glm::vec2(1.2, 10));
// 		//m_bullets.push_back(bullet);
// 		break;
// 
// 	case 5:
// 		bullet.setVel(glm::vec2(-1.2, 10));
// 		//m_bullets.push_back(bullet);
// 		bullet.setVel(glm::vec2(1.2, 10));
// 		//m_bullets.push_back(bullet);
// 		bullet.setVel(glm::vec2(-0.6, 10));
// 		//m_bullets.push_back(bullet);
// 		bullet.setVel(glm::vec2(0.6, 10));
// 		//m_bullets.push_back(bullet);
// 		break;
// 	default:
// 		break;
// 	}
// }
