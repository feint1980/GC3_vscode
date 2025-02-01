#include "F_Player.h"
#include "EnemyGuardian.h"
#include "F_Marisa_MasterSpark.h"
#include "GlobalValueClass.h"
#include "EngineSetting.h"

F_Player::F_Player()
{
	m_bullets.clear();
	m_grazeCount = 0;

	m_loadedRecordedStates.clear();
	m_loadedRecordedActions.clear();
	m_recordedActions.clear();
	m_recordedStates.clear();
	
}


F_Player::~F_Player()
{

}

void F_Player::init(const std::string & animationPath, 
	const std::string & accessorySprite, bool isShink)
{

	m_energy = MAX_ENERGY;
	m_animation.init(animationPath);
	if (isShink)
	{
		m_animation.setScale(glm::vec2(.3f)); // for scale down own sprite -> remove 
	}
	
	//m_animation.setPlaying(true);
	m_animation.playAnimation("idle");
	m_leftAccessory.init(m_pos, glm::vec2(12, 12), 
		Feintgine::SpriteManager::Instance()->getSprite(accessorySprite));
	m_rightAccessory.init(m_pos, glm::vec2(12, 12), 
		Feintgine::SpriteManager::Instance()->getSprite(accessorySprite),false);

	m_leftAccessory.initLaser
	(Feintgine::ResourceManager::getTexture("Assets/Textures/marisa_laser_small.png"),
		m_leftAccessory.getPos(), glm::vec2(1280, 13), Feintgine::Color(255, 255, 255, 255), 10, degreeToRad(-90), 5.0f,
		Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_projectile_star_2.png"));
	m_rightAccessory.initLaser
	(Feintgine::ResourceManager::getTexture("Assets/Textures/marisa_laser_small.png"),
		m_rightAccessory.getPos(), glm::vec2(1280, 13), Feintgine::Color(255, 255, 255, 255), 10, degreeToRad(-90), 5.0f,
		Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_projectile_star_2.png"));

	m_leftAccessory.initFocusLaser(Feintgine::ResourceManager::getTexture("Assets/Textures/marisa_laser_big.png"),
		m_leftAccessory.getPos(), glm::vec2(1280, 25), Feintgine::Color(255, 255, 255, 255), 10, degreeToRad(-90), 12.0f,
		Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_projectile_star_2.png"));

	m_hitParticleBatch = new Feintgine::ParticleBatch2D();
	Feintgine::F_Sprite sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png");
	m_hitParticleBatch->init(500, 0.057f, sprite, [](Feintgine::Particle2D& particles, float deltatime)
	{

		particles.position += particles.velocity * deltatime;
		particles.color.a = 1.0f * particles.life;
		particles.scale += 0.0075f * deltatime;

	});

	m_starParticleBatch1 = new Feintgine::ParticleBatch2D();
	//Feintgine::F_Sprite sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png");
	m_starAnim.init("Assets/F_AObjects/marisa_star.xml");

	m_starParticleBatch1->init(300, 0.05f, m_starAnim,
		[](Feintgine::Particle2D& particles, float deltatime)
	{

		particles.position += particles.velocity * deltatime;
		particles.color.a = 1.0f * particles.life;
		//particles.scale += 0.01f * deltatime;
		particles.angle += (0.1f * particles.velocity.x) * deltatime;

	});

	m_starSpawner.loadStar(m_starAnim);
	m_starSpawner.registerParticleBatch(m_starParticleBatch1);


	m_starParticleBatch2 = new Feintgine::ParticleBatch2D();
	//Feintgine::F_Sprite sprite = Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png");
	m_starAnim.init("Assets/F_AObjects/marisa_star.xml");


	m_starParticleBatch2->init(60, 0.05f, m_starAnim,
		[](Feintgine::Particle2D& particles, float deltatime)
	{
		particles.damp += 0.25f * deltatime;
		particles.position += particles.velocity * (particles.life * 1/ particles.damp) * deltatime;
		particles.color.a = 1.0f * particles.life;
		particles.scale += 0.01f * deltatime;
		particles.angle += (0.1f * particles.velocity.x) * deltatime;

	});


	m_luminousLauncher.loadAnimation("Assets/F_AObjects/marisa_star.xml");
	m_luminousLauncher.registerParticleBatch(m_starParticleBatch2);




	//m_animation.setColor(Feintgine::Color(-2550, -2550, -2550, 255));
	//m_testBulletAnimation.init("Assets/F_AObjects/reimu.xml");
	m_dim = glm::vec2(6);
	m_power = 0;



	m_fantasy_seal.loadDesciption("Dream sign", "\"Fantasy Seal\"",16.0f);

	m_spellSelector.setPos(glm::vec2(240, 0));
	

	switch (m_characterType)
	{

	case PLAYER_CHARACTER_REIMU:  // Reimu's spell
	{
		for (int i = 1; i < 10; i++)
		{
			SpellcardIcon * icon = new SpellcardIcon();
			std::string loadPath = "reimu_spell_icons/reimu_";
			loadPath.append(std::to_string(i));
			loadPath.append(".png");
			icon->init(Feintgine::SpriteManager::Instance()->getSprite(loadPath),
				glm::vec2(156, 256), Feintgine::Color(255, 255, 255, 255));

			icon->setScale(0.25f);
			icon->setSignName(getSignFromTextureList(i, 0));
			icon->setSpellName(getNameFromTextureList(i, 0));
			icon->setGrazeCost(getGrazeFromTextureList(i, 0));
			icon->setID(static_cast<SPELL_ID>(i));
			icon->setCD(getCDFromTextureList(i, 0));
			m_spellSelector.addSpell(icon);

			m_fantasy_seal.init(Feintgine::ResourceManager::getTexture("Assets/Textures/Reimu-00_sd.png"),
				glm::vec2(-400, 100), glm::vec2(-100, 100), glm::vec2(323, 360), Feintgine::Color(255, 255, 255, 255),
				10);
		}
	}
		break;
	case PLAYER_CHARACTER_MARISA:
	{
		for (int i = 1; i < 14; i++)
		{
			SpellcardIcon * icon = new SpellcardIcon();
			std::string loadPath = "marisa_spell_icons/marisa_";
			loadPath.append(std::to_string(i));
			loadPath.append(".png");
			icon->init(Feintgine::SpriteManager::Instance()->getSprite(loadPath),
				glm::vec2(156, 256), Feintgine::Color(255, 255, 255, 255));


			int index = i + 9;
			icon->setScale(0.25f);
			icon->setSignName(getSignFromTextureList(index, 0));
			icon->setSpellName(getNameFromTextureList(index, 0));
			icon->setGrazeCost(getGrazeFromTextureList(index, 0));
			icon->setID(static_cast<SPELL_ID>(index));
			icon->setCD(getCDFromTextureList(index, 0));
			m_spellSelector.addSpell(icon);
			
			m_fantasy_seal.init(Feintgine::ResourceManager::getTexture("Assets/Textures/Marisa-00_sd.png"),
				glm::vec2(-400, 100), glm::vec2(-100, 100), glm::vec2(386, 360), Feintgine::Color(255, 255, 255, 255),
				10);
		}
	}
		break;

	default:
		break;
	}
	
	// MarisaSpell
	
	m_spellSelector.arrangeSpellcard(false);

	m_binding_circle = new F_Reimu_Demon_Binding();
	m_binding_circle->init("Assets/F_AObjects/evil_sealing_circle.xml",
		"Assets/F_AObjects/evil_sealing_circle_support.xml",
		glm::vec2(m_pos.x, 0), glm::vec2(400, 800), Feintgine::Color(255, 255, 255, 200));


	p_pos = &m_pos;
	m_afterImageParticle.init(p_pos,&m_animation ,&m_animation.getColor(),
		.3f, 10);
	m_afterImageParticle.setScale(m_animation.getScale());
	m_yin_yang_orb = new Yin_Yang_Orb();
	m_yin_yang_orb->init("Assets/F_AObjects/yin_yang_orb.xml", Feintgine::Color(500, 500, 500, 255), 1.0f);
	m_yin_yang_orb->setDeathCallback([&] {
		m_logicCamera->startShake(3.0, 7.0f, 7.0f);

	});
	m_yin_yang_orb->setDMG(1.5f);

	m_yin_yang_orb_ex = new Yin_Yang_Orb_Ex();
	m_yin_yang_orb_ex->init("Assets/F_AObjects/yin_yang_orb_ex.xml", Feintgine::Color(500, 500, 500, 255), 1.3f);
	m_yin_yang_orb_ex->setDeathCallback([&] {
		m_logicCamera->startShake(4.3, 8.0f, 8.0f);

	});
	
	m_yin_yang_orb_ex->setDMG(3.5f);
	m_sealingAmulet.setIsDone(true);
	m_sealingAmulet.initParticle();


	m_masterSpark = new F_Marisa_MasterSpark();
 	m_masterSpark->init(glm::vec2(3.4f,2.4f),
 		Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_master_spark.png"),
 		Feintgine::Color(200, 200, 200, 50));
	
	m_starParticleBatch2->clear();


	m_suns.init(m_pos);

	m_starTrails.init(m_starAnim, 0.25f);
	m_starTrails.registerParticleBatch(m_starParticleBatch1);

	m_suns.setParticle(m_hitParticleBatch);
	

	m_sealingAmulet.init(m_pos, m_dim, Feintgine::Color(255, 255, 255, 255),
		"Assets/F_AObjects/sealing_amulet.xml", 44, 0, m_hitParticleBatch);
	m_sealingAmulet.setAlive(false);
	m_sealingAmulet.setBulletAnimationAction("idle");
	m_sealingAmulet.setLifeTime(40);
	m_sealingAmulet.setIsDone(true);
	m_sealingAmulet.setScale(glm::vec2(0.6f));



	//m_masterSpark->spawn();
	
	//m_fireSoundEffect = 
}

void F_Player::setSpellSelectorPos(const glm::vec2 & pos)
{

	m_spellSelector.setPos(pos);
	m_spellSelector.update(1.0f);
}


void F_Player::registerEffectBatch(Feintgine::EffectBatch * effectBatch)
{
	m_effectBatch = effectBatch;
	m_yin_yang_orb_ex->registerEffectBatch(m_effectBatch);
	m_sealingAmulet.registerEffectBatch(m_effectBatch);
	//m_yin_yang_orb->registerEffectBatch(m_effectBatch);

}

void F_Player::setPrimaryShot(bool t_isAnimated, const std::string & t_filePath, float t_dmg, float t_angle)
{
	m_primary.isAnimated = t_isAnimated;
	m_primary.filePath = t_filePath;
	m_primary.dmg = t_dmg;
	m_primary.angle = t_angle;
}

void F_Player::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void F_Player::setDim(const glm::vec2 & dim)
{
	m_dim = dim;
}

void F_Player::setVel(const glm::vec2 & vel)
{
	m_vel = vel;
}

void F_Player::setAccessoryShot(int val)
{
	m_leftAccessory.setBulletType(val);
	m_rightAccessory.setBulletType(val);
}



void F_Player::handleInput(Feintgine::InputManager & inputmanager)
{
	if (m_isControlable && !m_isReplay)
	{
		// reset state 
		m_playerState = 0;
		// reset action
		m_PlayerAction = 0;

		// fire (keydown/hold) 
		if (inputmanager.isKeyDown(SDLK_j))
		{
			m_playerState |= PLAYER_STATE_IS_FIRE;
// 			if (m_masterSparkEnd)
// 			{
// 
// 				m_isAttack = true;
// 				m_leftAccessory.setFire(true);
// 				m_rightAccessory.setFire(true);
// 				m_suns.setFire(true);
// 			}

		}// no longer hold fire key
		else
		{
// 			m_isAttack = false;
// 			m_leftAccessory.setFire(false);
// 			m_rightAccessory.setFire(false);
// 			m_suns.setFire(false);
		}

		if (inputmanager.isKeyDown(SDLK_a))
		{
			m_playerState |= PLAYER_STATE_MOVE_LEFT;
// 			m_vel.x = -moveSpeed;
// 			if (!alreadySetLeft)
// 			{
// 				m_animation.playAnimation("left");
// 				alreadySetLeft = true;
// 				alreadySetRight = false;
// 			}
// 			moveHor = true;
// 			isIdled = false;

		}
		else if (inputmanager.isKeyDown(SDLK_d))
		{
			m_playerState |= PLAYER_STATE_MOVE_RIGHT;
// 			m_vel.x = moveSpeed;
// 			if (!alreadySetRight)
// 			{
// 				m_animation.playAnimation("right");
// 				alreadySetRight = true;
// 				alreadySetLeft = false;
// 			}
// 			moveHor = true;
// 			isIdled = false;

		}
		if (inputmanager.isKeyDown(SDLK_w))
		{

			m_playerState |= PLAYER_STATE_MOVE_UP;
// 			m_vel.y = moveSpeed;
// 			moveVer = true;
	
		}
		else if (inputmanager.isKeyDown(SDLK_s))
		{
			m_playerState |= PLAYER_STATE_MOVE_DOWN;
// 			m_vel.y = -moveSpeed;
// 			moveVer = true;
		}

		if (!(m_playerState & PLAYER_STATE_MOVE_LEFT) && !(m_playerState & PLAYER_STATE_MOVE_RIGHT))
		{
			moveHor = false;
		}
		if (!(m_playerState & PLAYER_STATE_MOVE_DOWN) && !(m_playerState & PLAYER_STATE_MOVE_UP))
		{
			moveVer = false;
		}

// 		if (!inputmanager.isKeyDown(SDLK_a) && !inputmanager.isKeyDown(SDLK_d))
// 		{
// 			moveHor = false;
// 		}
// 		if (!inputmanager.isKeyDown(SDLK_s) && !inputmanager.isKeyDown(SDLK_w))
// 		{
// 			moveVer = false;
// 		}

		// Respawn (test) 
		if (inputmanager.isKeyDown(SDLK_RETURN)) 
		{
			m_isDeath = false;
			m_pos = glm::vec2(0, -300);
			m_afterImageTime = 5.0f;
		}

		if (moveVer && moveHor)
		{
			m_vel *= 0.5f;
		}
		if (!moveHor)
		{
			m_vel.x = 0;

			if (!isIdled)
			{
				m_animation.playAnimation("idle");
				isIdled = true;
			}
			alreadySetRight = false;
			alreadySetLeft = false;
		}
		if (!moveVer)
		{

			m_vel.y = 0;
		}
		else
		{

			// m_leftAccessory.setBoolFocus(false);
			// m_rightAccessory.setBoolFocus(false);
			// m_suns.setFocus(false);
		}

		if (inputmanager.isKeyPressed(SDLK_1))
		{
			m_leftAccessory.setType(1);
			m_rightAccessory.setType(1);
		}
		if (inputmanager.isKeyPressed(SDLK_2))
		{
			m_leftAccessory.setType(2);
			m_rightAccessory.setType(2);
		}


		if (!m_isDeath)
		{

			if (inputmanager.isKeyPressed(SDLK_l))
			{
				for (int i = 0; i < m_collectableItem.size(); i++)
				{
					m_collectableItem[i]->flyToPlayer();
				}
			}
			if (inputmanager.isKeyPressed(SDLK_k))
			{
				m_PlayerAction = PLAYER_ACTION_USE_SPELL ;

			}
			if (inputmanager.isKeyDown(SDLK_LSHIFT))
			{

				m_playerState |= PLAYER_STATE_IS_FOCUS;


			}
		}


	}
	if (inputmanager.isKeyPressed(SDLK_3))
	{
		//std::cout << "bat tu \n";
		toggleInvinsible();
	}
	
	if (inputmanager.isKeyPressed(SDLK_q))
	{
		m_PlayerAction = PLAYER_ACTION_SWITCH_SPELL_PREVIOUS;
		//m_spellSelector.changeSpellcardBackward();
	}
	if (inputmanager.isKeyPressed(SDLK_e))
	{
		m_PlayerAction = PLAYER_ACTION_SWITCH_SPELL_FORWARD;
		//m_spellSelector.changeSpellcardForward();
	}

	//std::cout << "state : " << m_playerState << "  " << ENGINE_current_tick << "\n";
	//t_duration = (SDL_GetTicks() - t_start) / (double)CLOCKS_PER_SEC;
// 	if (m_playerState != m_playerPrevState)
// 	{
		recordedState newState;
// 		if (m_recordedStates.size() > 0)
// 		{
// 			m_recordedStates[m_recordedStates.size() - 1].endTime = ENGINE_current_tick;
// 		}


		m_playerPrevState = m_playerState;
		newState.startTime = ENGINE_current_tick;
		newState.state = m_playerState;
		newState.x_pos = m_pos.x;
		newState.y_pos = m_pos.y;
		m_recordedStates.push_back(newState);

		//std::cout << "SDL_GetTicks() : " << SDL_GetTicks() << "\n";
//	}
	if (m_PlayerAction != 0)
	{
		recordedAction newAction;
		newAction.tAction = m_PlayerAction;
		newAction.time = ENGINE_current_tick;
		m_recordedActions.push_back(newAction);
		//m_PlayerAction = 0;
	}

}



void F_Player::setDeathCallback(const std::function <void(void)>& f)
{
	m_deathCallback = f;
}

bool F_Player::checkColliderWithEnemy(const F_BaseEnemy & enemy)
{

	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dim * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;
	

	if (m_pos.x + halfDim.x  > pos.x - t_halfDim.x &&
		m_pos.y + halfDim.y < pos.y + t_halfDim.y &&
		m_pos.x - halfDim.x < pos.x + t_halfDim.x &&
		m_pos.y - halfDim.y > pos.y - t_halfDim.y )
	{
		return true;
	}

	return false;

}

bool F_Player::checkColliderWithGuardian(const EnemyGuardian & enemy)
{

	glm::vec2 pos = enemy.getPos();
	glm::vec2 dim = enemy.getDim();

	glm::vec2 halfDim = m_dim * 0.5f;
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

bool F_Player::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim() * bullet.getScale();

	glm::vec2 halfDim = m_dim * 0.5f;
	glm::vec2 t_halfDim = dim * 0.5f;

	float radius = dim.x * 0.5f;

	glm::vec2 distVec = m_pos + m_dim.x * 0.5f - pos - radius;

	float distance = glm::length(distVec);

	float colliderDepth = radius - distance;

	if (colliderDepth > 0)
	{

		return true;
	}


// 	if (m_pos.x + halfDim.x > pos.x - t_halfDim.x &&
// 		m_pos.y + halfDim.y < pos.y + t_halfDim.y &&
// 		m_pos.x - halfDim.x < pos.x + t_halfDim.x &&
// 		m_pos.y - halfDim.y > pos.y - t_halfDim.y)
// 	{
// 		return true;
// 	}

	return false;
}


void F_Player::die()
{
	if (!m_isDeath)
	{
		m_deathCallback();
		m_isDeath = true;
		clearBullet();
		m_deadSoundEffect.playInChannel(0, 1);
	}
	
}

bool F_Player::checkColliderWithCollectable(F_CollectableItem * item)
{
	glm::vec2 pos = item->getPos();
	glm::vec2 dim = item->getDim();

	glm::vec2 halfDim = m_dim;
	glm::vec2 t_halfDim = dim ;

	float radius = dim.x ;

	glm::vec2 distVec = m_pos + (m_dim.x *2.5f) - pos - radius;

	float distance = glm::length(distVec);

	float colliderDepth = radius - distance;

	if (colliderDepth > 0)
	{

		return true;
	}


	return false;
}

bool F_Player::checkGrazedEnemyBullet(EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim() * bullet.getScale();

	glm::vec2 halfDim = m_dim ;
	glm::vec2 t_halfDim = dim;

	float radius = dim.x * 8.5f;

	glm::vec2 distVec = m_pos + m_dim.x * 0.5f - pos - radius;

	float distance = glm::length(distVec);

	float colliderDepth = radius - distance;

	if (colliderDepth > 0)
	{

		return true;
	}


	// 	if (m_pos.x + halfDim.x > pos.x - t_halfDim.x &&
	// 		m_pos.y + halfDim.y < pos.y + t_halfDim.y &&
	// 		m_pos.x - halfDim.x < pos.x + t_halfDim.x &&
	// 		m_pos.y - halfDim.y > pos.y - t_halfDim.y)
	// 	{
	// 		return true;
	// 	}

	return false;
}

void F_Player::setOffsetNoLight(const glm::vec2 & offset)
{
	if (m_yin_yang_orb)
	{
		m_yin_yang_orb->setOffsetNoLight(offset);
	}
	if (m_yin_yang_orb_ex)
	{
		m_yin_yang_orb_ex->setOffsetNoLight(offset);
	}
}

// void F_Player::registerBox2DWorld(b2World * world)
// {
// 	m_rod.initLogic(world);
// }

void F_Player::fire()
{
	m_fireSoundEffect.playInChannel(1, 5);
	glm::vec2 t_pos = m_pos;
	t_pos.y += 5.5f;
	switch (m_powerLevel)
	{
	case 0:
	case 1:
	{
		//bullet.setVel(glm::vec2(0, 10));
		//std::string path = "Assets/F_AObjects/marisa_normal_projectile.xml";
		if (m_primary.isAnimated)
		{

			F_BulletStraight  * t_bullet = new F_BulletStraight();
			t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
				m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
			t_bullet->setBulletAnimationAction("default");
			t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
			m_bullets.push_back(t_bullet);
			//delete t_bullet;
			break;
		}
	}
	case 2:
	case 3:
	{
		F_BulletStraight  * t_bullet = new F_BulletStraight();
		t_pos.x -= 6.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);


		t_bullet = new F_BulletStraight();
		t_pos.x += 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);

		//bullet.setVel(glm::vec2(-0.6, 10));
		//m_bullets.push_back(t_bullet);
		//bullet.setVel(glm::vec2(0.6, 10));
		//m_bullets.push_back(t_bullet);
		break;
	}
	case 4:
	case 5:
	{


		F_BulletStraight  * t_bullet = new F_BulletStraight();
		t_pos.x -= 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setAngle(degreeToRad(5));
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);


		t_bullet = new F_BulletStraight();
		t_pos.x += 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);

		t_bullet = new F_BulletStraight();
		t_pos.x += 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setAngle(degreeToRad(-5));
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);

		break;
	}
	case 6:
	{
		F_BulletStraight  * t_bullet = new F_BulletStraight();
		t_pos.x -= 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setAngle(degreeToRad(5));
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);


		t_bullet = new F_BulletStraight();
		t_pos.x += 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setAngle(degreeToRad(2.5));
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);

		t_bullet = new F_BulletStraight();
		t_pos.x += 12.0f;	
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setAngle(degreeToRad(-2.5));
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);

		t_bullet = new F_BulletStraight();
		t_pos.x += 12.0f;
		t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
			m_primary.filePath, 2, m_primary.dmg, m_hitParticleBatch);
		t_bullet->setBulletAnimationAction("default");
		t_bullet->setAngle(degreeToRad(-5));
		t_bullet->setBulletAnimationAngle(degreeToRad(m_primary.angle));
		m_bullets.push_back(t_bullet);
	}
	default:
		break;
	}
}

