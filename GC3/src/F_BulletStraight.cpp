#include "F_BulletStraight.h"
#include "EnemyGuardian.h"


F_BulletStraight::F_BulletStraight()
{
	m_angle = 1.57079633f;
}


F_BulletStraight::F_BulletStraight(const glm::vec2 & pos, const glm::vec2 & dim, 
	const Feintgine::Color & color, const std::string & animationPath, float depth, float dmg, Feintgine::ParticleBatch2D * hitParticleBatch /*= nullptr*/)
{
	m_pos = pos;
	m_dims = dim;
	m_color = color;
	//m_sprite = sprite;
	m_depth = depth;
	m_damage = dmg;

	m_particleBatch = new Feintgine::ParticleBatch2D();
	Feintgine::F_Sprite t_sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/particle_white_3.png");
	m_particleBatch->init(50, 0.1f, t_sprite);

	//m_scale = dim / m_sprite.getDim();
	//m_scale = 1.0f;
	m_animation.init(animationPath);
	m_animation.setColor(color);
	//m_animation = animation;
	m_particleBatch = hitParticleBatch;
	m_isAnimated = true;
	
	//m_animation.playAnimation("idle");
}

F_BulletStraight::~F_BulletStraight()
{
	//std::cout << "destroyed \n";
}


// void F_BulletStraight::setVel(const glm::vec2 & vel)
// {
// 	m_vel = vel;
// }

