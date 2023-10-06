#pragma once
#include <F_Sprite.h>
#include "F_player.h"
#include "F_BulletBase.h"

class IceWall;
class IcedObject
{
public:
	IcedObject();
	~IcedObject();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime, F_Player & player, IceWall * icewall);

	void init(const glm::vec2 & pos, const glm::vec2 & dim, Feintgine::F_Sprite & sprite,float angle, const glm::vec2 & scale);

	bool isCollisionWithPlayerBullets(const F_BulletBase & bullet);

	bool isCollisionWithAllyBullets(const EnemyBulletBase & bullet);

	bool isCollisionWithPlayer(const F_Player & player);

	bool isDone() const { return m_isDone; }

private:


	bool m_isDone = false;
	Feintgine::F_Sprite m_sprite;
	glm::vec2 m_dropVel;
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	float dropTime = -22.0f;
	float m_depth;
	float m_alpha;
	Feintgine::Color m_color;
	glm::vec2 m_scale;
	float m_angle;
	float m_angleRot;
};

 