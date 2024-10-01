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
#include "EmptyObject.h"
#include <feint_common.h>
#include <chrono>
#include <thread>
#include <SDL_TextRenderer.h>
#include <feint_common.h>
#include <TextRenderer.h>
#include "F_Player.h"
#include "F_EnemyBasic.h"
#include <F_AnimatedObject.h>
#include <SpriteFont.h>
#include <F_oEvent.h>
#include <ParticleEngine2D.h>
#include <ParticleBatch2D.h>
#include <AudioEngine.h>
#include <LightBatch.h>
#include <thread>
#include <deque>

#include <Timing.h>
#include <FTimer.h>
#include <FrameCounter.h>

#include "IlluminateLight.h"
#include "PauseMenu.h"
#include "TitleLabel.h"
#include "FairyBase.h"
#include "ExplosionRing.h"
#include "EnemyBulletBase.h"
#include "GlobalValueClass.h"
#include "LivingLabel.h"
#include "BGMLabel.h"
#include "BackGroundMap.h"
#include "Light.h"
#include "F_Player_Reimu.h"
#include "EGUI_TextRenderer.h"
#include "KanjiEffectManager.h"
#include "EnemyGuardian.h"
#include "EnemyAmplifier.h"
#include "LinkCreator.h"
#include "F_Boss_Base.h"

#include "EGUI_ChapterLabel.h"
#include "EGUI_BGMLabel.h"
#include <FrameBuffer.h>
#include <FrameBufferScreen.h>
#include <EffectBatch.h>
#include "F_PlayerRecorder.h"
#include "F_RecordPlayer.h"


#include <EGUI_DrawElement.h>	

#include "GlobalValueClass.h"

#include "BulletManupilator.h"

#include <F_ShaderEventHandler.h>

#include <F_ScreenCapture.h>

#include <F_IMGUI.h>

#include <async++.h>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SDL-TTF-OpenGL3.hpp>

#include "BGM_Label.h"
#include "Chapter_Label.h"

#include <csignal>

enum ShaderValueType
{
	T_Float,
	T_Int,
	T_Vec2,
	T_Vec3,
	T_Undefined
};


class Extra_DemoScreen : public Feintgine::IGameScreen
{
public:
	Extra_DemoScreen();
	~Extra_DemoScreen();


	Extra_DemoScreen(Feintgine::Window * window );

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	virtual void checkInput() override;

	void handleInput(Feintgine::InputManager & inputManager);

	void firstCheckPoint();

	void drawLoadingScreen();

	void drawGameplay();

	void drawBackground();

	void drawTimer();

	void drawGUIText();

	void drawCustomShader();

	void drawHitboxes();

	void addExplosion(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos,
		const glm::vec2 & scale, const glm::vec2 & explosionRate,
		const Feintgine::Color & color, float depth, float liveRate = 0.1f);


	virtual void reloadLevel();

	void loadLevel(const std::string & filePath);

	void e_darkeningScene(float maxVal, float rate);

	void getDropInstances(const std::string & value, std::vector<int> & data, int maxCount);

	void turnLight(bool val);

	void initShader();

	void switchShader();

	void drawBackup();

	void toggleLightAE();

	void toggleBalanceLight();



	// pause

	void togglePause();

	void togglePauseLogic();


	void toggleLight();

	void toggleCTRL();


	void updateShader(float deltaTime);

	void updateShaderCamera(float deltaTime);


protected :



	Feintgine::Window * m_window = nullptr;
	Feintgine::Camera2D m_camera;
	Feintgine::Camera2D m_sideCam;

	Feintgine::SpriteBatch m_spriteBatch;
	Feintgine::SpriteBatch m_timerSpriteBatch;

	Feintgine::DebugRender m_debug;

	Feintgine::GLSLProgram m_shader;
	Feintgine::GLSLProgram m_shaderNormal;


	Feintgine::GLSLProgram m_blackWhiteShader;
	Feintgine::GLSLProgram m_whiteBlackShader;

	Feintgine::GLSLProgram * m_foregroundShader = nullptr;
	Feintgine::GLSLProgram * m_backgroundShader = nullptr;

	Feintgine::SDL_TextRenderer m_sdlTextrenderer;

	Feintgine::GLSLProgram m_lightShader;
	Feintgine::GLSLProgram m_ambientShader;
	Feintgine::GLSLProgram m_magicalShader;
	Feintgine::GLSLProgram m_crystalShader;
	Feintgine::GLSLProgram m_glitchShader;


	Feintgine::GLSLProgram m_portalShader;

	Feintgine::GLSLProgram * m_currentEffect;

	std::vector<glm::vec2> m_lightPos;
	std::vector<glm::vec4> m_lightColor;
	std::vector<glm::vec2> m_lightUV;


	float m_shaderTime = 0.0f;
	float dayLight = 1.0;

