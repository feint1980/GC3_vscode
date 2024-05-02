#include "F_Marisa_MasterSpark.h"
#include "GlobalValueClass.h"

F_Marisa_MasterSpark::F_Marisa_MasterSpark()
{

	glm::vec3 m_attenuation = glm::vec3(7.0f, 8.0f, 5.0f); // glm::vec3(20.0f, 8.0f, 5.0f);
	glm::vec3 t_attenuation = m_attenuation;
	m_color = glm::vec4(0, 0, 0, 0);
	m_isVisible = false;
	m_isSwitchHappen = true;
}


F_Marisa_MasterSpark::~F_Marisa_MasterSpark()
{
}

void F_Marisa_MasterSpark::setAngle(float angle)
{
	m_angle = angle;
}

void F_Marisa_MasterSpark::draw(Feintgine::SpriteBatch & spriteBatch)
{
	spriteBatch.draw(m_pos, m_sprite.getDim() * m_scale, m_sprite.getUV(), m_sprite.getTexture().id, 1, Feintgine::Color(200,200,200,200), m_angle);
	Feintgine::Color t_color = m_color;
	float randomScale = 0.4;
	float randomR = feint_common::Instance()->randomFloat(randomScale, randomScale);
	float randomG = feint_common::Instance()->randomFloat(randomScale, randomScale);
	float randomB = feint_common::Instance()->randomFloat(randomScale, randomScale);

	float t_lifeTime = m_lifeTime +18;
	t_color.r += randomR * sin(t_lifeTime);
	t_color.g += randomG * cos(t_lifeTime);
	t_color.b += randomB * sin(t_lifeTime);
	t_color.a *= 0.3f;

	Feintgine::Color f_color = m_color;
	f_color.r += randomR * cos(t_lifeTime);
	f_color.g += randomG * cos(t_lifeTime);
	f_color.b += randomB * sin(t_lifeTime);
	f_color.a *= 0.3f;

	Feintgine::Color d_color = m_color;
	d_color.r += randomR * sin(t_lifeTime);
	d_color.g += randomG * cos(t_lifeTime);
	d_color.b += randomB * cos(t_lifeTime);
	d_color.a *= 0.3f;

	Feintgine::Color l_color = m_color;
	l_color.r += randomR * sin(t_lifeTime);
	l_color.g += randomG * sin(t_lifeTime);
	l_color.b += randomB * cos(t_lifeTime);
	l_color.a *= 0.3f;
// 
// 	Feintgine::Color e_color = m_color;
// 	e_color.r += randomR * cos(m_lifeTime);
// 	e_color.g += randomG * sin(m_lifeTime);
// 	e_color.b += randomB * cos(m_lifeTime);
// 	e_color.a *= 0.3f;

	float addOnScale = 1.1f;

	spriteBatch.draw(m_pos, m_sprite.getDim() * (m_scale * addOnScale), m_sprite.getUV(), m_sprite.getTexture().id, -5, t_color, m_angle + degreeToRad(5));

	spriteBatch.draw(m_pos, m_sprite.getDim() * (m_scale * addOnScale), m_sprite.getUV(), m_sprite.getTexture().id, -5, f_color, m_angle - degreeToRad(5));

	spriteBatch.draw(m_pos, m_sprite.getDim() * (m_scale * addOnScale), m_sprite.getUV(), m_sprite.getTexture().id, -5, d_color, m_angle + degreeToRad(10));

	spriteBatch.draw(m_pos, m_sprite.getDim() * (m_scale * addOnScale), m_sprite.getUV(), m_sprite.getTexture().id, -5, l_color, m_angle - degreeToRad(10));



	// draw Waves


	for (int i = 0; i < m_waves.size(); i++)
	{
		m_waves[i].draw(spriteBatch);
	}
}

