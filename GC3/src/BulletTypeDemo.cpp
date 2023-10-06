#include "BulletTypeDemo.h"



BulletTypeDemo::BulletTypeDemo()
{
}


BulletTypeDemo::~BulletTypeDemo()
{
}

void BulletTypeDemo::init(Feintgine::AudioEngine & audioEngine)
{
	glm::vec2 decidedPos(-440, 100);
	glm::vec2 playerPos(-440, 0);
	m_reimu.init("Assets/F_AObjects/reimu.xml", "character/reimu_accessory_1.png");
	m_reimu.setPrimaryShot(true, "Assets/F_AObjects/reimu_normal_projectile.xml", 5.0f, 90.0f);
	m_reimu.setAccessoryShot(1);

	m_marisa.init("Assets/F_AObjects/marisa.xml", "character/marisa_accessory_3.png");
	m_marisa.setPrimaryShot(true, "Assets/F_AObjects/marisa_normal_projectile.xml", 5.0f, 90.0f);
	m_marisa.setAccessoryShot(2);

	
	
	m_bg.init(Feintgine::ResourceManager::getTexture("Assets/Lazy/outline.png"),
		decidedPos, glm::vec2(480, 790));

	m_reimu.registerAudioEngine(&audioEngine);
	m_reimu.initSound();
	m_marisa.registerAudioEngine(&audioEngine);
	m_marisa.initSound();
	m_reimu.setVolume(0);
	m_marisa.setVolume(0);
	m_marisa.resetStack();
	m_reimu.resetStack();
	m_reimu.setPos(playerPos);
	m_marisa.setPos(playerPos);
	m_marisa.unlockState(false);
	m_reimu.unlockState(false);

// 	m_marisa.setParentColor(true);
// 	m_reimu.setParentColor(true);
}

void BulletTypeDemo::update(float deltaTime)
{
	
	
	switch (m_selection)
	{
		
	case IS_REIMU:
		m_reimu.setFire(true);
		m_marisa.setFire(false);
		m_marisa.resetStack();
		break;

	case IS_MARISA:
		m_marisa.setFire(true);
		m_reimu.setFire(false);
		m_reimu.resetStack();
		break;
	default:
		m_marisa.setFire(false);
		m_reimu.setFire(false);
		m_marisa.resetStack();
		m_reimu.resetStack();
		m_counter = 0.0f;
		break;
	}
	m_reimu.update(deltaTime, m_enemies, m_bullets, m_guardians, m_amplifiers);
	m_marisa.update(deltaTime, m_enemies, m_bullets, m_guardians, m_amplifiers);
	m_reimu.setFocus(isFocus);
	m_marisa.setFocus(isFocus);

	if (m_selection >= 0)
	{
		m_counter += m_rate * deltaTime;
		t_counter += m_rate * deltaTime;

	}
	
	if (m_counter >= 7.0f)
	{
		m_counter = 0.0f;
		toggleFocus();
	}
	if (t_counter >= 14.0f)
	{
		t_counter = 0.0f;
		toggleType();
		m_reimu.setAccessoryShot(m_reimuShootType);
		m_marisa.setAccessoryShot(m_marisaShootType);
	}


	if (m_isBGswitching)
	{
		if (m_isShowBG)
		{
			if (m_bg.changeColor(15, t_fadeRate * deltaTime, 1.0f))
			{
				
				//std::cout << "stop \n;"
				m_isBGswitching = false;
			}
		}
		else
		{
			if (m_bg.changeColor(15, -t_fadeRate * deltaTime, -0.01f))
			{
				
				//std::cout << "stop \n";
				m_isBGswitching = false;
			}
		}
	}
	if (m_isReimuswitching)
	{
		if (m_isShowReimu)
		{
			if (m_reimu.changeColor(15, t_fadeRate * deltaTime, 1.0f))
			{
				//std::cout << "stop \n;"
				m_isReimuswitching = false;
			}
		}
		else
		{
			if (m_reimu.changeColor(15, -t_fadeRate * deltaTime, -0.01f))
			{
				//std::cout << "stop \n";
				m_isReimuswitching = false;
			}
		}
	}
	if (m_isMarisaswitching)
	{
		if (m_isShowMarisa)
		{
			if (m_marisa.changeColor(15, t_fadeRate * deltaTime, 1.0f))
			{
				//std::cout << "stop \n;"
				m_isMarisaswitching = false;
			}
		}
		else
		{
			if (m_marisa.changeColor(15, -t_fadeRate * deltaTime, -0.01f))
			{
				//std::cout << "stop \n";
				m_isMarisaswitching = false;
			}
		}
	}
}

