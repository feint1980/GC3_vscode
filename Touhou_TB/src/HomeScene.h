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
#include "LuaEventHandler.h"
#include "ClientCharacterHandler.h"
#include "../../PacketDescription/SkillHandler.h"
#include "ControlHandler.h"
#include <LuaTaskManager.h>


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

    void backToMainMenu();

    void handleInput(Feintgine::InputManager & inputManager);

    void changeSceneIndex(int index);

    void initGUI();

    void drawGIFScene();

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

    bool loaded = false;

    lua_State * m_script = nullptr;

    ClientScriptingManager *m_clientScriptingManager = nullptr;

    ClientCharacterHandler * m_clientCharacterHandler = nullptr;

    RakNet::RakPeerInterface * m_client = nullptr;

    // bool isReady = false;

    Feintgine::FrameBuffer m_frameBuffer;

	Feintgine::FrameBufferScreen m_frameBufferScreen;

    TGUIScriptingManager * m_guiScriptingManager = nullptr;

    SkillHandler m_skillHandler;

    // LuaEventHandler m_luaEventHandler;

    Feintgine::F_AnimatedObject m_gif;

    ControlHandler * m_controlHandler = nullptr;

    LuaTaskManager m_luaTaskManager ;

};

