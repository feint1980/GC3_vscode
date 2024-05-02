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
#include <ParticleBatch2D.h>
#include <ParticleEngine2D.h>
#include <SDL_TextRenderer.h>
#include <feint_common.h>
#include <TextRenderer.h>
#include <SpriteFont.h>
#include "CustomButton.h"

#include <AudioEngine.h>
#include "CharacterAvatar.h"

#include "AvatarSelection.h"
#include "F_Player.h"
#include "BackGroundMap.h"

#include "F_BaseEnemy.h"
#include "EnemyBulletBase.h"

#include "BaseAnimatedObject.h"
#include "F_Player_Reimu.h"
#include "EGUI_TextRenderer.h"
#include "FairyBase.h"
#include "ExplosionRing.h"
#include "KanjiEffectManager.h"

#include "EnemyGuardian.h"
#include "EnemyAmplifier.h"

class CharacterTestScreen : public Feintgine::IGameScreen
{
public:
	CharacterTestScreen();
	~CharacterTestScreen();

	CharacterTestScreen(Feintgine::Window * window);

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

	void firstCheckpoint();

	void drawLoadingScreen();

	void spawnEnemy();

	void addExplosion(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos,
		const glm::vec2 & scale, const glm::vec2 & explosionRate,
		const Feintgine::Color & color, float depth, float liveRate = 0.1f);


private:

	bool isLoaded = false;

	bool startLoad = false;

	Feintgine::LightBatch m_lightBatch;

	Feintgine::Window * m_window;

	Feintgine::Camera2D m_camera;

	Feintgine::Camera2D m_camera_static;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::GLSLProgram m_shader;

	Feintgine::GLSLProgram m_gui_shader;

	F_Player_Reimu m_player;


	TextRenderer m_scoreRenderer;

	std::vector<ExplosionRing> m_exlosions;

	//std::vector<F_Player> m_players;

	BackGroundMap m_bg;

	GC3_EmptyObject m_tbg;

	Feintgine::AudioEngine m_audioEngine;

	std::vector<FairyBase *> m_enemies;

	std::vector<EnemyBulletBase *> m_bullets;


	std::vector<EnemyGuardian *> m_guardians;

	std::vector<EnemyAmplifier *> m_amplifiers;
	//std::vector<BaseAnimatedObject *> m_objects;

	float m_counter = 0.0f;
	BaseAnimatedObject *aa;

	Feintgine::ParticleEngine2D m_particleEngine;

	float m_ambientLightR = 1.0f;
	float m_ambientLightG = 1.0f;
	float m_ambientLightB = 1.0f;

	Feintgine::GLSLProgram m_shaderNormal;

	Feintgine::SpriteBatch m_timerSpriteBatch;

	CEGUI_TextRenderer m_CEGUI_textRenderer;

	Feintgine::SpriteFont * m_spriteFont;

	KanjiEffectManager m_kanjiEffectManager;

};

