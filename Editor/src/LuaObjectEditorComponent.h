#pragma once

#include <SpriteBatch.h>
#include <GUI.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <DebugRender.h>
#include <rapidxml.hpp>
#include <ResourceManager.h>
#include <EmptyObject.h>
#include <AudioEngine.h>
#include <EngineSetting.h>
#include <F_oEvent.h>
#include <LightBatch.h>
#include <F_LuaDynamicObject.h>
#include <F_LuaObjectManager.h>
#include "../../GC3/src/F_Lua_Boss_Manager.h"
#include "../../GC3/src/F_Lua_Boss.h" 
#include "../../GC3/src/F_Player.h"
#include "../../GC3/src/EnemyGuardian.h"
#include "../../GC3/src/EnemyAmplifier.h"

#include <fstream>


class LuaObjectEditorComponent
{

public:
	LuaObjectEditorComponent();
	~LuaObjectEditorComponent();

	void loadGUI(Feintgine::GUI * gui);
	void init(const glm::vec4 &drawScreen, Feintgine::Camera2D * cam, const
		Feintgine::Camera2D & staticCam);
	void loadShader(const std::string & vertexPath, const std::string &fragmentPath);
	void draw(Feintgine::SpriteBatch & spriteBatch, Feintgine::DebugRender & debug);

	bool toggleUpdate(const CEGUI::EventArgs &e);

	void internalToggleUpdate();

	bool resetEvent(const CEGUI::EventArgs &e);

	bool clearBullets(const CEGUI::EventArgs &e);

	bool pickMoveset(const CEGUI::EventArgs &e);

	//void callCreateFromLua(const std::string & filePath, const std::string & functionName);

	void handleInput(Feintgine::InputManager & inputManager);

	void showGUI(bool value);

	void update(float deltaTime);

	void loadMoveset(const std::string & path);

	bool loadMovesetInternal(const CEGUI::EventArgs &e);

	void loadBosses(const std::string & path);

	bool refreshData(const CEGUI::EventArgs &e);

	bool togglePlayer(const CEGUI::EventArgs &e);

	void reloadPlayer(int val);
	

private:
	
	bool m_isUpdate = false;
	glm::vec4 m_drawScreen;
	Feintgine::GLSLProgram m_shader;
	Feintgine::Camera2D * m_cam;
	Feintgine::Camera2D m_staticCam;
	Feintgine::GUI * m_gui;
	std::string savedLocation;
	Feintgine::LightBatch m_lightBatch;

	Feintgine::AudioEngine m_audioEngine;

	F_Lua_Boss m_testLuaObject;
	int m_shotType;

	CEGUI::DefaultWindow * m_bulletCount;

	CEGUI::PushButton * m_toggleUpdate = nullptr;

	CEGUI::PushButton * m_clearButton = nullptr;

	CEGUI::PushButton * m_clearBullets = nullptr;

	CEGUI::PushButton * m_refreshData = nullptr;

	CEGUI::ToggleButton * m_playerEnableTogger = nullptr;
	
	CEGUI::Listbox * m_movesetList = nullptr;

	CEGUI::Listbox * m_bossList = nullptr;

	std::vector<EnemyBulletBase *> m_bullets;

	F_Lua_Boss_Manager m_luaObjectManager;


	std::string m_currentLuaDir = "";

	F_Player m_player;


	std::vector<F_BaseEnemy *> m_enemies;
	std::vector<EnemyGuardian *> m_guardians;
	std::vector<EnemyAmplifier *> m_amplifiers;


	std::vector<std::string> m_lines;
	//Feintgine::F_LuaObjectManager m_luaObjectManager;
	EmptyObject bg;
};

