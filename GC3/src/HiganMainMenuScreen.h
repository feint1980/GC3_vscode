#pragma once
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>

#include <GLTexture.h>
#include <ResourceManager.h>
//#include <f_object.pb.h>
#include <iostream>
#include <IGameScreen.h>
#include <Window.h>
#include <InputManager.h>
#include <T_Scene.h>
#include <IMainGame.h>
#include "ScreenIndices.h"
#include "GC3_EmptyObject.h"
#include <feint_common.h>
#include <chrono>
#include <thread>
#include <SDL_TextRenderer.h>
#include <feint_common.h>
#include <TextRenderer.h>
#include <SpriteFont.h>
#include "CustomButton.h"
#include <AudioEngine.h>

#include "CharacterAvatar.h"

#include "AvatarSelection.h"
#include "BulletTypeDemo.h"
#include <F_Logger.h>
static float Higan_startupRate = 0.05f;
static float Higan_startdownRate = 0.05f;
static float Higan_textUpRate = 0.025f;


const int MAIN_MENU_STATE = 0;
const int SELECTION_STATE = 1;



class HiganMainMenuScreen : public Feintgine::IGameScreen
{
public:
	HiganMainMenuScreen();
	~HiganMainMenuScreen();

	HiganMainMenuScreen(Feintgine::Window * window);
	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	void handleInput(Feintgine::InputManager & inputManager);

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	void initShader();

	virtual void checkInput() override;

	void drawLoadingScreen();

	void drawBackground();

	void drawMainMenu();

	void drawAvat();

	void drawDemoType();

	void drawDemoText();

	void firstCheckPoint();

	void initGUI();

	void updateStartupEffect(float delta);

	void updateTextAlpha(float delta);

	void updatePanelStartUp(float delta);
	void updatePanelEnd(float delta);

	void fadeMainMenu(float delta);
	void showMainMenu(float delta);

	void showBackgound(float delta);
	void hideBackgound(float delta);

	void handleState(float delta);

	void switchState(int val);

	void handleBackPress();

	void updateTextPos(float delta);

private:

	Feintgine::Window * m_window;

	Feintgine::Camera2D m_camera;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::GLSLProgram m_shader;

	Feintgine::GLSLProgram m_selectScreenShader;

	GC3_EmptyObject bg;

	GC3_EmptyObject selectBg;

	TextRenderer m_textRenderer;
	TextRenderer m_textRendererEn;

	Feintgine::GLSLProgram m_shaderNormal;

	Feintgine::GLSLProgram m_avtShader;

	Feintgine::SpriteBatch m_timerSpriteBatch;

	Feintgine::SpriteFont * m_spriteFont;

	CustomButton m_startButton;
	CustomButton m_optionButton;
	CustomButton m_creditButton;
	CustomButton m_exitButton;
	CustomButton m_panelUnderstand;

	CEGUI::DefaultWindow * credit = nullptr;
	

	bool showOptions = false;


	CEGUI::GroupBox * notePanel = nullptr;
	CEGUI::DefaultWindow * panelBackground = nullptr;
	CEGUI::DefaultWindow * noteContent = nullptr;
	CEGUI::DefaultWindow * disclaimerContent = nullptr;
	Feintgine::GUI m_gui;

	Feintgine::GUI m_gui2;

	float m_effectAlpha = -6.0f;

	float m_backgoundAlpha = 0.0f;
	
	float textAlpha = 0.0f;

	bool peak = false;
	bool doneStartup = false;
	bool textAlphaDone = false;


	bool loaded = false;
	bool startLoad = false;
	bool effectDone = false;
	float withDraw = 0.0f;

	bool notePanelStart = false;
	float notePanelScale = 0.0f;
	bool notePanelEnd = false;

	bool showSelectionScreen = false;
	bool hideSelectionScreen = false;

	bool b_fadeMainMenu = false;
	bool b_showMainMenu = false;


	glm::vec2 m_titleJapTextPos_1;
	glm::vec2 m_titleEngTextPos_1;

	glm::vec2 m_titleJapTextPos_2;
	glm::vec2 m_titleEngTextPos_2;

	glm::vec2 currentJapTextPos; 
	glm::vec2 currentEngTextPos;

	float m_textScale;

	int previousState = 0;
	int currentScreenState = 0;


	CharacterAvatar m_reimu;
	CharacterAvatar m_marisa;
	CharacterAvatar m_patchouli;

	AvatarSelection m_avtSelection;

	BulletTypeDemo m_demoBoard;

	Feintgine::AudioEngine m_audioEngine;
};

