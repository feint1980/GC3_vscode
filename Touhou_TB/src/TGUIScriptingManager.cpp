#include "TGUIScriptingManager.h"
#include "lua.h"

int luaCallbackRef = LUA_NOREF;
// MARK: Panel
int lua_Panel_Create(lua_State * L)
{
    if(lua_gettop(L) < 5 || lua_gettop(L) > 6)
    {
        std::cout << "gettop failed (lua_Panel_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        float pX = lua_tonumber(L, 2);
        float pY = lua_tonumber(L, 3);
        float width = lua_tonumber(L, 4);
        float height = lua_tonumber(L, 5);
        
        tgui::Panel::Ptr * panel = new tgui::Panel::Ptr();

        if(lua_gettop(L) == 6)
        {
            tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 6));
            if(parent)
            {
                *panel = host->createPanel(pX, pY, width, height, *parent);
                
            }
            else
            {
                *panel = host->createPanel(pX, pY, width, height,nullptr);
            }
        }
        else
        {
    
            *panel = host->createPanel(pX, pY, width, height,nullptr);
        }
        
        lua_pushlightuserdata(L, panel);
        return 1;
    }
    return -1;
}

int lua_Panel_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Panel_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        std::string strX = lua_tostring(L, 2);
        std::string strY = lua_tostring(L, 3);
        panel->get()->setPosition(strX.c_str(), strY.c_str());
    }
    return 0;
}

int lua_Panel_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Panel_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        float width = lua_tonumber(L, 2);
        float height = lua_tonumber(L, 3);
        panel->get()->setSize({width, height});
    }
    return 0;
}

int lua_Panel_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Panel_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        std::string width = lua_tostring(L, 2);
        std::string height = lua_tostring(L, 3);
        panel->get()->setSize(width.c_str(), height.c_str());
    }
    return 0;
}

int lua_Panel_HideWithEffect(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Panel_HideWithEffect) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        int type = lua_tonumber(L,2);
        int time = lua_tonumber(L, 3);
        panel->get()->hideWithEffect((tgui::ShowEffectType)type, std::chrono::milliseconds(time));
        panel->get()->moveToBack();
        return 0;
    }
}

int lua_Panel_ShowWithEffect(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Panel_ShowWithEffect) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        int type = lua_tonumber(L,2);
        int time = lua_tonumber(L, 3);
        panel->get()->showWithEffect((tgui::ShowEffectType)type, std::chrono::milliseconds(time));
        panel->get()->moveToFront();
        return 0;
    }
}

int lua_Panel_setVisible(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_setVisible) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        bool visible = lua_toboolean(L, 2);
        panel->get()->setVisible(visible);
        return 0;
    }

}

int lua_Panel_SetAlignment(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Label_SetAlignment) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr *>(lua_touserdata(L, 1));
        float originX = lua_tonumber(L,2);
        float originY = lua_tonumber(L,3);
        panel->get()->setOrigin(0.5,0.5);
    }
    return 0;
}

int lua_Panel_SetHoverOnCallback(lua_State * L)
{
    // std::cout << "lua_Panel_SetHoverOnCallback called \n";
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_SetHoverOnCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        // std::cout << "lua_Panel_SetHoverOnCallback called \n";
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr *>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){
            lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);
        };
        // callback();
        panel->get()->onMouseEnter.disconnectAll();
        panel->get()->onMouseEnter(callback);
    }
    return 0;
}

int lua_Panel_SetHoverOffCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_SetHoverOffCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr *>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        panel->get()->onMouseLeave.disconnectAll();
        panel->get()->onMouseLeave(callback);
    }
    return 0;
}

int lua_Panel_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Panel_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        float pX = lua_tonumber(L, 2);
        float pY = lua_tonumber(L, 3);
        panel->get()->setPosition({pX, pY});
    }
    return 0;
}

int lua_Panel_SetBorderColor(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_Panel_SetBorderColor) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        int r = lua_tonumber(L, 2);
        int g = lua_tonumber(L, 3);
        int b = lua_tonumber(L, 4);
        int a = lua_tonumber(L, 5);
        tgui::Color color = tgui::Color(r, g, b, a);
        panel->get()->getRenderer()->setBorderColor(color);
        // panel->get()->getRenderer()->setBackgroundColor
    }
    return 0;
}

int lua_Panel_SetOpacity(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_SetOpacity) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        float value = lua_tonumber(L, 2);
        panel->get()->getRenderer()->setOpacity(value);
        // panel->get()->getRenderer()->setBackgroundColor
    }
    return 0;
}

int lua_Panel_SetOnClickCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_SetOnClickCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        panel->get()->onClick.disconnectAll();
        panel->get()->onClick(callback);
        
    }
    return 0;
}

int lua_Panel_SetOnRightClickCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_SetOnClickCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        panel->get()->onRightClick.disconnectAll();
        panel->get()->onRightClick(callback);
    }
    return 0;
}

int lua_Panel_SetOnDoubleClickCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Panel_SetOnClickCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        // panel->get()->
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        panel->get()->onDoubleClick.disconnectAll();
        panel->get()->onDoubleClick(callback);
    }
    return 0;
}
int lua_Panel_GetSize(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Panel_GetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        tgui::Vector2f size = panel->get()->getSize();
        // tgui::Gui::get
        lua_pushnumber(L, size.x);
        lua_pushnumber(L, size.y);
        return 2;
    }
    return 0;
}

int lua_Panel_RemoveHoverOnCallback(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Panel_RemoveHoverOnCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        panel->get()->onMouseEnter.disconnectAll();
    }
    return 0;
}

int lua_Panel_RemoveHoverOffCallback(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Panel_RemoveHoverOffCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        panel->get()->onMouseLeave.disconnectAll();
    }
    return 0;
}

int lua_Panel_GetPos(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Panel_GetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 1));
        tgui::Vector2f pos = panel->get()->getAbsolutePosition();
        // tgui::Gui::getfo
        lua_pushnumber(L, pos.x);
        lua_pushnumber(L, pos.y);
        return 2;
    }
    return 2;
}


// MARK: EditBox

int lua_EditBox_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_EditBox_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));
        float pX = lua_tonumber(L, 2);
        float pY = lua_tonumber(L, 3);
        editBox->get()->setPosition({pX, pY});
    }
    return 0;
}

int lua_EditBox_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_EditBox_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));
        std::string pX = lua_tostring(L,2);
        std::string pY = lua_tostring(L,3);
        editBox->get()->setPosition(pX.c_str(), pY.c_str());
    }
    return 0;
}

int lua_EditBox_SetSize(lua_State *L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_EditBox_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));
        float pX = lua_tonumber(L, 2);
        float pY = lua_tonumber(L, 3);
        editBox->get()->setSize({pX, pY});
    }
    return 0;
}

int lua_EditBox_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_EditBox_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));
        std::string pX = lua_tostring(L,2);
        std::string pY = lua_tostring(L,3);
        editBox->get()->setSize(pX.c_str(), pY.c_str());
    }
    return 0;
}

int lua_EditBox_SetPWChar(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_EditBox_SetPWChar) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));
        char tC = lua_tostring(L, 2)[0];
        editBox->get()->setPasswordCharacter(tC);
        return 0;
    }
    return -1;
}

int lua_EditBox_SetText(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_EditBox_SetText) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        editBox->get()->setText(text.c_str());
        return 0;
    }
    return -1;
}

int lua_EditBox_GetText(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_EditBox_GetText) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::EditBox::Ptr * editBox = static_cast<tgui::EditBox::Ptr*>(lua_touserdata(L, 1));

        std::string text = editBox->get()->getText().toStdString();
        lua_pushstring(L, text.c_str());
        return 1;
    }
    return 0;
}

int lua_EditBox_Create(lua_State * L)
{
    if(lua_gettop(L) < 5 || lua_gettop(L) > 6)
    {
        std::cout << "gettop failed (lua_EditBox_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        float pX = lua_tonumber(L, 2);
        float pY = lua_tonumber(L, 3);
        float width = lua_tonumber(L, 4);
        float height = lua_tonumber(L, 5);
        tgui::EditBox::Ptr * editBox = new tgui::EditBox::Ptr();
        if(lua_gettop(L) == 6)
        {
            tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 6));
            if(parent)
            {
                *editBox = host->createEditBox(pX,pY,width,height,*parent);
            }
            else
            {
                *editBox = host->createEditBox(pX,pY,width,height,nullptr);
            }
        }
        else
        {
            *editBox = host->createEditBox(pX,pY,width,height,nullptr);
        }
        lua_pushlightuserdata(L, editBox);
        return 1;
    }
    return -1;
}

