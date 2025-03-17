#include "HomeScene.h"


HomeScene::HomeScene()
{

}


HomeScene::~HomeScene()
{

}

HomeScene::HomeScene(Feintgine::Window * window)
{
    m_alpha = 0.0f;
    m_window = window;
    m_screenIndex = 1;

    std::cout << "home scene init \n";
    initShader();
}

void HomeScene::initShader()
{
    
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}

void HomeScene::onEntry()
{
    std::cout << "home scene onEntry \n";
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	

    m_camera.setPosition(glm::vec2(0, 0));
    //m_camera.setScale(1.5f);

    m_camera.update();

    
    // m_scriptingManager.init("127.0.0.1", 1123);

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

void HomeScene::build()
{

	// build screen (unused)
}

void HomeScene::destroy()
{
    // unload screen (unused)
}

int HomeScene::getNextScreenIndex() const
{
    return 12;
}

int HomeScene::getPreviousScreenIndex() const
{
    return -1;
}

void HomeScene::onExit()
{
    // unload screen (unused)
}

void HomeScene::update(float deltaTime)
{

    m_guiScriptingManager.update(deltaTime);
    m_clientScriptingManager.update(deltaTime);

}

void HomeScene::checkInput()
{
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        m_game->onSDLEvent(evnt);
        m_guiScriptingManager.checkInput(evnt);
    }
    handleInput(m_game->m_inputManager);
    
}

void HomeScene::handleInput(Feintgine::InputManager & inputManager)
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

    }
    m_guiScriptingManager.handleInput(inputManager);
}

void HomeScene::draw()
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


void HomeScene::initGUI()
{

    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    m_guiScriptingManager.init(m_window,m_script);

    m_clientScriptingManager.init("127.0.0.1", 1123,m_script);

    // inverse case

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/Home/homeScene.lua")))
    {
        std::cout << "Run loginScene script OK \n";
    }

    lua_getglobal(m_script, "HomeSceneInit");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        lua_pushlightuserdata(m_script, &m_guiScriptingManager);
        lua_pushlightuserdata(m_script, &m_clientScriptingManager);
        std::cout << "check ref : " << &m_guiScriptingManager << "\n";
        const int argc = 3;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Login scene init script from C++ OK \n";
        }
    }

}

void HomeScene::drawGUI()
{
    m_guiScriptingManager.draw();
}
