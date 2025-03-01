
#include "TGUIScriptingManager.h"


int lua_createWidget(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SendRequest) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host =   static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string requestCmd = lua_tostring(L, 2);
        int type = lua_tonumber(L,3);
        LuaWidgetDataStructure * guiObject = host->createGUI(requestCmd,WidgetType(type));
        lua_pushlightuserdata(L,guiObject);
        return 1;

    }
    return -1;
}

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
    TTF_Init(); // a must

    selectTheme(*m_tgui, "themes/Dark.txt");  // force to load in main thread since the openGL problem, you can only have texture created in mainthread ( OpenGL Context)

    auto loadFontTask = async::spawn([&]() {
        tgui::Font font_load("font/ARIALUNI.ttf");    
        m_tgui->setFont(font_load);
        m_tgui->setTextSize(20);        

    });


    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    // init lua component
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/system/GUI.lua")))
    {
        std::cout << "Run script OK \n";
    }

    // register lua functions

    lua_register(m_script, "cppCreateWidget", lua_createWidget);

    // run Init script
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/system/GUI/tguiScript.lua")))
    {
        std::cout << "Run script OK \n";
    }

    lua_getglobal(m_script, "TGUIScripting_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "TGUI Scripting Init from C++ OK \n";
        }
    }

}

void TGUIScriptingManager::addChildLabelToParent(LuaWidgetDataStructure * parent, tgui::Label::Ptr label)
{
    switch(parent->type)
    {
    case Label:
        // nothing
        std::cout << "attemp to add child to label widget, name : " << parent->name << "\n";
    break;
    case EditBox:
        std::cout << "attemp to add child to editbox widget, name : " << parent->name << "\n";
    break;
    case Panel:
        m_panelMap[parent->name]->add(label);
    break;
    default:
    break;
    }
}


void TGUIScriptingManager::addChildEditBoxToParent(LuaWidgetDataStructure * parent, tgui::EditBox::Ptr editBox)
{
    switch(parent->type)
    {
    case Label:
        // nothing
        std::cout << "attemp to add child to label widget, name : " << parent->name << "\n";
    break;
    case EditBox:
        std::cout << "attemp to add child to editbox widget, name : " << parent->name << "\n";
    break;
    case Panel:
        m_panelMap[parent->name]->add(editBox);
    break;
    default:
    break;
    }
}
    
void TGUIScriptingManager::addChildPanelToParent(LuaWidgetDataStructure * parent, tgui::Panel::Ptr panel)
{
    switch(parent->type)
    {
    case Label:
        // nothing
        std::cout << "attemp to add child to label widget, name : " << parent->name << "\n";
    break;
    case EditBox:
        std::cout << "attemp to add child to editbox widget, name : " << parent->name << "\n";
    break;
    case Panel:
        m_panelMap[parent->name]->add(panel);
    break;
    default:
    break;
    }
}
    
void TGUIScriptingManager::addTo(LuaWidgetDataStructure * child, LuaWidgetDataStructure * parent )
{
    if(!child)
    {
        return;
    }
    

    switch(child->type)
    {
    case Label:
    {
        if(parent)
        {
            addChildLabelToParent(parent, m_labelMap[child->name]);
        }
        else
        {
            m_tgui->add(m_labelMap[child->name]);
        }
    }
    break;
    case EditBox:
    {
        if(parent)
        {
            addChildEditBoxToParent(parent, m_editBoxMap[child->name]);
        }
        else
        {
            m_tgui->add(m_editBoxMap[child->name]);
        }
    }
    break;
    case Panel:
    {
        if(parent)
        {
            addChildPanelToParent(parent, m_panelMap[child->name]);
        }
        else
        {
            m_tgui->add(m_panelMap[child->name]);
        }
    }
    break;
    default:
    break;
    }
    
}

LuaWidgetDataStructure * TGUIScriptingManager::createGUI(const std::string & name, WidgetType type)
{
    LuaWidgetDataStructure * retVal = new LuaWidgetDataStructure;
    retVal->name = name;
    retVal->type = type;
    switch (type)
    {
    case Label:
        m_labelMap[name] = tgui::Label::create();
        // m_tgui->add(m_labelMap[name]);
        break;
    case EditBox:
        m_editBoxMap[name] = tgui::EditBox::create();
        // m_tgui->add(m_editBoxMap[name]);
        break;
    case Panel:
        m_panelMap[name] = tgui::Panel::create();
        // m_tgui->add(m_panelMap[name]);
        break;
    default:
        
    break;
    }
    m_widgets.insert(retVal);

    return retVal;
    
}