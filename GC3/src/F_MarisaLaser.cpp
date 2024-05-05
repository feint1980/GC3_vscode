#include "F_MarisaLaser.h"
#include "F_BaseEnemy.h"
#include "FairyBase.h"
#include "EnemyAmplifier.h"
#include "EnemyGuardian.h"
#include "GlobalValueClass.h"
#include <ParticleBatch2D.h>
#include <ParticleEngine2D.h>
F_MarisaLaser::F_MarisaLaser()
{
	//glm::vec3(20.0f, 11.0f, 5.0f);
	m_attenuation = glm::vec3(14.0f, 9.0f, 5.0f);

	// glm::vec3(7.0f, 5.0f, 12.0f);
	glm::vec3 m_sparkAttenuation = glm::vec3(10.0f, 8.0f, 12.0f);

	m_isVisible = false;
	m_isSwitchHappen = true;
}


F_MarisaLaser::~F_MarisaLaser()
{

}


void F_MarisaLaser::init(const  Feintgine::GLTexture & texture, const glm::vec2 & pos,
	const glm::vec2 & dim, const Feintgine::Color & color, float depth, float angle, float dps, const Feintgine::F_Sprite & starSprite,float dmg)
{

	m_texture = texture;
	m_pos = pos;
	m_dim = dim;
	//m_color = color;
	m_depth = depth;
	m_angle = angle;
	m_rotation = m_angle;
	m_dps = dps;
	m_uvrect = glm::vec4 (0.0f, 0.0f, 5.0f, 1.0f);
	m_isVisible = false;
	m_starSprite = starSprite;
	m_energy = MAX_ENERGY;
	m_dmg = dmg;
}


void F_MarisaLaser::draw(Feintgine::SpriteBatch & spriteBatch)
{
		
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dim.x / 2.0f;
	desRect.y = m_pos.y - m_dim.y / 2.0f;
	desRect.z = m_dim.x;
	desRect.w = m_dim.y;
	spriteBatch.draw(desRect, m_uvrect, m_texture.id, m_depth, m_color, m_angle);
	drawStar(spriteBatch);

}

void F_MarisaLaser::update(float deltaTime, const glm::vec2 pos, std::vector<FairyBase *>  enemies, bool updateColor )
{


	m_pos.x = pos.x;
	m_pos.y = pos.y + (m_dim.x * 0.5f);
	updateUV(deltaTime);

	m_starAngle += 0.1f * deltaTime;
	if (updateColor)
	{
		updateEnergyLocked(deltaTime);
	}
	
	if (m_isSwitchHappen)
	{
		if (m_isVisible)
		{
			if (updateColor)
			{
				updateEnergyBar(deltaTime);
			}
			
			m_particleCooldown += 0.1f * deltaTime;
			if (m_color.change(15, 0.05f, maxColorVal))
			{
				//std::cout << "stop \n;"
				m_isSwitchHappen = false;	
			}

			float totalDmg = m_dmg;
			if (m_isLowPower)
			{
				totalDmg *= 0.75f;
			// }
			// for (int i = 0; i < amplifiers.size(); i++)
			// {
			// 	if (checkColiderWithAmplifier(*amplifiers[i]))
			// 	{
					
			// 		amplifiers[i]->takeDamage(totalDmg);
			// 		createParticle(amplifiers[i]);
			// 		//std::cout << "1 \n";
			// 	}
			// }

			for (int i = 0; i < enemies.size(); i++)
			{
				if (checkColiderWithEmeny(*enemies[i]))
				{
					enemies[i]->takeDamage(totalDmg);
					createParticle(enemies[i]);
					//std::cout << "2 \n";
				}
			}

			// for (int i = 0; i < guardians.size(); i++)
			// {
			// 	if (checkColiderWithGuardian(*guardians[i]))
			// 	{
			// 		guardians[i]->takeDamage(totalDmg);
			// 		createParticle(guardians[i]);
			// 		//std::cout << "3 \n";
			// 	}
			// }
		}
		else
		{
			
// 			m_energy += ENERGY_RATE * m_pernaltyRate * deltaTime ;
// 
// 			if (m_energy >= MAX_ENERGY)
// 			{
// 				m_energy = MAX_ENERGY;
// 			}
// 			GlobalValueClass::Instance()->setLaserEnergy(m_energy);
			if (m_color.change(15, -0.025f, minColorVal))
			{
				//std::cout << "stop \n";
				m_isSwitchHappen = false;
			}
		}
	}
	
}

}
bool F_MarisaLaser::checkColiderWithEmeny(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dim * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	//bool returnValue;
	double center_rec_x = m_pos.x;
	double center_rec_y = m_pos.y + m_dim.y / 2.0f;
	double cir_x_rotate = cos(m_angle) * (pos.x - m_pos.x) - sin(m_angle) * (pos.y - m_pos.y) + m_pos.x;
	double cir_y_rotate = sin(m_angle) * (pos.x - m_pos.x) + cos(m_angle) * (pos.y - m_pos.y) + m_pos.y;
	double distance_center_x = abs(cir_x_rotate - center_rec_x);
	double distance_center_y = abs(cir_y_rotate - center_rec_y);
	double distance_center_corner_x = distance_center_x - m_dim.x / 2.0f;
	double distance_center_corner_y = distance_center_y - m_dim.y / 2.0f;
	if (distance_center_x > dim.x + m_dim.x / 2.0f) return false;
	if (distance_center_y > dim.x + m_dim.y / 2.0f) return false;
	if (distance_center_x < m_dim.x / 2.0f) return true;
	if (distance_center_y < m_dim.y / 2.0f) return true;
	if (pow(distance_center_corner_x, 2) + pow(distance_center_corner_y, 2) <= pow(dim.x, 2)) return true;

// 	if (sin(m_angle) * (pos.y - m_pos.y) >= cos(m_angle) * (pos.x - m_pos.x) - halfDim.x
// 		&& sin(m_angle) * (pos.y - m_pos.y) >= cos(m_angle) * (pos.x - m_pos.x) + halfDim.x)
// 	{
// 		if (m_pos.y * sin(m_angle) > pos.y)
// 		{
// 			return true;
// 		}
// 	}

// 	if (m_pos.x + halfDim.y > pos.x - t_halfDim.x &&
// 		m_pos.y + halfDim.x < pos.y + t_halfDim.y &&
// 		m_pos.x - halfDim.y < pos.x + t_halfDim.x &&
// 		m_pos.y - halfDim.x > pos.y - t_halfDim.y)
// 	{
// 		return true;
// 	}

	return false;
}

