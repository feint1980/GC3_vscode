#pragma once
#include "ScreenIndices.h"
#include <IGameScreen.h>
#include <SDL2/SDL.h>
#include <IMainGame.h>
#include <InputManager.h>
#include <GLSLProgram.h>
#include <ResourceManager.h>
#include <SpriteBatch.h>
#include <Camera2D.h>
#include<iostream>
#include <feint_common.h>


#include "EmptyObject.h"

class TestScreeb : public Feintgine::IGameScreen
{
public:
	TestScreeb();

	TestScreeb(Feintgine::Window * window);
	~TestScreeb();

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	void initShader();

	void handleInput(Feintgine::InputManager &inputManager);

	void checkInput();



private:

	EmptyObject testObj;

	Feintgine::GLSLProgram m_shader;
	Feintgine::SpriteBatch m_spriteBatch;
	Feintgine::Window * m_window;
	Feintgine::Camera2D m_camera;


};

