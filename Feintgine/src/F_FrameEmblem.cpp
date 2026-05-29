#include "F_FrameEmblem.h"
#include "feint_common.h"
namespace Feintgine
{

void F_FrameEmblem::init(const std::string& spriteName,
                        EmblemType         type,
                        int                placeMask,
                        int                hideMask,
                        const glm::vec2    &offset,    
                        float              scale,
                        float              depth)
{
    m_sprite    = SpriteManager::Instance()->getSprite(spriteName);
    m_type      = type;
    m_placeMask = placeMask;
    m_hideMask  = hideMask;
    m_offset    = offset;
    m_depth     = depth;
    m_emblemScale = scale;
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
    float drawW = spDim.x * m_emblemScale;
    float drawH = spDim.y * m_emblemScale;
    float hw = drawW * 0.5f;
    float hh = drawH * 0.5f;

    // frame edges in world space
    float left   = frameOrigin.x;
    float right  = frameOrigin.x + frameSize.x - cornerW;
    float bottom = frameOrigin.y;
    float top    = frameOrigin.y + frameSize.y - cornerH;

    // edge centers
    float midX = frameOrigin.x + frameSize.x * 0.5f + hw;
    float midY = frameOrigin.y + frameSize.y * 0.5f + hh;
    float topY   = frameOrigin.y + frameSize.y - cornerH - hh;
    float botY   = frameOrigin.y + hh;
    float leftX  = frameOrigin.x + hw;
    float rightX = frameOrigin.x + frameSize.x - cornerW - hw;

    if (m_type == EMBLEM_CORNER)
    {
        // Rotation per corner: TL=0, TR=90, BR=180, BL=270
        struct CornerInfo { int mask; float x; float y; float angle;  glm::vec2 offsetMul; };
        CornerInfo corners[4] = {
            { CORNER_TL, left,  top,    0.0f ,{1,1}  },
            { CORNER_TR, right, top,    -90.0f , {-1,1}  },
            { CORNER_BR, right, bottom, -180.0f , {-1,-1} },
            { CORNER_BL, left,  bottom, -270.0f , {1,-1} }
        };

        for (auto& c : corners)
        {
            if (!(m_placeMask & c.mask)) continue;
            // center-align emblem on corner slot
            float x = c.x + cornerW * 0.5f - hw + m_offset.x * c.offsetMul.x;
            float y = c.y + cornerH * 0.5f - hh + m_offset.y * c.offsetMul.y;
            pushQuad(x, y, drawW, drawH, c.angle);
        }
    }
    else // EMBLEM_LINE
    {
        // offset shifts along the edge from center
        // TOP/BOT: offset moves on X axis
        // LEFT/RIGHT: offset moves on Y axis

        struct LineInfo { int mask; float x; float y; float angle;;};
        LineInfo lines[4] = {
            { LINE_TOP,   midX + m_offset.x,   topY + m_offset.y, 0.0f   },
            { LINE_BOT,   midX + m_offset.x,   botY - m_offset.y, 180.0f },
            { LINE_LEFT,  leftX  - m_offset.y, midY + m_offset.x, 270.0f },
            { LINE_RIGHT, rightX + m_offset.y, midY + m_offset.x, 90.0f  }
        };

        for (auto& l : lines)
        {
            if (!(m_placeMask & l.mask)) continue;
            float x = l.x - hw;
            float y = l.y - hh;
            pushQuad(x, y, drawW, drawH, l.angle);
        }
    }

    m_dirty = false;
}

void F_FrameEmblem::draw(SpriteBatch& batch) const
{
    for (auto& q : m_cachedQuads)
    {
        
        batch.draw(q.destRect, q.uv, q.textureId, q.depth, { 255,255,255,255 }, q.angle /57.2957795f);
    }
}

} // namespace Feintgine

