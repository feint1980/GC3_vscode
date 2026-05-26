#include "F_FrameObject.h"
#include <algorithm>
#include <iostream>

namespace Feintgine
{

constexpr const char* F_FrameObject::SPRITE_NAMES[COUNT];

void F_FrameObject::init(const std::string& packetname,
                         const glm::vec2&   pos,
                         const glm::vec2&   size,
                         float              depth,
                         const Color&       color,
                         float              borderScale)
{
    m_pos   = pos;
    m_size  = size;
    m_depth = depth;
    m_color = color;
    m_dirty = true;

    m_borderScale = borderScale;

    SpriteManager* sm = SpriteManager::Instance();
    for (int i = 0; i < COUNT; i++)
    {
        m_parts[i].sprite = sm->getSprite(packetname + "/" + SPRITE_NAMES[i]);
        m_parts[i].slot   = (PartSlot)i;
    }
}

void F_FrameObject::pushQuad(int slot, float x, float y, float w, float h,float depth)
{
    // F_Sprite& spr = m_parts[slot].sprite;
    // m_cachedQuads.push_back({
    //     { x + w * 0.5f, y + h * 0.5f, w, h },
    //     spr.getUV(),
    //     spr.getTexture().id
    // });

    F_Sprite& spr = m_parts[slot].sprite;
    // SpriteBatch expects bottom-left, pass as-is
    m_cachedQuads.push_back({
        { x, y, w, h },
        spr.getUV(),
        spr.getTexture().id,
        depth
    });
}

void F_FrameObject::recalculate()
{
    m_cachedQuads.clear();

    glm::vec2 cornerDim = m_parts[TL].sprite.getDim();

    float scaleX = (m_size.x < cornerDim.x * 2.0f) ? (m_size.x / (cornerDim.x * 2.0f)) : 1.0f;
    float scaleY = (m_size.y < cornerDim.y * 2.0f) ? (m_size.y / (cornerDim.y * 2.0f)) : 1.0f;
    float scale  = std::min(scaleX, scaleY);



    scale = m_borderScale;
    // scale = 1.1f;

    float cw = cornerDim.x * scale;
    float ch = cornerDim.y * scale;

    float midW = m_size.x - cw * 2.0f;
    float midH = m_size.y - ch * 2.0f;

    // m_pos is CENTER of the frame, convert to bottom-left first
    float originX = m_pos.x - m_size.x * 0.5f;
    float originY = m_pos.y - m_size.y * 0.5f;

    float col0 = originX;
    float col1 = originX + cw;
    float col2 = originX + m_size.x - cw;

    float row0 = originY;
    float row1 = originY + ch;
    float row2 = originY + m_size.y - ch;

    float overlap = 6.0f * scale;  // tweak this value to taste

    // Corners
    pushQuad(TL, col0, row2, cw,  ch,70.0f);
    pushQuad(TR, col2, row2, cw,  ch,70.0f);
    pushQuad(BL, col0, row0, cw,  ch,70.0f);
    pushQuad(BR, col2, row0, cw,  ch,70.0f);

    // Horizontal borders
    pushQuad(Border_T, col1 - overlap , row2, midW + overlap * 2.0f, ch,50.0f);
    pushQuad(Border_B, col1 - overlap , row0, midW + overlap * 2.0f, ch,50.0f);

    // Vertical borders
    pushQuad(Border_L, col0, row1 - overlap, cw, midH + overlap * 2.0f  ,50.0f);
    pushQuad(Border_R, col2, row1 - overlap, cw, midH + overlap * 2.0f ,50.0f);

    m_dirty = false;
}

void F_FrameObject::draw(SpriteBatch& spriteBatch)
{
    if (m_dirty) recalculate();

    for (auto& q : m_cachedQuads)
    {
        spriteBatch.draw(q.destRect, q.uv, q.textureId, q.depth, m_color);
    }
}

} // namespace Feintgine