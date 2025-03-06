#include "LoginScene.h"


LoginScene::LoginScene()
{

}


LoginScene::~LoginScene()
{

}

LoginScene::LoginScene(Feintgine::Window * window)
{
    m_alpha = 0.0f;
    m_window = window;
    m_screenIndex = 10;

    initShader();
}

void LoginScene::initShader()
{
    
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}

void LoginScene::onEntry()
{
    
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	

    m_camera.setPosition(glm::vec2(0, 0));
    //m_camera.setScale(1.5f);

    m_camera.update();

    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    m_scriptingManager.init("127.0.0.1", 1123,m_script);

    m_spriteBatch.init();
    
    float tempScale = 0.85f;
	m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initGUI();

    if(SDL_HasScreenKeyboardSupport())
    {
        std::cout << "SDL_HasScreenKeyboardSupport !!!!!!!!!!!!!!!!! \n"; 
    }
    else{
        std::cout << " no SDL_HasScreenKeyboardSupport ##################\n";
    }
}

void LoginScene::build()
{

	// build screen (unused)
}

void LoginScene::destroy()
{
    // unload screen (unused)
}

int LoginScene::getNextScreenIndex() const
{
    return 12;
}

int LoginScene::getPreviousScreenIndex() const
{
    return -1;
}

void LoginScene::onExit()
{
    // unload screen (unused)
}

void LoginScene::update(float deltaTime)
{
    m_camera.update();
    m_tgui->updateTime(deltaTime);

    m_scriptingManager.update(deltaTime);



    // if(m_client)
    // {
    //     m_client->update(deltaTime);
    //     Status tStatus = m_client->getStatus();
    //     switch(tStatus)
    //     {
    //         case Status::Disconnected:
    //         {
    //             if(m_client->isConnected())
    //             {
    //                 m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    //                 //m_isDisconnected = false;
    //                 m_panel->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
    //                 m_panel->moveToFront();
    //                 m_guiStack.push(m_panel);
    //                 m_id_input->setFocused(true);
    //                 tStatus = Status::Connected;
    //             }
                
    //         }
    //         break;

    //         case Status::Connected:
    //         {
    //             if(m_noti_panel->isVisible())
    //             {
    //                 m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    //                 m_panel->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
    //                 m_panel->moveToFront();
    //                 m_guiStack.push(m_panel);
    //                 m_id_input->setFocused(true);
    //             }
    //         }
    //         break;

    //         case Status::FailedAttemp:
    //         {
    //             setNotification("Unable to connect to server", "OK",[&](){
    //                 m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    //                 m_client->setStatus(Status::Disconnected);
    //             }
    //             );
    //         }
    //         break;

    //         case Status::Banned:
    //         {
    //             setNotification("You are banned from this server", "OK",[&](){
    //                 m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    //                 m_client->setStatus(Status::Disconnected);
    //             }
    //             );
    //         }
    //         break;

    //         case Status::Incompatible:
    //         {
    //             setNotification("Error code K2 D32", "Oh no",[&](){
    //                 m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    //                 m_client->setStatus(Status::Disconnected);
    //             }
    //             );
    //         }
    //         break;

    //         case Status::IsFull:
    //         {
    //             setNotification("Server is full", "OK",[&](){
    //                 m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    //                 m_client->setStatus(Status::Disconnected);
    //             });
    //         }
    //         break;

    //         default:
    //         break;
    //     }
    // }
}

void LoginScene::checkInput()
{
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        m_game->onSDLEvent(evnt);
        m_tgui->handleEvent(evnt);
    }
    handleInput(m_game->m_inputManager);
}

void LoginScene::setTGUILableClickableEffect(tgui::Label::Ptr & label)
{
    label->onMouseEnter([&](){
        label->getRenderer()->setTextColor(tgui::Color::Green );
    });

    label->onMouseLeave([&](){
        label->getRenderer()->setTextColor(tgui::Color::White );
    });

}

