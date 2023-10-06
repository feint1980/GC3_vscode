#include "F_BulletBase.h"
#include "EnemyGuardian.h"


F_BulletBase::F_BulletBase()
{
	//m_animation
}


F_BulletBase::~F_BulletBase()
{
}

void F_BulletBase::init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
	const Feintgine::F_Sprite & sprite, float depth, float dmg,
	Feintgine::ParticleBatch2D * hitParticleBatch)
{
	m_pos = pos;
	m_dims = dim;
	m_color = color;
	m_sprite = sprite;
	m_depth = depth;
	m_damage = dmg;

// 	m_particleBatch = new Feintgine::ParticleBatch2D();
// 	Feintgine::F_Sprite t_sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/particle_white_3.png");
// 	m_particleBatch->init(50, 0.1f, t_sprite);
	
	//m_scale = dim / m_sprite.getDim();
	//m_scale = 1.0f;

	m_particleBatch = hitParticleBatch;
}

void F_BulletBase::init(const glm::vec2 & pos, const glm::vec2 & dim,
	const Feintgine::Color & color, const Feintgine::F_AnimatedObject & animation
	, float depth, float dmg, Feintgine::ParticleBatch2D * hitParticleBatch /*= nullptr*/)
{
	m_pos = pos;
	m_dims = dim;
	m_color = color;
	//m_sprite = sprite;
	m_depth = depth;
	m_damage = dmg;

// 	m_particleBatch = new Feintgine::ParticleBatch2D();
// 	Feintgine::F_Sprite t_sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/particle_white_3.png");
// 	m_particleBatch->init(50, 0.1f, t_sprite);

	//m_scale = dim / m_sprite.getDim();
	//m_scale = 1.0f;
	//m_animation.init(animationPath);
	m_animation = animation;
	m_animation.setColor(m_color);
	m_destroyAnimName = "destroy";
	m_particleBatch = hitParticleBatch;
	m_isAnimated = true;
}

void F_BulletBase::init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
	const std::string & animationPath, float depth, float dmg,
	Feintgine::ParticleBatch2D * hitParticleBatch)
{
	m_pos = pos;
	m_dims = dim;
	m_color = color;
	//m_sprite = sprite;
	m_depth = depth;
	m_damage = dmg;

// 	m_particleBatch = new Feintgine::ParticleBatch2D();
// 	Feintgine::F_Sprite t_sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/particle_white_3.png");
// 	m_particleBatch->init(50, 0.1f, t_sprite);

	//m_scale = dim / m_sprite.getDim();
	//m_scale = 1.0f;
	m_animation.init(animationPath);
	m_animation.setColor(color);
	m_destroyAnimName = "destroy";
	//m_animation = animation;
	m_particleBatch = hitParticleBatch;
	m_isAnimated = true;
}



void F_BulletBase::setBulletAnimationAction(const std::string & actionName)
{
	if (m_isAnimated)
	{
		m_animation.playAnimation(actionName,-1);
	}
}

void F_BulletBase::setBulletAnimationAngle(float angle)
{
	if (m_isAnimated)
	{
		m_animation.setAngle(angle);
	}
}

void F_BulletBase::draw(Feintgine::SpriteBatch & spriteBatch)
{
	//const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);

	if (!m_isAnimated)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
	}
	else
	{
		glm::vec2 additionalPos;
		//if (radToDegree(m_animation.getAngle() == 90))
		//{
		additionalPos.x = -m_animation.getDim().x ;
		//}

		m_animation.setPos(m_pos + additionalPos);
		//m_animation.setScale(glm::vec2(1.0));
		m_animation.draw(spriteBatch);
	}
}

void F_BulletBase::drawLight(Feintgine::LightBatch & lightBatch)
{

	glm::vec2 halfDim = m_animation.getDim();
	halfDim.x = halfDim.x * sin(m_animation.getAngle());
	halfDim.y = halfDim.y * cos(m_animation.getAngle());
	lightBatch.addLight(m_pos - halfDim * 0.5f, glm::vec4(1.0f), glm::vec3(1.0f / m_attentionua.x, 1.0f / m_attentionua.y, 1.0f / m_attentionua.z));

	//m_particleBatch->drawLight(lightBatch);
}

void F_BulletBase::setAlpha(float val)
{
	m_color.a = val;
	m_animation.setAlpha(val);
}

void F_BulletBase::setDamage(float dmg)
{
	m_damage = dmg;
}

bool F_BulletBase::checkColiderWithEmeny(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dims * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;


	if (m_pos.x + halfDim.x > pos.x - t_halfDim.x &&
		m_pos.y + halfDim.y < pos.y + t_halfDim.y &&
		m_pos.x - halfDim.x < pos.x + t_halfDim.x &&
		m_pos.y - halfDim.y > pos.y - t_halfDim.y)
	{
		return true;
	}

	return false;

}

bool F_BulletBase::checkColiderWithGuardian(const EnemyGuardian & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dims * 0.9f;
	glm::vec2 t_halfDim = dim * 0.9f;


	if (m_pos.x + halfDim.x > pos.x - t_halfDim.x &&
		m_pos.y + halfDim.y < pos.y + t_halfDim.y &&
		m_pos.x - halfDim.x < pos.x + t_halfDim.x &&
		m_pos.y - halfDim.y > pos.y - t_halfDim.y)
	{
		return true;
	}

	return false;
}



bool F_BulletBase::checkColiderWithAmplifier(const EnemyAmplifier & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dims * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;


	if (m_pos.x + halfDim.x > pos.x - t_halfDim.x &&
		m_pos.y + halfDim.y < pos.y + t_halfDim.y &&
		m_pos.x - halfDim.x < pos.x + t_halfDim.x &&
		m_pos.y - halfDim.y > pos.y - t_halfDim.y)
	{
		return true;
	}

	return false;
}

void F_BulletBase::setScale(const glm::vec2 & scale)
{
	m_scale = scale;
	m_animation.setScale(m_scale);
}

void F_BulletBase::setLifeTime(float time)
{
	m_lifeTime = time;
}

void F_BulletBase::setAlive(bool val)
{
	m_isAlive = val;
}

void F_BulletBase::destroy()
{
	if (m_isAnimated)
	{
		m_isDone = true;
		m_vel = glm::vec2(0, 0);
		m_animation.playAnimation(m_destroyAnimName, 1);
		m_scale *= 1.3f;

	}
}

void F_BulletBase::setVel(const glm::vec2 & vel)
{
	m_vel = vel;
}

void F_BulletBase::setDestroyAnimName(const std::string & name)
{
	m_destroyAnimName = name;
}

void F_BulletBase::setAttenuation(const glm::vec3 & atten)
{
	m_attentionua = atten;
}

