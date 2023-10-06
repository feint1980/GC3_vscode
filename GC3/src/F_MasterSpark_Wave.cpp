#include "F_MasterSpark_Wave.h"
#include <feint_common.h>


F_MasterSpark_Wave::F_MasterSpark_Wave()
{
}


F_MasterSpark_Wave::~F_MasterSpark_Wave()
{
}

void F_MasterSpark_Wave::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;
	desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
	desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
	desRect.z = m_sprite.getDim().x  * m_scale.x;
	desRect.w = m_sprite.getDim().y  * m_scale.y;
	spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, 1, m_color,
		m_angle);
}

void F_MasterSpark_Wave::init(const glm::vec2 & pos, const glm::vec2 & scale,
	const Feintgine::F_Sprite & textureName,
	const Feintgine::Color & color)
{
	m_pos = pos;
	t_scale = scale;
	m_scale = glm::vec2(0.8f);
	m_sprite = textureName; 
	m_color = color;
	m_isAlive = true;
}

void F_MasterSpark_Wave::drawLight(Feintgine::LightBatch & lightBatch)
{
	if (m_isAlive)
	{


		glm::vec2 tt;
		tt.x = m_pos.x + m_sprite.getDim().y * 0.4f * m_scale.x;
		tt.y = m_pos.y;

		float randomScale = 0.4;
		float randomR = feint_common::Instance()->randomFloat(0, randomScale);
		float randomG = feint_common::Instance()->randomFloat(0, randomScale);
		float randomB = feint_common::Instance()->randomFloat(0, randomScale);
		Feintgine::Color tColor = m_color;
		// 	tColor.r *= 0.7f;
		// 	tColor.g *= 0.7f;
		// 	tColor.b *= 0.7f;

		lightBatch.addLight(m_pos, glm::vec4(tColor.r + randomR * sin(m_lifeTime),
			tColor.g + randomG * cos(m_lifeTime),
			tColor.b + randomB * sin(m_lifeTime), m_color.a), glm::vec3(1.0f / m_attentionua.x, 1.0f / m_attentionua.y, 1.0f / m_attentionua.z));
// 		lightBatch.addLight(tt, glm::vec4(tColor.r + randomR * sin(m_lifeTime),
// 			tColor.g + randomG * sin(m_lifeTime),
// 			tColor.b + randomB * cos(m_lifeTime), m_color.a), glm::vec3(1.0f / m_attentionua.x, 1.0f / m_attentionua.y, 1.0f / m_attentionua.z));
// 		tt.x = m_pos.x - m_sprite.getDim().y * 0.4f * m_scale.x;
// 		lightBatch.addLight(tt, glm::vec4(tColor.r + randomR * sin(m_lifeTime),
// 			tColor.g + randomG * sin(m_lifeTime),
// 			tColor.b + randomB * sin(m_lifeTime), m_color.a), glm::vec3(1.0f / m_attentionua.x, 1.0f / m_attentionua.y, 1.0f / m_attentionua.z));


// 		tt.x = m_pos.x - m_sprite.getDim().y * 0.25f * m_scale.x;
// 		lightBatch.addLight(tt, glm::vec4(tColor.r + randomR * sin(m_lifeTime),
// 			tColor.g + randomG * sin(m_lifeTime),
// 			tColor.b + randomB * sin(m_lifeTime), m_color.a), glm::vec3(1.0f / m_attentionua.x, 1.0f / m_attentionua.y, 1.0f / m_attentionua.z));
// 
// 		tt.x = m_pos.x + m_sprite.getDim().y * 0.25f * m_scale.x;
// 		lightBatch.addLight(tt, glm::vec4(tColor.r + randomR * sin(m_lifeTime),
// 			tColor.g + randomG * sin(m_lifeTime),
// 			tColor.b + randomB * sin(m_lifeTime), m_color.a), glm::vec3(1.0f / m_attentionua.x, 1.0f / m_attentionua.y, 1.0f / m_attentionua.z));

	}
}

void F_MasterSpark_Wave::update(float deltaTime)
{
	handleScale(deltaTime);
	m_pos += m_vel * deltaTime;

	m_lifeTime -= 0.1f * deltaTime;
	if (m_lifeTime < 0.0f)
	{
		m_isAlive = false;
	}
}

void F_MasterSpark_Wave::handleScale(float deltaTime)
{
	if (m_scale.x < t_scale.x)
	{
		m_scale.x += 0.125f * deltaTime;
		m_scale.y += 0.125f * deltaTime;
	}
}

glm::vec2 F_MasterSpark_Wave::rotatePoint(const glm::vec2& pos, float angle)
{
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}

void F_MasterSpark_Wave::setAngle(float angle)
{
	m_angle = angle;
// 	m_vel.x = m_vel.x * cos(m_angle + degreeToRad(90));
// 	m_vel.y = m_vel.y * sin(m_angle + degreeToRad(90));

	float t_angle = m_angle - degreeToRad(90);
	m_vel.x = m_vel.x * cos(t_angle) - m_vel.y * sin(t_angle);
	m_vel.y = m_vel.x * sin(t_angle) + m_vel.y * cos(t_angle);
}