void F_Player::setSpellPos(const glm::vec2 & pos)
{
	m_spellSelector.setPos(pos);
	m_spellSelector.update(1.0f);
}

void F_Player::update(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets)
{
	m_starSpawner.update(deltaTime,enemy,bullets,m_pos);
	m_luminousLauncher.update(deltaTime, enemy, bullets, m_pos);


	float lightVal = GlobalValueClass::Instance()->getAmbientLight().x;
	m_hitParticleBatch->setLightScale(lightVal);
	m_starParticleBatch1->setLightScale(lightVal);

	//std::cout << "naides player " << feint_common::Instance()->convertiVec2toString(m_pos) << "\n";
	//m_rightAccessory.setLaserEnergy(m_leftAccessory.getLaserEnergy());
	if (!m_isDeath)
	{

		if (isLocked)
		{
			if (m_pos.x < -BORDER)
			{

				m_pos.x = -BORDER + m_vel.x;
				m_vel.x = 0;

			}
			if (m_pos.x > BORDER)
			{

				m_pos.x = BORDER + m_vel.x;
				m_vel.x = 0;

			}
			if (m_pos.y < -BORDER)
			{
				m_pos.y = -BORDER + m_vel.y;
				m_vel.y = 0;
			}
			if (m_pos.y > BORDER)
			{
				m_pos.y = BORDER + m_vel.y;
				m_vel.y = 0;
			}
		}
		
		m_animation.update(deltaTime);
		if (m_afterImageTime > 0.0f)
		{
			m_afterImageTime -= 0.1f * deltaTime;
			m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(),m_angle);

		}
		
		
		//std::cout << m_animation.getCurrentAnimation()->getCurrentIndex() << " / " << m_animation.getCurrentAnimation()->getSize() << "\n";

		m_pos += (m_vel * deltaTime);
		m_animation.setPos(m_pos);
		m_leftAccessory.setPos(m_pos);
		m_rightAccessory.setPos(m_pos);
		m_leftAccessory.update(deltaTime, enemy);
		m_rightAccessory.update(deltaTime, enemy);	

		for (auto i = 0; i < enemy.size(); i++)
		{
			if (!m_isInvinsible )
			{
				if (m_afterImageTime <= 0.0f)
				{

					if (checkColliderWithEnemy(*enemy[i]))
					{
						die();
// 						m_deathCallback();
// 						m_isDeath = true;
// 						m_deadSoundEffect.playInChannel(0, 1);
					}
				}
// 				if (m_velocitySegment > 0)
// 				{
// 					if (checkColliderWithEnemy(*enemy[i]))
// 					{
// 						enemy[i]->takeDamage(7.5f);
// 					}
// 				}
			}

		}

// 		 for (auto i = 0; i < guardians.size(); i++)
// 		{
// 			if (!m_isInvinsible)
// 			{
// 				if (m_afterImageTime <= 0.0f)
// 				{

// 					if (checkColliderWithEnemy(*guardians[i]))
// 					{
// 						die();
// // 						m_deathCallback();
// // 						m_isDeath = true;
// // 						m_deadSoundEffect.playInChannel(0, 1);
// 					}
// 				}
// // 				if (m_velocitySegment > 0)
// // 				{
// // 					if (checkColliderWithEnemy(*guardians[i]))
// // 					{
// // 						guardians[i]->takeDamage(7.5f);
// // 					}
// // 				}

// 			}

// 		}
		for (auto i = 0; i < bullets.size(); i++)
		{

			if (checkGrazedEnemyBullet(*bullets[i]) && bullets[i]->isGrazeable())
			{
				bullets[i]->setGrazeable(false);
				m_grazeCount++;
				m_spellSelector.updateSpellStates(m_grazeCount);
			}
			if (!m_isInvinsible )
			{
				if (m_afterImageTime <= 0.0f)
				{
					
					if (checkColliderWithEnemyBullet(*bullets[i]))
					{
						if (!bullets[i]->isDisabled())
						{
							die();					
						}
					}
				}
// 				if (m_velocitySegment > 0)
// 				{
// 					if (checkColliderWithEnemyBullet(*bullets[i]))
// 					{
// 						bullets[i]->setLifeTime(-1);
// 					}
// 				}
			}
					
		}
	}

	
	if (isParentColor)
	{
		for (auto i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i]->setAlpha(m_animation.getColor().a);
			
		}
	}
	if (m_isAttack && !m_isDeath)
	{
		
		if (!m_energyLocked)
		{
			if (m_unlimitedEnergyTimer > 0.0f)
			{
				m_unlimitedEnergyTimer -= 0.1f * deltaTime;

			}
			else
			{

				m_energy -= ENERGY_RATE * m_pernaltyRate * deltaTime;
			}
		}
		else
		{
			m_energy += ENERGY_RATE * m_pernaltyRate * 2.4f * deltaTime;
		}


		fireRate += 0.1f * deltaTime;
		if (fireRate >= delayBullet)
		{
			fire();
			//bullet;

		
// 			bullet.init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
// 				Feintgine::SpriteManager::Instance()->getSprite("character/reimu_bullet_fly.png"), 2,
// 				5.0f, m_hitParticleBatch);


// 			bullet.init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 255),
// 				Feintgine::SpriteManager::Instance()->getSprite("marisa_projectile/Marisa_projectile__special_green_1.png"), 2,
// 				5.0f, m_hitParticleBatch);


			
// 			bullet.init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
// 				m_testBulletAnimation, 2,
// 				5.0f, m_hitParticleBatch);

// 			bullet.init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120),
// 				"Assets/F_AObjects/reimu.xml", 2,
// 				5.0f, m_hitParticleBatch);
			
			//bullet.setBulletAnimationAction("idle");
			//bullet.setBulletAnimationAngle(degreeToRad(90));
			//bullet.setLifeTime(5);
			//if (m_bullets.size() == 0)
			//{
				
// 				switch (m_powerLevel)
// 				{
// 				case 0:
// 				case 1:
// 				{
// 					//bullet.setVel(glm::vec2(0, 10));
// 					std::string path = "Assets/F_AObjects/marisa_normal_projectile.xml";
// 					F_BulletStraight  * t_bullet = new F_BulletStraight();
// 					t_bullet->init(t_pos, glm::vec2(16, 12), Feintgine::Color(255, 255, 255, 120), 
// 						path, 2, 5.0f, m_hitParticleBatch);
// 					t_bullet->setBulletAnimationAction("default");
// 					t_bullet->setBulletAnimationAngle(degreeToRad(90));
// 					m_bullets.push_back(t_bullet);
// 					//delete t_bullet;
// 					break;
// 				}
// 				case 2:
// 				case 3:
// 					bullet.setVel(glm::vec2(-0.6, 10));
// 					//m_bullets.push_back(t_bullet);
// 					bullet.setVel(glm::vec2(0.6, 10));
// 					//m_bullets.push_back(t_bullet);
// 					break;
// 				case 4:
// 					bullet.setVel(glm::vec2(-1.2, 10));
// 					//m_bullets.push_back(bullet);
// 					bullet.setVel(glm::vec2(0, 10));
// 					//m_bullets.push_back(bullet);
// 					bullet.setVel(glm::vec2(1.2, 10));
// 					//m_bullets.push_back(bullet);
// 					break;
// 
// 				case 5:
// 					bullet.setVel(glm::vec2(-1.2, 10));
// 					//m_bullets.push_back(bullet);
// 					bullet.setVel(glm::vec2(1.2, 10));
// 					//m_bullets.push_back(bullet);
// 					bullet.setVel(glm::vec2(-0.6, 10));
// 					//m_bullets.push_back(bullet);
// 					bullet.setVel(glm::vec2(0.6, 10));
// 					//m_bullets.push_back(bullet);
// 					break;
// 				default:
// 					break;
// 				}
			//}
			
			//bullet.init(m_pos, glm::vec2(14, 16), Feintgine::Color(255, 255, 255, 144),
			//	Feintgine::ResourceManager::getTexture("./Assets/Lazy/bullet.png"), 14);
			
			//bullet.init(m_pos, glm::vec2(14, 16), Feintgine::Color(255, 255, 255, 144),
			//	Feintgine::ResourceManager::getTexture("./Assets/Lazy/bullet.png"), 14);
			
			fireRate = 0.0f;
		}
	}
	else
	{
		
			m_energy += ENERGY_RATE * m_pernaltyRate * deltaTime;
			if (m_energy >= MAX_ENERGY)
			{
				m_energy = MAX_ENERGY;
			}
		
	}
	updateEnergyLocked(deltaTime);
	m_leftAccessory.setLaserEnergy(m_energy);
	m_rightAccessory.setLaserEnergy(m_energy);

	for (auto i = 0; i < m_labelItems.size(); i++)
	{
		if (!m_labelItems[i].isExpired())
		{
			m_labelItems[i].update(deltaTime);
		}
		else
		{
			m_labelItems.erase(m_labelItems.begin() + i);
		}
	}
	for (auto i = 0; i < m_collectableItem.size(); i++)
	{
		m_collectableItem[i]->update(this,deltaTime);
		if (checkColliderWithCollectable(m_collectableItem[i]))
		{
			m_collectableItem[i]->onCollected(this);
			m_collectableItem.erase(m_collectableItem.begin() + i);
		}
	}

	for (auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(deltaTime, enemy);
		if (!m_bullets[i]->isAlive())
		{
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	for (auto i = 0; i < m_spells.size(); i++)
	{
		m_spells[i].update(deltaTime);
		if (!m_spells[i].isAlive())
		{
			//delete m_bullets[i];
			m_spells.erase(m_spells.begin() + i);
		}
		
	}
	for (auto i = 0; i < m_flyOrb.size(); i++)
	{
		m_flyOrb[i].update(deltaTime,enemy,bullets);
		if (!m_flyOrb[i].isAlive())
		{
			//delete m_bullets[i];
			m_flyOrb.erase(m_flyOrb.begin() + i);
		}
	}
	if (m_binding_circle)
	{
		m_binding_circle->update(deltaTime, enemy,bullets);
	}
	if (m_yin_yang_orb)
	{
		m_yin_yang_orb->update(deltaTime, enemy, bullets);
	}
	if (m_yin_yang_orb_ex)
	{
		m_yin_yang_orb_ex->update(deltaTime, enemy, bullets);
	}

	m_spellSelector.update(deltaTime);
	// if (m_logicCamera)
	// {
	// 	m_logicCamera->logicUpdate(deltaTime);
	// }
	m_rod.update(m_pos, deltaTime, bullets);



	if (m_sealingAmulet.isAlive())
	{
		m_sealingAmulet.update(deltaTime,enemy);
	}

	if (m_starParticleBatch1)
	{
		m_starParticleBatch1->update(deltaTime);
	}
	if (m_starParticleBatch2)
	{
		m_starParticleBatch2->update(deltaTime);
	}
	
	m_masterSpark->update(deltaTime, enemy, bullets);
	updateMasterSparkMode(deltaTime);
	updateEscapeVelocity(deltaTime);
	m_suns.update(m_pos, deltaTime, enemy, bullets);
	//m_starTrails.update(m_trailPos, deltaTime, enemy, bullets);
	m_starTrails.update(m_pos, deltaTime, enemy, bullets);

	updateState(deltaTime);

	
}


void F_Player::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!m_isDeath)
	{
		m_animation.draw(spriteBatch);
		m_leftAccessory.draw(spriteBatch);
		m_rightAccessory.draw(spriteBatch);
		
	}
	for (auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
	for (auto i = 0; i < m_collectableItem.size(); i++)
	{
		m_collectableItem[i]->draw(spriteBatch);
	}

	for (auto i = 0; i < m_flyOrb.size(); i++)
	{
		m_flyOrb[i].draw(spriteBatch);
	}

	if (m_binding_circle)
	{
		m_binding_circle->draw(spriteBatch);
	}
	
	if (m_yin_yang_orb)
	{
		m_yin_yang_orb->draw(spriteBatch);
	}
	if (m_yin_yang_orb_ex)
	{
		m_yin_yang_orb_ex->draw(spriteBatch);
	}
// 
// 
	m_rod.draw(spriteBatch);
	m_starSpawner.draw(spriteBatch);
	m_luminousLauncher.draw(spriteBatch);

	if (m_afterImageTime > 0.0f)
	{
		m_afterImageParticle.draw(spriteBatch);
	}
	if (m_sealingAmulet.isAlive())
	{
		m_sealingAmulet.draw(spriteBatch);
	}
		
	if (m_starParticleBatch1)
	{
		m_starParticleBatch1->draw(&spriteBatch);
	}
	
	if (m_starParticleBatch2)
	{
		m_starParticleBatch2->draw(&spriteBatch);
	}
	if (m_masterSpark)
	{
		m_masterSpark->draw(spriteBatch);
	}
		
	
	m_suns.draw(spriteBatch);
	m_starTrails.draw(spriteBatch);
			
	m_hitParticleBatch->draw(&spriteBatch);
	
}




