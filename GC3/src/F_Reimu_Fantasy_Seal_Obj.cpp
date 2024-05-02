#include "F_Reimu_Fantasy_Seal_Obj.h"
#include "GlobalValueClass.h"


F_Reimu_Fantasy_Seal_Obj::F_Reimu_Fantasy_Seal_Obj()
{
	srand(time(NULL));
	m_lifeTime = 30 + feint_common::Instance()->getRandomNum(-10.5f, 10.5f);
}



F_Reimu_Fantasy_Seal_Obj::~F_Reimu_Fantasy_Seal_Obj()
{

}

void F_Reimu_Fantasy_Seal_Obj::init(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 dim, const Feintgine::Color & color)
{
	m_pos = pos;
	m_dim = dim;
	m_sprite = sprite;
	m_color = color;
	//m_attentionua = glm::vec3(9, 33, 36);
	m_attentionua = glm::vec3(9, 16, 22) ;
	t_attentionua = m_attentionua;
	m_explosionSprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png");
	m_dim = m_sprite.getDim();
	
}

void F_Reimu_Fantasy_Seal_Obj::registerEffectBatch(Feintgine::EffectBatch * effectBatch)
{
	m_effectBatch = effectBatch;
}

void F_Reimu_Fantasy_Seal_Obj::draw(Feintgine::SpriteBatch & spriteBatch)
{
	// Universal way to draw object with F_sprite ( keep this in mind pls )
	glm::vec4 desRect;// (0, 0, 50, 50);
	desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale / 2.0f);
	desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale / 2.0f);
	desRect.z = m_scale * m_sprite.getDim().x;
	desRect.w = m_scale * m_sprite.getDim().y;
// 
 	spriteBatch.draw(desRect, m_sprite.getUV(),
 		m_sprite.getTexture().id, 15, m_color, 0);

}

void F_Reimu_Fantasy_Seal_Obj::registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch)
{
	m_hitParticleBatch = particleBatch;
}

void F_Reimu_Fantasy_Seal_Obj::registerExplosionRing(std::vector<ExplosionRing> * rings)
{
	m_exlosions = rings;
}

void F_Reimu_Fantasy_Seal_Obj::drawLight(Feintgine::LightBatch & lightBatch)
{
	glm::vec2 tt;
	//t_attentionua = m_attentionua;
	
	glm::vec2 m_additionalPos;
	int numberOfLight = 1;
//	for (int i = 0; i < numberOfLight; i++)
//	{
// 		m_additionalPos = glm::vec2(0);
// 		m_additionalPos.x = cos(m_circleAngle +  degreeToRad(360.0f / numberOfLight * i)) * 25.2f;
// 		m_additionalPos.y =  sin(m_circleAngle +  degreeToRad(360.0f / numberOfLight * i)) * 25.2f;
// 		tt.x = m_additionalPos.x + m_pos.x;
// 		tt.y = m_additionalPos.y + m_pos.y;


 		lightBatch.addLight(m_pos, getOrbColor(lightID) * GlobalValueClass::Instance()->getLightBalance(),
 			glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z));


	//}

	
}

