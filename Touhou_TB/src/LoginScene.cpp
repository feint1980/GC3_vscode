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

    m_spriteBatch.init();
    
    float tempScale = 0.85f;
	m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initGUI();
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


void LoginScene::handleInput(Feintgine::InputManager & inputManager)
{
    if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
   
	
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

    selectTheme(*m_tgui, "themes/Dark.txt");  // force to load in main thread since the openGL problem, you can only have texture created in mainthread ( OpenGL Context)
    auto loadFontTask = async::spawn([&]() {
        tgui::Font font_load("font/ARIALUNI.ttf");    
        m_tgui->setFont(font_load);
        

    });

    auto loadPanelTask = async::spawn([&]() {
        m_panel = tgui::Panel::create();
        m_panel->setSize(600, 300);
        m_panel->setPosition(m_window->getScreenWidth()/2 - (m_panel->getSize().x/2) ,   m_window->getScreenHeight()/2 - (m_panel->getSize().y /2) );
        //m_panel->setBackgroundColor(tgui::Color(30,30,30,255));
        m_id_label = tgui::Label::create();
        //tgui::Sprite
        m_id_label->setText("   ID");
        m_id_label->setPosition(100, 100);
        //m_id_label->setTextColor(tgui::Color::White);
        m_panel->add(m_id_label);
        
        m_pw_label = tgui::Label::create();
        m_pw_label->setText("Password");
        m_pw_label->setPosition(100, 150);
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
       

        m_login_button = tgui::Button::create();
        m_login_button->setText("Login");
        m_login_button->setPosition(240, 200);
        m_panel->add(m_login_button);
        
        m_cancel_button = tgui::Button::create();
        m_cancel_button->setText("Cancel");
        m_cancel_button->setPosition(340, 200);
        m_panel->add(m_cancel_button);

        m_tgui->add(m_panel);

      
    });
    
    loadFontTask.get();
    loadPanelTask.get();

     //createExample(*m_tgui, "themes/Dark.txt"); 

}

void LoginScene::drawGUI()
{
    m_tgui->draw();

}