// MARK: Label / RTLabel

int lua_Label_SetText(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Label_SetText) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        label->get()->setText(text);
    }
    return 0;
}

int lua_RTLabel_SetText(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RTLabel_SetText) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        label->get()->setText(text);
    }
    return 0;
}

int lua_Label_SetAlignment(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Label_SetAlignment) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr *>(lua_touserdata(L, 1));
        int aligmentType = lua_tonumber(L, 2);
        // 0 left, 1 center, 2 right
        if(label->get())
        {
        
        }
        else
        {
            std::cout << "label is null " << "\n";
            return -1;
        }
        switch(aligmentType)
        {
            case 0:// left
            {
                // left plank (default by C++)
                return 0;
            }
            break;
            case 1:// center
            {
                label->get()->setOrigin(0.5,0);
                label->get()->setAutoSize(true);
                return 0;
            }
            break;
            case 2:// right
            {
                // todo later
                label->get()->setOrigin(1.0,0);
                label->get()->setAutoSize(true);
                return 0;
            }
            break;
            default:
            {
                std::cout << "lua_Label_SetAlignment failed (lua_Label_SetAlignment) " << lua_gettop(L) << "\n";
                return -1;
            }
            break;
        }
        return 0;
    }
    return 0;
}

int lua_RTLabel_SetAlignment(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RTLabel_SetAlignment) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr *>(lua_touserdata(L, 1));
        int aligmentType = lua_tonumber(L, 2);
        // 0 left, 1 center, 2 right
        switch(aligmentType)
        {
            case 0:// left
            {
                // left plank (default by C++)
            }
            break;
            case 1:// center
            {
                label->get()->setOrigin(0.5,0);
                label->get()->setAutoSize(true);
            }
            break;
            case 2:// right
            {
                // todo later
            }
            break;
            default:
            {
                std::cout << "lua_RTLabel_SetAlignment failed (lua_Label_SetAlignment) " << lua_gettop(L) << "\n";
                return -1;
            }
            break;
        }
    }
    return 0;
}

int lua_Label_SetTextColor(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_Label_SetTextColor) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        int r = lua_tonumber(L, 2);
        int g = lua_tonumber(L, 3);
        int b = lua_tonumber(L, 4);
        int a = lua_tonumber(L, 5);
        label->get()->getRenderer()->setTextColor(tgui::Color(r,g,b,a));
        // label->get()->setTextColor(tgui::Color(r,g,b,a));
    }
    return 0;
}

int lua_RTLabel_SetTextColor(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_RTLabel_SetTextColor) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        int r = lua_tonumber(L, 2);
        int g = lua_tonumber(L, 3);
        int b = lua_tonumber(L, 4);
        int a = lua_tonumber(L, 5);
        label->get()->getRenderer()->setTextColor(tgui::Color(r,g,b,a));
    }
    return 0;
}

int lua_Label_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Label_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        std::string strX = lua_tostring(L, 2);
        std::string strY = lua_tostring(L, 3);
    
        label->get()->setPosition(strX.c_str(),strY.c_str());
    }
    return 0;
}

int lua_RTLabel_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_RTLabel_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        std::string strX = lua_tostring(L, 2);
        std::string strY = lua_tostring(L, 3);
    
        label->get()->setPosition(strX.c_str(),strY.c_str());
    }
    return 0;
}

int lua_Label_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Label_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        float fX = 0;
        float fY = 0;
        fX = lua_tonumber(L, 2);
        fY = lua_tonumber(L, 3);
        label->get()->setPosition(fX,fY);    
    }
    return 0;
}

int lua_RTLabel_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_RTLabel_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
    
        float fX = 0;
        float fY = 0;
        fX = lua_tonumber(L, 2);
        fY = lua_tonumber(L, 3);
        label->get()->setPosition(fX,fY);    
    }
    return 0;
}

int lua_Label_SetOnHoverCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Label_SetOnHoverCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onMouseEnter(callback);
    }
    return 0;
}

int lua_RTLabel_SetOnHoverCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RTLabel_SetOnHoverCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onMouseEnter(callback);
    }
    return 0;
}

int lua_Label_SetOffHoverCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Label_SetOffHoverCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        label->get()->onMouseLeave.disconnectAll();
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onMouseLeave(callback);
    }
    return 0;
}

int lua_RTLabel_SetOffHoverCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RTLabel_SetOffHoverCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onMouseLeave(callback);
    }
    return 0;
}

int lua_Label_SetOnClickCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Label_SetOnClickCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));           
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);;
        label->get()->onClick.disconnectAll();
        std::function<void()> callback = [L,ref](){
            // std::cout << "ref is " << ref << "\n";
            lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);
        };
        // lua_pop(L, 1);
        label->get()->onClick(callback);
    }
    return 0;
}

int lua_Label_SetScale(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Label_SetScale) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        float scale = lua_tonumber(L, 2);
        label->get()->setScale(scale);
    }
    return 0;
}

int lua_Label_GetPos(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Label_GetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        tgui::Vector2f pos = label->get()->getAbsolutePosition();
        tgui::Vector2f size = label->get()->getFullSize() ;
        // tgui::Vector2f scale = label->get()->getSiz();
        lua_pushnumber(L, pos.x + (size.x * 0.5f));
        lua_pushnumber(L, pos.y + (size.y * 0.5f));

    }
    return 2;
}

int lua_Label_GetText(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Label_GetText) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        std::string text = label->get()->getText().toStdString();
        //  text = label->get()->getText();
        lua_pushstring(L, text.c_str());
    }
    return 1;
}


int lua_RTLabel_SetOnClickCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RTLabel_SetOnClickCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 1));
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        label->get()->onClick.disconnectAll();
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onClick(callback);
    }
    return 0;
}

int lua_RTLabel_SetScale(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RTLabel_SetScale) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        float scale = lua_tonumber(L, 2);
        label->get()->setScale(scale);
    }
    return 0;
}

int lua_Label_Create(lua_State * L)
{
    if(lua_gettop(L) < 4 || lua_gettop(L) > 5)
    {
        std::cout << "gettop failed (lua_Label_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host =   static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        float x = lua_tonumber(L, 3);
        float y = lua_tonumber(L, 4);
        tgui::Label::Ptr * label = new tgui::Label::Ptr();
        *label = host->createLabel(text,x,y);
        if(lua_gettop(L) == 5)
        {
            tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 5));
            if(parent)
            {
                parent->get()->add(*label);
            }
            else
            {
                host->getTGUI()->add(*label);
            }
        }
        else
        {
            host->getTGUI()->add(*label);
        }
        lua_pushlightuserdata(L,label);
        return 1;
    }
    return 0;
}

int lua_RTLabel_Create(lua_State * L)
{
    if(lua_gettop(L) < 4 || lua_gettop(L) > 5)
    {
        std::cout << "gettop failed (lua_RTLabel_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host =   static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        float x = lua_tonumber(L, 3);
        float y = lua_tonumber(L, 4);
        tgui::RichTextLabel::Ptr * label = new tgui::RichTextLabel::Ptr();
        *label = host->createRTLabel(text,x,y);
        
        label->get()->getRenderer()->setTextColor(tgui::Color::White);
        label->get()->getRenderer()->setBorderColor(tgui::Color::Black);
        if(lua_gettop(L) == 5)
        {
            tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 5));
            if(parent)
            {
                parent->get()->add(*label);
            }
            else
            {
                host->getTGUI()->add(*label);
            }
        }
        else
        {
            host->getTGUI()->add(*label);
        }
        lua_pushlightuserdata(L,label);
        return 1;
    }
    return 0;
}

int lua_RTLabel_GetSize(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_RTLabel_GetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));

        auto size = label->get()->getFullSize();
        lua_pushnumber(L,size.x);
        lua_pushnumber(L,size.y);
        return 2;

    }
    return 0;
}

