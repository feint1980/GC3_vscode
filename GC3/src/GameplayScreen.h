// #pragma once

// #include "Player.h"
// #include "ScreenIndices.h"
// #include "Grid.h"
// #include "OutsideGrid.h"


// #include <IGameScreen.h>
// #include <SDL2/SDL.h>
// #include <IMainGame.h>

// #include <InputManager.h>
// #include <GUI.h>
// #include <fstream>
// #include <string>

// #include <vector>
// #include <SpriteBatch.h>
// #include <Camera2D.h>
// #include <GLSLProgram.h>
// #include <GLTexture.h>
// #include <DebugRender.h>

// #include"PushableObject.h"
// #include "TownTile.h"
// #include <time.h>




// class GameplayScreen : public Feintgine::IGameScreen
// {
// public:
// 	GameplayScreen(Feintgine::Window * window ,const std::string & file );
// 	~GameplayScreen();
	
// 	virtual int getNextScreenIndex() const override;
// 	virtual int getPreviousScreenIndex()const override;

// 	virtual void build()override;
// 	virtual void destroy()override;

// 	virtual void onEntry()override;
// 	virtual void onExit()override;

	
// 	virtual void draw() override;
// 	virtual void update(float deltaTime)override;

	
// 	void setType(GameState gameState);
// 	void handleInput(Feintgine::InputManager &inputManager);

	
// private:
// 	std::string levelFile;
// 	bool change = false;
// 	void loadLevel(const std::string & levelFile);

// 	int m_monsterNums = 0;

// 	std::vector<std::string> m_levelData;

// 	Feintgine::GLSLProgram m_textureProgram;
// 	Feintgine::SpriteBatch m_spriteBatch;
// 	Feintgine::SpriteBatch m_guispriteBatch;
// 	Feintgine::Camera2D m_camera;
// 	Feintgine::Camera2D m_guiCamera;
// 	Feintgine::Window * m_window;
	
// 	Feintgine::DebugRender m_debugRender;

	
// 	Feintgine::GLSLProgram m_lightProgram;

// 	Feintgine::GUI m_gui;

// 	std::vector<PushableObject> m_tiles;

// 	std::vector<OutsideGrid> m_outsideGrids;

// 	std::vector<Grid> m_grids;

// 	//std::vector<BasicMonster> m_monsters;

// 	std::vector<TownTile> m_townTile;
	
// 	PushableObject * m_tile = nullptr;

// 	void setDebug();
// 	void setPause();
// 	void initGUI();

// 	int width = 0;
// 	int height = 0;
// 	glm::vec2 centerPos;

// 	bool m_debugMode = false;
// 	bool m_isPaused = false;

// 	bool clickExit(const CEGUI::EventArgs & e);

// 	void checkInput();
	
	
// 	GameState m_gameState = GameState::TOWN;

// 	Player m_player;
	

// 	int rate = 0;


// };

