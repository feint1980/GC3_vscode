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
        [TL]--[BH_TL]--[EMB_T]--[BH_TR]--[TR]
          |                                  |
        [BV_TL]                          [BV_TR]
        [EMB_L]                          [EMB_R]
        [BV_BL]                          [BV_BR]
          |                                  |
        [BL]--[BH_BL]--[EMB_B]--[BH_BR]--[BR]
        */
        enum PartSlot
        {
            TL = 0, TR = 1, BL = 2, BR = 3,
            BH_TL = 4, BH_TR = 5, BH_BL = 6, BH_BR = 7,
            BV_TL = 8, BV_BL = 9, BV_TR = 10, BV_BR = 11,
            EMB_T = 12, EMB_B = 13, EMB_L = 14, EMB_R = 15,
            COUNT
        };

        static constexpr const char* SPRITE_NAMES[COUNT] = {
            "TL.png",           "TR.png",           "BL.png",           "BR.png",
            "border_hor.png",   "border_hor.png",   "border_hor.png",   "border_hor.png",
            "border_ver.png",   "border_ver.png",   "border_ver.png",   "border_ver.png",
            "Emblem_top.png",   "Emblem_bot.png",   "Emblem_left.png",  "Emblem_right.png"
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
        };

    public:
        F_FrameObject() = default;
        ~F_FrameObject() = default;

        void init(const std::string& packetname,
                  const glm::vec2&   pos,
                  const glm::vec2&   size,
                  float              depth = 0.5f,
                  const Color&       color = Color(255, 255, 255, 255));

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
        void pushQuad(int slot, float x, float y, float w, float h);

        F_FramePart             m_parts[COUNT];
        std::vector<CachedQuad> m_cachedQuads;

        glm::vec2 m_pos   = { 0, 0 };
        glm::vec2 m_size  = { 0, 0 };
        float     m_depth = 0.5f;
        Color     m_color = Color(255, 255, 255, 255);
        bool      m_dirty = true;
    };
}

#endif //_F_FRAMEDOBJECT_H_