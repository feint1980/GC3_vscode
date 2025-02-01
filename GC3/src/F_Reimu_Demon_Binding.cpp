#include "F_Reimu_Demon_Binding.h"

const float LIFE_TIME_RATE = 0.1f;
const float ALPHA_MULTIPLIER = 1.0f;

F_Reimu_Demon_Binding::F_Reimu_Demon_Binding()
{
	m_isAlive = false;
}


F_Reimu_Demon_Binding::~F_Reimu_Demon_Binding()
{
	m_isAlive = false;
}



void F_Reimu_Demon_Binding::init(const std::string & animationPath, const std::string & animationSupportPath,
	const glm::vec2 & pos, const glm::vec2 dim, const Feintgine::Color & color)
{
	m_animObj.init(animationPath);
	m_animObj2.init(animationPath);
	m_helper.init(animationSupportPath);
	m_pos = pos;
	m_dim = dim;
	m_offsetPos = glm::vec2(m_pos.x, m_pos.y - m_dim.y / 2);
	m_color = color;
	m_animObj.playAnimation("idle");
	m_animObj2.playAnimation("idle2");
	m_helper.playAnimation("idle");
	m_isAlive = false;
	m_animObj.setScale(glm::vec2(2.2f));
	m_animObj.setPos(glm::vec2(m_pos.x,0));
	m_helper.setPos(glm::vec2(m_pos.x, -320));
	m_helper.setScale(glm::vec2(1.15f));

	
	m_animObj.setColor(m_color);
	m_animObj2.setColor(Feintgine::Color(255, 255, 255, 120));
	m_helper.setColor(Feintgine::Color(255, 255, 255, 120));

	m_afterImageParticle.init(&m_pos, &m_animObj, &m_color, .25f, 10);
	m_afterImageParticle.setTraceLifeTime(2.65f);
	m_afterImageParticle.setAlphaRate(0.4f);
	m_afterImageParticle.setScale(glm::vec2(2.2f));

	
	//m_animObj.playAnimation("end", 1);
}

void F_Reimu_Demon_Binding::setLifeTime(float lifetime)
{
	m_lifeTime = lifetime;
	m_isAlive = true;
	m_isVisible = true;
	m_isPeak = false;
	m_castSound.playInChannel(0,2);
	m_endSound.playInChannel(1,3);
	m_camera->startShake(m_lifeTime, 4.0f, 7.0f);
	m_attentionua = glm::vec3(12.2f, 13.0f, 16.5f);

}


void F_Reimu_Demon_Binding::registerSound(Feintgine::AudioEngine * audioEngine)
{
	m_castSound = audioEngine->loadSoundEffect("Sounds/sfx/demon_binding_cast_2.wav");
	m_loopSound = audioEngine->loadSoundEffect("Sounds/sfx/demon_binding_end.wav");
	m_endSound = audioEngine->loadSoundEffect("Sounds/sfx/demon_binding_loop.wav");
	m_castSound.setVolume(21.0f);
	m_endSound.setVolume(21.0f);
}

void F_Reimu_Demon_Binding::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_isVisible)
	{
		m_helper.draw(spriteBatch);
		m_animObj.draw(spriteBatch);
		m_afterImageParticle.draw(spriteBatch);
	}

}

void F_Reimu_Demon_Binding::drawLight(Feintgine::LightBatch & lightBatch)
{
	if (m_isVisible && m_lifeTime > 0.1f)
	{
		glm::vec2 tPos = m_pos;
		tPos.y -= 350;
		int numberOfLight = 1;
		t_attentionua = m_attentionua + abs(cos(m_lifeTime)) * 1.1f;
		lightBatch.addLight(tPos, glm::vec4(1.0f,1.0f, 1.0f, m_lifeTime),
		glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z));
		lightBatch.addRayLight(tPos, glm::vec4(.1f, .1f, .1f, m_lifeTime),
			glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z),degreeToRad(-90.0f));
	}
}