void LoginScene::handleInput(Feintgine::InputManager & inputManager)
{
    if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

    if(inputManager.isKeyPressed(SDLK_F10))
    {
        //SDL_StartTextInput();
    }

    if (inputManager.isKeyPressed(SDLK_ESCAPE))
    {
        // if(!m_guiStack.empty())
        // {       
        //     m_guiStack.top().get()->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
        //     m_guiStack.pop();
        // }
    }
}

void LoginScene::setNotification(const std::string & msg,const std::string & btnMsg, const std::function<void()> & callback)
{
    if(!m_noti_panel->isVisible())
    {
        m_noti_panel->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
    }

    m_noti_label->setText(msg);
    m_noti_cancel_label->setText(btnMsg);
    m_noti_cancel_label->onClick(callback);
}

void LoginScene::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_shader.use();

	// GLint alphaLocation = m_shader.getUniformLocation("time");
	// glUniform1f(alphaLocation, 1);
		
	// Upload texture uniform
	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
	glUniform3f(dayLightIndex, 1, 1, 1);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

    //m_bg.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	

	drawGUI();
	SDL_GL_SetSwapInterval(1);	
}

void LoginScene::initGUI()
{
    m_tgui = new tgui::Gui(m_window->getWindow());
    TTF_Init();
    m_panel = tgui::Panel::create();
    m_register_panel = tgui::Panel::create();

    m_tos = tgui::Panel::create();
    m_tgui->add(m_panel);
    m_tgui->add(m_register_panel);
    m_tgui->add(m_tos);
    selectTheme(*m_tgui, "themes/Dark.txt");  // force to load in main thread since the openGL problem, you can only have texture created in mainthread ( OpenGL Context)

    auto loadFontTask = async::spawn([&]() {
        tgui::Font font_load("font/ARIALUNI.ttf");    
        m_tgui->setFont(font_load);
        m_tgui->setTextSize(20);        

    });

    // auto loadPanelTask = async::spawn([&]() {
        
        m_panel->setSize(600, 300);
        m_panel->setPosition(m_window->getScreenWidth()/2 - (m_panel->getSize().x/2) ,   m_window->getScreenHeight()/2 - (m_panel->getSize().y /2) );
        //m_panel->setBackgroundColor(tgui::Color(30,30,30,255));
        m_id_label = tgui::Label::create();
        //tgui::Sprite
        m_id_label->setText("   ID");
        m_id_label->setPosition(80, 100);
        //m_id_label->setTextColor(tgui::Color::White);
        m_panel->add(m_id_label);
        
        m_pw_label = tgui::Label::create();
        m_pw_label->setText("Password");
        m_pw_label->setPosition(80, 150);
        //m_pw_label->setTextColor(tgui::Color::White);
        m_panel->add(m_pw_label);

        m_id_input = tgui::EditBox::create();
        m_id_input->setSize(m_panel->getSize().x/2 , 30);
        m_id_input->setPosition(180, 100);
        m_panel->add(m_id_input);
        
        m_pw_input = tgui::EditBox::create();
        m_pw_input->setSize(m_panel->getSize().x/2  , 30);
        m_pw_input->setPosition(180, 150);
        m_panel->add(m_pw_input);        

        //m_pw_input->setPasswordCharacter()

        m_login_button = tgui::Label::create();
        m_login_button->setText("Login");
        m_login_button->setPosition(200, 200);
        m_panel->add(m_login_button);

        m_cancel_button = tgui::Label::create();
        m_cancel_button->setText("Cancel");
        m_cancel_button->setPosition(290, 200);
        m_panel->add(m_cancel_button);
        m_panel->setVisible(false);

        m_register_button = tgui::Label::create();
        m_register_button->setText("Register");
        m_register_button->setPosition(400, 200);
        m_panel->add(m_register_button);

        // Register panel
        m_register_panel->setSize(600, 300);
        m_register_panel->setPosition(m_window->getScreenWidth()/2 - (m_register_panel->getSize().x/2) ,   m_window->getScreenHeight()/2 - (m_register_panel->getSize().y /2) );


        m_register_id_label = tgui::Label::create();
        m_register_id_label->setText("            ID");
        m_register_id_label->setPosition(65, 50);
        m_register_panel->add(m_register_id_label);

        m_register_pw_label = tgui::Label::create();
        m_register_pw_label->setText("  Password");
        m_register_pw_label->setPosition(65, 100);
        m_register_panel->add(m_register_pw_label);

        m_register_pw_confirm_label = tgui::Label::create();
        m_register_pw_confirm_label->setText("Confirm PW");
        m_register_pw_confirm_label->setPosition(65, 150);
        m_register_panel->add(m_register_pw_confirm_label);

        m_register_key_label = tgui::Label::create();
        m_register_key_label->setText("          Key");
        m_register_key_label->setPosition(65, 200);
        m_register_panel->add(m_register_key_label);

        m_register_id_input = tgui::EditBox::create();
        m_register_id_input->setSize(m_register_panel->getSize().x /2, 30);
        m_register_id_input->setPosition(180,50);
        m_register_panel->add(m_register_id_input);

        m_register_pw_input = tgui::EditBox::create();
        m_register_pw_input->setSize(m_register_panel->getSize().x /2, 30);
        m_register_pw_input->setPosition(180,100);
        m_register_panel->add(m_register_pw_input);

        m_register_pw_confirm_input = tgui::EditBox::create();
        m_register_pw_confirm_input->setSize(m_register_panel->getSize().x /2, 30);
        m_register_pw_confirm_input->setPosition(180,150);
        m_register_panel->add(m_register_pw_confirm_input);

        m_register_key_input = tgui::EditBox::create();
        m_register_key_input->setSize(m_register_panel->getSize().x /2, 30);
        m_register_key_input->setPosition(180,200);
        m_register_panel->add(m_register_key_input);

        m_register_regis_button = tgui::Label::create();
        m_register_regis_button->setText("Register");
        m_register_regis_button->setPosition(230, 250);
        m_register_panel->add(m_register_regis_button);

        m_register_cancel_button = tgui::Label::create();
        m_register_cancel_button->setText("Cancel");
        m_register_cancel_button->setPosition(330, 250);
        m_register_panel->add(m_register_cancel_button);
        m_register_panel->setVisible(false);

        setTGUILableClickableEffect(m_register_button);
        setTGUILableClickableEffect(m_register_regis_button);
        setTGUILableClickableEffect(m_register_cancel_button);

        m_register_button->onClick([&]()
        {
            m_register_panel->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
            m_register_panel->moveToFront();
           // m_guiStack.push(m_register_panel);
        });

        m_register_cancel_button->onClick([&]() 
        {
            m_register_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
           // m_guiStack.pop();
        });

    // auto loadTOSTask = async::spawn([&]() {
        m_tos->setSize(400, 300);
        m_tos->setPosition(m_window->getScreenWidth()/2 - 200 , m_window->getScreenHeight()/2 -150 );

        m_tos_label = tgui::RichTextLabel::create();
        m_tos_label->setText("This is a fan-made game based on \nTouhou project,many assets from other \ngames as concepts/placeholder,if you are \nOK with this prototype then hit \"Agree\" ");
        m_tos_label->setPosition(10, 50);
        m_tos_label->setTextSize(14);

        m_tos_agre_label = tgui::Label::create();
        m_tos_agre_label->setText("Agree");
        m_tos_agre_label->setPosition(120, 200);

        m_tos_exit_label = tgui::Label::create();
        m_tos_exit_label->setText("Exit");
        m_tos_exit_label->setPosition(220, 200);

        m_tos->add(m_tos_label);
        m_tos->add(m_tos_agre_label);
        m_tos->add(m_tos_exit_label);
        m_tos->setVisible(false);

        m_online_label = tgui::Label::create();
        m_online_label->setText("Play Online");
        m_online_label->setPosition("50%" , m_window->getScreenHeight()/2 - 25);
        m_online_label->setOrigin(0.5,0);
        m_online_label->setAutoSize(true);
        m_tgui->updateTime(1);

        m_offline_label = tgui::Label::create();
        m_offline_label->setText("Play Offline");
        m_offline_label->setPosition("50%" , m_window->getScreenHeight()/2 + 25 );
        m_offline_label->setOrigin(0.5,0);
        m_offline_label->setAutoSize(true);

        m_exit_label = tgui::Label::create();
        m_exit_label->setText("Exit");
        m_exit_label->setOrigin(0.5,0);
        m_exit_label->setPosition("50%" , m_window->getScreenHeight()/2 + 75 );
        m_exit_label->setAutoSize(true);

        m_online_label->moveToBack();
        m_offline_label->moveToBack();
        m_exit_label->moveToBack();

        m_online_label->setVisible(false);
        m_offline_label->setVisible(false);
        m_exit_label->setVisible(false);

        m_tgui->add(m_online_label);
        m_tgui->add(m_offline_label);
        m_tgui->add(m_exit_label);

    // });

    loadFontTask.get();
    m_noti_panel = tgui::Panel::create();
    m_noti_panel->setSize(300, 200);
    m_noti_panel->setPosition(m_window->getScreenWidth()/2 - 150 , m_window->getScreenHeight()/2 -50 );
    m_noti_panel->setVisible(false);

    m_noti_label = tgui::RichTextLabel::create();
    m_noti_label->setPosition("50%" , 45);
    m_noti_label->setOrigin(0.5,0);
    m_noti_label->setAutoSize(true);
    m_noti_panel->add(m_noti_label);


    m_noti_cancel_label = tgui::Label::create();
    m_noti_cancel_label->setText("Cancel");
    // m_connect_cancel_label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

    m_noti_cancel_label->setPosition("50%"  , 150);
    m_noti_cancel_label->setOrigin(0.5,0);
    m_noti_cancel_label->setAutoSize(true);
    m_noti_panel->add(m_noti_cancel_label);

    m_tgui->add(m_noti_panel);

    m_noti_cancel_label->onClick([&]() {
        m_noti_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));

    });

    setTGUILableClickableEffect(m_noti_cancel_label);
    

    m_tos->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(200));
    m_tos->moveToFront();
    m_tos_agre_label->onClick([&]() {
        m_tos->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
        m_online_label->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
        m_offline_label->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
        m_exit_label->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
        m_isAccept = true;

    });

    setTGUILableClickableEffect(m_tos_agre_label);
    setTGUILableClickableEffect(m_tos_exit_label);

    m_online_label->onClick([&]() 
    {
        if(m_isDisconnected)
        {
            m_noti_panel->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
            m_noti_label->setText("Connecting...");
            m_noti_panel->moveToFront();
            // if(m_client == nullptr)
            // {
            //     m_client = new ClientHandler();
            //     m_client->init("127.0.0.1", 1123);
            // }
            // m_client->connect();
            //m_guiStack.push(m_noti_panel);
            m_scriptingManager.connect();

        }
        else
        {
            m_panel->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
            m_panel->moveToFront();
            //m_guiStack.push(m_panel);
        }
    });

    setTGUILableClickableEffect(m_online_label);

    m_offline_label->onClick([&]() {
        std::cout << "offline \n";
    });

    setTGUILableClickableEffect(m_offline_label);

    m_login_button->onClick([&]() {
        //todo login here
    });

    setTGUILableClickableEffect(m_login_button);


    m_cancel_button->onClick([&]() {
        m_panel->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(250));
        //m_panel->moveToBack();
        m_guiStack.pop();
    });

    setTGUILableClickableEffect(m_cancel_button);

    m_exit_label->onClick([&]() {
        exit(1);
    });

    setTGUILableClickableEffect(m_exit_label);

}

void LoginScene::drawGUI()
{
    m_tgui->draw();
}
