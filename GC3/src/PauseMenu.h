#pragma once
#include "EmptyObject.h"
#include <SpriteBatch.h>
#include <TextRenderer.h>
#include <ResourceManager.h>
#include <AudioEngine.h>

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void init();

	void drawBG(Feintgine::SpriteBatch & spriteBatch);
	void drawContext(TextRenderer & textRenderer, const Feintgine::Camera2D & cam);
	void togglePause();
	void playSound();
	bool isPause() const { return m_isPause; }
private :
	std::wstring m_pauseLabelKanji;
	std::wstring m_pauseLabelEng;
	std::wstring m_tittle;
	EmptyObject bg;

	Feintgine::SoundEffect m_pauseSound;
	bool m_isPause = false;
};

