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
        /*  Slot layout:
            [TL(0)]--[Border_T(1)]--[TR(2)]
              |                        |
            [Border_L(3)]        [Border_R(4)]
              |                        |
            [BL(5)]--[Border_B(6)]--[BR(7)]
        */
        enum PartSlot
        {
            TL       = 0,
            Border_T = 1,
            TR       = 2,
            Border_L = 3,
            Border_R = 4,
            BL       = 5,
            Border_B = 6,
            BR       = 7,
            COUNT
        };

        static constexpr const char* SPRITE_NAMES[COUNT] = {
            "TL.png",
            "Border_T.png",
            "TR.png",
            "Border_L.png",
            "Border_R.png",
            "BL.png",
            "Border_B.png",
            "BR.png"
        };

        struct F_FramePart
        {
            F_Sprite sprite;
            PartSlot slot;
        };

        struct CachedQuad
        {
            glm::vec4 destRect;
            glm::vec4 uv;
            GLuint    textureId;
            float     depth;
        };

    public:
        F_FrameObject() = default;
        ~F_FrameObject() = default;

        void init(const std::string& packetname,
                  const glm::vec2&   pos,
                  const glm::vec2&   size,
                  float              depth = 0.5f,
                  const Color&       color = Color(255, 255, 255, 255),
                  float              scale = 1.0f);

        void setScale(float scale)           { m_borderScale = scale; }
        void setPos  (const glm::vec2& pos)  { m_pos   = pos;   m_dirty = true; }
        void setSize (const glm::vec2& size) { m_size  = size;  m_dirty = true; }
        void setDepth(float depth)           { m_depth = depth; }
        void setColor(const Color& color)    { m_color = color; }

        glm::vec2 getPos()   const { return m_pos;   }
        glm::vec2 getSize()  const { return m_size;  }
        float     getDepth() const { return m_depth; }
        Color     getColor() const { return m_color; }

        void draw(SpriteBatch& spriteBatch);

    private:
        void recalculate();
        void pushQuad(int slot, float x, float y, float w, float h,float depth);

        F_FramePart             m_parts[COUNT];
        std::vector<CachedQuad> m_cachedQuads;

        glm::vec2 m_pos   = { 0, 0 };
        glm::vec2 m_size  = { 0, 0 };
        float     m_depth = 0.5f;
        Color     m_color = Color(255, 255, 255, 255);
        bool      m_dirty = true;
        float m_borderScale = 1.0f;
    };
}

#endif //_F_FRAMEDOBJECT_H_