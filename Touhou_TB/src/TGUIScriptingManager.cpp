
#include "TGUIScriptingManager.h"


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
        switch(aligmentType)
        {
            case 0:// left
            {
                // left plank (default by C++)
            }
            break;
            case 1:// center
            {

                //label->get()->setText("asdadase \n");
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
                std::cout << "lua_Label_SetAlignment failed (lua_Label_SetAlignment) " << lua_gettop(L) << "\n";
                return -1;
            }
            break;
        }
        //label->get()->setTextAlignment(tgui::TextAlignment(aligmentType));
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

                //label->get()->setText("asdadase \n");
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
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

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
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

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
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

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
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

        // label->get()->onClick(nullptr);
        label->get()->onClick.disconnectAll();
        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onClick(callback);
    }

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
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

        std::function<void()> callback = [L,ref](){lua_rawgeti(L, LUA_REGISTRYINDEX, ref);lua_pcall(L, 0, 0, 0);};
        label->get()->onClick(callback);
    }

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
}


int lua_RTLabel_Create(lua_State * L)
{
    std::cout << "[C++] lua_RTLabel_Create called \n";
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
}


TGUIScriptingManager::TGUIScriptingManager()
{



}
TGUIScriptingManager::~TGUIScriptingManager()
{

}


tgui::Label::Ptr TGUIScriptingManager::createLabel(const std::string & text,float x, float y)
{
    tgui::Label::Ptr label = tgui::Label::create(text);
    label->setPosition(x, y);
    label->setTextColor(tgui::Color::White);
    
    return label;
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


void TGUIScriptingManager::init(Feintgine::Window * m_window, lua_State *script)
{
    m_tgui = new tgui::Gui(m_window->getWindow());
    TTF_Init(); // a must

    selectTheme(*m_tgui, "themes/Dark.txt");  // force to load in main thread since the openGL problem, you can only have texture created in mainthread ( OpenGL Context)

    // auto loadFontTask = async::spawn([&]() {
        tgui::Font font_load("font/ARIALUNI.ttf");    
        m_tgui->setFont(font_load);
        m_tgui->setTextSize(20);        

    // });

    m_script = script; // luaL_newstate();
    // luaL_openlibs(m_script);

    // init lua component
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/system/GUI/tguiScript.lua")))
    {
        std::cout << "Run script OK \n";
    }

    // MARK: CPP_LUA
    // register lua functions

    // TGUI Main
    //lua_register(m_script, "cpp_Main_Add_Label", lua_Main_Add_Label);


    
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
    
    // TGUI EditBox section
    lua_register(m_script, "cpp_EditBox_Create", lua_EditBox_Create);
    lua_register(m_script, "cpp_EditBox_SetPos", lua_EditBox_SetPos);
    lua_register(m_script, "cpp_EditBox_SetPosStr", lua_EditBox_SetPosStr);
    lua_register(m_script, "cpp_EditBox_SetSize", lua_EditBox_SetSize);
    lua_register(m_script, "cpp_EditBox_SetSizeStr", lua_EditBox_SetSizeStr);
    lua_register(m_script, "cpp_EditBox_SetPWChar", lua_EditBox_SetPWChar);

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
    

    // run Init script
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/system/GUI/tguiScript.lua")))
    {
        std::cout << "Run script OK \n";
    }

    lua_getglobal(m_script, "TGUIScripting_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        lua_pushnumber(m_script,m_window->getScreenWidth());
        lua_pushnumber(m_script,m_window->getScreenHeight());
        std::cout << "pass ref : " << this << "\n";
        const int argc = 3;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "TGUI Scripting Init from C++ OK \n";
        }
    }
    
    // loadFontTask.get();

}
