#pragma once
#include <SpriteBatch.h>
#include <GLTexture.h>
#include "F_AnimatedObject.h"
#include <LightBatch.h>

#include <feint_common.h>
#include <F_oEvent.h>
#include <AudioEngine.h>
#include "EnemyBulletBase.h"
#include <glm/gtx/rotate_vector.hpp>
#include <chrono>
#include <Box2D/Box2D.h>
#include "GuardianShield.h"




class F_BaseEnemy
{
public:
	F_BaseEnemy();
	~F_BaseEnemy();

	void init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::GLTexture & texture);
	void init(const glm::vec2 & pos, const glm::vec2 & dim, const std::string & animationPath, float heath);

	glm::vec2 getRotatedVec(const glm::vec2 & t_vel,float angle);


	virtual void loadState(const std::string & name, bool preloaded = true) = 0;

	void loadLighting(const std::string & name);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void addLight(const glm::vec2 & offset, const glm::vec3 & color, const glm::vec3 & attenuation);

	void initShield(const std::string & animationPath, const glm::vec2 & pos, float scale);

	void setPos(const glm::vec2 & pos);
	/* still alive but playing death animation
	*/
	bool isDeath() const { return m_isDeath; }

	float getPt(float n1, float n2, float perc);

	virtual void update(float delta) = 0;

	void playAnim(const std::string & animName,int time = -1);
	void draw(Feintgine::SpriteBatch & spriteBatch);

	virtual void takeDamage(float dmg,bool playSound = true);

	bool isAlive() const { return m_isAlive; }

	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDim() const { return m_dim; }



	void addEvent(const Feintgine::oEvent::f_callback &cb, double when);

	void clearEvent();

	void timer();

	bool m_isDeath = false;
	

	void registerAudio(Feintgine::AudioEngine * engine);

	Feintgine::AudioEngine * getAudioEngine() const { return m_audioEngine; }

	void drawBullet(Feintgine::SpriteBatch & spriteBatch);

	void updateBullet(float deltaTime);

	//virtual void update(float deltaTime) = 0;
	
	std::vector<EnemyBulletBase *> m_bullets;
	int getScoreValue() const {
		return m_scoreValue;
	}

	void setPriority(int val);

	int getPriority() const { return m_priority; }

	glm::vec2 getVel() const { return m_vel; }

protected:

	GuardianShield * m_shield = nullptr;

	unsigned int m_scoreValue = 100;
	bool isAnimated = false;
	glm::vec2 m_pos;
	glm::vec2 m_dim;

	glm::vec2 m_vel;
	Feintgine::GLTexture m_texture;
	Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);
	float m_depth = 3.0f;
	float m_angle = 0.0f;
	
	bool m_isAlive = true;

	float berzierRate = 0.01f;
	
	int m_typeID = 0;

	std::vector<Feintgine::Light> m_lights;

	Feintgine::AudioEngine * m_audioEngine = nullptr;

	std::priority_queue<Feintgine::oEvent,
		std::vector<Feintgine::oEvent>, Feintgine::oEvent_less> event_queue;

	float m_heath = 100;
	Feintgine::F_AnimatedObject m_animation;

	int m_priority = 0;

};


