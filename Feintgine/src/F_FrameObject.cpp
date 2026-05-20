#include "F_FrameObject.h"
#include <iostream>

namespace Feintgine
{

constexpr const char* F_FrameObject::SUFFIXES[COUNT];

void F_FrameObject::init(const std::string& packetname,
                        const glm::vec2&   pos,
                        const glm::vec2&   size,
                        float              depth,
                        const Color&       color)
{
    m_pos   = pos;
    m_size  = size;
    m_depth = depth;
    m_color = color;
    m_dirty = true;

    SpriteManager* sm = SpriteManager::Instance();
    for (int i = 0; i < COUNT; i++)
    {
        m_parts[i].m_sprite = sm->getSprite(packetname + SUFFIXES[i]);
        m_parts[i].slot     = (PartSlot)i;
    }
}

void F_FrameObject::recalculate()
{
    // Corner dims read from sprites — artist controls corner size via sprite sheet
    glm::vec2 tl_dim = m_parts[TL].m_sprite.getDim();
    glm::vec2 br_dim = m_parts[BR].m_sprite.getDim();

    float cw   = tl_dim.x;
    float ch   = tl_dim.y;
    float midW = m_size.x - cw - br_dim.x;
    float midH = m_size.y - ch - br_dim.y;

    // Column x positions
    float col0 = m_pos.x;
    float col1 = m_pos.x + cw;
    float col2 = m_pos.x + cw + midW;

    // Row y positions (bottom-left origin)
    float row0 = m_pos.y;
    float row1 = m_pos.y + ch;
    float row2 = m_pos.y + ch + midH;

    m_destRects[TL]     = { col0, row2, cw,   ch   };
    m_destRects[Top]    = { col1, row2, midW, ch   };
    m_destRects[TR]     = { col2, row2, cw,   ch   };
    m_destRects[L]      = { col0, row1, cw,   midH };
    m_destRects[Center] = { col1, row1, midW, midH };
    m_destRects[R]      = { col2, row1, cw,   midH };
    m_destRects[BL]     = { col0, row0, cw,   ch   };
    m_destRects[Bot]    = { col1, row0, midW, ch   };
    m_destRects[BR]     = { col2, row0, cw,   ch   };

    m_dirty = false;
}

void F_FrameObject::draw(SpriteBatch& spriteBatch)
{
    if (m_dirty)
    {
        recalculate();
    } 

    for (int i = 0; i < COUNT; i++)
    {
        spriteBatch.draw(
            m_destRects[i],
            m_parts[i].m_sprite.getUV(),
            m_parts[i].m_sprite.getTexture().id,
            m_depth,
            m_color
        );
    }
}

} // namespace Feintgine