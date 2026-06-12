#ifndef _F_LUARENDERCONTEXT_H
#define _F_LUARENDERCONTEXT_H

#include "GLSLProgram.h"
#include "SpriteBatch.h"


// for now this will be used to draw F_FramePanel and along of Lua objects
#include "EmptyObject.h"
#include "F_FramePanel.h"
#include "LuaManager.h"
#include "F_Sprite.h"

#include "F_CompositeObject.h"

namespace Feintgine
{
    class F_LuaRenderContext
    {
    public:
        F_LuaRenderContext();
        ~F_LuaRenderContext();

        /*
        Reason why maxCompositeObjects need to be specificly has to state the number, is a reminder that, if you exceed the number, the pointer that return to Lua will be invalid 
        */
        void init(lua_State * script, int maxCompositeObjects);
        
        void update(float delta);
        
        void draw(Feintgine::SpriteBatch & spriteBatch);

        void removeCompositeObject(F_CompositeObject * compositeObject);

        F_CompositeObject * addObjectComposite(const glm::vec2 & pos, const glm::vec2 & dim, float angle, float depth);

    private:
        lua_State * m_script = nullptr;
        std::vector<F_CompositeObject> m_compositeObjects;

    };

}

#endif // _F_LUARENDERCONTEXT_H