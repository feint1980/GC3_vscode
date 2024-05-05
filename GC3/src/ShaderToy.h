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
#include "IlluminateLight.h"
#include <Timing.h>
#include <FTimer.h>
#include <FrameCounter.h>

#include "F_Player_Reimu.h"

#include "EGUI_TextRenderer.h"

#include "KanjiEffectManager.h"

#include <Box2D/Box2D.h>

#include "B2ContactListener.h"

#include "EnemyGuardian.h"

#include "EnemyAmplifier.h"

#include "LinkCreator.h"

#include "F_Boss_Base.h"

extern float xls_targetFPS;

class ShaderToy : public Feintgine::IGameScreen
{
public:
	ShaderToy();
	~ShaderToy();

	
	ShaderToy(Feintgine::Window * window);

	virtual void build() override;

	virtual void checkInput() override;

	virtual void destroy() override;

	virtual void draw() override;

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;
	
	void drawTimer();

	void drawCustomShader();

	void drawLoadingScreen();

	void drawHitboxes();

	void drawNoLight();

	void firstCheckPoint();

	void drawBackground();

	void initShader();

	void handleInput(Feintgine::InputManager & inputManager);

	void testFun();

	void loadLevel(const std::string & levelPath);

	void reloadLevel();

	void getDropInstances(const std::string & value, std::vector<int> & data, int maxCount);

	//void setPause

	void addExplosion(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos,
		const glm::vec2 & scale, const glm::vec2 & explosionRate,
		const Feintgine::Color & color, float depth,float liveRate = 0.1f);


	void addBullet(EnemyBulletBase * bullet);	

	void switchShader();

private:

	Feintgine::Window * m_window;

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

	Feintgine::GLSLProgram * m_currentEffect;

	std::vector<glm::vec2> m_lightPos;
	std::vector<glm::vec4> m_lightColor;
	std::vector<glm::vec2> m_lightUV;

	EmptyObject bg;

	EmptyObject bg1;
	EmptyObject bg2;
	//Light mouseLight;
	//Light b_ambient;
	// 54.0, 0.0f
	float m_shaderTime = 0.0f;

	float dayLight = 1.0;
	bool fayIn = false;

	std::vector<glm::vec2> m_lightListPos;
	std::vector<glm::vec4> m_lightListColor;
	std::vector<glm::vec3> m_lightListAttenuation;
	
	Feintgine::LightBatch m_lightBatch;

	TextRenderer m_textRenderer;

	TextRenderer m_scoreRenderer;

	F_Player_Reimu m_player;

	//std::vector<F_Player> m_testPlayers;
	BackGroundMap m_bg;

	void randomLight();

	Feintgine::SpriteFont * m_spriteFont;

	Feintgine::F_AnimatedObject m_animatObj; // eiki effect


	std::vector<FairyBase *> m_enemies;
	//std::vector<EnemyGuardian *> m_guardians;
	//std::vector<EnemyAmplifier *> m_amplifiers;
	Uint32 t_start;
	double t_duration;
	Uint32 t_now;

	bool isDone = true;

	Feintgine::ParticleEngine2D m_particleEngine;

	PauseMenu m_pauseMenu;

	void togglePauseLogic();

	void e_darkeningScene(float maxVal, float rate);

	Feintgine::Music m_music;

	Feintgine::AudioEngine m_audioEngine;

	std::vector<ExplosionRing> m_exlosions;
	std::vector<LivingLabel *> m_labels;
	//std::vector<int> dropInstace;

	void turnLight(bool val);

	void toggleLight();

	void toggleLightAE();

	std::vector<EnemyBulletBase *> m_bullets;

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

	CEGUI_TextRenderer m_CEGUI_textRenderer;

	KanjiEffectManager m_kanjiEffectManager;

	LinkCreator m_linkCreator;

	F_Boss_Base m_boss;


	//std::unique_ptr<b2World> m_world;


	//B2ContactListener m_contactListener;
};

