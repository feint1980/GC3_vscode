#ifndef _F_FRAMEDOBJECT_H_
#define _F_FRAMEDOBJECT_H_

#include "F_Sprite.h"
#include "GLSLProgram.h"
#include "SpriteManager.h"
#include "SpriteBatch.h"

namespace Feintgine
{
    class F_FrameObject 
    {
        /* Slot layout:
        TL(0)----Top(1)----TR(2)
        |                     |
        L(3)    Center(4)    R(5)
        |                     |
        BL(6)----Bot(7)----BR(8)
        */
        enum PartSlot
        {
            TL = 0, Top = 1, TR = 2,
            L  = 3, Center = 4, R = 5,
            BL = 6, Bot = 7, BR = 8,
            COUNT
        };

        struct F_FramePart
        {
            F_Sprite  m_sprite;
            PartSlot  slot;
        };

        static constexpr const char* SUFFIXES[COUNT] = {
            "_tl", "_top", "_tr",
            "_left", "_center", "_right",
            "_bl", "_bottom", "_br"
        };

    public:
        F_FrameObject() = default;
        ~F_FrameObject() = default;

        void init(const std::string& packetname,
                    const glm::vec2&   pos,
                    const glm::vec2&   size,
                    float              depth = 0.5f,
                    const Color&       color = Color(255, 255, 255, 255));

        void setPos  (const glm::vec2& pos)  { m_pos   = pos;  m_dirty = true; }
        void setSize (const glm::vec2& size) { m_size  = size; m_dirty = true; }
        void setDepth(float depth)           { m_depth = depth; }
        void setColor(const Color& color)    { m_color = color; }

        glm::vec2 getPos()   const { return m_pos;   }
        glm::vec2 getSize()  const { return m_size;  }
        float     getDepth() const { return m_depth; }
        Color     getColor() const { return m_color; }

        void draw(SpriteBatch& spriteBatch);  // non-const: may recalculate

    private:
        void recalculate();

        F_FramePart m_parts[COUNT];
        glm::vec4   m_destRects[COUNT];   // cached, only rebuilt when dirty

        glm::vec2 m_pos   = { 0, 0 };
        glm::vec2 m_size  = { 0, 0 };
        float     m_depth = 0.5f;
        Color     m_color = Color(255, 255, 255, 255);
        bool      m_dirty = true;
    };
}

#endif //_F_FRAMEDOBJECT_H_