void F_Player::drawLight(Feintgine::LightBatch &lightBatch)
{
	m_leftAccessory.drawLight(lightBatch);
	m_rightAccessory.drawLight(lightBatch);
	m_hitParticleBatch->drawLight(lightBatch);
	for (int i = 0; i < m_flyOrb.size(); i++)
	{
		m_flyOrb[i].drawLight(lightBatch);
	}
	if (m_binding_circle)
	{
		m_binding_circle->drawLight(lightBatch);
	}
	if (m_yin_yang_orb)
	{
		m_yin_yang_orb->drawLight(lightBatch);
	}
	if (m_yin_yang_orb_ex)
	{
		m_yin_yang_orb_ex->drawLight(lightBatch);
	}
	if (m_masterSpark)
	{
		m_masterSpark->drawRayLight(lightBatch);
	}

	if (m_starParticleBatch1)
	{
		m_starParticleBatch1->drawLight(lightBatch);
	}

	if (m_starParticleBatch2)
	{
		m_starParticleBatch2->drawLight(lightBatch);
	}


	m_starSpawner.drawLight(lightBatch);
	m_luminousLauncher.drawLight(lightBatch);
	m_suns.drawLight(lightBatch);
	m_starTrails.drawLight(lightBatch);
	
}

void F_Player::drawHitbox(Feintgine::DebugRender & debugRenderer)
{
	debugRenderer.drawCircle(m_pos, Feintgine::Color(255,0,0,255), m_dim.x * 0.5f);
 	m_leftAccessory.drawDebug(debugRenderer);
 	m_rightAccessory.drawDebug(debugRenderer);
	m_rod.drawDebug(debugRenderer);
}


