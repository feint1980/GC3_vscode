#ifndef _F_FRAMEEMBLEM_H_
#define _F_FRAMEEMBLEM_H_

#include "F_Sprite.h"
#include "SpriteBatch.h"
#include "SpriteManager.h"
#include <glm/glm.hpp>
#include <vector>

namespace Feintgine
{
    enum CornerMask
    {
        CORNER_TL = 1,
        CORNER_TR = 2,
        CORNER_BR = 4,
        CORNER_BL = 8
    };

    enum LineMask
    {
        LINE_TOP   = 1,
        LINE_BOT   = 2,
        LINE_LEFT  = 4,
        LINE_RIGHT = 8
    };

    enum EmblemType
    {
        EMBLEM_CORNER,
        EMBLEM_LINE
    };

    class F_FrameEmblem
    {
        struct CachedQuad
        {
            glm::vec4 destRect;
            glm::vec4 uv;
            GLuint    textureId;
            float     depth;
            float     angle;
        };

    public:
        F_FrameEmblem() = default;

        // For corner emblem
        void init(const std::string& spriteName,
                  EmblemType         type,
                  int                placeMask,
                  int                hideMask,
                  float              offset = 0.0f,
                  float              depth  = 60.0f);

        int  getHideCornerMask() const { return m_type == EMBLEM_CORNER ? m_hideMask : 0; }
        int  getHideLineMask()   const { return m_type == EMBLEM_LINE   ? m_hideMask : 0; }
        bool isDirty()           const { return m_dirty; }
        void markDirty()               { m_dirty = true; }

        void recalculate(const glm::vec2& frameOrigin,
                         const glm::vec2& frameSize,
                         float            cornerW,
                         float            cornerH);

        void draw(SpriteBatch& batch) const;

    private:
        F_Sprite  m_sprite;
        EmblemType m_type      = EMBLEM_CORNER;
        int        m_placeMask = 0;
        int        m_hideMask  = 0;
        float      m_offset    = 0.0f;
        float      m_depth     = 60.0f;
        bool       m_dirty     = true;

        std::vector<CachedQuad> m_cachedQuads;

        void pushQuad(float x, float y, float w, float h, float angle);
    };
}

#endif