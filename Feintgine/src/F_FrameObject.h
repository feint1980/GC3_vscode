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
        [Border_L(3)]           [Border_R(4)]
            |                        |
            [BL(5)]--[Border_B(6)]--[BR(7)]
        */
        enum CornerMask {
            CORNER_TL = 1,
            CORNER_TR = 2,
            CORNER_BR = 4,
            CORNER_BL = 8
            };

        enum LineMask {
            LINE_TOP   = 1,
            LINE_BOT   = 2,
            LINE_LEFT  = 4,
            LINE_RIGHT = 8
        };

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
            // float     angle;
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
        void setColor( const Feintgine::Color& color) ;
        glm::vec2 getPos()   const { return m_pos;   }
        glm::vec2 getSize()  const { return m_size;  }
        float     getDepth() const { return m_depth; }
        Feintgine::Color     getColor() const { return m_color; }

        void draw(SpriteBatch& spriteBatch);
        float getBorderScale() const { return m_borderScale; }

        float getScale() const
        {
            glm::vec2 cd = m_parts[TL].sprite.getDim();
            float sx = (m_size.x < cd.x * 2.0f) ? (m_size.x / (cd.x * 2.0f)) : 1.0f;
            float sy = (m_size.y < cd.y * 2.0f) ? (m_size.y / (cd.y * 2.0f)) : 1.0f;
            return std::min(sx, sy) * m_borderScale;
        }
        void setHideCornerMask(int mask) { m_hideCornerMask = mask; m_dirty = true; }
        void setHideLineMask  (int mask) { m_hideLineMask   = mask; m_dirty = true; }

        void setOverlap      (float v) { m_overlap = v;           m_dirty = true; }
        void setBorderThickness(float v) { m_borderThickness = v; m_dirty = true; }
        glm::vec2 getFrameOrigin()    const { return { m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f }; }
        float     getScaledCornerW()  const { return m_parts[TL].sprite.getDim().x * getScale(); }
        float     getScaledCornerH()  const { return m_parts[TL].sprite.getDim().y * getScale(); }
        
        glm::vec2 getFrameSize()      const { return m_size; }

        void setAngle(float angle) { m_angle = angle; m_dirty = true; }

    private:
        void recalculate();
        void pushQuad(int slot, float x, float y, float w, float h, float depth);

        // Rotate point around pivot by angle (radians)
        static glm::vec2 rotateAround(const glm::vec2& point, const glm::vec2& pivot, float angleRad)
        {
            float c = std::cos(angleRad);
            float s = std::sin(angleRad);
            glm::vec2 d = point - pivot;
            return pivot + glm::vec2(d.x * c - d.y * s, d.x * s + d.y * c);
        }
        F_FramePart             m_parts[COUNT];
        std::vector<CachedQuad> m_cachedQuads;

        glm::vec2 m_pos   = glm::vec2(0, 0 );
        glm::vec2 m_size  = glm::vec2(0, 0 );
        float     m_depth = 0.5f;
    
        float m_borderScale = 1.0f;
        float m_overlap          = 6.0f;
        float m_borderThickness  = 8.0f;  // tune this to match the line in your sprite
        int m_hideCornerMask = 0;
        int m_hideLineMask   = 0;
        alignas(16) Feintgine::Color     m_color = Feintgine::Color(255, 255, 255, 255); //works
        // float padding = 0.0f; // put after Color, great example for padding, context If padding is not here, m_angle will be changed when m_color it set/assign
        float m_angle = 0.0f;
        
        
        bool      m_dirty = true;


    };
}

#endif //_F_FRAMEDOBJECT_H_