int lua_RTLabel_GetPos(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_RTLabel_GetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::RichTextLabel::Ptr * label = static_cast<tgui::RichTextLabel::Ptr*>(lua_touserdata(L, 1));
        auto pos = label->get()->getPosition();
        lua_pushnumber(L,pos.x);
        lua_pushnumber(L,pos.y);
        return 2;
    }
    return 0;
}

// MARK: Picture
int lua_Picture_Create(lua_State * L)
{
    if(lua_gettop(L) < 6 || lua_gettop(L) > 7)
    {
        std::cout << "gettop failed (lua_Picture_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host =   static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string path = lua_tostring(L, 2);
        float x = lua_tonumber(L, 3);
        float y = lua_tonumber(L, 4);
        float width = lua_tonumber(L, 5);
        float height = lua_tonumber(L, 6);
        tgui::Picture::Ptr * picture = new tgui::Picture::Ptr();

        tgui::Panel::Ptr * parent = nullptr;
        parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 7));
        *picture = host->createPicture(path,x,y,width,height);
        if(lua_gettop(L) == 7)
        {
            if(parent && parent->get())
            {
                parent->get()->add(*picture);
            }
            else
            {
                host->getTGUI()->add(*picture);
            }
        }
        else
        {
            host->getTGUI()->add(*picture);
        }
        // host->getTGUI()->add(*picture);
        lua_pushlightuserdata(L,picture);
        return 1;
    }
    return 0;
}

int lua_Picture_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Picture_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Picture::Ptr * picture = static_cast<tgui::Picture::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        picture->get()->setPosition(x,y);
    }
    return 0;
}

int lua_Picture_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Picture_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Picture::Ptr * picture = static_cast<tgui::Picture::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        picture->get()->setPosition(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_Picture_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Picture_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Picture::Ptr * picture = static_cast<tgui::Picture::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        picture->get()->setSize(x,y);
    }
    return 0;
}

int lua_Picture_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Picture_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Picture::Ptr * picture = static_cast<tgui::Picture::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        picture->get()->setSize(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_Picture_SetTexture(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Picture_SetTexture) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Picture::Ptr * picture = static_cast<tgui::Picture::Ptr*>(lua_touserdata(L, 1));
        std::string path = lua_tostring(L, 2);
        tgui::Texture texture(path);
        picture->get()->getRenderer()->setTexture(texture);
    }
    return 0;
}

int lua_TabContainer_Create(lua_State * L)
{
    // std::cout << "lua_TabContainer_Create called !!!!!!! \n";
    if(lua_gettop(L) < 5 || lua_gettop(L) > 6)
    {
        std::cout << "gettop failed (lua_TabContainer_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        float width = lua_tonumber(L, 4);
        float height = lua_tonumber(L, 5); 
        tgui::TabContainer::Ptr * tabsContainer = new tgui::TabContainer::Ptr(); 

        *tabsContainer = host->createTabContainer(x,y,width,height);

        if(lua_gettop(L) == 6)
        {
            tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 6));
            if(parent)
            {
                parent->get()->add(*tabsContainer);
            }
            else
            {
                host->getTGUI()->add(*tabsContainer);
            }
        }
        else
        {
            host->getTGUI()->add(*tabsContainer);
        }
        // std::cout << "tabsContainer: " << tabsContainer << "\n";
        lua_pushlightuserdata(L,tabsContainer);
        return 1;
    }
    return 0;
}

// MARK: TabContainer

int lua_TabContainer_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_TabContainer_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * tabsContainer = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        tabsContainer->get()->setPosition(x,y);
    }
    return 0;
}

int lua_TabContainer_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_TabContainer_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * tabsContainer = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        tabsContainer->get()->setPosition(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_TabContainer_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_TabContainer_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * tabsContainer = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        float width = lua_tonumber(L, 2);
        float height = lua_tonumber(L, 3);
        tabsContainer->get()->setSize(width,height);
    }
    return 0;
}

int lua_TabContainer_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_TabContainer_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * tabsContainer = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        std::string width = lua_tostring(L, 2);
        std::string height = lua_tostring(L, 3);
        tabsContainer->get()->setSize(width.c_str(),height.c_str());
    }
    return 0;
}

int lua_TabContainer_AddTab(lua_State * L)
{
    if(lua_gettop(L) < 2 || lua_gettop(L) > 3)
    {
        std::cout << "gettop failed (lua_TabContainer_AddTab) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * tabsContainer = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        std::string TabName = lua_tostring(L, 2);
        tgui::Panel::Ptr * panel = new tgui::Panel::Ptr();

        bool setActive = false;
        if(lua_gettop(L) == 3)
        {
            setActive = lua_toboolean(L, 3);
        }
        *panel = tabsContainer->get()->addTab(TabName.c_str(),setActive);
        // std::cout << "panel created " << panel << "\n";
        lua_pushlightuserdata(L,panel);
        return 1;
    }
    return 0;
}

int lua_TabContainer_SetAlignment(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_TabContainer_SetAlignment) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * scrollablePanel = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        float originX = lua_tonumber(L, 2);
        float originY = lua_tonumber(L, 3);
        scrollablePanel->get()->setOrigin(originX,originY);
    }
    return 0;
}

int lua_TabContainer_SetTabFixedSize(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_TabContainer_SetTabFixedSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::TabContainer::Ptr * scrollablePanel = static_cast<tgui::TabContainer::Ptr*>(lua_touserdata(L, 1));
        float width = lua_tonumber(L, 2);
        scrollablePanel->get()->setTabFixedSize(width);
    }
    return 0;
}

int lua_Button_Create(lua_State * L)
{

    if(lua_gettop(L) < 6 || lua_gettop(L) > 7)
    {
        std::cout << "gettop failed (lua_Label_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host =   static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        float x = lua_tonumber(L, 3);
        float y = lua_tonumber(L, 4);
        float width = lua_tonumber(L, 5);
        float height = lua_tonumber(L, 6);
        tgui::Button::Ptr * button = new tgui::Button::Ptr();
        
        std::cout << "create button with " << lua_gettop(L) << "\n";
        if(lua_gettop(L) == 7)
        {
            tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 7));
            
            *button = host->createButton(text,x,y,width,height,*parent);

        }
        else
        {
            *button = host->createButton(text,x,y,width,height,nullptr);
        }
        lua_pushlightuserdata(L,button);
        return 1;
    }
    return 0;
}

int lua_Button_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Button_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Button::Ptr * button = static_cast<tgui::Button::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        button->get()->setPosition(x,y);
    }
    return 0;
}


int lua_Button_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Button_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Button::Ptr * button = static_cast<tgui::Button::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        button->get()->setPosition(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_Button_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Button_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Button::Ptr * button = static_cast<tgui::Button::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        button->get()->setSize(x,y);
    }
    return 0;
}

int lua_Button_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Button_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Button::Ptr * button = static_cast<tgui::Button::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        button->get()->setSize(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_Button_SetOnClickCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Button_SetOnClickCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::Button::Ptr * button = static_cast<tgui::Button::Ptr*>(lua_touserdata(L, 1));
        
        
        if(!lua_isfunction(L, 2))
        {
            std::cout << "param 2 is not a function \n";
            return -1;
        }
        lua_pushvalue(L, 2);
        button->get()->onClick.disconnectAll();
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        button->get()->onClick(callback);
        
    }
    return 0;
}


// MARK: ScrollablePanel

int lua_ScrollablePanel_Create(lua_State * L)
{
    if(lua_gettop(L) < 5 || lua_gettop(L) > 6)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        float width = lua_tonumber(L, 4);
        float height = lua_tonumber(L, 5);
        tgui::ScrollablePanel::Ptr * scrollablePanel = new tgui::ScrollablePanel::Ptr();
        tgui::Panel::Ptr * parent = nullptr;
        if(lua_gettop(L) == 6)
        {
            parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 6));
        }
        *scrollablePanel = host->createScrollablePanel(x,y,width,height,*parent);
        lua_pushlightuserdata(L,scrollablePanel);
        return 1;
    }
    return 0;
}

int lua_ScrollablePanel_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        scrollablePanel->get()->setPosition(x,y);
    }
    return 0;
}

int lua_ScrollablePanel_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        scrollablePanel->get()->setPosition(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_ScrollablePanel_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        float width = lua_tonumber(L, 2);
        float height = lua_tonumber(L, 3);
        scrollablePanel->get()->setSize(width,height);
    }
    return 0;
}

