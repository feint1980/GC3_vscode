#pragma once
#include "F_MarisaStar.h"

class F_Marisa_Luminous_Strike : public F_MarisaStar
{
public:
	F_Marisa_Luminous_Strike();
	~F_Marisa_Luminous_Strike();

	void update(float deltaTime, std::vector<FairyBase *>  enemy,
		std::vector<EnemyBulletBase * > bullets);

	Feintgine::Color getStarColor(int index);
	void updateColor(float deltaTime);


	void init(const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animation,
		const Feintgine::Color & color, const glm::vec2 & vel, const glm::vec2 & pos, int afterImageCount, float afterImageRate);


	void destroy();
private : 

	
	int count = 0;



};

