#pragma once

#include <SpriteBatch.h>
#include <GLTexture.h>
#include "F_AnimatedObject.h"

#include <feint_common.h>
#include <F_Event.h>
#include <AudioEngine.h>


class F_Player;

const float ITEM_GRAVITY = 0.5f;
const float MIN_FAL_VEL_Y = -2.5f;

class F_CollectableItem
{
public:
	F_CollectableItem();
	~F_CollectableItem();

	void create(const glm::vec2 & pos);


	void init(const Feintgine::F_Sprite & sprite, const glm::vec2 & dim, const Feintgine::Color & color, float depth);
	void draw(Feintgine::SpriteBatch & spriteBatch);

	void bump(float y);

	void update(F_Player * player, float deltaTime);

	void setPowerValue(unsigned int val);

	void flyToPlayer();

	virtual void onCollected(F_Player * player) = 0;

	glm::vec2 getPos() const { return m_pos; }

	glm::vec2 getDim() const { return m_dim; }

	protected:

	glm::vec2 m_pos;
	glm::vec2 m_dim;
	float m_angle;
	Feintgine::F_Sprite m_sprite;
	float m_depth;
	Feintgine::Color m_color;
	glm::vec2 m_vel;
	bool m_isOnPlayer = false;
	//glm::vec2 m_toPlayerVel;
	bool isBump = false;

	unsigned int m_powerValue = 0;


};

