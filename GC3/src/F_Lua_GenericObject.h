#pragma once
#include <F_LuaDynamicObject.h>
#include "EnemyBulletBase.h"

class F_Lua_GenericObject : public Feintgine::F_LuaDynamicObject
{
public:
    F_Lua_GenericObject();
    ~F_Lua_GenericObject();

    void t_editor_reset();

    virtual void draw(Feintgine::SpriteBatch & spriteBatch) override;

    std::vector<EnemyBulletBase *> m_bullets;

protected:

    
    
};