int lua_ScrollablePanel_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        std::string width = lua_tostring(L, 2);
        std::string height = lua_tostring(L, 3);
        scrollablePanel->get()->setSize(width.c_str(),height.c_str());
    }
    return 0;
}

int lua_ScrollablePanel_HideWithEffect(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_HideWithEffect) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        int type = lua_tonumber(L,2);
        int time = lua_tonumber(L, 3);
        scrollablePanel->get()->hideWithEffect((tgui::ShowEffectType)type, std::chrono::milliseconds(time));
    }
    return 0;
}

int lua_ScrollablePanel_ShowWithEffect(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_ShowWithEffect) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        int type = lua_tonumber(L,2);
        int time = lua_tonumber(L, 3);
        scrollablePanel->get()->showWithEffect((tgui::ShowEffectType)type, std::chrono::milliseconds(time));
    }
    return 0;
}

int lua_ScrollablePanel_setVisible(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_setVisible) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        bool visible = lua_toboolean(L, 2);
        scrollablePanel->get()->setVisible(visible);
    }
    return 0;
}

int lua_ScrollablePanel_SetAlignment(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Label_SetAlignment) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * panel = static_cast<tgui::ScrollablePanel::Ptr *>(lua_touserdata(L, 1));
        float originX = lua_tonumber(L,2);
        float originY = lua_tonumber(L,3);
        panel->get()->setOrigin(0.5,0.5);
    }
    return 0;
}

int lua_ScrollablePanel_GetSize(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_GetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * scrollablePanel = static_cast<tgui::ScrollablePanel::Ptr*>(lua_touserdata(L, 1));
        auto size = scrollablePanel->get()->getContentSize();
        lua_pushnumber(L,size.x);
        lua_pushnumber(L,size.y);
        return 2;
    }

    return 1;
}

int lua_ScrollablePanel_ClearItems(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_ScrollablePanel_ClearItems) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ScrollablePanel::Ptr * panel = static_cast<tgui::ScrollablePanel::Ptr *>(lua_touserdata(L, 1));
        panel->get()->removeAllWidgets();
    }
    return 0;
}


/// MARK:Canvas


int lua_Canvas_Create(lua_State * L)
{
    if(lua_gettop(L) != 7)
    {
        std::cout << "gettop failed (lua_Canvas_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string name = lua_tostring(L, 2);
        float x = lua_tonumber(L, 3);
        float y = lua_tonumber(L, 4);
        float width = lua_tonumber(L, 5);
        float height = lua_tonumber(L, 6);
    
        tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 7));

        tgui::CanvasOpenGL3::Ptr * canvas = host->createCanvas(name,x,y,width,height,*parent); 
        lua_pushlightuserdata(L,canvas);
    }
    return 1;
}

int lua_Canvas_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Canvas_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::CanvasOpenGL3::Ptr * canvas = static_cast<tgui::CanvasOpenGL3::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        canvas->get()->setPosition(x, y);
    }
    return 0;
}

int lua_Canvas_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Canvas_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::CanvasOpenGL3::Ptr * canvas = static_cast<tgui::CanvasOpenGL3::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L, 3);
        canvas->get()->setPosition(x.c_str(), y.c_str());
    }
    return 0;
}

int lua_Canvas_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Canvas_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::CanvasOpenGL3::Ptr * canvas = static_cast<tgui::CanvasOpenGL3::Ptr*>(lua_touserdata(L, 1));
        float width = lua_tonumber(L, 2);
        float height = lua_tonumber(L, 3);
        canvas->get()->setSize(width, height);
    }
    return 0;
}

int lua_Canvas_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Canvas_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::CanvasOpenGL3::Ptr * canvas = static_cast<tgui::CanvasOpenGL3::Ptr*>(lua_touserdata(L, 1));
        std::string width = lua_tostring(L, 2);
        std::string height = lua_tostring(L, 3);
        canvas->get()->setSize(width.c_str(), height.c_str());
    }
    return 0;
}

int lua_Canvas_BindDrawCall(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Canvas_BindDrawCall) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string name = lua_tostring(L, 2);
        std::string drawCallName = lua_tostring(L, 3);

        //std::function<void()> draw = host->getDrawCall(drawCallName);

        host->bindCanvasDrawCall(name,host->getDrawCall(drawCallName));
    }
    return 0;
}


// MARK:ListView 

int lua_ListView_Create(lua_State * L)
{
    std::cout << "lua_ListView_Create called \n";
    if(lua_gettop(L) < 7 || lua_gettop(L) > 8)
    {
        std::cout << "gettop failed (lua_ListView_Create) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::cout << "clean called \n";
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L,3);
        float width = lua_tonumber(L, 4);
        float height = lua_tonumber(L, 5);
        std::cout << "before check table \n";
        std::vector<std::string> collumsNames;
        if(!lua_istable(L, 6))
        {
            std::cout  << "lua_istable failed (lua_ListView_Create), expected table (collumNames)" << "\n";
        }
        else
        {
            std::cout << "table found  \n";
            lua_pushnil(L);
            // int index = 0;
            while(lua_next(L,6) != 0) //extract table format
            {
                // std::cout << "processing " << index++ << "\n";

                if(lua_isstring(L,-1))
                {
                    collumsNames.push_back(lua_tostring(L,-1));
                    // std::cout << "pushed back " << collumsNames.back() << "\n";
                }
                else
                {
                    std::cout << "lua_isstring failed (lua_ListView_Create), expected string " << lua_gettop(L) << "\n";
                    return -1;
                }
                lua_pop(L,1);
            }
        }
        std::vector<float> collumsSizes;
        if(!lua_istable(L, 7))
        {
            std::cout  << "lua_istable failed (lua_ListView_Create), expected table (collumSizes)" << "\n";
            return -1;
        }
        else
        {
            lua_pushnil(L);
            // int index = 0;
            while(lua_next(L,7) != 0) //extract table format
            {
                // std::cout << "processing " << index++ << "\n";
                if(lua_isnumber(L,-1))
                {
                    collumsSizes.push_back(lua_tonumber(L,-1));
                    // std::cout << "pushed back " << collumsSizes.back() << "\n";
                }
                else
                {
                    std::cout << "lua_isstring failed (lua_ListView_Create), expected string " << lua_gettop(L) << "\n";
                    return -1;
                }
                lua_pop(L,1);
            }

        }


    tgui::ListView::Ptr * listView = new tgui::ListView::Ptr();

    if(lua_gettop(L) == 8)
    {
    tgui::Panel::Ptr * parent = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 8));

    if(parent)
    {
        *listView = host->createListView(x,y,width,height,collumsNames,collumsSizes,*parent);
    }
    else
    {
        *listView = host->createListView(x,y,width,height,collumsNames,collumsSizes,nullptr);
    }
    }
    else
    {
        *listView = host->createListView(x,y,width,height,collumsNames,collumsSizes,nullptr);
    }
        lua_pushlightuserdata(L,listView);
        return 1;
    }
    return 0;
}


int lua_ListView_SetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ListView_SetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L,3);
        listView->get()->setPosition(x,y);
    }
    return 0;
}

int lua_ListView_SetPosStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ListView_SetPosStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        std::string x = lua_tostring(L, 2);
        std::string y = lua_tostring(L,3);
        listView->get()->setPosition(x.c_str(),y.c_str());
    }
    return 0;
}

int lua_ListView_SetSize(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ListView_SetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        float width = lua_tonumber(L, 2);
        float height = lua_tonumber(L,3);
        listView->get()->setSize(width,height);
    }
    return 0;
}

int lua_ListView_SetSizeStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_ListView_SetSizeStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        std::string width = lua_tostring(L, 2);
        std::string height = lua_tostring(L,3);
        listView->get()->setSize(width.c_str(),height.c_str());
    }
    return 0;
}

int lua_ListView_GetSize(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_ListView_GetSize) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        float width = listView->get()->getSize().x;
        float height = listView->get()->getSize().y;
        lua_pushnumber(L,width);
        lua_pushnumber(L,height);
        return 2;
    }
    return 0;
}

