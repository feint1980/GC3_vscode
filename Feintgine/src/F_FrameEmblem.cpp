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
    // x,y is bottom-left — convert to center, rotate around frame pivot, convert back
    glm::vec2 center(x + w * 0.5f, y + h * 0.5f);
    if (m_angle != 0.0f)
        center = rotateAround(center, m_pivot, glm::radians(m_angle));

    m_cachedQuads.push_back({
        { center.x - w * 0.5f, center.y - h * 0.5f, w, h },
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

    // Store frame center as pivot for positional rotation
    m_pivot = frameOrigin + frameSize * 0.5f;

    glm::vec2 spDim = m_sprite.getDim();
    float drawW = spDim.x * m_emblemScale;
    float drawH = spDim.y * m_emblemScale;
    float hw    = drawW * 0.5f;
    float hh    = drawH * 0.5f;

    // Pure frame geometry — all positions are CENTER points of their slot
    float midX   = frameOrigin.x + frameSize.x * 0.5f;
    float midY   = frameOrigin.y + frameSize.y * 0.5f;

    // Corner slot centers
    float left   = frameOrigin.x + cornerW * 0.5f;
    float right  = frameOrigin.x + frameSize.x - cornerW * 0.5f;
    float bottom = frameOrigin.y + cornerH * 0.5f;
    float top    = frameOrigin.y + frameSize.y - cornerH * 0.5f;

    if (m_type == EMBLEM_CORNER)
    {
        struct CornerInfo { int mask; float x; float y; float angle; glm::vec2 offsetMul; };
        CornerInfo corners[4] = {
            { CORNER_TL, left,  top,   m_angle +  0.0f,    {  1,  1 } },
            { CORNER_TR, right, top,   m_angle -90.0f,   { -1,  1 } },
            { CORNER_BR, right, bottom,m_angle -180.0f,  { -1, -1 } },
            { CORNER_BL, left,  bottom,m_angle -270.0f,  {  1, -1 } }
        };

        for (auto& c : corners)
        {
            if (!(m_placeMask & c.mask)) continue;
            // position is already center of slot, just apply offset then convert to bottom-left for SpriteBatch
            float x = c.x + m_offset.x * c.offsetMul.x - hw;
            float y = c.y + m_offset.y * c.offsetMul.y - hh;
            pushQuad(x, y, drawW, drawH, c.angle);
        }
    }
    else // EMBLEM_LINE
    {
        struct LineInfo { int mask; float x; float y; float angle; };
        LineInfo lines[4] = {
            { LINE_TOP,   midX  + m_offset.x, top   + m_offset.y, m_angle +  0.0f   },
            { LINE_BOT,   midX  + m_offset.x, bottom   - m_offset.y, m_angle + 180.0f },
            { LINE_LEFT,  left - m_offset.y, midY   + m_offset.x, m_angle + 90.0f }, 
            { LINE_RIGHT, right + m_offset.y, midY  + m_offset.x, m_angle + 270.0f  }
        };

        for (auto& l : lines)
        {
            if (!(m_placeMask & l.mask)) continue;
            // convert center to bottom-left for SpriteBatch
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
        
        batch.draw(q.destRect, q.uv, q.textureId, q.depth, m_color, glm::radians(q.angle));
    }
}

} // namespace Feintgine