	std::vector<glm::vec2> m_lightListPos;
	std::vector<glm::vec4> m_lightListColor;
	std::vector<glm::vec3> m_lightListAttenuation;

	Feintgine::LightBatch m_lightBatch;

	std::vector<FairyBase *> m_enemies;
	std::vector<EnemyGuardian *> m_guardians;
	std::vector<EnemyAmplifier *> m_amplifiers;



	EmptyObject bg; // higan skin
	EmptyObject bg1; // shadowing
	EmptyObject bg2; // shadowing


	// loading benchmark
	Uint32 t_start;
	double t_duration;
	Uint32 t_now;
	bool isDone = true;

	F_Player m_player;

	BackGroundMap m_bg;

	BackGroundMap m_bg2;

	Feintgine::ParticleEngine2D m_particleEngine;

	PauseMenu m_pauseMenu;

	Feintgine::Music m_music;

	Feintgine::AudioEngine m_audioEngine;

	std::vector<ExplosionRing> m_exlosions;
	std::vector<LivingLabel *> m_labels;

	std::vector<EnemyBulletBase *> m_bullets;


	Feintgine::SpriteFont * m_spriteFont;

	bool loaded = false;

	bool m_blackWhiteMode = false;

	bool startLoad = false;

	bool m_showHitBox = true;

	bool startCount = false;

	bool changeLight = false;

	bool lightPositive = false;

	bool lightChange = false;

	bool is_lightOn = false;

	float m_lightMaxVal;

	float m_lightRate;

	Feintgine::FTimer m_timer;
	Feintgine::FrameCounter fcounter;

	Feintgine::F_ScreenCapture m_capture;

	//CEGUI_TextRenderer m_CEGUI_textRenderer;
	//CEGUI_TextRenderer m_CEGUI_textRenderer2;
	KanjiEffectManager m_kanjiEffectManager;



	// text render fix
	// EGUI_DrawElement m_text_realTime;
	tgui::Label::Ptr m_text_realTime_tgui;
	// EGUI_DrawElement m_text_fps;
	tgui::Label::Ptr m_text_fps_tgui;
	// EGUI_DrawElement m_text_eventTime;
	tgui::Label::Ptr m_text_eventTime_tgui;


	tgui::Label::Ptr m_text_load;


	// EGUI_DrawElement m_text_spellName;
	tgui::Label::Ptr m_text_spellName;
	// EGUI_DrawElement m_text_spellSign;
	tgui::Label::Ptr m_text_spellSign;

	// portal shader effect
	float m_reachTimer = 0.0f;
	int m_reach = 100;
	float m_portalAlpha = 0.0f;

	// CEGUI_ChapterLabel m_chapterLabel;
	// CEGUI_BGMLabel m_bmLabel;
	BGM_Label m_bgmLabel;

	Chapter_Label m_chapterLabel;
	

	LinkCreator m_linkCreator;

	// ===== Cloud Camera Control Start	
	glm::vec3 m_lookDir = glm::vec3(1.0f, 0, 0.f);// glm::vec3(0, 0.0f, 0.0f); glm::vec3(1.f, -0.45f, 0.f);
	glm::vec3 m_camVel  = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_forwardCamVel = glm::vec3(-3.0f, 0.0f, 0.0f);

	int m_cloudCameraViewFlag = 0;

	const int CLOUD_CAM_ROT_LEFT = 1;
	const int CLOUD_CAM_ROT_RIGHT = 2;	
	const int CLOUD_CAM_ROT_UP = 4;
	const int CLOUD_CAM_ROT_DOWN = 8;

	int m_cloudCameraPosFlag = 0;

	const int CLOUD_CAM_MOVE_LEFT = 1;
	const int CLOUD_CAM_MOVE_RIGHT = 2;
	const int CLOUD_CAM_MOVE_UP = 4;
	const int CLOUD_CAM_MOVE_DOWN = 8;

	Feintgine::F_ShaderEventHandler m_shaderEventHandler;
	Feintgine::F_ShaderEventBase * m_shaderDirection;
	Feintgine::F_ShaderEventBase * m_shaderVel;
	Feintgine::F_ShaderEventBase * m_cloudAlpha;

	float speed = 3.0f;

	bool isControlMode = true;
	
	// ===== Cloud Camera Control End

	float t_time = 0.0f;

	std::thread m_captureThread;

	bool startThread = false;

	Uint32 t_currentTick = 0;// SDL_GetTicks();
	Uint32 t_prevTick = 0;

	float t_counter = 0;
	F_PlayerRecorder m_recorder;

	F_RecordPlayer m_recordPlayer;

	Feintgine::FrameBuffer m_frameBuffer;

	Feintgine::FrameBufferScreen m_frameBufferScreen;

	Feintgine::EffectBatch m_effectBatch;

	BulletManupilator bulletManipulator;

	tgui::Gui * m_tgui;
	tgui::Gui * m_tgui_load;


	
};

