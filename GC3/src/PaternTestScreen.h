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
#include <T_Scene.h>
#include <IMainGame.h>
#include "ScreenIndices.h"
#include "EmptyObject.h"
#include <feint_common.h>
#include <chrono>
#include <thread>
#include <F_oEvent.h>
#include "TestObject.h"

#define T_PI = 3.14159265359;

class PaternTestScreen : public Feintgine::IGameScreen
{
public:
	PaternTestScreen();
	~PaternTestScreen();

	PaternTestScreen(Feintgine::Window * window);

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

	void initShader();

	

	

private : 
	Feintgine::Window * m_window;

	Feintgine::Camera2D m_camera;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::GLSLProgram m_shader;

	std::vector<TestObject> m_objects;


	float m_t = 0.0f;
	TestObject bg;

};