bool F_MarisaLaser::checkColiderWithGuardian(const EnemyGuardian & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	double center_rec_x = m_pos.x;
	double center_rec_y = m_pos.y + m_dim.y / 2.0f;
	double cir_x_rotate = cos(m_angle) * (pos.x - m_pos.x) - sin(m_angle) * (pos.y - m_pos.y) + m_pos.x;
	double cir_y_rotate = sin(m_angle) * (pos.x - m_pos.x) + cos(m_angle) * (pos.y - m_pos.y) + m_pos.y;
	double distance_center_x = abs(cir_x_rotate - center_rec_x);
	double distance_center_y = abs(cir_y_rotate - center_rec_y);
	double distance_center_corner_x = distance_center_x - m_dim.x / 2.0f;
	double distance_center_corner_y = distance_center_y - m_dim.y / 2.0f;
	if (distance_center_x > dim.x + m_dim.x / 2.0f) return false;
	if (distance_center_y > dim.x + m_dim.y / 2.0f) return false;
	if (distance_center_x < m_dim.x / 2.0f) return true;
	if (distance_center_y < m_dim.y / 2.0f) return true;
	if (pow(distance_center_corner_x, 2) + pow(distance_center_corner_y, 2) <= pow(dim.x, 2)) return true;

	return false;
}
// 	glm::vec2 halfDim = m_dim * 0.5f;
// 	glm::vec2 t_halfDim = dim * 0.5f;
// 
// 	if (sin(m_angle) * (pos.y - m_pos.y) >= cos(m_angle) * (pos.x - m_pos.x) - halfDim.x
// 		&& sin(m_angle) * (pos.y - m_pos.y) >= cos(m_angle) * (pos.x - m_pos.x) + halfDim.x)
// 	{
// 		if (m_pos.y * sin(m_angle) > pos.y)
// 		{
// 			return true;
// 		}
// 		
// 	}
// 	return false;
// }

