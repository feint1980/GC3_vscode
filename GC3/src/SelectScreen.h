// #pragma once
// #include "ScreenIndices.h"
// #include <functional>
// #include <iostream>
// #include <Enet_UDP.h>

// #include <IGameScreen.h>
// #include <SDL2/SDL.h>
// #include <IMainGame.h>
// #include <InputManager.h>
// #include <GUI.h>

// #include <SpriteBatch.h>
// #include <GLSLProgram.h>
// #include <Camera2D.h>
// #include <ResourceManager.h>

// #include "EmptyObject.h"
// #include "PushableObject.h"
// #include "BasicMonster.h"
// #include "TownTile.h"
// #include "Player.h"
// #include "OtherPlayer.h"
// #include "CustomMessageBox.h"
// #include "MainGUI.h"



// class SelectScreen : public Feintgine::IGameScreen
// {
// public:

// 	SelectScreen();
// 	SelectScreen(Feintgine::Window *window);
// 	~SelectScreen();

// 	void initShader();

// 	virtual int getNextScreenIndex() const override;

// 	virtual int getPreviousScreenIndex() const override;

// 	virtual void build() override;

// 	virtual void destroy() override;

// 	virtual void onEntry() override;

// 	void handleInput(Feintgine::InputManager &inputManager);
	
// 	void checkInput();

// 	virtual void onExit() override;

// 	virtual void update(float deltaTime) override;

// 	virtual void draw() override;

// 	void createMessageBox(const std::string & message, std::function<bool(const CEGUI::EventArgs & e)> setOnClick = nullptr);

// 	void initGUI();

// 	void updateGUI();
// 	void updateSocket();

// 	void updateUDP();

// 	int getOtherPlayerIndex(const std::string & target);

// private:

// 	int attemp = 0;
// 	Feintgine::GUI m_gui;

// 	Feintgine::GLSLProgram m_objectShader;


// 	Feintgine::SpriteBatch m_spriteBatch;

// 	Feintgine::DebugRender m_debugRender;

// 	void loadLevel(const std::string & levelFile);

// 	std::vector<std::string> m_levelData;
	
// 	Feintgine::Camera2D m_camera;

// 	Feintgine::Window *m_window;

// 	EmptyObject bg;

// 	//
// 	std::vector<PushableObject> m_tiles;

// 	std::vector<OutsideGrid> m_outsideGrids;

// 	std::vector<Grid> m_grids;

// 	std::vector<BasicMonster> m_monsters;

// 	std::vector<TownTile> m_townTile;

// 	std::vector<OtherPlayer > m_others;
// 	//
// 	glm::vec2 centerPos;
// 	Player m_player;

// 	CustomMessageBox *error_msgbox = nullptr;

// 	int checkPosTimeStack = 0;

// };

