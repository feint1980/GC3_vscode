#pragma once

#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>

#include <GLTexture.h>
#include <ResourceManager.h>
//#include <f_object.pb.h>
#include <iostream>
#include <IGameScreen.h>
#include <Window.h>
#include <InputManager.h>
#include <T_Scene.h>
#include <IMainGame.h>
#include "ScreenIndices.h"
#include "GC3_EmptyObject.h"
#include <feint_common.h>
#include <chrono>
#include <thread>
#include <SDL_TextRenderer.h>
#include <feint_common.h>
#include <TextRenderer.h>
#include <SpriteFont.h>
#include "CustomButton.h"

class CharacterSelectionScreen : public Feintgine::IGameScreen
{
public:
	CharacterSelectionScreen();
	~CharacterSelectionScreen();

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	virtual void checkInput() override;

};

