#include "F_FrameObject.h"
#include <iostream>
#include <algorithm>

namespace Feintgine
{

constexpr const char* F_FrameObject::SPRITE_NAMES[COUNT];

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
        m_parts[i].sprite = sm->getSprite(packetname + "/" + SPRITE_NAMES[i]);
        m_parts[i].slot   = (PartSlot)i;
    }
}

void F_FrameObject::pushQuad(int slot, float x, float y, float w, float h)
{
    F_Sprite& spr = m_parts[slot].sprite;
    // convert bottom-left origin to center origin for SpriteBatch
    m_cachedQuads.push_back({
        { x + w * 0.5f, y + h * 0.5f, w, h },
        spr.getUV(),
        spr.getTexture().id
    });
}

void F_FrameObject::recalculate()
{
    m_cachedQuads.clear();

    // --- Natural dims from sprites ---
    glm::vec2 cornerDim = m_parts[TL].sprite.getDim();
    glm::vec2 embT_dim  = m_parts[EMB_T].sprite.getDim();
    glm::vec2 embL_dim  = m_parts[EMB_L].sprite.getDim();
    glm::vec2 bh_dim    = m_parts[BH_TL].sprite.getDim();
    glm::vec2 bv_dim    = m_parts[BV_TL].sprite.getDim();

    // --- Scale for corners and emblems only (scale down only, never up) ---
    // Natural size = 2 corners + 2 borders + 1 emblem per axis
    // But borders stretch, so we only scale-protect corners and emblems.
    // Scale is driven by how much space corners+emblems need vs what we have.

    // float fixedW = cornerDim.x * 2.0f + embT_dim.x;   // non-stretchable width
    // float fixedH = cornerDim.y * 2.0f + embL_dim.y;   // non-stretchable height
    // Natural fixed size includes corners + emblems + border thickness
    float fixedW = cornerDim.x * 2.0f + embT_dim.x + bh_dim.x * 2.0f;
    float fixedH = cornerDim.y * 2.0f + embL_dim.y + bv_dim.y * 2.0f;

    // If the box is smaller than the fixed parts, scale them down uniformly
    float scaleX = (m_size.x < fixedW) ? (m_size.x / fixedW) : 1.0f;
    float scaleY = (m_size.y < fixedH) ? (m_size.y / fixedH) : 1.0f;
    float scale  = std::min(scaleX, scaleY);  // uniform to avoid distortion

    // --- Scaled fixed dims ---
    float cw    = cornerDim.x * scale; 
    float ch    = cornerDim.y * scale;
    float embTw = embT_dim.x  * scale;
    float embTh = embT_dim.y  * scale;
    float embLw = embL_dim.x  * scale;
    float embLh = embL_dim.y  * scale;

    // Border thickness is also scaled (height of hor border, width of ver border)
    float bh_h  = bh_dim.y * scale;
    float bv_w  = bv_dim.x * scale;

    // --- Border stretch dims ---
    // Whatever space is left after corners and emblem = border stretch area
    // Split evenly left/right of emblem (or top/bottom)
    float bh_w  = (m_size.x - cw * 2.0f - embTw) / 2.0f;  // horizontal border width, stretches
    float bv_h  = (m_size.y - ch * 2.0f - embLh) / 2.0f;  // vertical border height, stretches

    // --- Row y positions (bottom to top) ---
    float row0_y = m_pos.y;                          // bottom edge
    float row1_y = m_pos.y + ch;                     // above bottom corners
    float row2_y = m_pos.y + ch + bv_h;             // above bottom vert border
    float row3_y = m_pos.y + ch + bv_h + embLh;    // above side emblem
    float row4_y = m_pos.y + m_size.y - ch;         // top corners row

    // --- Col x positions (left to right) ---
    float col0_x = m_pos.x;                          // left edge
    float col1_x = m_pos.x + cw;                    // right of left corners
    float col2_x = m_pos.x + cw + bh_w;            // right of left hor border
    float col3_x = m_pos.x + cw + bh_w + embTw;   // right of top emblem
    float col4_x = m_pos.x + m_size.x - cw;        // right corners col

    // --- Corners ---
    pushQuad(TL, col0_x, row4_y, cw, ch);
    pushQuad(TR, col4_x, row4_y, cw, ch);
    pushQuad(BL, col0_x, row0_y, cw, ch);
    pushQuad(BR, col4_x, row0_y, cw, ch);

    // --- Horizontal borders (stretch width, fixed scaled height) ---
    pushQuad(BH_TL, col1_x, row4_y, bh_w, bh_h);
    pushQuad(BH_TR, col3_x, row4_y, bh_w, bh_h);
    pushQuad(BH_BL, col1_x, row0_y, bh_w, bh_h);
    pushQuad(BH_BR, col3_x, row0_y, bh_w, bh_h);

    // --- Vertical borders (fixed scaled width, stretch height) ---
    pushQuad(BV_TL, col0_x, row3_y, bv_w, bv_h);
    pushQuad(BV_BL, col0_x, row1_y, bv_w, bv_h);
    pushQuad(BV_TR, col4_x, row3_y, bv_w, bv_h);
    pushQuad(BV_BR, col4_x, row1_y, bv_w, bv_h);

    // --- Emblems (scaled, centered in their slot) ---
    pushQuad(EMB_T, col2_x, row4_y, embTw, embTh);
    pushQuad(EMB_B, col2_x, row0_y, embTw, embTh);
    pushQuad(EMB_L, col0_x, row2_y, embLw, embLh);
    pushQuad(EMB_R, col4_x, row2_y, embLw, embLh);

    m_dirty = false;
}

void F_FrameObject::draw(SpriteBatch& spriteBatch)
{
    if (m_dirty) recalculate();

    for (auto& q : m_cachedQuads)
    {
        spriteBatch.draw(q.destRect, q.uv, q.textureId, m_depth, m_color);
    }
}

} // namespace Feintgine