int lua_ListView_SetColumnSizeRatios(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_ListView_SetColumnSizeRatioss) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        std::vector<float> ratios;

        if(!lua_istable(L,2))
        {
            std::cout << "gettop failed (lua_ListView_SetColumnSizeRatioss) " << lua_gettop(L) << "\n";
            return -1;
        }
        else
        {
            lua_pushnil(L);
            while(lua_next(L,2) != 0)
            {
                if(lua_isnumber(L,-1))
                {
                    ratios.push_back(lua_tonumber(L,-1));
                }
                lua_pop(L,1);
            }
        }

        float totalWidth = listView->get()->getSize().x;

        if(ratios.size() > listView->get()->getColumnCount())
        {
            std::cout << "warning: more ratios than collums\n";
        }
        for(int i = 0; i < ratios.size(); i++)
        {
            listView->get()->setColumnWidth(i,ratios[i] * totalWidth);
        }
        
        return 0;

    }
    return 0;
}

int lua_ListView_ClearItems(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_ListView_ClearItems) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        listView->get()->removeAllItems();
    }
    return 0;
}

int lua_ListView_AddItem(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_ListView_AddItem) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        tgui::ListView::Ptr * listView = static_cast<tgui::ListView::Ptr*>(lua_touserdata(L, 1));
        std::vector<tgui::String> itemValues;
        
        if(!lua_istable(L,2))
        {
            std::cout << "gettop failed (lua_ListView_AddItem), expected table " << lua_gettop(L) << "\n";
            return -1;
        }
        else
        {
            lua_pushnil(L);
            while(lua_next(L,2) != 0)
            {
                if(lua_isstring(L,-1))
                {
                    itemValues.push_back(lua_tostring(L,-1));
                }
                lua_pop(L,1);
            }
        }
        
        listView->get()->addItem(itemValues);
        // listView->get()->addItem(itemValues);
        
    }
    return 0;
}
// MARK:Focus Stack

int lua_Add_DrawCall(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Add_DrawCall) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        std::string name = lua_tostring(L, 2);
        std::function<void()> *draw = static_cast<std::function<void()> *>(lua_touserdata(L, 3));
        
        host->addDrawCall(name,*draw);
    }
    return 0;
}

int lua_FocusStack_SetFocus(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_FocusStack_SetFocus) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 2));

        host->setNowFocusPanel(panel);

        // FocusPanel * focusPanel = host->getFocusPanel(panel);

        // host->addPanelToFocusStack(focusPanel);
    }
    return 0;
}

int lua_FocusStack_GetFocus(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_FocusStack_GetFocus) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        // FocusPanel* focusPanel = host->getTopFocusPanel();

        // tgui::Panel::Ptr * panel = focusPanel->getPanel();

        // lua_pushlightuserdata(L, panel);
        return 0;
    }
    return 0;
}

int lua_FocusStack_RemovePanel(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_FocusStack_RemovePanel) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 2));

        // FocusPanel * focusPanel = host->getFocusPanel(panel);

        host->removeFocusPanel(panel);
    }
    return 0;
}


int lua_FocusStack_GetFocusLabel(lua_State * L)
{
    // std::cout << "lua_FocusStack_GetFocusLabel called \n";
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_FocusStack_GetFocusLabel) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));

        // std::cout << "host is "

        tgui::Label::Ptr * label = host->getCurrentFocusLabel();

        lua_pushlightuserdata(L, label);
        return 1;
    }
    return 0;
}

int lua_FocusStack_AddFocusableLabel(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_FocusStack_AddFocusableLabel) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        tgui::Label::Ptr * label = static_cast<tgui::Label::Ptr*>(lua_touserdata(L, 2));
        tgui::Panel::Ptr * panel = static_cast<tgui::Panel::Ptr*>(lua_touserdata(L, 3));

        if(!label)
        {
            return -1;
        }
        if(!panel)
        {
            // std::cout << "baseless widget found \n";
            host->addBaselessLabel(label);
            return 0;
        }
        else
        {
            // std::cout << "host is " << host << "\n";
            // std::cout << "paneled widget found \n";
            // std::cout << "panel " << panel << "\n";
            // host->addFocusPanel(panel);
            host->addFocusableLabel(label,panel);
            return 0;
        }

    }
    return 0;
}

int lua_FocusLabel_ChangeIndex(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_FocusLabel_ChangeIndex) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        TGUIScriptingManager * host = static_cast<TGUIScriptingManager*>(lua_touserdata(L, 1));
        int value = lua_tonumber(L, 2);

        host->changeFocusLabelIndex(value);
    }
    return 0;
}

TGUIScriptingManager::TGUIScriptingManager()
{

}
TGUIScriptingManager::~TGUIScriptingManager()
{
    m_script = nullptr;
    m_tgui = nullptr;
}

tgui::Label::Ptr TGUIScriptingManager::createLabel(const std::string & text,float x, float y)
{
    tgui::Label::Ptr label = tgui::Label::create(text);
    label->setPosition(x, y);
    label->setTextColor(tgui::Color::White);
    return label;
}

void TGUIScriptingManager::changeFocusLabelIndex(int index)
{
    // first set 
    if(m_focusStack.size() > 0 )
    {
        m_focusState = FOCUS_STATE_PANEL;
    }
    else
    {
        m_focusState = FOCUS_STATE_BASE;
    }

    if(m_previousFocusState != m_focusState)
    {
        if(m_focusStack.size() > 0 )
        {
            m_focusStack[m_focusStack.size() - 1]->resetLabelIndex();
        }
        else
        {
            m_baselessLabelIndex = 0;
        }
        m_previousFocusState = m_focusState;
        return;
    }
    
    if(m_focusStack.size() > 0 )
    {
        m_focusStack[m_focusStack.size() - 1]->changeLabelIndex(index);
    }
    else
    {
        m_baselessLabelIndex += index;
        m_baselessLabelIndex = m_baselessLabelIndex % m_baselessLabels.size();
    }
}

tgui::ScrollablePanel::Ptr TGUIScriptingManager::createScrollablePanel(float x, float y, float width, float height,tgui::Panel::Ptr parent)
{
    tgui::ScrollablePanel::Ptr scrollablePanel = tgui::ScrollablePanel::create();
    scrollablePanel->setPosition(x, y);
    scrollablePanel->setSize(width, height);
    scrollablePanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    if(parent)
    {
        // std::cout << "parent not null" << "\n";
        parent->add(scrollablePanel);
    }
    else 
    {
        // std::cout << "parent null" << "\n";
        m_tgui->add(scrollablePanel);
    }
    return scrollablePanel;
}

tgui::Picture::Ptr TGUIScriptingManager::createPicture(const std::string & path, float x, float y, float width, float height)
{
    tgui::Picture::Ptr picture = tgui::Picture::create();
    tgui::Texture texture(path);
    picture->getRenderer()->setTexture(texture);
    picture->setPosition(x, y);
    picture->setSize(width, height);
    return picture;
}

std::function<void()> TGUIScriptingManager::getDrawCall(const std::string & name)
{
    // std::cout << "getDrawCall " << name << " !!!!!!!!!!!!!!!!!!!!!!!!!\n";
    if(m_drawCallMap.find(name) == m_drawCallMap.end())
    {
        std::cout << "Draw call not found: " << name << "\n";
        return nullptr;
    }
    return m_drawCallMap[name];
}

tgui::TabContainer::Ptr TGUIScriptingManager::createTabContainer(float x, float y, float width, float height)
{
    tgui::TabContainer::Ptr tabsContainer = tgui::TabContainer::create();
    tabsContainer->setPosition(x, y);
    tabsContainer->setSize(width, height);
    tabsContainer->setVisible(true);

    tgui::Tabs::Ptr tabs = tgui::Tabs::create();
    tabs->changeText(1, "Tab 1");
    tabsContainer->add(tabs);
    // tabsContainer->getRenderer()->
    return tabsContainer;
}

tgui::Tabs::Ptr TGUIScriptingManager::createTabs(float x, float y, float width, float height, tgui::TabContainer::Ptr parent)
{
    tgui::Tabs::Ptr tabs = tgui::Tabs::create();
    tabs->setPosition(x, y);
    tabs->setSize(width, height);
    tabs->add("Tab 1",true);
    tabs->add("Tab 2",false);
    tabs->add("Tab 3",true);
    return tabs;
}

