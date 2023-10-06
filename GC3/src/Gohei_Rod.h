#pragma once
#include <F_Sprite.h>
#include <SpriteBatch.h>
#include <AfterImageParticle.h>
#include <GLTexture.h>
#include "EnemyBulletBase.h"
#include <Box2D/Box2D.h>
#include <Camera2D.h>

class Gohei_Rod
{
public:
	Gohei_Rod();
	~Gohei_Rod();

	void init(const Feintgine::GLTexture & texture, const Feintgine::Color & color,
		const glm::vec2 & scale, float angle);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(const glm::vec2 &pos, float deltaTime, std::vector<EnemyBulletBase * > bullets);

	void drawDebug(Feintgine::DebugRender & renderer);

	void setMaxAngle(float angle);

	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	void registerCamera(Feintgine::Camera2D * camera);

	float getMax(float a, float b, float c, float d);

	float getMin(float a, float b, float c, float d);
	//void initLogic(b2World * world);

private :

	//b2Body * m_body = nullptr;

	//b2Fixture * m_fixture = nullptr;
	//glm::vec2 positionOffset;

	glm::vec2 m_dim;// = glm::vec2(100);


	Feintgine::Camera2D * m_camera;

	glm::vec2 m_pos;
	float m_angle;
	bool m_isDone = true;
	glm::vec2 m_scale;
	Feintgine::Color m_color;
	Feintgine::GLTexture m_texture;

	float m_maxAngle;

	AfterImageObject m_afterImageParticle;

};

