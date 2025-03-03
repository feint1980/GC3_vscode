#ifndef _TGUI_SCRIPTING_MANAGER_H_
#define _TGUI_SCRIPTING_MANAGER_H_


#include <Window.h>
#include <InputManager.h>
#include <map>
#include <set>
#include "../../TGUI_theme/ThemeCreator.hpp"
#include <async++.h>
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

    void addChildLabelToParent(LuaWidgetDataStructure * parent, tgui::Label::Ptr label);

    void addChildEditBoxToParent(LuaWidgetDataStructure * parent, tgui::EditBox::Ptr editBox);
    
    void addChildPanelToParent(LuaWidgetDataStructure * parent, tgui::Panel::Ptr panel);
    
    tgui::Label::Ptr createLabel(const std::string & text,float x, float y); 
    

    tgui::EditBox::Ptr createEditBox(const std::string & text,float x, float y, tgui::Panel::Ptr parent);

    tgui::Panel::Ptr createPanel(float x, float y, float width, float height, tgui::Panel::Ptr parent);

    lua_State * getLuaScript() { return m_script; }

    LuaWidgetDataStructure * createGUI(const std::string & name, WidgetType type);

    void checkInput(const SDL_Event &  evnt);

    void handleInput(Feintgine::InputManager & inputManager);

    void addTo(LuaWidgetDataStructure * child, LuaWidgetDataStructure * parent = nullptr);

    tgui::Gui * getTGUI() { return m_tgui; }

private:

    tgui::Gui * m_tgui;

    std::map<std::string, tgui::Label::Ptr> m_labelMap;
    std::map<std::string, tgui::EditBox::Ptr> m_editBoxMap;
    std::map<std::string, tgui::Panel::Ptr> m_panelMap;

    std::set<LuaWidgetDataStructure *> m_widgets;

    lua_State * m_script = nullptr;

};

#endif