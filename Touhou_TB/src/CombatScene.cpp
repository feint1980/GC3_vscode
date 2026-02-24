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

    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	
    m_camera.setPosition(glm::vec2(0, 0));
    m_camera.update();
    m_spriteBatch.init();

    m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));
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
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/CombatScene.lua")))
    {
        std::cout << "Run script CombatScene.lua OK \n";
    }
    

}


void CombatScene::onExit()
{
    // on exit
}



void CombatScene::update(float deltaTime)
{

}


void CombatScene::draw()
{

}


void CombatScene::checkInput()
{

}
