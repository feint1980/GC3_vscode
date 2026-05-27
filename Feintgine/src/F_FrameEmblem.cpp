#include "F_FrameEmblem.h"

namespace Feintgine
{

void F_FrameEmblem::init(const std::string& spriteName,
                        EmblemType         type,
                        int                placeMask,
                        int                hideMask,
                        float              offset,
                        float              depth)
{
    m_sprite    = SpriteManager::Instance()->getSprite(spriteName);
    m_type      = type;
    m_placeMask = placeMask;
    m_hideMask  = hideMask;
    m_offset    = offset;
    m_depth     = depth;
    m_dirty     = true;
}

void F_FrameEmblem::pushQuad(float x, float y, float w, float h, float angle)
{
    m_cachedQuads.push_back({
        { x, y, w, h },
        m_sprite.getUV(),
        m_sprite.getTexture().id,
        m_depth,
        angle
    });
}

void F_FrameEmblem::recalculate(const glm::vec2& frameOrigin,
                                const glm::vec2& frameSize,
                                float            cornerW,
                                float            cornerH)
{
    m_cachedQuads.clear();

    glm::vec2 spDim = m_sprite.getDim();
    float hw = spDim.x * 0.5f;
    float hh = spDim.y * 0.5f;

    // frame edges in world space
    float left   = frameOrigin.x;
    float right  = frameOrigin.x + frameSize.x - cornerW;
    float bottom = frameOrigin.y;
    float top    = frameOrigin.y + frameSize.y - cornerH;

    // edge centers
    float midX = frameOrigin.x + frameSize.x * 0.5f;
    float midY = frameOrigin.y + frameSize.y * 0.5f;

    if (m_type == EMBLEM_CORNER)
    {
        // Rotation per corner: TL=0, TR=90, BR=180, BL=270
        struct CornerInfo { int mask; float x; float y; float angle; };
        CornerInfo corners[4] = {
            { CORNER_TL, left,  top,    0.0f   },
            { CORNER_TR, right, top,    90.0f  },
            { CORNER_BR, right, bottom, 180.0f },
            { CORNER_BL, left,  bottom, 270.0f }
        };

        for (auto& c : corners)
        {
            if (!(m_placeMask & c.mask)) continue;
            // center-align emblem on corner slot
            float x = c.x + cornerW * 0.5f - hw;
            float y = c.y + cornerH * 0.5f - hh;
            pushQuad(x, y, spDim.x, spDim.y, c.angle);
        }
    }
    else // EMBLEM_LINE
    {
        // offset shifts along the edge from center
        // TOP/BOT: offset moves on X axis
        // LEFT/RIGHT: offset moves on Y axis

        struct LineInfo { int mask; float x; float y; float angle; };
        LineInfo lines[4] = {
            { LINE_TOP,   midX + m_offset, frameOrigin.y + frameSize.y - cornerH, 0.0f   },
            { LINE_BOT,   midX + m_offset, frameOrigin.y,                         0.0f   },
            { LINE_LEFT,  frameOrigin.x,   midY + m_offset,                       90.0f  },
            { LINE_RIGHT, frameOrigin.x + frameSize.x - cornerW, midY + m_offset, 270.0f }
        };

        for (auto& l : lines)
        {
            if (!(m_placeMask & l.mask)) continue;
            // center-align emblem on edge
            float x = l.x - hw;
            float y = l.y - hh;
            pushQuad(x, y, spDim.x, spDim.y, l.angle);
        }
    }

    m_dirty = false;
}

void F_FrameEmblem::draw(SpriteBatch& batch) const
{
    for (auto& q : m_cachedQuads)
    {
        batch.draw(q.destRect, q.uv, q.textureId, q.depth, { 255,255,255,255 }, q.angle);
    }
}

} // namespace Feintgine