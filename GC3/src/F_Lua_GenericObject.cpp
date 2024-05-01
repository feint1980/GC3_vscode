#include "F_Lua_GenericObject.h"


F_Lua_GenericObject::F_Lua_GenericObject()
{

}


F_Lua_GenericObject::~F_Lua_GenericObject()
{

}

void F_Lua_GenericObject::t_editor_reset()
{
    for (int i = 0; i < m_bullets.size(); i++)
    {
        m_bullets[i]->setLifeTime(0.0f);
        clearEvent();
    }
}


void F_Lua_GenericObject::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		F_LuaDynamicObject::draw(spriteBatch);
		for (int i = 0; i < m_bullets.size(); i++)
		{
			
			m_bullets[i]->draw(spriteBatch);
		}
	}