tgui::RichTextLabel::Ptr TGUIScriptingManager::createRTLabel(const std::string & text,float x, float y)
{
    tgui::RichTextLabel::Ptr label = tgui::RichTextLabel::create(text);
    label->setPosition(x, y);
    label->setTextColor(tgui::Color::White);
    return label;
}

tgui::EditBox::Ptr TGUIScriptingManager::createEditBox(float x, float y, float width, float height, tgui::Panel::Ptr parent)
{
    tgui::EditBox::Ptr editBox = tgui::EditBox::create();
    editBox->setPosition(x, y);
    editBox->setSize(width,height);
    if(parent)
    {
        parent->add(editBox);
    }
    else 
    {
        m_tgui->add(editBox);
    }
    return editBox;
}

tgui::Panel::Ptr TGUIScriptingManager::createPanel(float x, float y, float width, float height, tgui::Panel::Ptr parent)
{
    tgui::Panel::Ptr panel = tgui::Panel::create();
    panel->setPosition(x, y);
    panel->setSize(width, height);
    if(parent)
    {
        parent->add(panel);
    }
    else 
    {
        m_tgui->add(panel);
    }
    return panel;
}

tgui::Button::Ptr TGUIScriptingManager::createButton(const std::string & text,float x, float y, float width, float height, tgui::Panel::Ptr parent)
{
    tgui::Button::Ptr button = tgui::Button::create();
    button->setText(text);
    std::cout << "create ok \n";
    button->setPosition(x, y);

    std::cout << "access ok \n";
    button->setSize(width, height);
    if(parent)
    {
        std::cout << "here \n";
        parent->add(button);
    }
    else 
    {
        std::cout << "tgui \n";
        if(!m_tgui)
        {

            std::cout << "tgui is null \n";
        }
        else
        {
            std::cout << "tgui is not null \n";
            // m_tgui->add(button);
        }
    }
    // m_tgui->add(button);
    // m_tgui->add(button);
    std::cout << "rech add \n";
    return button;
}

tgui::CanvasOpenGL3::Ptr * TGUIScriptingManager::createCanvas(const std::string & name,float x, float y, float width, float height, tgui::Panel::Ptr parent)
{
    if(m_canvasMap.find(name) != m_canvasMap.end())
    {
        if(m_canvasMap[name].canvas)
        {
            return m_canvasMap[name].canvas;
        }
    }
    tgui::CanvasOpenGL3::Ptr * canvas = new tgui::CanvasOpenGL3::Ptr();
    *canvas = tgui::CanvasOpenGL3::create();

    canvas->get()->setPosition(x, y);
    canvas->get()->setSize(width, height);
    
    if(parent)
    {
        parent->add(*canvas);
    }
    else 
    {
        m_tgui->add(*canvas);
    }
    m_canvasMap[name] = canvas;

    return m_canvasMap[name].canvas;
}

tgui::ListView::Ptr TGUIScriptingManager::createListView(float x, float y, float width, float height, const std::vector<std::string>& collumName ,const std::vector<float> collumSizes, tgui::Panel::Ptr parent)
{
    tgui::ListView::Ptr listView = tgui::ListView::create();
    listView->setPosition(x, y);
    listView->setSize(width, height);
    for(int i = 0; i < collumName.size(); i++)
    {
        listView->addColumn(collumName[i],collumSizes[i],tgui::ListView::ColumnAlignment::Center);
        
    }
    if(parent)
    {
        parent->add(listView);
    }
    else 
    {
        m_tgui->add(listView);
    }

    listView->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    // listView->setItemData()
    // listView->setAutoLayoutUpdateEnabled(true);
    // listView->setColumnAutoResize(true);
    return listView;
}

void TGUIScriptingManager::update(float deltaTime)
{
    if(m_tgui)
    {
        m_tgui->updateTime(deltaTime);
    }
}
void TGUIScriptingManager::draw()
{
    if(m_tgui)
    {
        m_tgui->draw();
        for(int i = 0 ; i < m_canvasList.size(); i++)
        {
            m_canvasList[i].draw();
        }
    }
}

void TGUIScriptingManager::handleInput(Feintgine::InputManager & inputManager)
{

}

void TGUIScriptingManager::checkInput(const SDL_Event &  evnt)
{
    if(m_tgui)
    {
        m_tgui->handleEvent(evnt);
    }
}

void TGUIScriptingManager::cleanup()
{
    for(auto it = m_tgui->getWidgets().begin(); it != m_tgui->getWidgets().end(); it++)
    {
        m_tgui->remove(*it);
    }
}

void TGUIScriptingManager::addDrawCall(const std::string & name, std::function<void()> draw)
{
    if(m_drawCallMap.find(name) != m_drawCallMap.end())
    {
        m_drawCallMap[name] = draw;
    }
    else// remove existing one, then add the new
    {
        m_drawCallMap[name] = nullptr;
        m_drawCallMap[name] = draw;
    }
}

void TGUIScriptingManager::bindCanvasDrawCall(const std::string & name, std::function<void()> draw)
{
    if(m_canvasMap.find(name) != m_canvasMap.end())
    {
        m_canvasMap[name].bindDrawCall(draw);
        m_canvasList.push_back(m_canvasMap[name]);
    }
}

void TGUIScriptingManager::setNowFocusPanel(tgui::Panel::Ptr * panel)
{
    // brute force all the way, there should only ~10 panels each scene, no need to be smart about that

    if(m_savedFocusPanel.find(panel) != m_savedFocusPanel.end())
    {
    // iterating throught m_savedPanel

        // std::cout << "setNowFocusPanel called \n";
        for(int i = 0; i < m_focusStack.size(); i++)
        {
            if(m_focusStack[i]->getType() == 1)
            {
                if(m_focusStack[i]->getPanel() == panel)
                {
                    // if already in the stack, do nothing, put it to the back
                    std::vector<FocusPanel *> saveStack;

                    for (int j = i + 1; j < m_focusStack.size(); j++)
                    {
                        saveStack.push_back(m_focusStack[j]);
                    }

                    for(int j = i ; j < m_focusStack.size(); j++)
                    {
                        m_focusStack.pop_back();
                    }

                    for(int j = 0; j < saveStack.size(); j++)
                    {
                        m_focusStack.push_back(saveStack[j]);
                    }

                    m_focusStack.push_back(m_focusStack[i]);
                    return;
                    // swap to back somehow doesn't work
                }
            }
        }
        // std::cout << "none of the step above, re adding saved to stack \n";
        m_focusStack.push_back(m_savedFocusPanel[panel]);
        return;
    }
    // if not in the stack, add it
    std::cout << "not on the stack, adding \n";
    FocusPanel * focusPanel = getFocusPanel(panel);
    m_focusStack.push_back(focusPanel);
    m_savedFocusPanel.insert(std::make_pair(panel, focusPanel));

    std::cout << "stack size " << m_focusStack.size() << "\n";
    for(int i = 0; i < m_focusStack.size(); i++)
    {
        std::cout << "stack " << i << " " << m_focusStack[i]->getPanel() << "\n";
    }
    std::cout << "end \n";

}

void TGUIScriptingManager::removeFocusPanel(tgui::Panel::Ptr * panel)
{
    FocusPanel * focusPanel = getFocusPanel(panel);
    if(focusPanel)
    {
        for(int i = 0; i < m_focusStack.size(); i++)
        {
            if(m_focusStack[i] == focusPanel)
            {
                m_focusStack.erase(m_focusStack.begin() + i);
                return;
            }
        }
    }
    else
    {
        std::cout << "focusPanel is null \n";
        return;
    }
    // std::cout << "unable to rempove panel " << panel << "\n";

}

tgui::Label::Ptr * TGUIScriptingManager::getCurrentFocusLabel()
{

    // std::cout << "getCurrentFocusLabel called \n";
    // std::cout << "size " << m_focusStack.size() << "\n";
    if(m_focusStack.size() > 0)
    {
        // std::cout << " size > 0 check \n";
        if(m_focusStack[m_focusStack.size() - 1])
        {
            return m_focusStack.back()->getFirstLabel();
        }
        else
        {
            std::cout << "back is null \n";
        }
        // return m_focusStack.back()->getFirstLabel();
    }
    else
    {
        if(m_baselessLabels.size() > 0)
        {
            return m_baselessLabels[m_baselessLabelIndex];
        }
    }
    std::cout << "return nullptr \n";
    return nullptr;
}

