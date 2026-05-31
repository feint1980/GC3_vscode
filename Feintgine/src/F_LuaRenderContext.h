#ifndef _F_LUARENDERCONTEXT_H
#define _F_LUARENDERCONTEXT_H

#include "GLSLProgram.h"
#include "SpriteBatch.h"


// for now this will be used to draw F_FramePanel and along of Lua objects
#include "EmptyObject.h"
#include "F_FramePanel.h"
#include "LuaManager.h"
#include "F_Sprite.h"

namespace Feintgine
{
    class F_LuaRenderContext
    {
    public:
        F_LuaRenderContext();
        ~F_LuaRenderContext();

        void init(lua_State * script);
        
        void update(float delta);
        
        void draw(Feintgine::SpriteBatch & spriteBatch);

    private:
        lua_State * m_script = nullptr;
        std::vector<EmptyObject> m_emptyObjects;
        std::vector<F_Sprite> m_spriteObjects;2
    };

}

#endif // _F_LUARENDERCONTEXT_H