bool F_MarisaLaser::checkColiderWithAmplifier(const EnemyAmplifier & enemy)
{
	glm::vec2 pos = enemy.getPos(); // x,y 
	glm::vec2 dim = enemy.getDim(); // 


	double center_rec_x = m_pos.x;
	double center_rec_y = m_pos.y + m_dim.y / 2.0f;
	double cir_x_rotate = cos(m_angle) * (pos.x - m_pos.x) - sin(m_angle) * (pos.y - m_pos.y) + m_pos.x;
	double cir_y_rotate = sin(m_angle) * (pos.x - m_pos.x) + cos(m_angle) * (pos.y - m_pos.y) + m_pos.y;
	double distance_center_x = abs(cir_x_rotate - center_rec_x);
	double distance_center_y = abs(cir_y_rotate - center_rec_y);
	double distance_center_corner_x = distance_center_x - m_dim.x / 2.0f;
	double distance_center_corner_y = distance_center_y - m_dim.y / 2.0f;
	if (distance_center_x > dim.x + m_dim.x / 2.0f) return false;
	if (distance_center_y > dim.x + m_dim.y / 2.0f) return false;
	if (distance_center_x < m_dim.x / 2.0f) return true;
	if (distance_center_y < m_dim.y / 2.0f) return true;
	if (pow(distance_center_corner_x, 2) + pow(distance_center_corner_y, 2) <= pow(dim.x, 2)) return true;

	return false;

// 	glm::vec2 pos = enemy.getPos(); // x,y 
// 	glm::vec2 dim = enemy.getDim(); // 
// 
// 	glm::vec2 halfDim = m_dim * 0.5f;
// 	glm::vec2 t_halfDim = dim * 0.5f;
// 
// 
// 	if (sin(m_angle) * (pos.y - m_pos.y) >= cos(m_angle) * (pos.x - m_pos.x) - halfDim.x
// 		&& sin(m_angle) * (pos.y - m_pos.y) >= cos(m_angle) * (pos.x - m_pos.x) + halfDim.x)
// 	{
// 		if (m_pos.y * sin(m_angle) > pos.y)
// 		{
// 			return true;
// 		}
// 	}
// 
 	
}

void F_MarisaLaser::drawHitbox(Feintgine::DebugRender & debugRenderer)
{
	glm::vec2 halfDim = m_dim * 0.5f;

	glm::vec2 tl = glm::vec2(-halfDim.x, halfDim.y) + m_pos;
	glm::vec2 bl = glm::vec2(-halfDim.x, -halfDim.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDim.x, -halfDim.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDim.x, halfDim.y) + m_pos;

	glm::vec2 positionOffset = m_pos;

	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;
	// Rotate the points
	//float tAgnle = (m_angle);
	// 	a_tl = t_rotatePoint(tl, tAgnle) ;
	// 	a_bl = t_rotatePoint(bl, tAgnle)  ;
	// 	a_br = t_rotatePoint(br, tAgnle)  ;
	// 	a_tr = t_rotatePoint(tr, tAgnle)  ;
	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim);
	//renderer.drawBox(a_tl, a_tr, a_br, a_bl, Feintgine::Color(255, 0, 0, 255), tAgnle);
	//renderer.drawBox(tl, tr, br, bl, Feintgine::Color(255, 0, 0, 255), tAgnle);
	debugRenderer.drawBox(desRect, Feintgine::Color(255, 0, 0, 255), m_angle);
}

void F_MarisaLaser::updateUV(float deltaTime)
{
	m_uvrect.x += updateUVRate;
	//m_uvrect.z += updateUVRate;
}

void F_MarisaLaser::setVisible(bool val)
{
	//if(m_energy )
	if (m_energyLocked)
	{
		val = false;
	}
	m_isVisible = val;
	m_isSwitchHappen = true;

}

void F_MarisaLaser::setMaxMinColorVal(float t_max, float t_min)
{
	maxColorVal = t_max;
	minColorVal = t_min;
}

void F_MarisaLaser::drawStar(Feintgine::SpriteBatch & spriteBatch)
{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_starSprite.getDim().x / 2.0f ) * m_starScale;
		desRect.y = m_pos.y - m_starSprite.getDim().y / 2.0f - m_dim.x /2.0f;
		desRect.z = m_starSprite.getDim().x * m_starScale;
		desRect.w = m_starSprite.getDim().y * m_starScale;
		spriteBatch.draw(desRect, m_starSprite.getUV(), m_starSprite.getTexture().id, m_depth, glm::vec4(m_color.r * m_rateR * 0.1f, m_color.g * m_rateG * 5.5f, m_color.b * m_rateB, m_color.a), m_starAngle);
	
}

void F_MarisaLaser::drawRayLight(Feintgine::LightBatch & lightBatch)
{
	glm::vec2 lightPos = m_pos;
	lightPos.y -= m_dim.x * 0.5f;
	//float m_rotation = 
	t_attenuation = m_attenuation  - (m_attenuation *0.5f) *  GlobalValueClass::Instance()->getAmbientLight().x;
	lightBatch.addRayLight(lightPos, glm::vec4(m_color.r * m_rateR, m_color.g * m_rateG, m_color.b * m_rateB, m_color.a)
		, 1.0f/ t_attenuation, m_rotation);
}

