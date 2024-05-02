#include "F_Non_Direction_Laser.h"
#include "GlobalValueClass.h"


F_Non_Direction_Laser::F_Non_Direction_Laser()
{
}


F_Non_Direction_Laser::~F_Non_Direction_Laser()
{
}

void F_Non_Direction_Laser::init(const glm::vec2 & scale, 
	const Feintgine::F_Sprite & sprite, const Feintgine::Color & color)
{
	m_scale = scale;
	t_color = color;
	m_sprite = sprite;

	m_color = Feintgine::Color(0, 0, 0, 0);

	m_isVisible = false;
	m_isSwitchHappen = false;
	m_isSwitchSizeHappen = false;
	c_scale = scale;
	m_lifeTime = -1.0f;
	m_colorFlag = getColorFlag(t_color);
	m_attenuation = glm::vec3(30.0f, 8.0f, 50.0f);
}

void F_Non_Direction_Laser::draw(Feintgine::SpriteBatch & spriteBatch)
{
	spriteBatch.draw(m_pos, m_sprite.getDim() * m_scale, m_sprite.getUV(),
		m_sprite.getTexture().id, -5, m_color, m_angle);
}

void F_Non_Direction_Laser::drawRayLight(Feintgine::LightBatch & lightBatch)
{
	if (m_isVisible)
	{

		t_attenuation = m_attenuation - (m_attenuation * 0.5f) * GlobalValueClass::Instance()->getAmbientLight().x;

		lightBatch.addRayLight(m_pos, glm::vec4(m_color.r * 2.0f ,m_color.g  * 2.0f ,m_color.b  * 2.0f,1.0f)
			, 1.0f / t_attenuation, m_angle + degreeToRad(180));
	}
		//glm::vec2 lightPos = m_pos + glm::vec2(0, 5);

}

void F_Non_Direction_Laser::update(const glm::vec2 &pos,float angle, float deltaTime, std::vector<FairyBase *> enemy, std::vector<EnemyBulletBase * > bullets)
{
	m_pos = pos;
	m_angle = angle;
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
				enemy[i]->takeDamage(0.35f *deltaTime, false);
			}
		}

	}

	if (m_isSwitchHappen)
	{

		if (m_isVisible)
		{
			if (m_color.change(m_colorFlag, 0.025f, maxColorVal))
			{
				m_isSwitchHappen = false;
			}
		}
		else
		{
			if (m_color.change(m_colorFlag, -0.025f, minColorVal))
			{
				//std::cout << "stop \n";
				m_isSwitchHappen = false;
			}

		}
	}
}

int F_Non_Direction_Laser::getColorFlag(const Feintgine::Color & color)
{
	int returnValue = 0;
	returnValue |= COLOR_CHANNEL_HAS_A;

	

	if (color.r > 0.5f)
	{
		returnValue |= COLOR_CHANNEL_HAS_R;
	}
	if (color.g > 0.5f)
	{
		returnValue |= COLOR_CHANNEL_HAS_G;
	}
	if (color.b > 0.5f)
	{
		returnValue |= COLOR_CHANNEL_HAS_B;
	}
	
	//std::cout << "returnValue " << returnValue << "\n";
	return returnValue;
}

void F_Non_Direction_Laser::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	//m_startSound = audioEngine->loadSoundEffect("Sounds/sfx/master_spark.wav");
}

void F_Non_Direction_Laser::updateState(float deltaTime)
{
	if (m_lifeTime > 0.0f)
	{
		m_lifeTime -= 0.1f * deltaTime;

	}
	else
	{
		m_isVisible = false;
		m_isSwitchHappen = true;
		m_isSwitchSizeHappen = true;

	}
}

void F_Non_Direction_Laser::updateScale(float deltaTime)
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
			if (m_scale.y > 0)
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

void F_Non_Direction_Laser::spawn(float lifeTime)
{
	m_lifeTime = lifeTime;
	m_isSwitchSizeHappen = true;
	m_isSwitchHappen = true;
	m_isVisible = true;
	//m_startSound.play();
}

bool F_Non_Direction_Laser::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos(); // x,y 
	glm::vec2 dim = bullet.getDim(); // 

	float f_angle = m_angle + degreeToRad(90);


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

bool F_Non_Direction_Laser::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{
	glm::vec2 pos = enemy.getPos(); // x,y 
	glm::vec2 dim = enemy.getDim(); // 


	float f_angle = m_angle + degreeToRad(90);

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
