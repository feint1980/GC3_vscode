#include "IcedObject.h"
#include "IceWall.h"


IcedObject::IcedObject()
{
}


IcedObject::~IcedObject()
{
}

void IcedObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;
	desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
	desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
	desRect.z = m_sprite.getDim().x  * m_scale.x;
	desRect.w = m_sprite.getDim().y  * m_scale.y;
	spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, 25.0f, m_color, m_angle);
}


void IcedObject::update(float deltaTime, F_Player & player, IceWall * icewall)
{

	dropTime += deltaTime;

	m_angle += m_angleRot * deltaTime;
	m_pos += /*(glm::vec2(0,4.0f) +*/  (m_dropVel * dropTime) * deltaTime;

	if (m_pos.y < -400)
	{
		m_isDone = true;
	}

	if(isCollisionWithPlayer(player))
	{
		player.die();
	}


	for (int i = 0; i < player.getBullets().size(); i++)
	{
		//std::cout << "called here \n";
		if (!player.getBullets()[i]->isDone())
		{
			if (isCollisionWithPlayerBullets(*player.getBullets()[i]))
			{
				
				icewall->freezeBullet(player.getBullets()[i]);
				

			}
		}
	}

	for (int i = 0; i < player.getLeftAccessosry().getBullets().size(); i++)
	{
		if (player.getLeftAccessosry().getBullets()[i])
		{
			if (!player.getLeftAccessosry().getBullets()[i]->isDone())
			{
				if (isCollisionWithPlayerBullets(*player.getLeftAccessosry().getBullets()[i]))
				{		
					icewall->freezeBullet(player.getLeftAccessosry().getBullets()[i]);

				}
			}
		}
	}
	for (int i = 0; i < player.getRightAccesory().getBullets().size(); i++)
	{

		if (player.getRightAccesory().getBullets()[i])
		{
			if (!player.getRightAccesory().getBullets()[i]->isDone())
			{
				if (isCollisionWithPlayerBullets(*player.getRightAccesory().getBullets()[i]))
				{

					icewall->freezeBullet(player.getRightAccesory().getBullets()[i]);

				}
			}
		}
	}
}

void IcedObject::init(const glm::vec2 & pos, const glm::vec2 & dim, Feintgine::F_Sprite & sprite, float angle, const glm::vec2 & scale)
{
	m_pos = pos;
	m_dim = dim;
	m_sprite = sprite;
	m_angle = angle;
	m_scale = scale;

	m_color = Feintgine::Color(300, 300, 300, 120);

	m_dropVel = glm::vec2(feint_common::Instance()->randomFloat(-0.01, 0.01f), -0.1f);
	m_angleRot = feint_common::Instance()->randomFloat(-0.01, 0.01f);
}

bool IcedObject::isCollisionWithPlayerBullets(const F_BulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim();

	glm::vec2 halfDim = m_dim * m_scale * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	if (pos.x + t_halfDim.x > m_pos.x - halfDim.x &&
		pos.y + t_halfDim.y < m_pos.y + halfDim.y &&
		pos.x - t_halfDim.x < m_pos.x + halfDim.x &&
		pos.y - t_halfDim.y > m_pos.y - halfDim.y)
	{
		//std::cout << "hit \n";
		return true;
	}

	return false;
}

bool IcedObject::isCollisionWithAllyBullets(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim();

	glm::vec2 halfDim = m_dim * m_scale * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	if (pos.x + t_halfDim.x > m_pos.x - halfDim.x &&
		pos.y + t_halfDim.y < m_pos.y + halfDim.y &&
		pos.x - t_halfDim.x < m_pos.x + halfDim.x &&
		pos.y - t_halfDim.y > m_pos.y - halfDim.y)
	{
		//std::cout << "hit \n";
		return true;
	}

	return false;
}

bool IcedObject::isCollisionWithPlayer(const F_Player & player)
{
	glm::vec2 pos = player.getPos();
	glm::vec2 dim = player.getDim();

	glm::vec2 halfDim = m_dim * m_scale * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	if (pos.x + t_halfDim.x > m_pos.x - halfDim.x &&
		pos.y + t_halfDim.y < m_pos.y + halfDim.y &&
		pos.x - t_halfDim.x < m_pos.x + halfDim.x &&
		pos.y - t_halfDim.y > m_pos.y - halfDim.y)
	{
		//std::cout << "hit \n";
		return true;
	}

	return false;
}
