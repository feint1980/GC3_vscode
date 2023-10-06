#include "F_CollectableItem.h"
#include "F_Player.h"


F_CollectableItem::F_CollectableItem()
{
	
}


F_CollectableItem::~F_CollectableItem()
{
}


void F_CollectableItem::create(const glm::vec2 & pos)
{
	m_pos = pos;
}



void F_CollectableItem::init(const Feintgine::F_Sprite & sprite, const glm::vec2 & dim, const Feintgine::Color & color, float depth)
{
	m_dim = dim;
	m_sprite = sprite;
	m_color = color;
	m_depth = depth;
}

void F_CollectableItem::draw(Feintgine::SpriteBatch & spriteBatch)
{
	
	glm::vec4 desRect;
	desRect.x = m_pos.x - (m_dim.x) / 2.0f;
	desRect.y = m_pos.y - (m_dim.y) / 2.0f;
	desRect.z = m_dim.x;
	desRect.w = m_dim.y;
	spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);

}

void F_CollectableItem::bump(float y)
{
	m_vel.y = y;
	isBump = true;
}

void F_CollectableItem::update(F_Player * player, float deltaTime)
{
	if (isBump)
	{

		m_vel.y -= ITEM_GRAVITY * deltaTime;
		m_angle += 0.43f * deltaTime;
		if (m_vel.y < MIN_FAL_VEL_Y)
		{
			m_angle = 0;
			isBump = false;
		}
	}
	if (m_isOnPlayer)
	{
		m_vel = glm::normalize(player->getPos() - m_pos) * 12.5f;
	}
	m_pos += m_vel * deltaTime;
}

void F_CollectableItem::setPowerValue(unsigned int val)
{
	m_powerValue = val;
}

void F_CollectableItem::flyToPlayer()
{
	m_isOnPlayer = true;
	
}
