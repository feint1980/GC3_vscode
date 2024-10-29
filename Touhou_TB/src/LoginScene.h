#pragma once 
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <SDL2/SDL_keyboard.h>
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
#include <SpriteManager.h>
#include <async++.h>
#include <ResourceManager.h>
#include "TB_EmptyObject.h"
#include "ClientHandler.h"
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

    void setTGUILableClickableEffect(tgui::Label::Ptr & label);

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

    tgui::Label::Ptr m_login_button;
    tgui::Label::Ptr m_cancel_button;

    tgui::Panel::Ptr m_tos;
    tgui::RichTextLabel::Ptr m_tos_label;
    tgui::Label::Ptr m_tos_agre_label;
    tgui::Label::Ptr m_tos_exit_label;

    tgui::Label::Ptr m_offline_label;
    tgui::Label::Ptr m_online_label;
    tgui::Label::Ptr m_exit_label;

    tgui::Panel::Ptr m_connect_panel;
    tgui::Label::Ptr m_connect_label;
    tgui::Label::Ptr m_connect_cancel_label;

    ClientHandler * m_client;

    bool m_isDisconnected = true;

    //BattleScene m_battleScene;

};