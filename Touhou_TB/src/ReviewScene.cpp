#include "ReviewScene.h"

ReviewScene::ReviewScene()
{

}

ReviewScene::~ReviewScene()
{

}

ReviewScene::ReviewScene(Feintgine::Window * window)
{
    m_alpha = 0.0f;
    m_window = window;
    m_screenIndex = 9;
    initShader();
}


void ReviewScene::initShader()
{
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}


void ReviewScene::build()
{
    // build scene (unused)
}

int ReviewScene::getNextScreenIndex() const
{
    return 0;
}


int ReviewScene::getPreviousScreenIndex() const
{
    return 0;
}

void ReviewScene::destroy()
{
    // unload screen (unused) ... yet 
}

void ReviewScene::onEntry()
{
    std::cout << "review scene onEntry \n";

    if(!loaded)
    {
        Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
        loaded = true;
    }

    // init text renderer
    m_textRenderer.init(24,128, "font/ARIALUNI.ttf");

    // loaded = true;
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	
    m_camera.setPosition(glm::vec2(0, 0));
    m_camera.update();
    m_spriteBatch.init();

    // m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/loading.png"),glm::vec2(0,0), glm::vec2(400, 100),Feintgine::Color(255, 255, 255, 255));
    std::cout << "after entry \n";
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "now init lua components\n";
    initGUI();
    // glViewport(0, 0, 1366, 768);
    glViewport(0, 0, m_window->getScreenWidth(), m_window->getScreenHeight());

}


void ReviewScene::initGUI()
{
    if(!isInitialized)
    {
        m_script = luaL_newstate();
        luaL_openlibs(m_script);
        m_luaTaskManager.init("../../Lua/system/event/TaskManager.lua",m_script);
        m_luaEventPipeline.init("../../Lua/system/event/EventPipeline.lua",m_script); // must init event pipeline after task manager (use on top of task manager )
        m_luaPollEvent.init("../../Lua/system/event/PollEvent.lua",m_script);

    
        InfoHolder::getInstance()->registerLuaEventPipeline(&m_luaEventPipeline);

        InfoHolder::getInstance()->registerLuaPollEvent(&m_luaPollEvent);

        if(!m_guiScriptingManager)
        {
            m_guiScriptingManager = new TGUIScriptingManager();
        }
        m_guiScriptingManager->init(m_window,m_script);
        m_skillHandler.init(m_script);
        m_controlHandler = new ControlHandler();
        m_controlHandler->init(m_script,m_window->getWindow(),m_guiScriptingManager);

        InfoHolder::getInstance()->initLuaInterface(m_script);

        if(!m_combatField)
        {
            m_combatField = new CombatField();
        }

        m_combatField->init("../../Lua/TouhouTB/Combat/combatField.lua",m_script);

        if(!m_fieldInfo)
        {
            m_fieldInfo = new FieldInfo();
        }

        m_fieldInfo->init("../../Lua/TouhouTB/Combat/fieldInfo.lua",m_script);


        unsigned int port = 1123;
    
        if(!m_clientCharacterHandler)
        {
            m_clientCharacterHandler = new ClientCharacterHandler();
        }
        
        m_clientCharacterHandler->init(m_script);

        m_luaRenderContext.init(m_script,250);
        m_luaRenderContext.initTextRenderer(24,100, "font/ARIALUNI.ttf");
        isInitialized = true;
    }
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/TouhouTB/Review/reviewScene.lua")))
    {
        std::cout << "Run script ReviewScene.lua OK \n";
    }
    // 

    m_tgui = m_guiScriptingManager->getTGUI();
    lua_getglobal(m_script, "ReviewSceneInit");
    m_argCount = 0;
    if(lua_isfunction(m_script, -1))
    {
        // const int argc = 8;
        // passUserData(this); 
        // passUserData(m_guiScriptingManager);
        // passUserData(m_clientCharacterHandler);
        // passUserData(&m_skillHandler);
        // passUserData(m_controlHandler);
        // passUserData(m_combatField);
        // passUserData(&m_luaRenderContext);
        
        lua_pushlightuserdata(m_script, this);
        lua_pushlightuserdata(m_script, m_guiScriptingManager);
        lua_pushlightuserdata(m_script, m_clientCharacterHandler);
        lua_pushlightuserdata(m_script, &m_skillHandler);
        lua_pushlightuserdata(m_script, m_controlHandler);
        lua_pushlightuserdata(m_script, m_combatField);
        lua_pushlightuserdata(m_script, &m_luaRenderContext);

        const int arc = 7;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arc, returnCount, 0)))
        {
            std::cout << "Combat scene init script from C++ OK \n";
        }
    }

    
}

void ReviewScene::onExit()
{
    // on exit
}

void ReviewScene::setSceneReady(bool value)
{
    m_isSceneReady = value;
}

void ReviewScene::update(float deltaTime)
{
    
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->update(deltaTime);
    }
    m_luaTaskManager.update(deltaTime);
    m_luaEventPipeline.update(deltaTime);
    m_luaPollEvent.update(deltaTime);

    m_luaRenderContext.update(deltaTime);

    if(m_combatField)
    {
        m_combatField->update(deltaTime);
    }
    
}

void ReviewScene::passUserData(void * p)
{
    lua_pushlightuserdata(m_script, p);
    m_argCount++;
}

void ReviewScene::draw()
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
    
    // if(m_combatField)
    // {
    //     m_combatField->draw(m_spriteBatch);
    // }
    
    m_luaRenderContext.draw(m_spriteBatch, &m_camera);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	
    m_luaRenderContext.drawText(m_camera);

	drawGUI();
	SDL_GL_SetSwapInterval(1);

    drawText();
}

void ReviewScene::drawText()
{

    m_textRenderer.begin();

    // m_textRenderer.renderTextBatched( 
	// 		L"FPS :" + 
	// 		feint_common::Instance()->convertStringtoWstring(feint_common::
	// 			Instance()->convertPreciousFloatToString(m_game->getFps())),
	// 		glm::vec2(720, -415), Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);

    if(m_combatField)
    {
        m_combatField->drawText(&m_textRenderer);
    }
    
    m_textRenderer.end(m_camera);

}

void ReviewScene::drawGUI()
{
    if(m_guiScriptingManager)
    {
        m_guiScriptingManager->draw();
    }
}

void ReviewScene::checkInput()
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

void ReviewScene::handleInput(Feintgine::InputManager & inputManager)
{
    // std::cout << "handle input called \n";

    if(m_controlHandler)
    {
        m_controlHandler->handleInput(inputManager);
    }
    if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

    m_luaRenderContext.updateSignals(inputManager);

}

void ReviewScene::sendPollSignal(const std::string& signalName,bool value)
{
    m_luaPollEvent.sendPollSignal(signalName,value);
}