void F_Player::drawScore(TextRenderer & textRenderer, const Feintgine::Camera2D & cam)
{
	for (auto i = 0; i < m_labelItems.size(); i++)
	{
		
		m_labelItems[i].draw(textRenderer, cam);
		
	}

}

void F_Player::drawText(TextRenderer & textRenderer, const Feintgine::Camera2D & cam)
{
	for (auto i = 0; i < m_spells.size(); i++)
	{
		//m_spells[i].drawText(cam, textRenderer);
	}
}

void F_Player::registerLogicCamera(Feintgine::Camera2D * camera)
{

	//std::cout << "finally register " << camera << "\n";
	m_logicCamera = camera;

	m_binding_circle->registerCamera(m_logicCamera);
	m_rod.registerCamera(m_logicCamera);

	

	//std::cout << "after register " << m_logicCamera << "\n";
}

void F_Player::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
	
}

void F_Player::initSound()
{
	if (m_audioEngine)
	{
		//std::cout << "init sound called \n";
		m_fireSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/fire_sound.wav");
		m_deadSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/pldead00.wav");
		m_dashSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/se_tan00.wav");
		m_spellcardCastSoundEffect = m_audioEngine->loadSoundEffect("Sounds/sfx/spellcard_cast.wav");
		m_sealingAmulet.registerAudioEngine(m_audioEngine);
		m_spellcardCastSoundEffect.setVolume(10);
		
		m_spellSelector.registerAudio(m_audioEngine);
		if (m_binding_circle)
		{
			m_binding_circle->registerSound(m_audioEngine);
		}
		
		if (m_yin_yang_orb)
		{
			m_yin_yang_orb->registerAudioEngine(m_audioEngine);
		}

		if (m_yin_yang_orb_ex)
		{
			m_yin_yang_orb_ex->registerAudioEngine(m_audioEngine);
		}
		if (m_masterSpark)
		{
			m_masterSpark->registerAudioEngine(m_audioEngine);
		}
		m_starSpawner.registerAudioEngine(m_audioEngine);
		m_luminousLauncher.registerAudioEngine(m_audioEngine);
		m_suns.registerAudioEngine(m_audioEngine);
	}
	else
	{
		feint_common::Instance()->showMessageBox("Error", "Player audio engine is null ");
	}
}

