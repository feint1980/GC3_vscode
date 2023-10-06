#pragma once
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>

#include <GLTexture.h>
#include <ResourceManager.h>

#include <iostream>
#include <IGameScreen.h>
#include <Window.h>
#include <InputManager.h>
//#include <T_Scene.h>
#include <IMainGame.h>
#include "ScreenIndices.h"
#include "EmptyObject.h"
#include <feint_common.h>
#include <chrono>
#include <thread>

class DemoScreen : public Feintgine::IGameScreen
{
public:
	DemoScreen();
	~DemoScreen();

	DemoScreen(Feintgine::Window * window);

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	void checkInput();

	void initShader();

	void handleInput(Feintgine::InputManager & inputManager);

	void loadScreen(std::string & filePath);

	void switchScreen();

	bool full = false;

private:

	Feintgine::Window * m_window;

	Feintgine::Camera2D m_camera;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::GLSLProgram m_shader;

	//T_Scene m_scene;

	EmptyObject bg;

};

