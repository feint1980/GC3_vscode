#pragma once

#include "EnemyAmplifier.h"
#include "F_Player.h"
#include "IceWall.h"

const int LINK_EFFECT_LIGHTNING = 1;

const int LINK_EFFECT_FROST = 2;

const int LINK_EFFECT_FLAME = 3;


class LinkAmplifier
{
public:
	LinkAmplifier();

	~LinkAmplifier();
	
	void init(const std::string & animationPath, const glm::vec2 & pos, EnemyAmplifier * leftAmplifier );


	/* will need :
	 - delta Time
	 - enemy bullets
	 - player
		- player bullet
		- player accessory 

	*/

	void update(float deltaTime,std::vector<EnemyBulletBase *> & enemies_bullets, F_Player & players);

	void updateAmplifyEffect(std::vector<EnemyBulletBase *> & enemies_bullets, F_Player & players);

	void handlingState(float deltaTime);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawDebug(Feintgine::DebugRender & debugRenderer);

	float calculateLinkScale();

	bool isCollisionWithPlayer(const F_Player & player);

	void handleLinker();

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	bool isCollisionWithPlayerBullets(const F_BulletBase & bullet);

	bool isCollisionWithAllyBullets(const EnemyBulletBase & bullet);

	bool isAlive() const { return m_isAlive; }

	bool isRemove() const { return m_isRemoved; }




private : 

	bool m_isIvertXY = false;

	bool m_isRemoved = false;
	bool m_isAlive = false;
	int m_state = 0 ;

	float m_alpha = 1.0f;

	glm::vec2 m_pos;

	glm::vec2 m_dim;

	glm::vec2 m_scale = glm::vec2(1.0f);

	Feintgine::F_AnimatedObject m_animation;

	EnemyAmplifier * m_leftAmplifier;

	EnemyAmplifier * m_rightAmplifier;

	int m_type = LINK_EFFECT_FROST;//LINK_EFFECT_LIGHTNING;

	IceWall m_iceWall;

};