void F_Reimu_Fantasy_Seal_Obj::update(float deltaTime, 
	std::vector<FairyBase *>  enemy, std::vector<EnemyBulletBase * > bullets)
{

	if (isLocked)
	{
		if (m_pos.x < -FANTASY_SEAL_BORDER)
		{

			m_pos.x = -FANTASY_SEAL_BORDER + m_vel.x;
			m_vel.x = 0;
			isDecided = false;
			m_lifeTime -= 0.5f * deltaTime;


		}
		if (m_pos.x > FANTASY_SEAL_BORDER)
		{

			m_pos.x = FANTASY_SEAL_BORDER + m_vel.x;
			m_vel.x = 0;
			isDecided = false;
			m_lifeTime -= 0.5f * deltaTime;

		}
		if (m_pos.y < -FANTASY_SEAL_BORDER)
		{
			m_pos.y = -FANTASY_SEAL_BORDER + m_vel.y;
			m_vel.y = 0;
			isDecided = false;
			m_lifeTime -= 0.5f * deltaTime;
		}
		if (m_pos.y > FANTASY_SEAL_BORDER)
		{
			m_pos.y = FANTASY_SEAL_BORDER + m_vel.y;
			m_vel.y = 0;
			isDecided = false;
			m_lifeTime -= 0.5f * deltaTime;
		}
	}
	//m_pos += m_vel * deltaTime;
	m_circleAngle += 0.08f * deltaTime;


	if (m_isAlive)
	{
		for (auto i = 0; i < bullets.size(); i++)
		{

			if (checkColliderWithEnemyBullet(*bullets[i]))
			{
				bullets[i]->setLifeTime(-1.0f);

			}
		}

		for (auto i = 0; i < enemy.size(); i++)
		{

			if (checkColliderWithEnemy(*enemy[i]))
			{
				//std::cout << "deal dmg \n";
				enemy[i]->takeDamage(m_dmg *deltaTime, false);

			}
		}
	}


	if (m_circleRadius <= 14.0f)
	{
		m_circleRadius += .23f * deltaTime;
	}
	// X: = originX + cos(angle)*radius;
	// Y: = originY + sin(angle)*radius;
	//m_vel
	if (m_lifeTime >= 22.0f)
	{
		m_pos.x = m_pos.x + (cos(m_circleAngle) * m_circleRadius * deltaTime);
		m_pos.y = m_pos.y + (sin(m_circleAngle) * m_circleRadius * deltaTime);
	}
	else
	{
// 		m_pos.x = m_pos.x + m_vel.x * deltaTime;
// 		m_pos.y = m_pos.y + m_vel.y * deltaTime;

		glm::vec2 direction;
		F_BaseEnemy * t_enemy = getNearstEnemy(m_pos, enemy);
		if (t_enemy)
		{
			direction = glm::normalize(t_enemy->getPos() - m_pos);
		}
		else
		{
			direction = glm::vec2(0, 0.0f);
		}

		m_pos.x = m_pos.x + ((cos(m_circleAngle) * randomRad.x * deltaTime) * 0.5f) + direction.x;
		m_pos.y = m_pos.y + ((sin(m_circleAngle) * randomRad.y * deltaTime) * 0.5f) + direction.y;
		
	}

	decideInterval += m_lifeTimeRate * deltaTime;
	if (decideInterval > 2.5f)
	{
		isDecided = false;
		decideInterval = 0.0f;
		
	}

	if (!isDecided)
	{
		randomRad.x = feint_common::Instance()->randomFloat(-20, 20);
		randomRad.y = feint_common::Instance()->randomFloat(-20, 20);
	
		isDecided = true;
	}

	if (!m_isExplode)
	{
		if (m_lifeTime <= 1.0f)
		{
			if (m_effectBatch)
			{
				m_effectBatch->addRippleEffect(m_pos, .4f * m_scale, 5.5f * m_scale, -1.0f * m_scale, 0.005f * m_scale, 0.025f * m_scale);
			}
			else
			{
				std::cout << " effect batch in Fantasy Seal not set \n";
			}
			m_isExplode = true;
		}
	}

	if (m_lifeTime <= 0.0f)
	{
		m_isAlive = false;

		m_dim *= 2.0f * deltaTime;

		if (m_deathCallback)
		{
			m_deathCallback();
		}
		if (m_hitParticleBatch)
		{
			int numberOfSpark = 4;
			for (int i = 0; i < numberOfSpark; i++)
			{


				float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
				float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);

				glm::vec2 halfDim = glm::vec2(25);
				m_hitParticleBatch->addParticle(m_pos - halfDim,
					glm::vec2(ranX,ranY), Feintgine::Color(255, 255, 255, 0), 1.4f, glm::vec3(9.0f, 9.0f, 9.0f));
			}
		}
		if (m_exlosions)
		{
			m_exlosions->emplace_back(m_explosionSprite, m_pos,
				glm::vec2(m_scale), glm::vec2(0.56), m_color, 10, 0.05f);
		}
		int v1 = rand() % 2;
		switch (v1)
		{
		case 0:
			//m_end1.play(0);
			m_end1.playInChannel(0, 1);
			break;
		case 1:
			//m_end2.play(0);
			m_end2.playInChannel(0, 2);
			break;
		case 2:
			//m_end3.play(0);
			m_end3.playInChannel(0, 3);
			break;

		default:
			break;
		}
	}
	

	m_lightScale += 0.1f * deltaTime;
	m_lifeTime -= m_lifeTimeRate * deltaTime;

	//std::cout << "value x " << m_attentionua.x << " y " << t_attentionua.y << " z " << t_attentionua.z << "\n";

	t_attentionua  = m_attentionua +  abs(cos(m_lightScale) + 1.0f) * 2.5f;

}

