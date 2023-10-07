#pragma once
#include <functional>
#include <iostream>
#include <IGameScreen.h>
#include <IMainGame.h>
#include <InputManager.h>
#include <GUI.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <DebugRender.h>
#include <GLTexture.h>
#include <ResourceManager.h>
#include <Timing.h>
#include <windows.h>
#include <dirent.h>
#include <string>
#include <functional>



class TestCEGUIScreen : public Feintgine::IGameScreen
{
public:
	TestCEGUIScreen();
	~TestCEGUIScreen();

	TestCEGUIScreen(Feintgine::Window * window);

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	void checkInput();

	void handleInput(Feintgine::InputManager & inputManager);


	//init ********************************************************************************
	void initGUI();

private:

	Feintgine::GUI m_gui;

	Feintgine::Window * m_window;

	


};

