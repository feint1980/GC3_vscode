#pragma once
#include <F_LuaDynamicObject.h>



class  F_Lua_BaseEntity : public Feintgine::F_LuaDynamicObject
{
public:
    F_Lua_BaseEntity();
    ~F_Lua_BaseEntity();    

    virtual void draw(Feintgine::SpriteBatch & spriteBatch) override;

    virtual void update(float deltaTime) override;

protected:

    float m_strength;
    float m_vitality;
    float m_dexterity;
    float m_agility;
    float m_intelligence;
    float m_wisdom;



};