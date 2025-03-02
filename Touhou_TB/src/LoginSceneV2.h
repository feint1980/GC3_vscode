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

#include "../../PacketDescription/NetworkPacket.h"
// #include "../../TGUI_theme/ThemeCreator.hpp"

#include "TGUIScriptingManager.h"

#include "ClientScriptingManager.h"

class LoginSceneV2 : public Feintgine::IGameScreen
{
public:
    LoginSceneV2();
    ~LoginSceneV2();

    LoginSceneV2(Feintgine::Window * window);

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

    void initGUIV2();

    void setNotification(const std::string & msg,const std::string & btnMsg, const std::function<void()> & callback2);
    
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
    tgui::Panel::Ptr m_register_panel;


    tgui::Label::Ptr m_id_label;
    tgui::Label::Ptr m_pw_label;

    tgui::EditBox::Ptr m_id_input;
    tgui::EditBox::Ptr m_pw_input;

    tgui::Label::Ptr m_register_id_label;
    tgui::Label::Ptr m_register_pw_label;
    tgui::Label::Ptr m_register_pw_confirm_label;
    tgui::Label::Ptr m_register_key_label;

    tgui::EditBox::Ptr m_register_id_input;
    tgui::EditBox::Ptr m_register_pw_input;
    tgui::EditBox::Ptr m_register_pw_confirm_input;
    tgui::EditBox::Ptr m_register_key_input;


    tgui::Label::Ptr m_login_button;
    tgui::Label::Ptr m_register_button;
    tgui::Label::Ptr m_cancel_button;

    tgui::Label::Ptr m_register_regis_button;
    tgui::Label::Ptr m_register_cancel_button;

    tgui::Panel::Ptr m_tos;
    tgui::RichTextLabel::Ptr m_tos_label;
    tgui::Label::Ptr m_tos_agre_label;
    tgui::Label::Ptr m_tos_exit_label;

    tgui::Label::Ptr m_offline_label;
    tgui::Label::Ptr m_online_label;
    tgui::Label::Ptr m_exit_label;

    tgui::Panel::Ptr m_noti_panel;
    tgui::RichTextLabel::Ptr m_noti_label;
    tgui::Label::Ptr m_noti_cancel_label;



    // tgui::Panel::Ptr m_notification_panel;
    // tgui::Label::Ptr m_notification_label;
    // tgui::Label::Ptr m_notification_cancel_label;
    // tgui::Label::Ptr m_notification_cancel_label;
    
    // ClientHandler * m_client = nullptr;


    ClientScriptingManager m_scriptingManager;

    bool m_isAccept = false;

    std::stack<tgui::Panel::Ptr> m_guiStack;

    bool m_isDisconnected = true;

    TGUIScriptingManager m_guiScriptingManager;

    //Status m_lastResponse = Status::Disconnected;

    //BattleScene m_battleScene;

};