void BulletTypeDemo::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_bg.draw(spriteBatch);


	switch (m_selection)
	{

	case IS_REIMU:
		m_reimu.draw(spriteBatch);
		break;

	case IS_MARISA:
		m_marisa.draw(spriteBatch);
		break;
	default:

		break;
	}
	

	
}

void BulletTypeDemo::drawDecription(Feintgine::Camera2D & camera, TextRenderer & renderer)
{
	switch (m_selection)
	{

	case IS_REIMU:
		renderer.renderText(camera, L"Shrine Maiden of Paradise",
			m_reimu.getPos() + textOffset,
			m_reimu.getAnimation().getColor(), 0.35f, ALIGN_FT_CENTER);
		renderer.renderText(camera, L"Exterminate Youkai with homing amulet mini amulet",
			m_reimu.getPos() + textOffsetDescript,
			m_reimu.getAnimation().getColor(), 0.2f, ALIGN_FT_CENTER);
		break;

	case IS_MARISA:
		renderer.renderText(camera, L"Ordinary Magician",
			m_marisa.getPos() + textOffset,
			m_marisa.getAnimation().getColor(), 0.35f, ALIGN_FT_CENTER);
		renderer.renderText(camera, L"Can shoot out laser or rocket",
			m_marisa.getPos() + textOffsetDescript,
			m_marisa.getAnimation().getColor(), 0.2f, ALIGN_FT_CENTER);
		break;
	case IS_PATCHOULI:
		renderer.renderText(camera, L"Unmoving Great Library",
			m_reimu.getPos() + textOffset,
			Feintgine::Color(255,255,255,255), 0.35f, ALIGN_FT_CENTER);
		renderer.renderText(camera, L"Coming soon",
			m_reimu.getPos() + textOffsetDescript,
			Feintgine::Color(255, 255, 255, 255), 0.2f, ALIGN_FT_CENTER);
		break;
	default:

		break;
	}
}

void BulletTypeDemo::updateSelection(int val)
{
	m_selection = val;

	switch (m_selection)
	{

	case IS_REIMU:
		m_isShowBG = true;
		m_isShowReimu = true;
		m_isBGswitching = true;
		m_isReimuswitching = true;
		m_isMarisaswitching = true;
		m_isShowMarisa = false;
		break;

	case IS_MARISA:
		m_isShowBG = true;
		m_isShowMarisa = true;
		m_isBGswitching = true;
		m_isShowReimu = false;
		m_isMarisaswitching = true;
		m_isReimuswitching = true;
		break;
	default:
		
		m_isShowBG = false;
		m_isShowMarisa = false;
		m_isShowReimu = false;
		m_isBGswitching = true;
		m_isMarisaswitching = true;
		m_isReimuswitching = true;
		break;
	}

}

void BulletTypeDemo::toggleFocus()
{
	if (isFocus)
	{
		isFocus = false;
	}
	else
	{
		isFocus = true;
	}
}

void BulletTypeDemo::toggleType()
{
	if (m_marisaShootType == 2)
	{
		m_marisaShootType += 2;
	}
	else
	{
		m_marisaShootType -= 2;		
	}

	if (m_reimuShootType == 1)
	{
		m_reimuShootType += 2;
	}
	else
	{
		m_reimuShootType -= 2;
	}

}