void F_Player::clearBullet()
{
	m_bullets.clear();
	m_leftAccessory.clearBullet();
	m_rightAccessory.clearBullet();

	
}

void F_Player::setDepth(float depth)
{
	//m_animation.
}

void F_Player::onFocus()
{
	
}

void F_Player::offFocus()
{
	
}

void F_Player::setAccessoryLaser(const Feintgine::GLTexture & texture, 
	const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color, float depth, float angle, float dps)
{
// 	m_leftAccessory.initLaser(texture,
// 		pos, dim, color, depth, angle, dps, Feintgine::SpriteManager::Instance()->getSprite("dddd"));
}

void F_Player::addScore(int score)
{
	
	m_score += score;
	popupLabel(std::to_string(score), Feintgine::Color(255, 255, 255, 255));
	
}


void F_Player::addScoreSilence(int score)
{
	m_score += score;
}

void F_Player::reset()
{
	m_powerLevel = 1;
	m_power = 0;
	m_startPower = 3;
	m_score = 0;
	for (auto i = 0 ;i < m_collectableItem.size(); i++)
	{
		m_collectableItem.erase(m_collectableItem.begin() + i);
	}
	m_collectableItem.clear();
	m_isDeath = false;
	m_grazeCount = 0;
	m_spellSelector.updateSpellStates(m_grazeCount);
}

void F_Player::addPower(unsigned int val)
{
	m_power += val;
	if (m_powerLevel >= 6)
	{
		return;
	}
	if (m_power > pow(THE_POWER_OF, m_startPower))
	{

		popupLabel("Power Up", Feintgine::Color(255, 255, 0, 255));
// 		std::cout << "current power " << m_power << "\n";
// 		std::cout << "power up"  << pow(THE_POWER_OF, m_startPower) << " \n";
		m_startPower++;
		m_powerLevel++;
	}
}



void F_Player::drawNoLight(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_yin_yang_orb)
	{
		m_yin_yang_orb->drawNoLight(spriteBatch);
	}
	if (m_yin_yang_orb_ex)
	{
		m_yin_yang_orb_ex->drawNoLight(spriteBatch);
	}
}

void F_Player::drawSpellSelector(Feintgine::SpriteBatch & spriteBatch)
{
	m_spellSelector.draw(spriteBatch);
	for (auto i = 0; i < m_spells.size(); i++)
	{
		m_spells[i].draw(spriteBatch);
	}
	
}

void F_Player::addDropItem(F_CollectableItem * item)
{
	m_collectableItem.push_back(item);
}

void F_Player::popupLabel(const std::string & msg, const Feintgine::Color & color)
{
	LabelItem item;
	glm::vec2 offsetPos = m_pos;
	offsetPos.y += 12;
	item.init(offsetPos, msg, color, 1, ALIGN_FT_CENTER);
	m_labelItems.push_back(item);
}

void F_Player::setInvinsible(bool val)
{
	m_isInvinsible = val;
}

void F_Player::toggleInvinsible()
{
	if (m_isInvinsible)
	{
		m_isInvinsible = false;
		std::cout << "bat tu off \n";
	}
	else
	{
		std::cout << "bat tu on \n";
		m_isInvinsible = true;
	}
}

void F_Player::resetStack()
{
	m_leftAccessory.resetStack();
	m_rightAccessory.resetStack();
	m_leftAccessory.setBoolFocus(false);
	m_rightAccessory.setBoolFocus(false);
}

void F_Player::setFire(bool value)
{
	if(value)
	{
		m_isAttack = true;
		m_leftAccessory.setFire(true);
		m_rightAccessory.setFire(true);
		//if(m_bul)
	
	}
	else
	{
		m_isAttack = false;
		m_leftAccessory.setFire(false);
		m_rightAccessory.setFire(false);
		//m_rightAccessory.setLaserEnergy(m_leftAccessory.getLaserEnergy());
	}
}

void F_Player::setVolume(float value)
{
	m_fireSoundEffect.setVolume(value);
}

bool F_Player::changeColor(int channel, float rate, float maxVal)
{
	bool t_self = m_animation.changeColor(channel, rate, maxVal);
	bool t_left = m_leftAccessory.changeColor(channel, rate, maxVal);
	bool t_right = m_rightAccessory.changeColor(channel, rate, maxVal);

	return t_self | t_left | t_right;
	//return m_animation.changeColor(channel, rate, maxVal);

}

void F_Player::unlockState(bool val)
{
	isLocked = val;
}

void F_Player::setParentColor(bool val)
{
	isParentColor = val;
	m_leftAccessory.setParentColor(val);
	m_rightAccessory.setParentColor(val);
}

void F_Player::registerKanjiEffect(KanjiEffectManager * effectManager)
{
	m_kanjiEffectManager_p = effectManager;
	m_sealingAmulet.registerKanjiEffectManager(m_kanjiEffectManager_p);
}

std::wstring F_Player::getSignFromTextureList(int val, int characterIndex)
{
	std::wstring returnVal;
	
	switch (val)
	{
		case 1:
			returnVal = L"Divine Spirit";
			break;
		case 2:
			returnVal = L"Dream Sign";
			break;
		case 3:
			returnVal = L"Spirit Sign";
			break;
		case 4:
			returnVal = L"Dream Sign";
			break;
		case 5:
			returnVal = L"Treasure Sign";
			break;
		case 6:
			returnVal = L"Bewitched Weapon";
			break;
		case 7:
			returnVal = L"Divine Arts";
			break;
		case 8:
			returnVal = L"Holy Relic";
			break;
		case 9:
			returnVal = L"Divine Spirit";
			break;

		// Marisa 


		case 10 : 
			returnVal = L"Star Sign";
			break;

		case 11:
			returnVal = L"Magic Sign";
			break;

		case 12:
			returnVal = L"Light Sign";
			break;

		case 13:
			returnVal = L"Ritual Sign";
			break;

		case 14:
			returnVal = L"Love Sign";
			break;

		case 15:
			returnVal = L"Star Sign";
			break;

		case 16:
			returnVal = L"Star Sign";
			break;

		case 17:
			returnVal = L"Light Sign";
			break;

		case 18:
			returnVal = L"Love Sign";
			break;

		case 19:
			returnVal = L"Comet";
			break;

		case 20:
			returnVal = L"Magicannon";
			break;

		case 21:
			returnVal = L"Perversion";
			break;


		default:
			break;
	}

	return returnVal;

}

std::wstring F_Player::getNameFromTextureList(int val, int characterIndex)
{
	std::wstring returnVal;

	switch (val)
	{
	case 1:
		returnVal = L"Fantasy Heaven";
		break;
	case 2:
		returnVal = L"Youkai Seal";
		break;
	case 3:
		returnVal = L"Fantasy Orbs";
		break;
	case 4:
		returnVal = L"Demon Binding Array";
		break;
	case 5:
		returnVal = L"Yin-Yang Orb";
		break;
	case 6:
		returnVal = L"Purification Rod";
		break;
	case 7:
		returnVal = L"Demon Binding Circle";
		break;
	case 8:
		returnVal = L"Yin-Yang Sanctifier Orb";
		break;
	case 9:
		returnVal = L"Fantasy Seal";
		break;

	// Marisa

	case 10:
		returnVal = L"Meteoric Shower";
		break;

	case 11:
		returnVal = L"Stardust Reverie";
		break;

	case 12:
		returnVal = L"Luminous Strike";
		break;

	case 13:
		returnVal = L"Orreries Sun";
		break;

	case 14:
		returnVal = L"Master Spark";
		break;

	case 15:
		returnVal = L"Escape Velocity";
		break;

	case 16:
		returnVal = L"Gravity Beat";
		break;

	case 17:
		returnVal = L"Earthlight Ray";
		break;

	case 18:
		returnVal = L"Non-Directional Laser";
		break;

	case 19:
		returnVal = L"Blazing Star";
		break;

	case 20:
		returnVal = L"Final Spark";
		break;

	case 21:
		returnVal = L"Sure-Fire Master Spark";
		break;

	default:
		break;
	}

	return returnVal;
}

