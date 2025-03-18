#pragma once 
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <SDL2/SDL_keyboard.h>
#include <GLTexture.h>
#include <ResourceManager.h>

#include <iostream>
#include <IGameScreen.h>
#include <Window.h>
#include <InputManager.h>
#include <T_Scene.h>
#include <IMainGame.h>
#include <feint_common.h>

#include <thread>
#include <deque>
#include <stack>

#include <Timing.h>
#include <FTimer.h>
#include <FrameCounter.h>

#include <FrameBuffer.h>
#include <FrameBufferScreen.h>
#include <EffectBatch.h>
#include <SpriteManager.h>
#include <async++.h>
#include <ResourceManager.h>
#include "TB_EmptyObject.h"
#include "ClientHandler.h"

#include "InfoHolder.h"

#include "../../PacketDescription/NetworkPacket.h"

#include "TGUIScriptingManager.h"

#include "ClientScriptingManager.h"

class HomeScene : public Feintgine::IGameScreen
{
public:
    HomeScene();
    ~HomeScene();

    HomeScene(Feintgine::Window * window);

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

    void initGUI();

    void drawGameplay();

    void initShader();

    void drawLoading();

    void drawGUI();

    void initLoading();

private:

    Feintgine::Window * m_window = nullptr;

    Feintgine::Camera2D m_camera;

    Feintgine::GLSLProgram m_shader;

    Feintgine::SpriteBatch m_spriteBatch;

    TB_EmptyObject m_bg;

    tgui::Gui * m_tgui = nullptr;
    tgui::Label::Ptr m_text_load;

    tgui::Gui * m_tgui_load;

    lua_State * m_script = nullptr;

    ClientScriptingManager *m_clientScriptingManager;

    TGUIScriptingManager m_guiScriptingManager;

};