FocusPanel * TGUIScriptingManager::getFocusPanel(tgui::Panel::Ptr * panel)
{


    // std::cout << "getFocusPanel called \n";
    // std::cout << "look for panel " << panel << "\n";
    // std::cout << "stack size " << m_focusStack.size() << "\n";

    if(m_savedFocusPanel.find(panel) != m_savedFocusPanel.end())
    {
        return m_savedFocusPanel[panel];
    }

    for(int i = 0; i < m_focusStack.size(); i++)
    {
        if(m_focusStack[i]->getType() == 1)
        {
            if(m_focusStack[i]->getPanel() == panel)
            {
                // std::cout << "found panel " << m_focusStack[i]->getPanel() << "\n";
                return m_focusStack[i];
            }
        }
    }
    // not found 
    // std::cout << "warning, focus panel not found, adding new to stack \n";
    FocusPanel * focusPanel = new FocusPanel(panel);
    m_focusStack.push_back(focusPanel);
    m_savedFocusPanel.insert(std::make_pair(panel, focusPanel));
    
    return m_focusStack.back();

}

void TGUIScriptingManager::addFocusableLabel(tgui::Label::Ptr * label, tgui::Panel::Ptr * panel)
{
    FocusPanel * focusPanel = getFocusPanel(panel);
    if(focusPanel)
    {
        focusPanel->addLabel(label);
        // std::cout << "added Label successfully \n";
    }
}

void TGUIScriptingManager::addBaselessLabel(tgui::Label::Ptr * label)
{
    for(int i = 0; i < m_baselessLabels.size(); i++)
    {
        if(m_baselessLabels[i] == label)
        {
            return;
        }
    }
    m_baselessLabels.push_back(label);
}

void TGUIScriptingManager::clearup()
{
    for(int i = 0; i < m_focusStack.size(); i++)
    {
        delete m_focusStack[i];
        m_focusStack.erase(m_focusStack.begin() + i);
    }
    m_focusStack.clear();
    for(int i = 0; i < m_baselessLabels.size(); i++)
    {
        delete m_baselessLabels[i];
        m_baselessLabels.erase(m_baselessLabels.begin() + i);
    }
    m_baselessLabels.clear();
    for(auto it = m_savedFocusPanel.begin(); it != m_savedFocusPanel.end(); it++)
    {
        delete it->second;
    }
    m_savedFocusPanel.clear();

}