int F_Player::getGrazeFromTextureList(int val, int characterIndex)
{
	int returnVal;
	switch (val)
	{
	case 1:
		returnVal = 500;
		break;
	case 2:
		returnVal = 140;
		break;
	case 3:
		returnVal = 200;
		break;
	case 4:
		returnVal = 125;
		break;
	case 5:
		returnVal = 180;
		break;
	case 6:
		returnVal = 100;
		break;
	case 7:
		returnVal = 250;
		break;
	case 8:
		returnVal = 340;
		break;
	case 9:
		returnVal = 480;
		break;

	// Marisa 

	case 10:
		returnVal = 120;
		break;

	case 11:
		returnVal = 150;
		break;

	case 12:
		returnVal =100;
		break;

	case 13:
		returnVal  =200;
		break;

	case 14:
		returnVal = 350;
		break;

	case 15:
		returnVal = 250;
		break;

	case 16:
		returnVal = 300;
		break;

	case 17:
		returnVal = 325;
		break;

	case 18:
		returnVal = 300;
		break;

	case 19:
		returnVal = 420;
		break;

	case 20:
		returnVal = 550;
		break;

	case 21:
		returnVal = 550;
		break;

	default:
		break;
	}
	return returnVal;
}


float F_Player::getCDFromTextureList(int val, int characterIndex)
{
	int returnVal;
	switch (val)
	{
	case 1:
		returnVal = 120;
		break;
	case 2:
		returnVal = 15;
		break;
	case 3:
		returnVal = 20;
		break;
	case 4:
		returnVal = 15;
		break;
	case 5:
		returnVal = 18;
		break;
	case 6:
		returnVal = 7;
		break;
	case 7:
		returnVal = 20;
		break;
	case 8:
		returnVal = 25;
		break;
	case 9:
		returnVal = 60;
		break;

		// Marisa 

	case 10:
		returnVal = 12;
		break;

	case 11:
		returnVal = 22;
		break;

	case 12:
		returnVal = 14;
		break;

	case 13:
		returnVal = 12;
		break;

	case 14:
		returnVal = 18;
		break;

	case 15:
		returnVal = 13;
		break;

	case 16:
		returnVal = 16;
		break;

	case 17:
		returnVal = 15;
		break;

	case 18:
		returnVal = 15;
		break;

	case 19:
		returnVal = 22;
		break;

	case 20:
		returnVal = 25;
		break;

	case 21:
		returnVal = 25;
		break;

	default:
		break;
	}
	return returnVal;
}



void F_Player::registerTextCEGUI(Feintgine::GUI & gui)
{
	m_fantasy_seal.registerText(gui,"m_fantasy_seal",
		glm::vec2(glm::vec2(-1.0f, -1.0f)),glm::vec2(0.4,0.1));
}

void F_Player::setFocus(bool val)
{
	m_rightAccessory.setBoolFocus(val);
	m_leftAccessory.setBoolFocus(val);
}

void F_Player::t_fantasySealOrbEndCallback()
{
	float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
	float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
	glm::vec2 halfDim = glm::vec2(25);
	m_hitParticleBatch->addParticle(glm::vec2(0) - halfDim,
		glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
}

void F_Player::updateMasterSparkMode(float deltaTime)
{
	if(m_masterSpark)
	{
		m_masterSpark->setPos(m_pos);
	}
	if (m_masterSparkTime > 0.0f)
	{	
		m_masterSparkTime -= 0.1f * deltaTime;
		moveSpeed = t_moveSpeed * m_speedPelnaty;

		if (abs(m_angle) < degreeToRad(LIMITED_ANGLE_MASTERSPARK) + 0.001f)
		{

			if (m_vel.x < 0)
			{
				m_angle += 0.0025f * deltaTime;
			}
			if (m_vel.x > 0)
			{
				m_angle -= 0.0025f * deltaTime;
			}
		}
		else
		{
			if (m_angle >  degreeToRad(LIMITED_ANGLE_MASTERSPARK))
			{
				m_angle = degreeToRad(LIMITED_ANGLE_MASTERSPARK);
			}
			if (m_angle < -degreeToRad(LIMITED_ANGLE_MASTERSPARK))
			{
				m_angle = -degreeToRad(LIMITED_ANGLE_MASTERSPARK);
			}		

			
		}
		m_masterSpark->setAngle(m_angle + degreeToRad(90));
		
		//m_v
	}
	else
	{
		//std::cout << m_angleFlag << "\n";
		if (!m_masterSparkEnd)
		{
			if (m_angle > 0)
			{
				m_angleFlag = 1;
			}
			if (m_angle < 0)
			{
				m_angleFlag = 2;
			}
			if (m_angle == 0)
			{
				m_angleFlag = 0;
			}
			if (m_angleFlag != 0)
			{
				if (m_angleFlag == 1)
				{
					m_angle -= 0.05f * deltaTime;
					if (m_angle <= 0)
					{
						m_angle = 0;
						m_angleFlag = 0;
						m_masterSparkEnd = true;
						moveSpeed = t_moveSpeed;
					}
				}
				if (m_angleFlag == 2)
				{
					m_angle += 0.05f * deltaTime;
					if (m_angle >= 0)
					{
						m_angle = 0;
						m_angleFlag = 0;
						m_masterSparkEnd = true;
						moveSpeed = t_moveSpeed;
					}
				}
			}
			m_animation.setAngle(m_angle);
			
		}
		
	}
	
}

void F_Player::registerExplosionRing(std::vector<ExplosionRing> * rings)
{
	m_exlosions = rings;
}

void F_Player::updateEnergyLocked(float deltaTime)
{

	if (m_energy <= 0.0f)
	{
		m_energyLocked = true;
		m_energyCounter = 0.0f;
		m_pernaltyRate = 0.9f;
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
			m_pernaltyRate = 1.7f;
		}
	}
	
	
}

void F_Player::escapeVelocity(int segment,float trailThreshold)
{
	m_velocitySegment = segment;
	mt_pos = m_pos;
	m_trailPos = mt_pos;
	m_isControlable = false;
	isLocked = false;
	moveHor = false;
	moveVer = false;
	isMove = false;

	m_firstVelocity = true;
	m_isPathDeciced = false;
	m_velocityDesRate = 1.0f;
	m_velocityDelayTimer = 3.5f;
	m_velocityEscapeSpeed = 0.1f;
	m_trailThreshold = trailThreshold;
	m_velocotyEscapeLaserTrailSet = false;
	m_starTrails.setTrailThreshold(m_trailThreshold);
	m_starTrails.setLeaveTrail(true);
	m_vel = glm::vec2(0);
}

void F_Player::updateEscapeVelocity(float deltaTime)
{
	if (m_velocitySegment > 0)
	{
		m_playerState = 0;
		if (!m_isPathDeciced)
		{
			tg_pos = calculateNextLocation(m_pos, m_velocitySegment);
			t_direction = glm::normalize(tg_pos - m_pos);
			//std::cout << "break " << m_velocitySegment << " \n";
			m_velocityTimer = 0;
			m_velocitySegment--;
			m_velocityEscapeSpeed += 0.05f;
			m_isPathDeciced = true;
			m_velocityDelayTimer -= 0.2f;
			m_velocityDelayTimer =std::max(m_velocityDelayTimer, 0.1f);
			m_trailThreshold *= 0.6f;
			//m_trailThreshold -= 0.15f;
			m_trailThreshold = std::max(m_trailThreshold, 0.07f);
			m_starTrails.setTrailThreshold(m_trailThreshold);
		
			if (m_velocitySegment > 0)
			{
				//addDistorionEffect(m_pos - glm::vec2(0, -50), .8f, 9.5f, 0.0f, 0.01f, 0.0001f);
				if (m_velocitySegment == 1)
				{
					addDistorionFollowEffect(&m_pos, .8f, 9.5f, -5.0f, 0.01f, 0.01f);
				}
				else
				{
					m_logicCamera->startShake(1.5f, 12.0f, 2.0f);
				}
				
				
			}
			if(m_velocitySegment ==0)
			{

				//addDistorionEffect(m_pos - glm::vec2(0, -50), .8f, 9.5f, 0.0f, 0.01f, 0.0001f);
				//addDistorionEffect(m_pos, 7.5f, 15.5f, 0.0f,0.0125f, 0.0125f);
				
			}
			
		}
		else 
		{
			m_velocityTimer += 0.1f * deltaTime;
			if (m_velocityTimer > m_velocityDelayTimer)
			{
				m_isPathDeciced = false;
				m_velocotyEscapeLaserTrailSet = false;
				m_angle = 0;
				m_animation.setAngle(m_angle);
				return;
			}
			m_trailPos +=  t_direction * m_velocityEscapeSpeed * 0.85f * glm::distance(m_pos, tg_pos) * deltaTime;
			m_pos += t_direction * m_velocityEscapeSpeed * glm::distance(m_pos, tg_pos) * deltaTime;
			
			m_angle = atan2(t_direction.y, t_direction.x) -degreeToRad(90);
			//std::cout << m_angle << "\n";
			if (!m_velocotyEscapeLaserTrailSet)
			{

				float randomR = feint_common::Instance()->randomFloat(0.7f, 1.3f);
				float randomG = feint_common::Instance()->randomFloat(0.7f, 1.3f);
				float randomB = feint_common::Instance()->randomFloat(0.7f, 1.3f);
				Feintgine::Color tfColor = Feintgine::Color(255, 255, 255, 255);
				m_starTrails.spawnLaserTrait(m_pos, glm::vec3(20.0f, 25.0f, 15.0f),
					((int)feint_common::Instance()->getRandomNum(0,15) + 2 )%15,
					/*Feintgine::Color(randomR * 255.0f, randomG * 255.0f, randomB * 255.0f, 255)*/tfColor
					, m_angle);
				m_velocotyEscapeLaserTrailSet = true;
				m_dashSoundEffect.playInChannel(0, 4);
			}
			m_animation.setAngle(m_angle);
		}
		
		
		//if(tg_pos)
	}
	else
	{
		m_starTrails.setLeaveTrail(false);
		m_isControlable = true;
		isLocked = true;
		m_afterImageParticle.setTotalTrace(10);
		m_afterImageParticle.setTraceInterval(0.3);
		
	}
}



