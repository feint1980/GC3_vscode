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
#include <feint_common.h>

#include <thread>
#include <deque>

#include <Timing.h>
#include <FTimer.h>
#include <FrameCounter.h>

#include <FrameBuffer.h>
#include <FrameBufferScreen.h>
#include <EffectBatch.h>


#include "TB_EmptyObject.h"
#include "BattleScene.h"
#include "../../PacketDescription/NetworkPacket.h"
#include "../../TGUI_theme/ThemeCreator.hpp"


class LoginScene : public Feintgine::IGameScreen
{
public:
    LoginScene();
    ~LoginScene();

    LoginScene(Feintgine::Window * window);

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

    //void loadMT();

    //void drawLoadingScreen();

    void drawGameplay();

    void initShader();

    void drawGUI();

private:

    Feintgine::Window * m_window = nullptr;

    Feintgine::Camera2D m_camera;

    Feintgine::GLSLProgram m_shader;

    Feintgine::SpriteBatch m_spriteBatch;

    TB_EmptyObject m_bg;

    tgui::Gui * m_tgui;

    tgui::Panel::Ptr m_panel;

    tgui::Label::Ptr m_id_label;
    tgui::Label::Ptr m_pw_label;

    tgui::EditBox::Ptr m_id_input;
    tgui::EditBox::Ptr m_pw_input;

    tgui::Button::Ptr m_login_button;
    tgui::Button::Ptr m_cancel_button;

    //BattleScene m_battleScene;

};