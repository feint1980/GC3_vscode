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
#include <DebugRender.h>
#include <GLTexture.h>
#include <ResourceManager.h>
#include <string>
#include <feint_common.h>

#include <F_Sprite.h>

#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include <SpriteManager.h>
#include <F_EmptyObject.h>
#include <EmptyObject.h>
#include <SpriteManager.h>

#include <glm/gtx/string_cast.hpp>
#include "SpriteDisplayer.h"

#include <TextRenderer.h>

class NewRenderModel : public Feintgine::IGameScreen
{
public:
	NewRenderModel();
	~NewRenderModel();

	NewRenderModel(Feintgine::Window * window);

	virtual void build() override;

	virtual void checkInput() override;

	virtual void destroy() override;

	virtual void draw() override;

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	void initGUI();

	void initShader();


	void handleInput(Feintgine::InputManager & inputManager);
	
	virtual void onEntry() override;

	virtual void onExit() override;

	void initSpriteList();

	virtual void update(float deltaTime) override;

private:


	TextRenderer m_textRenderer;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::Camera2D m_camera;

	Feintgine::Window * m_window;

	Feintgine::GUI m_gui;

	Feintgine::GLSLProgram m_shader;

	Feintgine::F_EmptyObject testObject;

	EmptyObject bg;

	SpriteDisplayer m_spriteDisplayer;



	CEGUI::PushButton * m_button;
	CEGUI::ToggleButton * m_checkbox;
	CEGUI::FrameWindow * m_fwnd;


};