void F_MarisaLaser::setStarScale(float val)
{
	m_starScale = val;
}

void F_MarisaLaser::setAlpha(float val)
{
	m_color.a = val;
}

void F_MarisaLaser::setAttenuation(const glm::vec3 & atten)
{
	m_attenuation = atten;
}

void F_MarisaLaser::setRotation(float value)
{
	m_angle = value;
	m_rotation = value;
}

float F_MarisaLaser::getEnergy()
{
	return m_energy;
	//return GlobalValueClass::Instance()->getLaserEnergy();
}

void F_MarisaLaser::setEnergy(float energy)
{
	//GlobalValueClass::Instance()->setLaserEnergy(energy);
	m_energy = energy;
}

void F_MarisaLaser::updateEnergyBar(float deltaTime)
{
	//std::cout << m_energy << "\n";
	//m_energy -= ENERGY_RATE * deltaTime;

	if (m_energy < LOW_ENERGY_RATE)
	{
		m_isLowPower = true;
		toggleSwitchEnergy();
		//m_energyCounter = 0.0f;
			
	}
	else
	{
		m_isLowPower = false;
		toggleSwitchEnergy();
		//m_energyCounter = 0.0f;
	}

	// update Color

	if (m_energySwitching)
	{
		if (m_isLowPower)
		{
			if (m_rateR <= 1.0f)
			{
				m_rateR += ENERGY_RATE * 5.0f * deltaTime;
				if (m_rateR >= 1.0f)
				{
					m_rateR = 1.0f;
					m_energySwitching = false;
				}
			}
			if (m_rateG >= 0.4f)
			{
				m_rateG -= ENERGY_RATE * 12.0f * deltaTime;
				if (m_rateG <= .4f)
				{
					m_rateG = .4f;
					m_energySwitching = false;
				}
			}
		}
		else
		{
			if (m_rateG <= 1.0f)
			{
				m_rateG += ENERGY_RATE * 5.0f *  deltaTime;
				if (m_rateG >= 1.0f)
				{
					m_rateG = 1.0f;
					m_energySwitching = false;
				}
			}
			if (m_rateR >= 0.4f)
			{
				m_rateR -= ENERGY_RATE * 12.0f *  deltaTime;
				if (m_rateR <= .4f)
				{
					m_rateR = .4f;
					m_energySwitching = false;
				}
			}
		}
	}
	//GlobalValueClass::Instance()->setLaserEnergy(m_energy);
}

void F_MarisaLaser::toggleSwitchEnergy()
{
	if (!m_energySwitching)
	{
		m_energySwitching = true;
	}
}

void F_MarisaLaser::setParticle(Feintgine::ParticleBatch2D * particleBatch)
{
	m_particleBatch = particleBatch;
}

void F_MarisaLaser::createParticle(F_BaseEnemy * enemy)
{
	if (m_particleCooldown > 0.4f)
	{

		if (m_particleBatch)
		{
			//std::cout << "created spark " << m_particleCooldown << "\n";
			float ranX = feint_common::Instance()->getRandomNum(-1.5f, 1.5f);
			float ranY = feint_common::Instance()->getRandomNum(-1.5f, 4.5f);
			glm::vec2 halfDim = enemy->getDim() * 0.5f;
			t_sparkAttenuation = m_sparkAttenuation - (m_sparkAttenuation * 0.8f) *  GlobalValueClass::Instance()->getAmbientLight().x;

			m_particleBatch->addParticle(enemy->getPos() - halfDim, glm::vec2(ranX, ranY),
				Feintgine::Color(255 * m_rateR, 255 * m_rateG, 255 * m_rateB, 255), 
				0.0f,3.1f, t_sparkAttenuation);
		}
		m_particleCooldown = 0.0f;
	}

}

void F_MarisaLaser::updateEnergyLocked(float deltaTime)
{
	if (m_energy <= 0.0f)
	{
		m_energyLocked = true;
		m_energyCounter = 0.0f;
		m_pernaltyRate = 0.7f;
	}
	if (m_energyLocked)
	{
		if (m_energyCounter < 3.7f)
		{
			m_energyCounter += 0.1f * deltaTime;
		}
		else
		{
			m_energyLocked = false;
			m_pernaltyRate = 1.0f;
		}
	}
}

void F_MarisaLaser::setColorRate(const glm::vec3 & colorRate)
{
	m_rateR = colorRate.x;
	m_rateG = colorRate.y;
	m_rateB = colorRate.z; 
}

void F_MarisaLaser::setSparkAttenuation(const glm::vec3 & color)
{
	m_sparkAttenuation = color;
}
