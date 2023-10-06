#pragma once

#include "F_EnemyBasic.h"


const int ANIM_LEFT = 0;
const int ANIM_RIGHT = 1;
const int ANIM_CENTER = 2;
class FairyBase : public F_EnemyBasic
{ 
public:
	FairyBase();
	~FairyBase();
	void decideAnimation(const glm::vec2 & pos);

	void setMovementAnim(int val);

	void setCustomAnim(int type, const std::string & name);

	void update(float deltaTime);

	protected:
	std::string m_animation_left_name;
	std::string m_animation_right_name;
	std::string m_animation_center_name;

	int lastAnim;
	
	int currentState  = ANIM_CENTER;
	int state = ANIM_CENTER;
	glm::vec2 oldPos;


};

