#pragma once
#include "ScreenIndices.h"
#include <IGameScreen.h>
#include <IMainGame.h>
#include <InputManager.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <ResourceManager.h>
#include "EmptyObject.h"


#include <T_Scene.h>

class DemoScreen2 : public Feintgine::IGameScreen
{
public:
	DemoScreen2();
	~DemoScreen2();
	DemoScreen2(Feintgine::Window * window);

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	void initShader();

	void handleInput(Feintgine::InputManager & inputManager);
	
	void checkInput();


private:

	Feintgine::GLSLProgram m_shader;
	Feintgine::SpriteBatch m_spriteBatch;
	Feintgine::Window * m_window;
	Feintgine::Camera2D m_camera;
	
	EmptyObject bg;

	//T_Scene m_scene;
};

