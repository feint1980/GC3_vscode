#ifndef _TGUI_SCRIPTING_MANAGER_H_
#define _TGUI_SCRIPTING_MANAGER_H_


#include <Window.h>
#include <InputManager.h>
#include <map>
#include <set>
#include "../../TGUI_theme/ThemeCreator.hpp"
#include <async++.h>
#include "LuaManager.h"

class TGUIScriptingManager
{
    
public:
    TGUIScriptingManager();
    ~TGUIScriptingManager();

    void init(Feintgine::Window * m_window,lua_State * script);

    void update(float deltaTime);
    void draw();
    
    tgui::Label::Ptr createLabel(const std::string & text,float x, float y); 
    
    tgui::RichTextLabel::Ptr createRTLabel(const std::string & text,float x, float y); 

    tgui::Picture::Ptr createPicture(const std::string & path, float x, float y, float width, float height);

    tgui::EditBox::Ptr createEditBox(float x, float y, float width, float height, tgui::Panel::Ptr parent);

    tgui::Panel::Ptr createPanel(float x, float y, float width, float height, tgui::Panel::Ptr parent);

    lua_State * getLuaScript() { return m_script; }

    void checkInput(const SDL_Event &  evnt);

    void handleInput(Feintgine::InputManager & inputManager);

    tgui::Gui * getTGUI() { return m_tgui; }

private:

    tgui::Gui * m_tgui = nullptr;

    lua_State * m_script = nullptr;

};

#endif