void F_Reimu_Demon_Binding::update(float deltaTime,
	std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets)
{
	m_lifeTime -= LIFE_TIME_RATE * deltaTime;
	m_animObj.update(deltaTime);
	m_helper.update(deltaTime);
	m_animObj2.update(deltaTime);
	//m_loopSound.playInChannel(-1, 3);
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
				enemy[i]->takeDamage(0.25f *deltaTime,false);
			}
		}

		if (m_lifeTime > 22.0f)
		{
			m_attentionua += 3.0f * deltaTime;
			
		}

		if (m_animObj.getCurrentAnimation())
		{
			if (m_animObj.getCurrentAnimation()->getCurrentIndex() != -1)
			{
				//m_afterImageParticle.update(deltaTime, m_animObj.getCurrentAnimation()->getCurrentIndex(), 0);
			}
		}
			
		if (m_lifeTime < 5.0f)
		{
			m_attentionua -= 2.5f * deltaTime;
		}
		if (m_lifeTime < 0.5f)
		{
			m_animObj.setAlpha(m_lifeTime * ALPHA_MULTIPLIER);
			m_animObj2.setAlpha(m_lifeTime * ALPHA_MULTIPLIER);
			m_helper.setAlpha(m_lifeTime * ALPHA_MULTIPLIER);
			m_attentionua *= m_lifeTime + .2f;
		}

		if (m_lifeTime < 0.0f)
		{
			m_lifeTime = 0.0F;
			m_isAlive = false;
			//std::cout << "is out \n";
			m_animObj.playAnimation("end", 1);
			m_helper.playAnimation("end", 1);
			m_animObj2.playAnimation("end", 1);
		}
	}
	else
	{
		if (!m_animObj.isPlaying())
		{
			m_isVisible = false;
			m_endSound.stahp();
			m_isPeak = false;
		}
	}
	

}

bool F_Reimu_Demon_Binding::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim() * bullet.getScale();

	//glm::vec2 halfDim = (m_dim - glm::vec2(180,0))* 0.5f;

	// 	glm::vec2 tl = glm::vec2(-halfDim.x, halfDim.y) + m_pos;
	// 	glm::vec2 bl = glm::vec2(-halfDim.x, -halfDim.y) + m_pos;
	// 	glm::vec2 br = glm::vec2(halfDim.x, -halfDim.y) + m_pos;
	// 	glm::vec2 tr = glm::vec2(halfDim.x, halfDim.y) + m_pos;
	// 
	// 	glm::vec2 positionOffset = m_pos;
	// 
	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;
	// 	// Rotate the points
	// 	a_tl = t_rotatePoint(tl, tAgnle)  ;
	// 	a_bl = t_rotatePoint(bl, tAgnle);
	// 	a_br = t_rotatePoint(br, tAgnle) ;
	// 	a_tr = t_rotatePoint(tr, tAgnle) ;

	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim * 0.8f);

	glm::vec2 halfDims(desRect.z / 2.0f, desRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl = glm::vec2(-halfDims.x, halfDims.y) + m_pos;
	glm::vec2 bl = glm::vec2(-halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDims.x, halfDims.y) + m_pos;

	glm::vec2 positionOffset(desRect.x, desRect.y);

	// Rotate the points


	if (pos.x > tl.x && pos.x < tr.x
		&& pos.y < tl.y && pos.y > br.y)
	{
		return true;
	}

	return false;
}

bool F_Reimu_Demon_Binding::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim() * 0.5f;

	//glm::vec2 halfDim = (m_dim - glm::vec2(180,0))* 0.5f;

	// 	glm::vec2 tl = glm::vec2(-halfDim.x, halfDim.y) + m_pos;
	// 	glm::vec2 bl = glm::vec2(-halfDim.x, -halfDim.y) + m_pos;
	// 	glm::vec2 br = glm::vec2(halfDim.x, -halfDim.y) + m_pos;
	// 	glm::vec2 tr = glm::vec2(halfDim.x, halfDim.y) + m_pos;
	// 
	// 	glm::vec2 positionOffset = m_pos;
	// 
	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;
	// 	// Rotate the points
	// 	a_tl = t_rotatePoint(tl, tAgnle)  ;
	// 	a_bl = t_rotatePoint(bl, tAgnle);
	// 	a_br = t_rotatePoint(br, tAgnle) ;
	// 	a_tr = t_rotatePoint(tr, tAgnle) ;

	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim * 0.8f);

	glm::vec2 halfDims(desRect.z / 2.0f, desRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl = glm::vec2(-halfDims.x, halfDims.y) + m_pos;
	glm::vec2 bl = glm::vec2(-halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDims.x, -halfDims.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDims.x, halfDims.y) + m_pos;

	glm::vec2 positionOffset(desRect.x, desRect.y);

	// Rotate the points


	if (pos.x + dim.x > tl.x && pos.x - dim.x < tr.x
		&& pos.y - dim.y < tl.y && pos.y + dim.y > br.y)
	{
		return true;
	}

	return false;
}

void F_Reimu_Demon_Binding::registerCamera(Feintgine::Camera2D * camera)
{
	m_camera = camera;
}