void F_Marisa_MasterSpark::drawRayLight(Feintgine::LightBatch & lightBatch)
{
	if (m_isVisible)
	{

		t_attenuation = m_attenuation - (m_attenuation * 0.9f) * GlobalValueClass::Instance()->getAmbientLight().x;

		glm::vec2 lightPos = m_pos + glm::vec2(0, 5);
		//lightPos.y -= m_dim.x * 0.5f;
		//float m_rotation = 
		float randomScale = 0.4;
		float randomR = feint_common::Instance()->randomFloat(0, randomScale);
		float randomG = feint_common::Instance()->randomFloat(0, randomScale);
		float randomB = feint_common::Instance()->randomFloat(0, randomScale);
		Feintgine::Color tColor = m_color;
		tColor.r *= 0.4f;
		tColor.g *= 0.4f;
		tColor.b *= 0.4f;
		float t_lifeTime = m_lifeTime + 18;
		lightBatch.addRayLight(lightPos, glm::vec4(tColor.r + randomR * sin(t_lifeTime),
			tColor.g + randomG * cos(t_lifeTime) ,
			tColor.b + randomB * sin(t_lifeTime), 1)
			, 1.0f / t_attenuation, m_angle + degreeToRad(180));
		lightBatch.addRayLight(lightPos + glm::vec2(-8,0), glm::vec4(tColor.r + randomR * cos(t_lifeTime),
			tColor.g + randomG * sin(t_lifeTime),
			tColor.b + randomB * cos(t_lifeTime), 1)
			, 1.0f / t_attenuation, m_angle + degreeToRad(180) /*+ degreeToRad(3)*/);
		lightBatch.addRayLight(lightPos + glm::vec2(8, 0), glm::vec4(tColor.r + randomR * cos(t_lifeTime),
			tColor.g + randomG * cos(t_lifeTime),
			tColor.b + randomB * sin(t_lifeTime),1)
			, 1.0f / t_attenuation, m_angle + degreeToRad(180) /*- degreeToRad(3)*/);

// 		lightBatch.addRayLight(lightPos, glm::vec4(m_color.r + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime),
// 			m_color.g  * sin(m_lifeTime) + feint_common::Instance()->randomFloat(-0.3f, 0.3f),
// 			m_color.b + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime), m_color.a)
// 			, 1.0f / m_attenuation, -m_angle + degreeToRad(10));
// 		lightBatch.addRayLight(lightPos, glm::vec4(m_color.r + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime),
// 			m_color.g  * sin(m_lifeTime) + feint_common::Instance()->randomFloat(-0.3f, 0.3f),
// 			m_color.b + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime), m_color.a)
// 			, 1.0f / m_attenuation, -m_angle - degreeToRad(10));
// 		lightBatch.addRayLight(lightPos, glm::vec4(m_color.r + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime),
// 			m_color.g  * sin(m_lifeTime) + feint_common::Instance()->randomFloat(-0.3f, 0.3f),
// 			m_color.b + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime), m_color.a)
// 			, 1.0f / m_attenuation, -m_angle + degreeToRad(20));
// 		lightBatch.addRayLight(lightPos, glm::vec4(m_color.r + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime),
// 			m_color.g  * sin(m_lifeTime) + feint_common::Instance()->randomFloat(-0.3f, 0.3f),
// 			m_color.b + feint_common::Instance()->randomFloat(-0.3f, 0.3f) * sin(m_lifeTime), m_color.a)
// 			, 1.0f / m_attenuation, -m_angle - degreeToRad(20));
	}
	for (int i = 0; i < m_waves.size(); i++)
	{
		m_waves[i].drawLight(lightBatch);
	}
}

void F_Marisa_MasterSpark::init(const glm::vec2 & scale, const Feintgine::F_Sprite & sprite, const Feintgine::Color & color)
{
	//m_pos = pos;
	//m_player = player;
	m_scale = scale;
	//m_color = color;
	m_sprite = sprite;

	m_isVisible = false;
	m_isSwitchHappen = false;
	m_isSwitchSizeHappen = false;
	c_scale = scale;
	m_angle = degreeToRad(90);
	//m_sprite.init(m_pos, m_scale,glm::vec2(0))
}



