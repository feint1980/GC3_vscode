// #pragma once
// //#include <ClientSys.h>
// #include <ClientSocket.h>
// #include "ScreenIndices.h"
// #include <functional>
// #include <iostream>

// #include <IGameScreen.h>
// #include <SDL2/SDL.h>
// #include <IMainGame.h>
// #include <InputManager.h>
// #include <GUI.h>
// #include <SDL2/SDL_net.h>
// #include <time.h>


// #include "EmptyObject.h"
// #include "CustomMessageBox.h"
// #include "ItemSlot.h"

// #include <DebugRender.h>
// #include <vector>
// #include <SpriteBatch.h>
// #include <Camera2D.h>
// #include <GLSLProgram.h>
// #include <GLTexture.h>
// #include <ResourceManager.h>
// #include <SpriteFont.h>
// #include <Timing.h>

// #include <Box2D/Box2D.h>
// #include "Droping_Particle.h"
// #include "CustomButton.h"
// #include "Profile.h"
// #include "Player.h"
// #include "F_Player.h"
// const float MARK = 0.15f;



// class MainMenuScreen : public Feintgine::IGameScreen
// {
// public :

// 	MainMenuScreen(Feintgine::Window* window);
// 	~MainMenuScreen();

// 	virtual int getNextScreenIndex() const override;

// 	virtual int getPreviousScreenIndex() const override;

// 	virtual void build() override;

// 	virtual void destroy() override;

// 	virtual void onEntry() override;

// 	virtual void onExit() override;

// 	virtual void update(float deltaTime) override;

// 	void initWorld();

// 	virtual void draw() override;


// 	void expandPannel();
// 	int access_row = 0;
	

// 	void initShader();

	
// 	Feintgine::GUI getGUI() const { return m_gui; }

// 	void updateSocket();


// 	void createMessageBox(const std::string & message , std::function<bool(const CEGUI::EventArgs & e)> setOnClick = nullptr);
// private:
// 	int withDraw = 0;
// 	void initGUI();
// 	void checkInput();
// 	int attemp = 0;

// 	b2World * m_world = nullptr;
// 	//Feintgine::InputManager m_inputManager;
// 	//b2Fixture * m_fixture = nullptr;

// 	std::string revStr;

// 	bool hasClickLog = false;

// 	std::vector<std::string> m_account_data;
	

// 	void drawHUD();

// 	void show();
// 	void hideSlice();
// 	bool hide = true;
// 	bool ready = false;

// 	void showLoginPanel();
// 	void destroyLoginPanel();

// 	void showRegisterPanel();
// 	void destroyRegisterPanel();

// 	bool isLoginPanelShowed = false;
// 	bool isRegisterPanelShowed = false;
// 	float registerPanel_alpha = 0.0f;
// 	float loginPanel_alpha = 0.0f;
// 	bool showTheLoginBox = false;
// 	bool showTheRegisterBox = false;
// 	bool loged_in = false;

// 	void login( char * id,  char * password);
// 	void registing(char * id, char * password, char * confirm);
// 	bool clickable = true;

// 	void handleInput(Feintgine::InputManager & inputManager);
	
// 	float current_slide_pos;
// 	Feintgine::FpsLimiter m_fpsLimiter;
// 	float m_fps;
// 	float m_time;
// 	float m_frameTime;


// 	CustomButton start , exit , regis;

// 	Feintgine::Camera2D m_hudCamera;
// 	Feintgine::Camera2D m_camera;
// 	Feintgine::Window* m_window;
// 	Feintgine::GUI m_gui;
// 	Feintgine::SpriteBatch m_spriteBatch;
// 	Feintgine::GLSLProgram m_textureProgram;

// 	Feintgine::GLSLProgram m_lightProgram;

// 	Feintgine::GLSLProgram m_blurShader;

// 	Feintgine::SpriteBatch m_hudSpriteBatch;
// 	Feintgine::SpriteFont *m_fontRenderer;

	
// 	EmptyObject bg;
// 	EmptyObject pop;

	
// 	CEGUI::DefaultWindow * credit = nullptr;
// 	CEGUI::GroupBox * testo = nullptr;
// 	CEGUI::DefaultWindow * testbg = nullptr;

// 	CEGUI::GroupBox * loginPanel = nullptr;
// 	CEGUI::Editbox * login_id = nullptr;
// 	CEGUI::Editbox * login_password = nullptr;
// 	CEGUI::DefaultWindow * login_id_label  = nullptr;
// 	CEGUI::DefaultWindow * login_password_label  = nullptr;
// 	CEGUI::DefaultWindow * background = nullptr;

// 	CEGUI::GroupBox *registerPanel = nullptr;
// 	CEGUI::Editbox * register_id = nullptr;
// 	CEGUI::Editbox * register_password = nullptr;
// 	CEGUI::DefaultWindow * register_id_label = nullptr;
// 	CEGUI::DefaultWindow * register_password_label = nullptr;
// 	CEGUI::DefaultWindow * register_background = nullptr;
// 	CEGUI::Editbox * register_confirm = nullptr;
// 	CEGUI::DefaultWindow * register_confirm_label = nullptr;


// 	CEGUI::GroupBox * messageBox = nullptr;
// 	CEGUI::DefaultWindow * messageBoxbg = nullptr;

// 	CustomMessageBox *login_fail = nullptr;
	
// 	CustomButton pannel_login, panel_cancel;

// 	CustomButton register_regis, register_cancel;

// 	CEGUI::EventArgs evnt;
// 	bool isHover = false;
// 	bool isExit = false;

// 	bool active_camera = false;
// 	float m_fixer = 0.9988f;

// 	Feintgine::DebugRender m_debugRenderer;
// 	CEGUI::GridLayoutContainer *drag_container;

	
// 	//Droping_Particle m_particles[MAX_PARTICLE];
	
// 	std::vector<Droping_Particle *> m_particles;

// 	Feintgine::GLTexture particle_Texture;

// 	Feintgine::GLTexture particle_Texture_2;

// 	Feintgine::GLTexture particle_Texture_3;
// 	void createParticle();

// 	bool pannelTurnoff = false;

// 	float cam_angle = 0.01f;

// 	float ui_alpha = 0;

// 	bool first = true;

// 	bool isConnected = false;

// 	bool is_sock_init = false;
// 	//ClientSocket *m_socket = nullptr;

// 	//Player m_player;

	
	

// };

