#include "LobbyScene.h"

int lua_lobby_getInfo(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_getInfo) " << lua_gettop(L) << "\n";
        std::cout << lua_tostring(L, 1) << "\n";
        return -1;
    }
    else
    {
        int totalNum = lua_tonumber(L, 1);
        std::vector<std::string> data;
        InfoHolder::getInstance()->getData(data);
        for(int i = 0 ; i < totalNum; i++)
        {
            // std::cout << "push data " << data[i] << "\n";
            lua_pushstring(L, data[i].c_str());
        }
        return totalNum;
    }
    return 0;
}

int lua_lobby_changeScene(lua_State * L)
{
    std::cout << "lua_lobby_changeScene called \n";
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_changeScene) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        // LobbyScene * host = (LobbyScene *)lua_touserdata(L, 1);

        int index = lua_tonumber(L, 1);

        // host->backToHomeMenu()
        
        Feintgine::IMainGame * game =  InfoHolder::getInstance()->getGame();

        if(game)
        {
            std::cout << "(lua_changeScene) change scene to " << index << "\n";
            game->setSceneByIndex(index);
        }
        else
        {
            std::cout << "IMainGame unregistered \n";
        }

    }
    return 0;
}

int lua_backToHomeMenu(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_backToMenu) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::cout << " back to main menu \n";
        LobbyScene * host = (LobbyScene *)lua_touserdata(L, 1);
        host->backToMainMenu();
    }
    return 0;
}


LobbyScene::LobbyScene()
{

}
    

LobbyScene::~LobbyScene()
{
    
}

void LobbyScene::backToMainMenu()
{
    m_currentState = Feintgine::ScreenState::CHANGE_PREVIOUS;
}


LobbyScene::LobbyScene(Feintgine::Window * window)
{
    m_alpha = 0.0f;
    m_window = window;
    m_screenIndex = 2;

    std::cout << "Lobby Scene init \n";
    initShader();
}

void LobbyScene::initShader()
{
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}

void LobbyScene::build()
{
	// build screen (unused)
}

void LobbyScene::destroy()
{
    // unload screen (unused)
}

int LobbyScene::getNextScreenIndex() const
{
    return 12;
}

int LobbyScene::getPreviousScreenIndex() const
{
    return 1;
}


void LobbyScene::onEntry()
{
    std::cout << "lobby scene onEntry \n";

    if(!loaded)
    {
        Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
        loaded = true;
    }

    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	
    m_camera.setPosition(glm::vec2(0, 0));
    m_camera.update();
    m_spriteBatch.init();

    m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));
    std::cout << "after entry \n";
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "now init lua components\n";
    initGUI();
    // glViewport(0, 0, 1366, 768);
    glViewport(0, 0, m_window->getScreenWidth(), m_window->getScreenHeight());

}

void LobbyScene::onExit()
{
    InfoHolder::getInstance()->registerBattleServerIPMap(m_clientScriptingManager->getBattleServerIPMap()); // save the battle 

    m_tgui->removeAllWidgets();

    // InfoHolder::getInstance()->registerClient(m_client);
}

void LobbyScene::backToHomeMenu()
{
    m_currentState = Feintgine::ScreenState::CHANGE_PREVIOUS;
}

void LobbyScene::update(float deltaTime)
{
    if(m_clientScriptingManager)
    {
        m_clientScriptingManager->updateV2(deltaTime);
    }
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->update(deltaTime);
    }
    m_luaTaskManager.update(deltaTime);
    m_luaEventPipeline.update(deltaTime);
}

void LobbyScene::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_shader.use();

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
    // m_bg.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	
	drawGUI();
	SDL_GL_SetSwapInterval(1);
}

void LobbyScene::checkInput()
{
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        m_game->onSDLEvent(evnt);
        if(m_guiScriptingManager)
        {
            m_guiScriptingManager->checkInput(evnt);
        }
        
    }
    handleInput(m_game->m_inputManager);
}


void LobbyScene::handleInput(Feintgine::InputManager & inputManager)
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

    if(m_controlHandler)
    {
        m_controlHandler->handleInput(inputManager);
    }

    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->handleInput(inputManager);
    }
}