void F_Reimu_Fantasy_Seal_Obj::setCircleAngle(float circleAngle)
{
	m_circleAngle = circleAngle;
}

void F_Reimu_Fantasy_Seal_Obj::setAttenuation(const glm::vec3 & attenuation)
{
	m_attentionua = attenuation;
}

void F_Reimu_Fantasy_Seal_Obj::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_end1= audioEngine->loadSoundEffect("Sounds/sfx/se_tan00.wav");
	m_end2 = audioEngine->loadSoundEffect("Sounds/sfx/se_tan01.wav");
	m_end3 = audioEngine->loadSoundEffect("Sounds/sfx/se_tan02.wav");
}

void F_Reimu_Fantasy_Seal_Obj::setDeathCallback(const std::function <void(void)>& f)
{
	m_deathCallback = f;
}

F_BaseEnemy * F_Reimu_Fantasy_Seal_Obj::getNearstEnemy(const glm::vec2 & pos, std::vector<FairyBase *> enemy)
{
	F_BaseEnemy * nearstEnemy = nullptr;

	float nearest = 1000.0f;

	for (int i = 0; i < enemy.size(); i++)
	{
		glm::vec2 disVec = enemy[i]->getPos() - pos;
		float distance = glm::length(disVec);
		if (!enemy[i]->isDeath())
		{
			if (distance < nearest)
			{
				nearest = distance;
				nearstEnemy = enemy[i];

			}
		}
	}

	return nearstEnemy;
}

bool F_Reimu_Fantasy_Seal_Obj::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	//glm::vec2 dim = bullet.getDim() * bullet.getScale();

	glm::vec4 desRect(m_pos - m_sprite.getDim() * 0.5f, m_sprite.getDim() * m_scale);

	glm::vec2 halfDims(desRect.z / 2.0f, desRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl = glm::vec2(-halfDims.x, halfDims.y) + m_pos;
	glm::vec2 bl = glm::vec2(-halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDims.x, halfDims.y) + m_pos;


	// Rotate the points


	if (pos.x > tl.x && pos.x < tr.x
		&& pos.y < tl.y && pos.y > br.y)
	{
		return true;
	}
	return false;
}

bool F_Reimu_Fantasy_Seal_Obj::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dim * 0.5f;
	glm::vec2 t_halfDim = m_sprite.getDim() * 0.5f * m_scale;


	if (m_pos.x  > pos.x - t_halfDim.x &&
		m_pos.y  < pos.y + t_halfDim.y &&
		m_pos.x  < pos.x + t_halfDim.x &&
		m_pos.y > pos.y - t_halfDim.y)
	{
		return true;
	}

	return false;
}

void F_Reimu_Fantasy_Seal_Obj::roll()
{
	
}

void F_Reimu_Fantasy_Seal_Obj::setLifeTime(float val, float randomRange)
{
	m_lifeTime = val + feint_common::Instance()->getRandomNum(-randomRange, randomRange);
}


glm::vec4 F_Reimu_Fantasy_Seal_Obj::getOrbColor(int num)
{
	glm::vec4 returnVal;

	float intensity = 4.6f;
	float t_offset = intensity * 0.01f;
	switch (num)
	{
	case 0:
		returnVal = glm::vec4(intensity, t_offset, t_offset,1.0f);
		break;
	case 1:
		returnVal = glm::vec4(t_offset, intensity, t_offset, 1.0f);
		break;
	case 2:
		returnVal = glm::vec4(t_offset, t_offset, intensity, 1.0f);
		break;
	case 3:
		returnVal = glm::vec4(intensity, intensity, t_offset, 1.0f);
		break;
	case 4:
		returnVal = glm::vec4(intensity, t_offset, intensity, 1.0f);
		break;
	case 5:
		returnVal = glm::vec4(t_offset, intensity, intensity, 1.0f);
		break;

	default:
		returnVal = glm::vec4(1.0f);
		break;
	}

	return returnVal;
}

void F_Reimu_Fantasy_Seal_Obj::setLightID(int val)
{
	lightID = val;
	m_color = getOrbColor(lightID);
}

void F_Reimu_Fantasy_Seal_Obj::setScale(float val)
{
	m_scale = val;
}

void F_Reimu_Fantasy_Seal_Obj::setDMG(float val)
{
	m_dmg = val;
}
