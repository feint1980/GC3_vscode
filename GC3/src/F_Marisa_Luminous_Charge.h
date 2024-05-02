#pragma once
#include "F_MarisaStar.h"
class F_Player;
class F_Marisa_Luminous_Charge : public F_MarisaStar
{
public:
	F_Marisa_Luminous_Charge();
	~F_Marisa_Luminous_Charge();



	void update(float deltaTime, std::vector<FairyBase *>  enemy,
		std::vector<EnemyBulletBase * > bullets);

	void destroy();

	void setFPlayer(F_Player * player);

private:

	glm::vec2 direction = glm::vec2(1);

	F_Player * m_player;

};