void LobbyScene::initGUI()
{
    if(!isInitialized)
    {

        m_script = luaL_newstate();
        luaL_openlibs(m_script);

        m_luaTaskManager.init("../../Lua/system/event/TaskManager.lua",m_script);
        m_luaEventPipeline.init("../../Lua/system/event/EventPipeline.lua",m_script); // must init event pipeline after task manager (use on top of task manager )
        InfoHolder::getInstance()->registerLuaEventPipeline(&m_luaEventPipeline);

        if(!m_guiScriptingManager)
        {
            m_guiScriptingManager = new TGUIScriptingManager();
        }
        
        m_guiScriptingManager->init(m_window,m_script);
        m_skillHandler.init(m_script);
        m_controlHandler = new ControlHandler();
        m_controlHandler->init(m_script,m_window->getWindow(),m_guiScriptingManager);

        InfoHolder::getInstance()->initLuaInterface(m_script);

        unsigned int port = 1123;
        if(!m_clientScriptingManager)
        {
            m_clientScriptingManager = new ClientScriptingManager();
        }
        
        m_client = InfoHolder::getInstance()->getClient();
        m_clientScriptingManager->init("127.0.0.1", port,m_client, m_script);
        m_clientScriptingManager->setIPAddress(InfoHolder::getInstance()->getServerIP());

        m_clientScriptingManager->setBattleServerIPMap(InfoHolder::getInstance()->getBattleServerIPMap());  // recieve the battle server ip map from the storage

        m_clientCharacterHandler = new ClientCharacterHandler();
        m_clientCharacterHandler->init(m_script);

        InfoHolder::getInstance()->registerGame(m_game);

        // InfoHolder::getInstance()->registerClient(m_client);

        isInitialized = true;
    }
    else
    {
        // lua_getglobal(m_script, "Lobby_UpdateInfo");
        // if(lua_isfunction(m_script, -1))
        // {
        //     const int argc = 0;
        //     const int returnCount = 0;
        //     if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        //     {
        //         std::cout << "Lobby scene init script from C++ OK \n";
        //     }
        // }
    }

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/TouhouTB/Lobby/lobbyScene.lua")))
    {
        std::cout << "Run lobby scene script OK \n";
    }
    // InfoHolder::getInstance()->initLuaInterface(m_script);

    lua_register(m_script, "cpp_lobby_getInfo", lua_lobby_getInfo);
    lua_register(m_script, "cpp_lobby_changeScene", lua_lobby_changeScene);
    lua_register(m_script, "cpp_backToHomeMenu", lua_backToHomeMenu);

    m_clientScriptingManager->setCommonHandlingLuaFunction("Lobby_RecieveData");
    m_clientScriptingManager->setWrappedMessageHandlingLuaFunction(ID_TH_TB,"LobbyHandlerWrapResponse");
    m_clientScriptingManager->setWrappedMessageHandlingLuaFunction(ID_TH_TB_BATTLE,"LobbyHandlerBattleResponse");

    m_tgui = m_guiScriptingManager->getTGUI();
    lua_getglobal(m_script, "LobbySceneInit");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        lua_pushlightuserdata(m_script, m_guiScriptingManager);
        lua_pushlightuserdata(m_script, m_clientScriptingManager);
        lua_pushlightuserdata(m_script, m_clientCharacterHandler);
        lua_pushlightuserdata(m_script, &m_skillHandler);
        lua_pushlightuserdata(m_script, m_controlHandler);
        std::cout << "check ref : " << &m_guiScriptingManager << "\n";
        const int argc = 6;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Lobby scene init script from C++ OK \n";
        }
    }
    std::cout << "init GUI (lobby) end \n";
    
}


void LobbyScene::drawGIFScene()
{
    // todo : draw something funny 
}


void LobbyScene::drawLoading()
{
    if(m_tgui_load)
    {
        m_tgui_load->draw();
    }
}

void LobbyScene::drawGUI()
{
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->draw();
    }
}

void LobbyScene::initLoading()
{
    m_tgui_load = new tgui::Gui(m_window->getWindow());
    tgui::Font font_load("font/Chronicle.ttf");
	m_tgui_load->setFont(font_load);

    m_text_load = tgui::Label::create();
	m_text_load->setPosition(m_window->getScreenWidth() / 2, m_window->getScreenHeight() / 2);
	m_text_load->setTextSize(32);
    m_text_load->setOrigin(0.5,0);
	m_text_load->getRenderer()->setTextColor(tgui::Color::White);
	m_text_load->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_load->getRenderer()->setTextOutlineThickness(4);
	m_text_load->setText("Loading ...");
	m_tgui_load->add(m_text_load);
}