void F_Player::clearData()
{

	if(m_yin_yang_orb)
	{
		delete m_yin_yang_orb;
		m_yin_yang_orb = nullptr;
	}
	if(m_yin_yang_orb_ex)
	{
		delete m_yin_yang_orb_ex;
		m_yin_yang_orb_ex = nullptr;
	}
	if(m_masterSpark)
	{
		delete m_masterSpark;
		m_masterSpark = nullptr;
	}

	for(int i =0 ; i < m_spells.size(); i++)
	{
		m_spells.erase(m_spells.begin() + i);
	}
	m_spells.clear();
	m_spellSelector.clearAllSpells();
}

void F_Player::spawnTrail(float deltaTime)
{
	
}

void F_Player::activeSpell()
{
	m_fantasy_seal.loadDesciption(m_spellSelector.getSpellcards()[m_spellSelector.getCurrentSelection()]->getSignName(),
		m_spellSelector.getSpellcards()[m_spellSelector.getCurrentSelection()]->getSpellName(),
		m_spellSelector.getCurrentSelectCard()->getID());


	if (m_spellSelector.getSpellcards()[m_spellSelector.getCurrentSelection()]->getGrazeCost() > 150)
	{
		m_spells.push_back(m_fantasy_seal);

	}
	m_spellcardCastSoundEffect.playInChannel(0, 3);


	switch (m_spellSelector.getCurrentSelectCard()->getID())
	{
	case SPELL_ID::Fantasy_Orb: 
	{
		std::cout << "Fantasy Orb \n";
		F_Reimu_Fantasy_Seal_Obj obj;
		obj.init(
			Feintgine::SpriteManager::Instance()->getSprite("reimu_projectile/reimu_57.png"),
			m_pos, glm::vec2(42, 42), Feintgine::Color(255, 255, 255, 255));
		int spawnCount = 8;
		if(m_logicCamera)
		{
			m_logicCamera->startShake(10, 2, 2);
		}
		//m_afterImageTime = 20.0f;
		obj.registerParticleBatch(m_leftAccessory.getParticleBatch());
		obj.registerExplosionRing(m_exlosions);
		obj.registerAudioEngine(m_audioEngine);
		obj.setScale(1.8f);
		obj.setDMG(1.25);
		obj.setAttenuation(glm::vec3(9, 16, 22));
		obj.registerEffectBatch(m_effectBatch);
		obj.setDeathCallback([&] {
			//std::cout << "end \n";
			m_logicCamera->startShake(4.0, 3.0f, 3.0f);
			m_effectBatch->addRippleEffectContinuos(&obj.getPos(), .5f, 15.5f, 0.0f, 0.001f, 0.01f);
		});
		for (int i = 0; i < spawnCount; i++)
		{

			obj.setCircleAngle(i * degreeToRad(360 / spawnCount));
			obj.setLightID(i % 6);
			obj.setLifeTime(28, 5.5f);
			m_flyOrb.push_back(obj);
		}
		break;
	}
	case SPELL_ID::Fantasy_Seal:
	{
		F_Reimu_Fantasy_Seal_Obj obj;
		obj.init(
			Feintgine::SpriteManager::Instance()->getSprite("reimu_projectile/reimu_57.png"),
			m_pos, glm::vec2(42, 42), Feintgine::Color(255, 255, 255, 255));
		int spawnCount = 12;
		if(m_logicCamera)
		{
			m_logicCamera->startShake(10, 2, 2);
		}
		//m_afterImageTime = 20.0f;
		obj.registerParticleBatch(m_leftAccessory.getParticleBatch());
		obj.registerExplosionRing(m_exlosions);
		obj.registerAudioEngine(m_audioEngine);
		obj.setScale(2.5f);
		obj.setDMG(2.55);
		obj.setAttenuation(glm::vec3(14, 22, 22));
		obj.registerEffectBatch(m_effectBatch);
		obj.setDeathCallback([&] {
			m_logicCamera->startShake(4.0, 3.0f, 3.0f);
			//m_effectBatch->addRippleEffect(obj.getPos(), .6f, 2.5f, -15.0f, 0.0025f, 0.0025f);
			m_effectBatch->addRippleEffectContinuos(&obj.getPos(), .5f, 15.5f, 0.0f, 0.002f, 0.02f);

		});
		for (int i = 0; i < spawnCount; i++)
		{

			obj.setCircleAngle(i * degreeToRad(360 / spawnCount));
			obj.setLightID(i % 6);
			obj.setLifeTime(40, 5.5f);
			m_flyOrb.push_back(obj);
		}
		break;
	}

	case SPELL_ID::Demon_Binding_Circle:
	{

		m_binding_circle->init("Assets/F_AObjects/evil_sealing_circle.xml",
			"Assets/F_AObjects/evil_sealing_circle_support.xml",
			glm::vec2(m_pos.x, 0), glm::vec2(400, 800), Feintgine::Color(255, 255, 255, 200));
		m_binding_circle->setLifeTime(27.0f);
		addDistorionFollowEffect(m_binding_circle->getOffsetPosPointer(), .7f, 8.5f, -135.0f, 0.001f, 0.0007f);
		addDistorionFollowEffect(m_binding_circle->getPosPointer(), .6f, 9.5f, -135.0f, 0.001f, 0.0007f);
		
	}
	break;

	case SPELL_ID::Purification_Rod:
	{
		m_rod.init(Feintgine::ResourceManager::getTexture("Assets/Lazy/rod.png"),
			Feintgine::Color(255, 255, 255, 255), glm::vec2(1.3f), degreeToRad(180));
		m_rod.setMaxAngle(degreeToRad(-20));
		m_afterImageParticle.clear();
		m_afterImageParticle.setTotalTrace(10);
		m_afterImageParticle.setTraceInterval(0.3f);
		m_afterImageTime = 5.0f;
		m_logicCamera->startShake(4.0, 2.0f, 2.0f);
		addDistorionFollowEffect(&m_pos, .8f, 9.5f, -5.0f,0.01f, 0.01f);
	}
	break;

	case SPELL_ID::s_Yin_Yang_Orb:
	{
		if (m_yin_yang_orb)
		{
			m_yin_yang_orb->spawn(m_pos, 32.0f, glm::vec2(0, 1.2f));
		}
		m_logicCamera->startShake(30.0, 2.0f, 1.0f);
		addDistorionFollowEffect(m_yin_yang_orb->getPosPointer(), .4f, 6.5f, -150.0f, 0.0011f, 0.0005f);

	}
	break;
	case SPELL_ID::Yin_Yang_Sancitifier_Orb:
	{
		if (m_yin_yang_orb_ex)
		{
			m_yin_yang_orb_ex->spawn(m_pos, 32.0f, glm::vec2(0, 1.2f));
			//addDistorionEffect(m_pos, .8f, 9.5f, -5.0f);
		}

		addDistorionFollowEffect(m_yin_yang_orb_ex->getPosPointer(), .3f, 7.5f, -300.0f, 0.0011f, 0.0005f);
		m_logicCamera->startShake(99.0, 2.0f, 1.0f);
	}
	break;

	case SPELL_ID::Youkai_Seal:
	{
		//std::cout << "called \n";
		m_sealingAmulet.setPos(m_pos);
		m_sealingAmulet.setAlive(true);
		m_sealingAmulet.setLifeTime(40);
		m_sealingAmulet.setIsDone(false);
		m_sealingAmulet.setBulletAnimationAction("idle");
	}

	break;

	case SPELL_ID::Master_Spark:
	{
		m_masterSpark->spawn();
		m_logicCamera->startShake(32.0, 12.0f, 12.0f);
		m_speedPelnaty = 0.25f;
		m_masterSparkTime = m_masterSpark->getLifeTime();
		m_masterSparkEnd = false;
		m_isAttack = false;
		m_leftAccessory.setFire(false);
		m_rightAccessory.setFire(false);

		addDistorionFollowEffect(&m_pos, .2f, 3.0f, -150.0f, 0.0011f, -0.0005f);
	}
	break;

	case SPELL_ID::Meteoric_Shower:
	{
		m_starSpawner.spawn(15, 1.0f, 0.6f);
		m_logicCamera->startShake(19.0, 4.0f, 4.0f);
	}
	break;

	case SPELL_ID::Luminous_Strike:
	{
		m_luminousLauncher.chargeStar(20);
		m_afterImageParticle.clear();
		m_afterImageParticle.setTotalTrace(10);
		m_afterImageParticle.setTraceInterval(0.3f);
		m_afterImageTime = 12.0f;
		m_logicCamera->startShake(9.0, 5.0f, 5.0f);
	}
	break;
	case SPELL_ID::Orreries_Sun:
	{
		m_suns.spawn(4, 68);
	}
	break;

	case SPELL_ID::Non_Directional_Laser:
	{
		m_suns.activeNondirectionLaser();
		m_logicCamera->startShake(30.0, 7.0f, 8.0f);
		m_speedPelnaty = 0.5f;
		m_masterSparkTime = 30;
		m_masterSparkEnd = false;
		m_isAttack = false;
		m_leftAccessory.setFire(false);
		m_rightAccessory.setFire(false);
	}
	break;

	case SPELL_ID::Stardust_Reverie:
	{
		escapeVelocity(6,1.2f);
		m_afterImageParticle.clear();
		m_afterImageTime = 20.0f;
		m_afterImageParticle.setTotalTrace(20);
		m_afterImageParticle.setTraceInterval(0.05f);


		addDistorionEffect(m_pos - glm::vec2(0,-50), .8f, 9.5f, -5.0f, 0.01f, 0.0001f);
		//addDistorionEffect(m_pos, .4f, 5.5f, -5.0f,0.125f, 0.125f);
	}
	break;
	case SPELL_ID::Escape_Velocity:
	{
		// 12
		escapeVelocity(33,2.0f);
		m_afterImageParticle.clear();
		m_afterImageTime = 45.0f;
		m_afterImageParticle.setTotalTrace(50);
		m_afterImageParticle.setTraceInterval(0.025f);

		addDistorionEffect(m_pos - glm::vec2(0, -50), .8f, 9.5f, -5.0f, 0.01f, 0.0001f);

		//addDistorionEffect(m_pos, .6f, 7.5f, 0.0f, 0.25f, 0.25f);
	}
	break;

	default:
		break;
	}

}

