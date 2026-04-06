#include "HomeScene.h"

int lua_getInfo(lua_State * L)
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

int lua_backToMenu(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_backToMenu) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        
        //std::cout << " back to main menu \n";
        HomeScene * host = (HomeScene *)lua_touserdata(L, 1);
        host->backToMainMenu();
    }
    return 0;
}

int lua_changeScene(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_changeScene) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        int index = lua_tonumber(L, 1);
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

HomeScene::HomeScene()
{

}

HomeScene::~HomeScene()
{

}

void HomeScene::backToMainMenu()
{
    m_currentState = Feintgine::ScreenState::CHANGE_PREVIOUS;
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
    if(!loaded)
    {
        Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
        loaded = true;
    }
    std::cout << "after entry \n";

    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	
    m_camera.setPosition(glm::vec2(0, 0));
    m_camera.update();
    m_spriteBatch.init();
    
    float tempScale = 0.85f;
	m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "now init lua components\n";
    initGUI();

    if(SDL_HasScreenKeyboardSupport())
    {
        std::cout << "SDL_HasScreenKeyboardSupport !!!!!!!!!!!!!!!!! \n"; 
    }
    else{
        std::cout << "no SDL_HasScreenKeyboardSupport ##################\n";
    }

    m_gif.init("./Assets/F_AObjects/komachi_chill.xml");
    m_gif.playAnimation("play");
   // m_gif.setScale(glm::vec2(1.7f));

}

void HomeScene::initLoading()
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

void HomeScene::build()
{
	// build screen (unused)
}

void HomeScene::destroy()
{
    // unload screen (unused)
}

void HomeScene::changeSceneIndex(int index)
{
    m_game->setSceneByIndex(index);
    // m_screenIndex = index;
}

int HomeScene::getNextScreenIndex() const
{
    return 12;
}

int HomeScene::getPreviousScreenIndex() const
{
    return 0;
}

void HomeScene::onExit()
{
    // Transfer data to other game
    InfoHolder::getInstance()->registerBattleServerIPMap(m_clientScriptingManager->getBattleServerIPMap()); // save the battle server IP maps

    // InfoHolder::getInstance()->saveServerIP(m_clientScriptingManager->getServerIPAddr());

    InfoHolder::getInstance()->registerClient(m_client);

    // unload screen (unused)
}

void HomeScene::update(float deltaTime)
{
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->update(deltaTime);

    }
    if(m_clientScriptingManager)
    {
        //m_clientScriptingManager->update(deltaTime);
        m_clientScriptingManager->updateV2(deltaTime);
    }
    m_gif.update(deltaTime);
    m_luaTaskManager.update(deltaTime);
    m_luaEventPipeline.update(deltaTime);
    m_luaPollEvent.update(deltaTime);
    // m_luaEventHandler.update(deltaTime);
    
}

void HomeScene::checkInput()
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

    if(m_controlHandler)
    {
        m_controlHandler->handleInput(inputManager);
    }

    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->handleInput(inputManager);
    }

}

void HomeScene::draw()
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
    //m_bg.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	
	drawGUI();
	SDL_GL_SetSwapInterval(1);	
}

void HomeScene::drawGIFScene()
{
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

    m_gif.draw(m_spriteBatch); // F-TODO : draw gif

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();

	SDL_GL_SetSwapInterval(1);	
}


void HomeScene::initGUI()
{
    if(!isInitialized)
    {

    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    // m_luaEventHandler.init(m_script);
    m_luaTaskManager.init("../../Lua/system/event/TaskManager.lua",m_script);

    m_luaEventPipeline.init("../../Lua/system/event/EventPipeline.lua",m_script); // must init event pipeline after task manager (use on top of task manager )

    m_luaPollEvent.init("../../Lua/system/event/PollEvent.lua",m_script);

    InfoHolder::getInstance()->registerLuaEventPipeline(&m_luaEventPipeline);

    m_guiScriptingManager = new TGUIScriptingManager();

    m_guiScriptingManager->addDrawCall("drawGIFScene", std::bind(&HomeScene::drawGIFScene, this));

    m_guiScriptingManager->init(m_window,m_script);
    m_skillHandler.init(m_script);
    m_controlHandler = new ControlHandler();
    m_controlHandler->init(m_script,m_window->getWindow(),m_guiScriptingManager);

    InfoHolder::getInstance()->initLuaInterface(m_script);

    unsigned int port = 1123;
    
    m_client = InfoHolder::getInstance()->getClient();

    if(!m_clientScriptingManager)
    {
        m_clientScriptingManager = new ClientScriptingManager();
    
        m_clientScriptingManager->init("127.0.0.1", port,m_client, m_script);
    }
    m_clientScriptingManager->setIPAddress(InfoHolder::getInstance()->getServerIP());
    
    
    m_clientCharacterHandler = new ClientCharacterHandler();
    m_clientCharacterHandler->init(m_script);

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/TouhouTB/Home/homeScene.lua")))
    {
        std::cout << "Run home scene script OK \n";
    }

    lua_register(m_script, "cpp_getInfo", lua_getInfo);
    lua_register(m_script, "cpp_backToMenu", lua_backToMenu);
    lua_register(m_script, "cpp_changeScene", lua_changeScene);

    // InfoHolder::getInstance()->saveLuaState(m_script);
    // InfoHolder::getInstance()->registerGUIScriptingManager(m_guiScriptingManager);
    InfoHolder::getInstance()->registerGame(m_game);

    m_clientScriptingManager->setCommonHandlingLuaFunction("Client_ReceiveData");
    m_clientScriptingManager->setWrappedMessageHandlingLuaFunction(ID_TH_TB,"ClientHandlerWrapResponse");
    m_clientScriptingManager->setWrappedMessageHandlingLuaFunction(ID_TH_TB_BATTLE,"ClientHandlerBattleResponse");

    lua_getglobal(m_script, "HomeSceneInit");
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
            std::cout << "Home scene init script from C++ OK \n";
        }
    }

    isInitialized = true;
    }
    else
    {
        m_clientScriptingManager->setBattleServerIPMap(InfoHolder::getInstance()->getBattleServerIPMap());
        std::cout << "reconnect attemp \n";
        // m_clientScriptingManager->connect();
        m_clientScriptingManager->setIPAddress(InfoHolder::getInstance()->getServerIP());

        lua_getglobal(m_script, "Arena_Request_ArenaData");
        if(lua_isfunction(m_script, -1))
        {
            const int argc = 0;
            const int returnCount = 0;
            if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
            {
                std::cout << "Home scene init script from C++ OK \n";
            }
        }
    }


    m_clientScriptingManager->setClientEndPoint(m_client);
    
    m_clientScriptingManager->setBattleServerIPMap(InfoHolder::getInstance()->getBattleServerIPMap()); 

}

void HomeScene::drawGUI()
{
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->draw();
    }
}

void HomeScene::drawLoading()
{
    if(m_tgui_load)
    {
        m_tgui_load->draw();
    }
}