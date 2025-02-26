#ifndef _TGUI_SCRIPTING_MANAGER_H_
#define _TGUI_SCRIPTING_MANAGER_H_


#include <Window.h>
#include <InputManager.h>
#include <map>
#include <set>
#include "../../TGUI_theme/ThemeCreator.hpp"

#include "LuaManager.h"


enum WidgetType 
{
    Label = 1,
    EditBox,
    Panel
};

struct LuaWidgetDataStructure
{
    std::string name;
    WidgetType type;
};

class TGUIScriptingManager
{
    
public:
    TGUIScriptingManager();
    ~TGUIScriptingManager();

    void init(Feintgine::Window * m_window);

    void update(float deltaTime);
    void draw();

    LuaWidgetDataStructure * createGUI(const std::string & name, WidgetType type);

    void handleInput(Feintgine::InputManager & inputManager);

    void addTo(const std::string & childrenTarget, const std::string & parentTarget = "");

private:

    tgui::Gui * m_tgui;

    std::map<std::string, tgui::Label::Ptr> m_labelMap;
    std::map<std::string, tgui::EditBox::Ptr> m_editBoxMap;
    std::map<std::string, tgui::Panel::Ptr> m_panelMap;

    std::vector<LuaWidgetDataStructure *> m_widgets;

    lua_State * m_script = nullptr;

};

#endif