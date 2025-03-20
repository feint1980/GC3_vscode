#include "LoginSceneV2.h"


int lua_switchScene(lua_State * L)
{

    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_switchScene) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        
        std::cout << " cpp_switchScene called \n";
        LoginSceneV2 * host = (LoginSceneV2 *)lua_touserdata(L, 1);
        std::string t_id = lua_tostring(L, 2);
        std::string t_pw = lua_tostring(L, 3);
        std::string t_guid = lua_tostring(L, 4);

        host->changeScene(t_id, t_pw, t_guid);

    }
    return 0;
}


void LoginSceneV2::changeScene(const std::string & tID, const std::string & tPW, const std::string & tGUID)
{
    InfoHolder::getInstance()->registerPersonalData(tGUID, tID, tPW);

    m_currentState = Feintgine::ScreenState::CHANGE_NEXT;
}

LoginSceneV2::LoginSceneV2()
{

}


LoginSceneV2::~LoginSceneV2()
{

}

LoginSceneV2::LoginSceneV2(Feintgine::Window * window)
{
    m_alpha = 0.0f;
    m_window = window;
    m_screenIndex = 0;

    initShader();
}

void LoginSceneV2::initShader()
{
    
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}

void LoginSceneV2::onEntry()
{
    
	// Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
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

void LoginSceneV2::build()
{

	// build screen (unused)
}

void LoginSceneV2::destroy()
{
    // unload screen (unused)
}

int LoginSceneV2::getNextScreenIndex() const
{
    return 1;
}

int LoginSceneV2::getPreviousScreenIndex() const
{
    return -1;
}

void LoginSceneV2::onExit()
{

    std::cout << "on exi call \n";
    // m_tgui->;
    m_guiScriptingManager.cleanup();
    // m_shader.dispose();
    // if(m_clientScriptingManager)
    // {
    //     m_clientScriptingManager->cleanUp();
    // }
    // m_spriteBatch.~SpriteBatch();
    // std::cout << "exit call OK \n";
    // unload screen (unused)
}

void LoginSceneV2::update(float deltaTime)
{

    m_guiScriptingManager.update(deltaTime);
    if(m_clientScriptingManager)
    {
        m_clientScriptingManager->update(deltaTime);

    }

}

void LoginSceneV2::checkInput()
{
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        m_game->onSDLEvent(evnt);
        m_guiScriptingManager.checkInput(evnt);
    }
    handleInput(m_game->m_inputManager);
    
}

void LoginSceneV2::handleInput(Feintgine::InputManager & inputManager)
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

void LoginSceneV2::draw()
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


void LoginSceneV2::initGUI()
{

    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    m_guiScriptingManager.init(m_window,m_script);

    m_clientScriptingManager = new ClientScriptingManager();

    // m_clientScriptingManager->init("127.0.0.1", 1123,m_script);

    m_client = RakNet::RakPeerInterface::GetInstance();



    unsigned int port = 1123;
    m_client->AllowConnectionResponseIPMigration(false);
    RakNet::SocketDescriptor socketDescriptor = RakNet::SocketDescriptor(0, 0);
    socketDescriptor.socketFamily = AF_INET;
    m_client->Startup(8, &socketDescriptor, 1);
    m_client->SetOccasionalPing(true);
    m_clientScriptingManager->init("192.168.0.27", port, m_client, m_script);


    // m_clientScriptingManager.init("127.0.0.1", 1123,m_script);

    InfoHolder::getInstance()->registerClient(m_client);

    // inverse case
    //m_script = m_guiScriptingManager.getLuaScript();
    //luaL_openlibs(m_script);

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/Login/loginScene.lua")))
    {
        std::cout << "Run loginScene script OK \n";
    }


    lua_register(m_script, "cpp_switchScene", lua_switchScene);

    lua_getglobal(m_script, "LoginSceneInit");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        lua_pushlightuserdata(m_script, &m_guiScriptingManager);
        lua_pushlightuserdata(m_script, m_clientScriptingManager);
        std::cout << "check ref : " << &m_guiScriptingManager << "\n";
        const int argc = 3;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Login scene init script from C++ OK \n";
        }
    }
}

void LoginSceneV2::drawGUI()
{
    m_guiScriptingManager.draw();
}
