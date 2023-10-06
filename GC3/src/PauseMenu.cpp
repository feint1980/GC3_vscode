#include "PauseMenu.h"



PauseMenu::PauseMenu()
{
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::init()
{
	m_pauseLabelKanji = L"一時停止";
	m_pauseLabelEng = L"Pause";
	m_tittle = L"東方幻想郷の";
	bg.init( Feintgine::ResourceManager::getTexture("Assets/Textures/shadowing.png"), glm::vec2(0), glm::vec2(800, 800), Feintgine::Color(0, 0, 0, 100));
	bg.setDepth(20);

	m_pauseSound =    Feintgine::AudioEngine::getInstance()->loadSoundEffect("Sounds/sfx/pause.wav");
}

void PauseMenu::drawBG(Feintgine::SpriteBatch & spriteBatch)
{
	bg.draw(spriteBatch);
}

void PauseMenu::drawContext(TextRenderer & textRenderer, const Feintgine::Camera2D & cam)
{
	textRenderer.renderText(cam, m_pauseLabelKanji, glm::vec2(0, 0),
		Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);
	textRenderer.renderText(cam, m_pauseLabelEng, glm::vec2(0, -50),
		Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);
	textRenderer.renderText(cam, m_tittle, glm::vec2(0, 120),
		Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);
}

void PauseMenu::togglePause()
{
	if (m_isPause)
	{
		m_isPause = false;
	}
	else
	{
		m_isPause = true;
		m_pauseSound.play();
	}
}
