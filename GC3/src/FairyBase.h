#pragma once

#include "F_EnemyBasic.h"


#define ANIM_LEFT 0
#define ANIM_RIGHT 1
#define ANIM_CENTER 2


#define FAIRY_BASE 0
#define AMPLIFIER 1
#define GUARDIAN 2
class FairyBase : public F_EnemyBasic
{ 
public:
	FairyBase();
	~FairyBase();
	void decideAnimation(const glm::vec2 & pos);

	void setMovementAnim(int val);

	void setCustomAnim(int type, const std::string & name);

	void update(float deltaTime);

	int getInternalID() const { return m_internal_ID; }

	protected:
	std::string m_animation_left_name;
	std::string m_animation_right_name;
	std::string m_animation_center_name;

	int lastAnim;
	
	int currentState  = ANIM_CENTER;
	int state = ANIM_CENTER;
	glm::vec2 oldPos;

	int m_internal_ID = FAIRY_BASE;


};

