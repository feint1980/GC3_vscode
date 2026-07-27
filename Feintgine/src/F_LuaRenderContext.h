#ifndef _F_LUARENDERCONTEXT_H
#define _F_LUARENDERCONTEXT_H

// #include "GLSLProgram.h"
#include "SpriteBatch.h"

// for now this will be used to draw F_FramePanel and along of Lua objects
// #include "EmptyObject.h"
// #include "F_FramePanel.h"
#include "LuaManager.h"
// #include "F_Sprite.h"
#include "TextRenderer.h"
#include "F_CompositeObject.h"


#define EMBLEM_LINE 0
#define EMBLEM_CORNER 1
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
        
        void initTextRenderer(int fontSize, int charCount, const std::string& fontFilePath); 

        void initTextRendererByRange(int fontSize, const std::string & letters , const std::string& fontFilePath);

        void update(float delta);
        
        void updateSignals(Feintgine::InputManager & inputManager);

        void draw(Feintgine::SpriteBatch & spriteBatch,Feintgine::Camera2D * camera);

        void drawText(const Feintgine::Camera2D & camera);

        void removeCompositeObject(F_CompositeObject * compositeObject);

        F_CompositeObject * addObjectComposite(const glm::vec2 & pos, const glm::vec2 & dim, float angle, float depth);

    private:
        lua_State * m_script = nullptr;
        std::vector<F_CompositeObject> m_compositeObjects;
        TextRenderer m_textRenderer;
        Feintgine::Camera2D * m_tCam = nullptr; 

    };

}

#endif // _F_LUARENDERCONTEXT_H