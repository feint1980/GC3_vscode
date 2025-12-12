#include "LobbyScene.h"



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
    std::cout << "after entry \n";




}