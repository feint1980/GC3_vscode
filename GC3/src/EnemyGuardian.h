#pragma once
#include "FairyBase.h"
//#include <>
#include "F_Player.h"
#include "EnemyAmplifier.h"


class EnemyGuardian : public FairyBase
{
public:
	EnemyGuardian();
	~EnemyGuardian();

	void update(float deltaTime, std::vector<FairyBase *> enemy, const F_Player & player );

	void decideStrat(float deltaTime, std::vector<FairyBase *> enemy,   const F_Player & player);

	FairyBase * getHighestPriorityEnemy(std::vector<FairyBase *> enemy, const F_Player & player);

	FairyBase * getHighestPriorityAmplifier(std::vector<FairyBase *> amplifier, const F_Player & player);

	void handleShieldFormation(float deltaTime);

	void decideAnimation(const glm::vec2 & pos);

	void setDisabled(bool value);

protected:


	bool m_isDisabled = false;
	float m_intervalTime = 9.0f;	
	float m_intervalValue = 10.0f;
	float m_intervalRate = 0.1f;

	float animationLimitCounter = 0;

	glm::vec2 direction;

	FairyBase * protectingTarget = nullptr;
	

};