void F_BulletStraight::update(float deltaTime, std::vector<FairyBase * >  enemy)
{

	//std::cout << m_animation.getName() << "\n";
	m_angle += 0.5 * deltaTime;
	if (m_isAnimated)
	{
		m_animation.update(deltaTime);
	}
	
	m_pos += (m_vel *deltaTime);
	if (m_isAlive)
	{
		m_lifeTime -= 0.025f * deltaTime;
		if (m_lifeTime < 0)
		{
			m_isAlive = false;
		}
	}
	if (!m_animation.isPlaying())
	{
		m_isAlive = false;
	}
	if (!m_isDone)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			if (!enemy[i]->isDeath())
			{
				if (checkColiderWithEmeny(*enemy[i]))
				{
					enemy[i]->takeDamage(m_damage);
					if (m_isAnimated)
					{
						destroy();
					
						if (m_particleBatch)
						{
							switch (m_particleType)
							{
							case 0:
							{
								break;
							}
							case 1:
							{
								float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
								glm::vec2 t_pos = m_pos;
								t_pos.x += ranX;
								glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
								for (int f = 0; f < m_particleNum; f++)
								{
									m_particleBatch->addParticle(true,t_pos - halfDim, glm::vec2(ranX, 3.15f), Feintgine::Color(100, 255, 100, 255), 0.7f, 2.2f, glm::vec3(12, 10, 15));
								}
							}
								break;
							case 2:
							{
								float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
								glm::vec2 t_pos = m_pos;
								t_pos.x += ranX;
								glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
								for (int f = 0; f < m_particleNum; f++)
								{
									m_particleBatch->addParticle(true,t_pos - halfDim, glm::vec2(ranX, 4.15f), Feintgine::Color(255, 100, 100, 255), 0.7f, 2.2f, glm::vec3(8, 12, 17));
								}
							}
							break;

							default:
								break;
							}
							
						}
					}
					else
					{
						m_isAlive = false;
						if (m_particleBatch)
						{
							float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
							glm::vec2 t_pos = m_pos;
							t_pos.x += ranX;
							glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
							for (int f = 0; f < m_particleNum; f++)
							{
								//std::cout << "created \n";
								m_particleBatch->addParticle(t_pos - halfDim, glm::vec2(0, 1.15f), Feintgine::Color(255, 255, 255, 120), 0.7f);
							}
						}
					}

				}
			}
		}
			
		// for (int i = 0; i < guardians.size(); i++)
		// {
		// 	if (!guardians[i]->isDeath())
		// 	{
		// 		if (checkColiderWithGuardian(*guardians[i]))
		// 		{
		// 			guardians[i]->takeDamage(m_damage);
		// 			if (m_isAnimated)
		// 			{
		// 				destroy();
		// 				if (m_particleBatch)
		// 				{
		// 					switch (m_particleType)
		// 					{
		// 					case 0:
		// 					{
		// 						break;
		// 					}
		// 					case 1:
		// 					{
		// 						float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
		// 						glm::vec2 t_pos = m_pos;
		// 						t_pos.x += ranX;
		// 						glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
		// 						for (int f = 0; f < m_particleNum; f++)
		// 						{
		// 							m_particleBatch->addParticle(true,t_pos - halfDim, glm::vec2(ranX, 3.15f), Feintgine::Color(100, 255, 100, 255), 0.7f, 2.2f, glm::vec3(12, 10, 15));
		// 						}
		// 					}
		// 					break;
		// 					case 2:
		// 					{
		// 						float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
		// 						glm::vec2 t_pos = m_pos;
		// 						t_pos.x += ranX;
		// 						glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
		// 						for (int f = 0; f < m_particleNum; f++)
		// 						{
		// 							m_particleBatch->addParticle(true,t_pos - halfDim, glm::vec2(ranX, 4.15f), Feintgine::Color(255, 100, 100, 255), 0.7f, 2.2f, glm::vec3(8, 12, 17));
		// 						}
		// 					}
		// 					break;

		// 					default:
		// 						break;
		// 					}

		// 				}
		// 			}
		// 			else
		// 			{
		// 				m_isAlive = false;
		// 				if (m_particleBatch)
		// 				{
		// 					float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
		// 					glm::vec2 t_pos = m_pos;
		// 					t_pos.x += ranX;
		// 					glm::vec2 halfDim = guardians[i]->getDim() * 0.5f;
		// 					for (int f = 0; f < m_particleNum; f++)
		// 					{
		// 						//std::cout << "created \n";
		// 						m_particleBatch->addParticle(t_pos - halfDim, glm::vec2(0, 1.15f), Feintgine::Color(255, 255, 255, 120), 0.7f);
		// 					}
		// 				}
		// 			}

		// 		}
		// 	}
		// }

		// for (int i = 0; i < amplifiers.size(); i++)
		// {
		// 	if (!amplifiers[i]->isDeath())
		// 	{
		// 		if (checkColiderWithAmplifier(*amplifiers[i]))
		// 		{
		// 			amplifiers[i]->takeDamage(m_damage);
		// 			if (m_isAnimated)
		// 			{
		// 				destroy();
		// 				if (m_particleBatch)
		// 				{
		// 					switch (m_particleType)
		// 					{
		// 					case 0:
		// 					{
		// 						break;
		// 					}
		// 					case 1:
		// 					{
		// 						float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
		// 						glm::vec2 t_pos = m_pos;
		// 						t_pos.x += ranX;
		// 						glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
		// 						for (int f = 0; f < m_particleNum; f++)
		// 						{
		// 							m_particleBatch->addParticle(true,t_pos - halfDim, glm::vec2(ranX, 3.15f), Feintgine::Color(100, 255, 100, 255), 0.7f, 2.2f, glm::vec3(8, 12, 17));
		// 						}
		// 					}
		// 					break;
		// 					case 2:
		// 					{
		// 						float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
		// 						glm::vec2 t_pos = m_pos;
		// 						t_pos.x += ranX;
		// 						glm::vec2 halfDim = enemy[i]->getDim() * 0.5f;
		// 						for (int f = 0; f < m_particleNum; f++)
		// 						{
		// 							m_particleBatch->addParticle(true,t_pos - halfDim, glm::vec2(ranX, 4.15f), Feintgine::Color(255, 100, 100, 255), 0.7f, 2.2f, glm::vec3(12, 15, 22));
		// 						}
		// 					}
		// 					break;

		// 					default:
		// 						break;
		// 					}

		// 				}
		// 			}
		// 			else
		// 			{
		// 				m_isAlive = false;
		// 				if (m_particleBatch)
		// 				{
		// 					float ranX = feint_common::Instance()->getRandomNum(-1.5, 1.5);
		// 					glm::vec2 t_pos = m_pos;
		// 					t_pos.x += ranX;
		// 					glm::vec2 halfDim = amplifiers[i]->getDim() * 0.5f;
		// 					for (int f = 0; f < m_particleNum; f++)
		// 					{
		// 						std::cout << "created \n";
		// 						m_particleBatch->addParticle(t_pos - halfDim, glm::vec2(0, 1.15f), Feintgine::Color(255, 255, 255, 120), 0.7f);
		// 					}
		// 				}
		// 			}

		// 		}
		// 	}
		// }
	}
}

void F_BulletStraight::draw(Feintgine::SpriteBatch & spriteBatch)
{
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
		additionalPos.x = (m_animation.getDim().x * 0.5f ) - m_animation.getDim().y ;
		//}


		m_animation.setPos(m_pos + additionalPos);
		//m_animation.setScale(glm::vec2(1.0));
		m_animation.draw(spriteBatch);
	}
}

void F_BulletStraight::setParticleNum(int val)
{
	m_particleNum = val;
}


void F_BulletStraight::setAngle(float angle)
{
	glm::vec2 tvel = m_vel;
	m_angle = angle;
	if (m_isAnimated)
	{
		m_animation.setAngle(angle);
	}
	m_vel.x = tvel.x * cos(angle) - tvel.y * sin(angle);
	m_vel.y = tvel.x * sin(angle) + tvel.y * cos(angle);
}

// void F_BulletStraight::destroy()
// {
// 	if (m_isAnimated)
// 	{
// 		m_isDone = true;
// 		m_vel = glm::vec2(0, 0);
// 		m_animation.playAnimation("destroy",1);
// 		m_scale *= 1.3f;
// 	}
// }