void TGUIScriptingManager::init(Feintgine::Window * m_window, lua_State *script)
{
    m_tgui = new tgui::Gui(m_window->getWindow());
    TTF_Init(); // a must

    // m_focusStack = std::vector<FocusPanel *>();
    // m_focusPanelMap = std::unordered_map<tgui::Panel::Ptr *, FocusPanel *>();

    selectTheme(*m_tgui, "themes/Dark.txt");  // force to load in main thread since the openGL problem, you can only have texture created in mainthread ( OpenGL Context)

    tgui::Font font_load("font/ARIALUNI.ttf");    
    m_tgui->setFont(font_load);
    m_tgui->setTextSize(20);        

    m_script = script; // luaL_newstate();

    // init lua component
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/GUI/tguiScript.lua")))
    {
        std::cout << "TGUIScriptingManager Run script tguiScript.lua OK \n";
    }

    // MARK: CPP_LUA
    // register lua functions

    // TGUI Label section
    lua_register(m_script, "cpp_Label_Create", lua_Label_Create);
    lua_register(m_script, "cpp_Label_SetPos" , lua_Label_SetPos);
    lua_register(m_script, "cpp_Label_SetPosStr", lua_Label_SetPosStr);
    lua_register(m_script, "cpp_Label_SetText", lua_Label_SetText);
    lua_register(m_script, "cpp_Label_SetAlignment", lua_Label_SetAlignment);
    lua_register(m_script, "cpp_Label_SetTextColor", lua_Label_SetTextColor);
    lua_register(m_script, "cpp_Label_SetOnHoverCallback", lua_Label_SetOnHoverCallback);
    lua_register(m_script, "cpp_Label_SetOffHoverCallback", lua_Label_SetOffHoverCallback);
    lua_register(m_script, "cpp_Label_SetOnClickCallback", lua_Label_SetOnClickCallback);
    lua_register(m_script, "cpp_Label_SetScale", lua_Label_SetScale);
    lua_register(m_script, "cpp_Label_GetPos", lua_Label_GetPos);
    lua_register(m_script, "cpp_Label_GetText", lua_Label_GetText);

    
    // TGUI Rich Text Label section
    lua_register(m_script, "cpp_RTLabel_Create", lua_RTLabel_Create);
    lua_register(m_script, "cpp_RTLabel_SetPos" , lua_RTLabel_SetPos);
    lua_register(m_script, "cpp_RTLabel_SetPosStr", lua_RTLabel_SetPosStr);
    lua_register(m_script, "cpp_RTLabel_SetText", lua_RTLabel_SetText);
    lua_register(m_script, "cpp_RTLabel_SetAlignment", lua_RTLabel_SetAlignment);
    lua_register(m_script, "cpp_RTLabel_SetTextColor", lua_RTLabel_SetTextColor);
    lua_register(m_script, "cpp_RTLabel_SetOnHoverCallback", lua_RTLabel_SetOnHoverCallback);
    lua_register(m_script, "cpp_RTLabel_SetOffHoverCallback", lua_RTLabel_SetOffHoverCallback);
    lua_register(m_script, "cpp_RTLabel_SetOnClickCallback", lua_RTLabel_SetOnClickCallback);
    lua_register(m_script, "cpp_RTLabel_SetScale", lua_RTLabel_SetScale);
    lua_register(m_script, "cpp_RTLabel_GetSize", lua_RTLabel_GetSize);
    lua_register(m_script, "cpp_RTLabel_GetPos", lua_RTLabel_GetPos);
    
    // TGUI EditBox section
    lua_register(m_script, "cpp_EditBox_Create", lua_EditBox_Create);
    lua_register(m_script, "cpp_EditBox_SetPos", lua_EditBox_SetPos);
    lua_register(m_script, "cpp_EditBox_SetPosStr", lua_EditBox_SetPosStr);
    lua_register(m_script, "cpp_EditBox_SetSize", lua_EditBox_SetSize);
    lua_register(m_script, "cpp_EditBox_SetSizeStr", lua_EditBox_SetSizeStr);
    lua_register(m_script, "cpp_EditBox_SetPWChar", lua_EditBox_SetPWChar);
    lua_register(m_script, "cpp_EditBox_SetText", lua_EditBox_SetText);
    lua_register(m_script, "cpp_EditBox_GetText", lua_EditBox_GetText);

    // TGUI Panel section
    lua_register(m_script, "cpp_Panel_Create", lua_Panel_Create);
    lua_register(m_script, "cpp_Panel_SetPos", lua_Panel_SetPos);
    lua_register(m_script, "cpp_Panel_SetPosStr", lua_Panel_SetPosStr);
    lua_register(m_script, "cpp_Panel_SetSize", lua_Panel_SetSize);
    lua_register(m_script, "cpp_Panel_SetSizeStr", lua_Panel_SetSizeStr);
    lua_register(m_script, "cpp_Panel_HideWithEffect", lua_Panel_HideWithEffect);
    lua_register(m_script, "cpp_Panel_ShowWithEffect", lua_Panel_ShowWithEffect);
    lua_register(m_script, "cpp_Panel_SetVisible", lua_Panel_setVisible);
    lua_register(m_script, "cpp_Panel_SetAlignment", lua_Panel_SetAlignment);
    lua_register(m_script, "cpp_Panel_SetHoverOnCallback", lua_Panel_SetHoverOnCallback); 
    lua_register(m_script, "cpp_Panel_SetHoverOffCallback", lua_Panel_SetHoverOffCallback); 
    lua_register(m_script, "cpp_Panel_SetBorderColor", lua_Panel_SetBorderColor);
    lua_register(m_script, "cpp_Panel_SetOpacity", lua_Panel_SetOpacity);
    lua_register(m_script, "cpp_Panel_SetOnClickCallback", lua_Panel_SetOnClickCallback);
    lua_register(m_script, "cpp_Panel_SetOnDoubleClickCallback", lua_Panel_SetOnDoubleClickCallback);
    lua_register(m_script, "cpp_Panel_SetOnRightClickCallback", lua_Panel_SetOnRightClickCallback);
    lua_register(m_script, "cpp_Panel_GetSize", lua_Panel_GetSize);
    lua_register(m_script, "cpp_Panel_RemoveHoverOnCallback", lua_Panel_RemoveHoverOnCallback);
    lua_register(m_script, "cpp_Panel_RemoveHoverOffCallback", lua_Panel_RemoveHoverOffCallback);
    lua_register(m_script, "cpp_Panel_GetPos", lua_Panel_GetPos);

    // TGUI ScrollablePanel section
    lua_register(m_script, "cpp_ScrollablePanel_Create", lua_ScrollablePanel_Create);
    lua_register(m_script, "cpp_ScrollablePanel_SetPos", lua_ScrollablePanel_SetPos);
    lua_register(m_script, "cpp_ScrollablePanel_SetPosStr", lua_ScrollablePanel_SetPosStr);
    lua_register(m_script, "cpp_ScrollablePanel_SetSize", lua_ScrollablePanel_SetSize);
    lua_register(m_script, "cpp_ScrollablePanel_SetSizeStr", lua_ScrollablePanel_SetSizeStr);
    lua_register(m_script, "cpp_ScrollablePanel_HideWithEffect", lua_ScrollablePanel_HideWithEffect);
    lua_register(m_script, "cpp_ScrollablePanel_ShowWithEffect", lua_ScrollablePanel_ShowWithEffect);
    lua_register(m_script, "cpp_ScrollablePanel_SetVisible", lua_ScrollablePanel_setVisible);
    lua_register(m_script, "cpp_ScrollablePanel_SetAlignment", lua_ScrollablePanel_SetAlignment);
    lua_register(m_script, "cpp_ScrollablePanel_GetSize", lua_ScrollablePanel_GetSize);
    lua_register(m_script, "cpp_ScrollablePanel_ClearItems", lua_ScrollablePanel_ClearItems);

    // TGUI Picture section
    lua_register(m_script, "cpp_Picture_Create", lua_Picture_Create);
    lua_register(m_script, "cpp_Picture_SetPos", lua_Picture_SetPos);
    lua_register(m_script, "cpp_Picture_SetPosStr", lua_Picture_SetPosStr);
    lua_register(m_script, "cpp_Picture_SetSize", lua_Picture_SetSize);
    lua_register(m_script, "cpp_Picture_SetSizeStr", lua_Picture_SetSizeStr);
    lua_register(m_script, "cpp_Picture_SetTexture", lua_Picture_SetTexture);

    
    // TGUI Tabs container section
    lua_register(m_script, "cpp_TabContainer_Create", lua_TabContainer_Create);
    lua_register(m_script, "cpp_TabContainer_SetPos", lua_TabContainer_SetPos);
    lua_register(m_script, "cpp_TabContainer_SetPosStr", lua_TabContainer_SetPosStr);
    lua_register(m_script, "cpp_TabContainer_SetSize", lua_TabContainer_SetSize);
    lua_register(m_script, "cpp_TabContainer_SetSizeStr", lua_TabContainer_SetSizeStr);
    lua_register(m_script, "cpp_TabContainer_AddTab", lua_TabContainer_AddTab);
    lua_register(m_script, "cpp_TabContainer_SetAlignment", lua_TabContainer_SetAlignment);
    lua_register(m_script, "cpp_TabContainer_SetTabFixedSize", lua_TabContainer_SetTabFixedSize);

    // TGUI Button 
    lua_register(m_script, "cpp_Button_Create", lua_Button_Create);
    lua_register(m_script, "cpp_Button_SetPos", lua_Button_SetPos);
    lua_register(m_script, "cpp_Button_SetPosStr", lua_Button_SetPosStr);
    lua_register(m_script, "cpp_Button_SetSize", lua_Button_SetSize);
    lua_register(m_script, "cpp_Button_SetSizeStr", lua_Button_SetSizeStr);
    lua_register(m_script, "cpp_Button_SetOnClickCallback", lua_Button_SetOnClickCallback);

    // TGUI Canvas section

    lua_register(m_script, "cpp_Canvas_Create", lua_Canvas_Create);
    lua_register(m_script, "cpp_Canvas_SetPos", lua_Canvas_SetPos);
    lua_register(m_script, "cpp_Canvas_SetPosStr", lua_Canvas_SetPosStr);
    lua_register(m_script, "cpp_Canvas_SetSize", lua_Canvas_SetSize);
    lua_register(m_script, "cpp_Canvas_SetSizeStr", lua_Canvas_SetSizeStr);
    lua_register(m_script, "cpp_Canvas_BindDrawCall", lua_Canvas_BindDrawCall);
    lua_register(m_script, "cpp_Add_DrawCall", lua_Add_DrawCall);

    // TGUI ListView

    lua_register(m_script, "cpp_ListView_Create", lua_ListView_Create);
    lua_register(m_script, "cpp_ListView_SetPos", lua_ListView_SetPos);
    lua_register(m_script, "cpp_ListView_SetPosStr", lua_ListView_SetPosStr);
    lua_register(m_script, "cpp_ListView_SetSize", lua_ListView_SetSize);
    lua_register(m_script, "cpp_ListView_SetSizeStr", lua_ListView_SetSizeStr);
    lua_register(m_script, "cpp_ListView_GetSize", lua_ListView_GetSize);
    lua_register(m_script, "cpp_ListView_SetColumnSizeRatios", lua_ListView_SetColumnSizeRatios);
    lua_register(m_script, "cpp_ListView_ClearItems", lua_ListView_ClearItems);
    lua_register(m_script, "cpp_ListView_AddItem", lua_ListView_AddItem);

    // Focus Panels

    lua_register(m_script, "cpp_FocusStack_SetFocus", lua_FocusStack_SetFocus);
    lua_register(m_script, "cpp_FocusStack_GetFocus", lua_FocusStack_GetFocus);
    lua_register(m_script, "cpp_FocusStack_RemovePanel", lua_FocusStack_RemovePanel);

    lua_register(m_script, "cpp_FocusStack_AddFocusableLabel", lua_FocusStack_AddFocusableLabel);
    lua_register(m_script, "cpp_FocusStack_GetFocusLabel", lua_FocusStack_GetFocusLabel);
    lua_register(m_script, "cpp_FocusLabel_ChangeIndex", lua_FocusLabel_ChangeIndex);

    // lua_register(m_script, "cpp_FocusLabels_GetCurrent", lua_FocusLabels_GetCurrent);

    
    // TGUI Tabs section
    // lua_register(m_script, "cpp_Tabs_Create", lua_Tabs_Create);
    // lua_register(m_script, "cpp_Tabs_SetPos", lua_Tabs_SetPos);
    // lua_register(m_script, "cpp_Tabs_SetPosStr", lua_Tabs_SetPosStr);
    // lua_register(m_script, "cpp_Tabs_SetSize", lua_Tabs_SetSize);
    // lua_register(m_script, "cpp_Tabs_SetSizeStr", lua_Tabs_SetSizeStr);
      // lua_register(m_script, "cpp_Tabs_SetTextColor", lua_Tabs_SetTextColor);
    // lua_register(m_script, "cpp_Tabs_SetOnHoverCallback", lua_Tabs_SetOnHoverCallback);
    // lua_register(m_script, "cpp_Tabs_SetOffHoverCallback", lua_Tabs_SetOffHoverCallback);
    // lua_register(m_script, "cpp_Tabs_SetOnClickCallback", lua_Tabs_SetOnClickCallback);
    // lua_register(m_script, "cpp_Tabs_SetTabActive", lua_Tabs_SetTabActive);

    // lua_register(m_script, "cpp_FocusPanel_Register", lua_FocusPanel_Register);

    lua_getglobal(m_script, "TGUIScripting_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        lua_pushnumber(m_script,m_window->getScreenWidth());
        lua_pushnumber(m_script,m_window->getScreenHeight());
        // std::cout << "pass ref : " << this << "\n";
        const int argc = 3;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "TGUI Scripting Init from C++ OK \n";
        }
    }
}

