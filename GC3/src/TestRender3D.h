#pragma once
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


#include <TextRenderer.h>
#include <Model.h>

#include <Camera3D.h>


class TestRender3D : public Feintgine::IGameScreen
{
public:
	TestRender3D();
	~TestRender3D();

	TestRender3D(Feintgine::Window * window);

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

	TextRenderer m_textRenderer;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::Camera2D m_camera;

	Feintgine::Window * m_window;

	Feintgine::GUI m_gui;

	Feintgine::GLSLProgram m_shader;

	Feintgine::F_EmptyObject testObject;

	EmptyObject bg;

	Feintgine::Model ourModel;

	Feintgine::Camera3D camera = Feintgine::Camera3D(glm::vec3(0.0f, 0.0f, 3.0f));

	GLboolean m_cameraClick;
	

	float modelAngle = 0;

	unsigned int cameraMovement = 0;

};

