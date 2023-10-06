#pragma once
#include "FairyBase.h"

const int linkBorderX = 300;
const int linkBorderY = 0;

class EnemyAmplifier : public FairyBase
{
public:
	EnemyAmplifier();
	~EnemyAmplifier();

	void update(float deltaTime, std::vector<EnemyAmplifier *> enemy, const F_Player & player);

	EnemyAmplifier * getNearestPartner(std::vector<EnemyAmplifier * > enemy);

	void handleAI(float deltaTime, std::vector<EnemyAmplifier *> enemy);

	void executeLink(float deltaTime);

	void decideAnimation(const glm::vec2 & pos);

	void setDisabled(bool value);

	bool isLeft() const { return m_isLeft; }

	bool isDisabled() const { return m_isDisabled; }

	EnemyAmplifier * getLinkPartner() const { return m_linkPartner; }

	int getLinkingStatus() const { return m_linkingStatus; }

	void setCreateFlag(bool val);

	bool getCreateFlag() const { return m_createFlag; }
	
protected:

	glm::vec2 direction;

	bool m_isLeft;
	bool m_isDisabled = false;
	EnemyAmplifier * m_linkPartner = nullptr;
	float m_intervalTime = 0.0f;
	float m_intervalValue = 10.0f;
	float m_intervalRate = 0.1f;

	bool m_createFlag = true;
	bool m_createFlag2 = false;


	bool linkBreak = false;

	float animationLimitCounter = 0;

	float m_phase2Timer = 0;
	//glm::vec2 speed = glm::vec2;
	
	int m_linkingStatus = 0;

};

