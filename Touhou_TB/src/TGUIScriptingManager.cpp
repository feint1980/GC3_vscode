
#include "TGUIScriptingManager.h"

TGUIScriptingManager::TGUIScriptingManager()
{

}
TGUIScriptingManager::~TGUIScriptingManager()
{

}


void TGUIScriptingManager::update(float deltaTime)
{


}
void TGUIScriptingManager::draw()
{
    if(m_tgui)
    {
        m_tgui->draw();
    }
}

void TGUIScriptingManager::handleInput(Feintgine::InputManager & inputManager)
{

}

void TGUIScriptingManager::init(Feintgine::Window * m_window)
{
    m_tgui = new tgui::Gui(m_window->getWindow());
    TTF_Init();
    
}