float F_Player::decideDestination(float Xpos)

{
	float returnVal;

	if (Xpos >= 0)
	{
		returnVal = -BORDER - 50;
	}
	else
	{
		returnVal = BORDER + 50;
	}
	return returnVal;
}

void F_Player::loadRecord(const std::string & filePath)
{
	std::ifstream infile(filePath.c_str());

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		double  a, b, c, d;
		if (!(iss >> a >> b >> c >> d))
		{
			break;
					
		}
		else
		{
			recordedState newRecord;
			newRecord.state = a;
			newRecord.startTime = b;
			newRecord.x_pos = c;
			newRecord.y_pos = d;
			m_loadedRecordedStates.push_back(newRecord);
		}

	}
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		double  a, b;
		if (!(iss >> a >> b ))
		{
			break;
		}
		else
		{
			recordedAction newAction;
			newAction.tAction = a;
			newAction.time = b;
			m_loadedRecordedActions.push_back(newAction);
		}

	}

	m_isReplay = true;
	m_currentRecordState = 0;
	m_currentRecordAction = 0;
	m_playerState = 0;
	m_PlayerAction = 0;
	m_currentTick = ENGINE_current_tick;
	//t_start = SDL_GetTicks();
	std::cout << m_loadedRecordedActions.size() << " !!!!!!!\n";
	infile.close();
}

void F_Player::writeRecord(const std::string & filePath)
{
// 	if (m_recordedStates.size() > 0)
// 	{
// 		m_recordedStates[m_recordedStates.size() - 1].endTime = SDL_GetTicks();
// 	}
	std::ofstream myfile(filePath.c_str());

	if (myfile.is_open())
	{
		std::string str;
		for (int i = 0; i < m_recordedStates.size(); i++)
		{
			str = "";
			str += std::to_string(m_recordedStates[i].state);
			str += " " + std::to_string(m_recordedStates[i].startTime) + " " +std::to_string(m_recordedStates[i].x_pos) \
				 + " " + std::to_string(m_recordedStates[i].y_pos);
			myfile << str << "\n";
		}
		myfile << "\n";
		for (int i = 0; i < m_recordedActions.size(); i++)
		{
			str = "";
			str += std::to_string(m_recordedActions[i].tAction);
			str += " " + std::to_string(m_recordedActions[i].time);
			myfile << str << "\n";
		}
		std::cout << "written to " << filePath.c_str() << "\n";
		myfile.close();
	}
	else std::cerr << "Unable to open file";
}

// void F_Player::loadRecord(F_RecordPlayer * records)
// {
// 	m_recordPlayer = records;
// }

glm::vec2 F_Player::calculateNextLocation(const glm::vec2 & currentLoction,
	int & segmenntIndex)
{
	glm::vec2 returnValue;

	if (m_velocityDesRate < 0.0f)
	{
		m_velocityDesRate = 0.8f;
	}
	if (m_firstVelocity)
	{
		//std::cout << "first\n";
		m_firstVelocity = false;
		returnValue = glm::vec2(currentLoction.x, BORDER + 50); // hit out of the screen;
		
	}
	else
	{

		if (segmenntIndex > 2) // calculate next spot
		{
			returnValue = glm::vec2(decideDestination(currentLoction.x),
				(BORDER * m_velocityDesRate) + feint_common::Instance()->getRandomNum(-50,50)); // 
		}
		else	// return to startedPos
		{
			//std::cout << "back to original \n";
			returnValue = mt_pos; //glm::vec2(mt_pos.x, -BORDER + 100); // return to previous pos
			//std::cout << feint_common::Instance()->convertiVec2toString(returnValue) << "\n";
		}
	}
	m_velocityDesRate -= 0.2f;
	//segmenntIndex--;
	return returnValue;
}

void F_Player::updateState(float deltaTime)
{
	if (m_isReplay)
	{
		recordUpdate(deltaTime);
		//return; 
	}
	if (m_playerState & PLAYER_STATE_IS_FIRE)
	{
		if (m_masterSparkEnd)
		{

			m_isAttack = true;
			m_leftAccessory.setFire(true);
			m_rightAccessory.setFire(true);
			m_suns.setFire(true);
		}
	}
	else/*if (!(m_playerState & PLAYER_STATE_IS_FIRE))*/
	{
		m_isAttack = false;
		m_leftAccessory.setFire(false);
		m_rightAccessory.setFire(false);
		m_suns.setFire(false);
	}
	if (m_playerState & PLAYER_STATE_MOVE_LEFT)
	{
		m_vel.x = -moveSpeed;
		if (!alreadySetLeft)
		{
			m_animation.playAnimation("left");
			alreadySetLeft = true;
			alreadySetRight = false;
		}
		moveHor = true;
		isIdled = false;
	}
	if (m_playerState & PLAYER_STATE_MOVE_RIGHT)
	{
		m_vel.x = moveSpeed;
		if (!alreadySetRight)
		{
			m_animation.playAnimation("right");
			alreadySetRight = true;
			alreadySetLeft = false;
		}
		moveHor = true;
		isIdled = false;
	}
	if (m_playerState & PLAYER_STATE_MOVE_UP)
	{
		m_vel.y = moveSpeed;
		moveVer = true;
	}
	if (m_playerState & PLAYER_STATE_MOVE_DOWN)
	{
		m_vel.y = -moveSpeed;
		moveVer = true;
	}

	if (!(m_playerState & PLAYER_STATE_MOVE_LEFT) && !(m_playerState & PLAYER_STATE_MOVE_RIGHT))
	{
		moveHor = false;
	}
	if (!(m_playerState & PLAYER_STATE_MOVE_DOWN) && !(m_playerState & PLAYER_STATE_MOVE_UP))
	{
		moveVer = false;
	}
// 	if (moveVer && moveHor)
// 	{
// 		m_vel *= 0.5f * deltaTime;
// 	}
	if (!moveHor)
	{
		m_vel.x = 0;

		if (!isIdled)
		{
			m_animation.playAnimation("idle");
			isIdled = true;
		}
		alreadySetRight = false;
		alreadySetLeft = false;
	}
	if (!moveVer)
	{

		m_vel.y = 0;
	}
	if (m_playerState & PLAYER_STATE_IS_FOCUS)
	{
		m_vel *= 0.5f ;
		m_leftAccessory.setBoolFocus(true);
		m_rightAccessory.setBoolFocus(true);
		m_suns.setFocus(true);
	}
	else
	{
		m_leftAccessory.setBoolFocus(false);
		m_rightAccessory.setBoolFocus(false);
		m_suns.setFocus(false);
	}

	switch (m_PlayerAction)
	{
	case PLAYER_ACTION_USE_SPELL:
		activeSpell();
		//if (m_isReplay)
		//{
			m_PlayerAction = 0;
		//}
		
		break;
	case PLAYER_ACTION_SWITCH_SPELL_PREVIOUS:
		m_spellSelector.changeSpellcardBackward();
		//if (m_isReplay)
		//{
		m_PlayerAction = 0;
		//}
		break;
	case PLAYER_ACTION_SWITCH_SPELL_FORWARD:
		m_spellSelector.changeSpellcardForward();
		//if (m_isReplay)
		//{
		m_PlayerAction = 0;
		//}
		break;
	default:
		break;
	}
}

void F_Player::recordUpdate(float deltaTime)
{
	
		//m_playerState = 0;
		//m_PlayerAction = 0;
		m_currentTick = ENGINE_current_tick;
	//	std::cout << "play from record \n";
		if (m_currentRecordState >= m_loadedRecordedStates.size())
		{
			return;
		}
		if (m_currentTick  >= m_loadedRecordedStates[m_currentRecordState].startTime - 0.1f)
		{
			m_playerState = m_loadedRecordedStates[m_currentRecordState].state;
			m_pos = glm::vec2(m_loadedRecordedStates[m_currentRecordState].x_pos, m_loadedRecordedStates[m_currentRecordState].y_pos);
			m_currentRecordState++;
// 			if (m_currentTick >= m_loadedRecordedStates[m_currentRecordState].endTime - 0.5f)
// 			{
// 				m_currentRecordState++;
// 			}
		}
		if (m_currentRecordAction >= m_loadedRecordedActions.size())
		{
			return;
		}
		if (m_currentTick >= m_loadedRecordedActions[m_currentRecordAction].time)
		{

			m_PlayerAction = m_loadedRecordedActions[m_currentRecordAction].tAction;
			m_currentRecordAction++;
			
		}
		
	//ENGINE_current_tick
}

void F_Player::addDistorionEffect(const glm::vec2 & pos, float size, float freq, float lifeTime, float sizeRate, float freqRate)
{
	m_effectBatch->addRippleEffect(pos, size, freq, lifeTime,  sizeRate, freqRate);
}

void F_Player::addDistorionFollowEffect(glm::vec2 * pos, float size, float freq, float lifeTime, float sizeRate, float freqRate)
{
	m_effectBatch->addRippleEffectContinuos(pos, size, freq, lifeTime, sizeRate, freqRate);
}

void F_Player::setCharacterSpell(unsigned int value)
{
	m_characterType = value;
}

F_PlayerAccessory F_Player::getLeftAccessosry()
{	
	return m_leftAccessory;
	
}

F_PlayerAccessory F_Player::getRightAccesory()
{
	return m_rightAccessory;
}
