#include "CombatScene.h"

CombatScene::CombatScene()
{

}

CombatScene::~CombatScene()
{

}


CombatScene::CombatScene(Feintgine::Window * window)
{
    m_alpha = 0.0f;
    m_window = window;
    m_screenIndex = 3;
    initShader();
}


void CombatScene::initShader()
{
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}


void CombatScene::build()
{
    // build scene (unused)
}

int CombatScene::getNextScreenIndex() const
{
    return 13;
}


int CombatScene::getPreviousScreenIndex() const
{
    return 1;
}

void CombatScene::destroy()
{
    // unload screen (unused) ... yet 
}

void CombatScene::onEntry()
{
    std::cout << "combat scene onEntry \n";

    if(!loaded)
    {
        Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
        loaded = true;
    }

    // loaded = true;
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	
    m_camera.setPosition(glm::vec2(0, 0));
    m_camera.update();
    m_spriteBatch.init();

    m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/loading.png"),glm::vec2(0,0), glm::vec2(400, 100),Feintgine::Color(255, 255, 255, 255));
    std::cout << "after entry \n";
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "now init lua components\n";
    initGUI();
    glViewport(0, 0, 1366, 768);

}


void CombatScene::initGUI()
{
    if(!isInitialized)
    {
        m_script = luaL_newstate();
        luaL_openlibs(m_script);
        m_luaTaskManager.init("../../Lua/system/event/TaskManager.lua",m_script);

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

        if(!m_clientCharacterHandler)
        {
            m_clientCharacterHandler = new ClientCharacterHandler();
        }
        
        m_clientCharacterHandler->init(m_script);

        isInitialized = true;
    }
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/TouhouTB/Combat/CombatScene.lua")))
    {
        std::cout << "Run script CombatScene.lua OK \n";
    }
    m_clientScriptingManager->setCommonHandlingLuaFunction("Combat_RecieveData");
    m_clientScriptingManager->setWrappedMessageHandlingLuaFunction(ID_TH_TB,"CombatHandlerWrapResponse");
    m_clientScriptingManager->setWrappedMessageHandlingLuaFunction(ID_TH_TB_BATTLE,"CombatHandlerBattleResponse");

    m_tgui = m_guiScriptingManager->getTGUI();
    lua_getglobal(m_script, "CombatSceneInit");
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
            std::cout << "Combat scene init script from C++ OK \n";
        }
    }
}


void CombatScene::onExit()
{
    // on exit
}



void CombatScene::update(float deltaTime)
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
}


void CombatScene::draw()
{
    if(!loaded)
    {
        return;
    }
    
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
    m_bg.draw(m_spriteBatch);
    
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	
	drawGUI();
	SDL_GL_SetSwapInterval(1);

}

void CombatScene::drawGUI()
{
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->draw();
    }
}

void CombatScene::checkInput()
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

void CombatScene::handleInput(Feintgine::InputManager & inputManager)
{
    if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

}