void F_Marisa_MasterSpark::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	std::cout << "start sound created \n";
	m_startSound = audioEngine->loadSoundEffect("Sounds/sfx/master_spark.wav");
	if(m_startSound.getChunk())
	{
		std::cout << "created chunk OK \n";
	}
}

bool F_Marisa_MasterSpark::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos(); // x,y 
	glm::vec2 dim = bullet.getDim(); // 

	float f_angle = m_angle - degreeToRad(90);


	double center_rec_x = m_pos.x;
	double center_rec_y = m_pos.y + m_sprite.getDim().y * m_scale.y / 2.0f;
	double cir_x_rotate = cos(f_angle) * (pos.x - m_pos.x) - sin(f_angle) * (pos.y - m_pos.y) + m_pos.x;
	double cir_y_rotate = sin(f_angle) * (pos.x - m_pos.x) + cos(f_angle) * (pos.y - m_pos.y) + m_pos.y;
	double distance_center_x = abs(cir_x_rotate - center_rec_x);
	double distance_center_y = abs(cir_y_rotate - center_rec_y);
	double distance_center_corner_x = distance_center_x - m_sprite.getDim().x * m_scale.x / 2.0f;
	double distance_center_corner_y = distance_center_y - m_sprite.getDim().y * m_scale.y / 2.0f;
	//if (distance_center_x > dim.x + m_sprite.getDim().x * m_scale.x / 2.0f) return true;
	//if (distance_center_y > dim.x + m_sprite.getDim().y * m_scale.y / 2.0f) return true;
	if (distance_center_x < m_sprite.getDim().x * m_scale.x / 2.0f) return true;
	if (distance_center_y <m_sprite.getDim().y * m_scale.y / 2.0f) return true;
	if (pow(distance_center_corner_x, 2) + pow(distance_center_corner_y, 2) <= pow(dim.x, 2)) return true;

	return false;
}

bool F_Marisa_MasterSpark::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos(); // x,y 
	glm::vec2 dim = enemy.getDim(); // 

	float f_angle = m_angle - degreeToRad(90);

	double center_rec_x = m_pos.x;
	double center_rec_y = m_pos.y + m_sprite.getDim().y * m_scale.y / 2.0f;
	double cir_x_rotate = cos(f_angle) * (pos.x - m_pos.x) - sin(f_angle) * (pos.y - m_pos.y) + m_pos.x;
	double cir_y_rotate = sin(f_angle) * (pos.x - m_pos.x) + cos(f_angle) * (pos.y - m_pos.y) + m_pos.y;
	double distance_center_x = abs(cir_x_rotate - center_rec_x);
	double distance_center_y = abs(cir_y_rotate - center_rec_y);
	double distance_center_corner_x = distance_center_x - m_sprite.getDim().x * m_scale.x / 2.0f;
	double distance_center_corner_y = distance_center_y - m_sprite.getDim().y * m_scale.y / 2.0f;
	//if (distance_center_x > dim.x + m_sprite.getDim().x * m_scale.x / 2.0f) return true;
	//if (distance_center_y > dim.x + m_sprite.getDim().y * m_scale.y / 2.0f) return true;
	if (distance_center_x < m_sprite.getDim().x * m_scale.x / 2.0f) return true;
	if (distance_center_y < m_sprite.getDim().y * m_scale.y / 2.0f) return true;
	if (pow(distance_center_corner_x, 2) + pow(distance_center_corner_y, 2) <= pow(dim.x, 2)) return true;

	return false;
}

