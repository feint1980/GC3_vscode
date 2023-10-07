#pragma once
#include <SpriteBatch.h>
#include <GUI.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <DebugRender.h>
#include <rapidxml.hpp>
#include <ResourceManager.h>
#include <F_EnemyBasic.h>
#include <FairyBase.h>
#include <EmptyObject.h>
#include <AudioEngine.h>
#include <EngineSetting.h>
#include <F_oEvent.h>
#include <F_Player.h>
#include "GlobalValueClass.h"
#include <F_MarisaRocket_small.h>
#include <LightBatch.h>
#include <F_BaseEnemy.h>


//#include "F_Player_Reimu.h"
class EnemyEditorComponent
{
public:
	EnemyEditorComponent();
	~EnemyEditorComponent();


	void loadGUI(Feintgine::GUI * gui);
	void init(const glm::vec4 &drawScreen,Feintgine::Camera2D * cam, const 
	Feintgine::Camera2D & staticCam);
	void loadShader(const std::string & vertexPath, const std::string &fragmentPath);
	void draw(Feintgine::SpriteBatch & spriteBatch, Feintgine::DebugRender & debug);

	void handleInput(Feintgine::InputManager & inputManager);

	bool pickEnemy(const CEGUI::EventArgs &e);
	
	void showGUI(bool value);
	void loadEnemy(const std::string & path);

	int getEnemyNodeIndexByName(const std::string & name);

	void update(float deltaTime);

private:
	glm::vec4 m_drawScreen;
	Feintgine::GLSLProgram m_shader;
	Feintgine::Camera2D * m_cam;
	Feintgine::Camera2D m_staticCam;
	Feintgine::GUI * m_gui;
	std::string savedLocation;


	CEGUI::Listbox * m_enemyList;

	F_EnemyBasic * m_enemy = nullptr;
	std::vector<F_EnemyBasic *> m_enemyObjectList;


	std::vector<F_BaseEnemy *> m_baseenemiesObjectList;
	std::vector<EnemyBulletBase *> m_enemiesbulletObjectList;
	std::vector<EnemyGuardian *> m_enemyguardianObjectList;
	std::vector<EnemyAmplifier *> m_enemyamplifierObjectList;

	F_Player m_player;

	Feintgine::LightBatch m_lightBatch;

	Feintgine::AudioEngine m_audioEngine;
	EmptyObject bg;

};

