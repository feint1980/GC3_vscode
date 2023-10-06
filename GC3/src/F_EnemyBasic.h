#pragma once
#include "F_BaseEnemy.h"
#include "F_CollectableItem.h"
#include "ScoreItem.h"
#include "PowerItem.h"
#include "ArcFunction_hypocycloid.h"
#include "ArcFunction_hypotrochoid.h"
#include "feint_common.h"

class F_EnemyBasic : public F_BaseEnemy
{
public:
	F_EnemyBasic();
	~F_EnemyBasic();

	void update(float deltaTime);


	void setVel(const glm::vec2 & vel);

	virtual void loadState(const std::string & name, bool preloaded = true) override;


	void takeDamage(float damage, bool playSound = true);

	void initSound();

	void death();

	void onDrop(F_Player * player);

	glm::vec2 getBerzierPos(const glm::vec2 & start, const glm::vec2 & interotation, const glm::vec2 & destination, float perc);

	void moveBerzier(const glm::vec2 & start, const glm::vec2 & interotation, const glm::vec2 & destination, float speed);

	void loadPatern(const std::string & name,int count,int p_time);

	void setCollectableItem(const std::string & itemName);

	

	
	protected:
	bool m_isMoveBerzier = false;
	Feintgine::SoundEffect m_deadSoundEffect;
	Feintgine::SoundEffect m_hitSoundEffect;
	//glm::vec2 m_vel = glm::vec2(0, -0.0f);
	//float m_heath = 200;

	F_CollectableItem * m_item = nullptr;

	// Berzier section 
	glm::vec2 m_start;
	glm::vec2 m_inter;
	glm::vec2 m_des;
	float m_perc;
	float m_berzierSpeed;

	float t_angle = 0;
	//float posneg = 1;
	float f_angle = 0;


	
};