void F_Marisa_MasterSpark::update(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets)
{

 	if (GlobalValueClass::Instance()->getPlayer())
 	{
		m_pos = GlobalValueClass::Instance()->getPlayer()->getPos() + glm::vec2(0,5);
	}
	updateState(deltaTime);
	updateScale(deltaTime);

	if (m_lifeTime > 0.0f)
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
				enemy[i]->takeDamage(5.25f *deltaTime, false);
			}
		}

		if (m_lifeTime > 2.0f)
		{
			handleWave(deltaTime);
			//m_startSound.stahp();
		}
	}

	if (m_isSwitchHappen)
	{
		
		if (m_isVisible)
		{
			if (m_color.change(15, 0.025f, maxColorVal))
			{
				m_isSwitchHappen = false;
			}
		}
		else
		{
			if (m_color.change(15, -0.025f, minColorVal))
			{
				//std::cout << "stop \n";
				m_isSwitchHappen = false;
				
				
			}

		}
	}
	for (int i = 0; i < m_waves.size(); i++)
	{
		
		m_waves[i].update(deltaTime);
		//m_waves[i].setAngle(m_angle);
		if (!m_waves[i].isAlive())
		{
			m_waves.erase(m_waves.begin() + i);
		}
	}
}

void F_Marisa_MasterSpark::updateState(float deltaTime)
{
	if (m_lifeTime > 0.0f)
	{
		m_lifeTime -= 0.1f * deltaTime;
		//t_lifeTime -= 0.2f * deltaTime;
		if (m_lifeTime < 5.0f)
		{
			if(m_startSound.getChunk())
			{
				m_startSound.setVolume(m_lifeTime);
				//m_startSound.getChunk()->volume = m_lifeTime;
			}
			//
		}
	}
	else
	{
		m_isVisible = false;
		m_isSwitchHappen = true;
		m_isSwitchSizeHappen = true;

	}
}

void F_Marisa_MasterSpark::updateScale(float deltaTime)
{
	if (m_isSwitchSizeHappen)
	{

		if (m_isVisible)
		{
			if (m_scale.y < c_scale.y)
			{
				m_scale.y += 0.125f * deltaTime;
			}
			else
			{
				m_scale.y = c_scale.y;
				m_isSwitchSizeHappen = false;

			}
		}
		else
		{
			if (m_scale.y > 0 )
			{
				m_scale.y -= 0.125f * deltaTime;
				if (m_scale.y < 1.0f)	
				{
					
					m_attenuation *= m_scale.y;
				}
			}
			else
			{
				m_scale.y = 0;
				m_isSwitchSizeHappen = false;
			}
		}
		
	}
}

void F_Marisa_MasterSpark::spawn()
{
	// 20.0f
	m_lifeTime = 30.0f;
	m_isVisible = true;
	m_isSwitchHappen = true;
	m_isSwitchSizeHappen = true;
	m_scale = glm::vec2(c_scale.x,0.1f);//glm::vec2(4.0f);// c_scale.y;
	m_startSound.setVolume(10);
	m_attenuation =  glm::vec3(25.0f, 18.0f, 29.0f);
	m_startSound.playInChannel(0,1);
	//m_startSound.stahp()
	//m_attenuation = glm::vec3(3.0f, 2.0f, 15.0f);
	//std::cout << "start \n";
	//m_scale.y = 1.0f;
}

void F_Marisa_MasterSpark::handleWave(float deltaTime)
{
	m_spawnWaveCount += 0.1f * deltaTime;
	if (m_spawnWaveCount >= 1.0f)
	{
		F_MasterSpark_Wave wave;
		wave.init(m_pos + glm::vec2(0,15), glm::vec2(m_scale.y) * 0.55f, Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_master_spark_wave.png"),
			Feintgine::Color(400,400,400,100));
		wave.setAngle(m_angle);
		m_waves.push_back(wave);
		m_spawnWaveCount = 0;
	}
}

glm::vec2 F_Marisa_MasterSpark::rotatePoint(const glm::vec2& pos, float angle)
{
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}
