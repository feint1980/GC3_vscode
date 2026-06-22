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
    m_hasBG = false;
    m_dirty = true;
    m_bgScale = 1.0f;

    m_borderScale = borderScale;
    m_bgColor = Feintgine::Color(46, 46, 46, 100);

    SpriteManager* sm = SpriteManager::Instance();
    for (int i = 0; i < COUNT; i++)
    {
        m_parts[i].sprite = sm->getSprite(packetname + "/" + SPRITE_NAMES[i]);
        m_parts[i].slot   = (PartSlot)i;
    }
    m_cachedQuads.reserve(COUNT);
}

void F_FrameObject::pushQuad(int slot, float x, float y, float w, float h, float depth)
{
    F_Sprite& spr = m_parts[slot].sprite;

    // Rotate the quad's center around the frame pivot (m_pos)
    glm::vec2 center(x + w * 0.5f, y + h * 0.5f);
    if (m_angle != 0.0f)
        center = rotateAround(center, m_pos, m_angle / 57.2957795f);

    CachedQuad q;
    q.destRect  = glm::vec4(center.x - w * 0.5f, center.y - h * 0.5f, w, h);
    q.uv        = spr.getUV();
    q.textureId = spr.getTexture().id;
    q.depth     = m_depth + (depth * 0.01f);

    m_cachedQuads.push_back(q);
}

void F_FrameObject::recalculate()
{
    m_cachedQuads.clear();
    m_lines.clear();
    glm::vec2 cornerDim = m_parts[TL].sprite.getDim();  // 72x72

    float scaleX = (m_size.x < cornerDim.x * 2.0f) ? (m_size.x / (cornerDim.x * 2.0f)) : 1.0f;
    float scaleY = (m_size.y < cornerDim.y * 2.0f) ? (m_size.y / (cornerDim.y * 2.0f)) : 1.0f;
    float scale  = std::min(scaleX, scaleY) * m_borderScale;

    float cw = cornerDim.x * scale;
    float ch = cornerDim.y * scale;

    float midW = m_size.x - cw * 2.0f;
    float midH = m_size.y - ch * 2.0f;

    float originX = m_pos.x - m_size.x * 0.5f;
    float originY = m_pos.y - m_size.y * 0.5f;

    float col0 = originX;
    float col1 = originX + cw;
    float col2 = originX + m_size.x - cw;

    float row0 = originY;
    float row1 = originY + ch;
    float row2 = originY + m_size.y - ch;

    float overlap = cw * 0.1f;  // overlap as fraction of corner size, stays proportional

    // Corners
    if (!(m_hideCornerMask & CORNER_TL)) pushQuad(TL, col0, row2, cw, ch, 70.0f);
    if (!(m_hideCornerMask & CORNER_TR)) pushQuad(TR, col2, row2, cw, ch, 70.0f);
    if (!(m_hideCornerMask & CORNER_BL)) pushQuad(BL, col0, row0, cw, ch, 70.0f);
    if (!(m_hideCornerMask & CORNER_BR)) pushQuad(BR, col2, row0, cw, ch, 70.0f);

    // Horizontal borders
    if (!(m_hideLineMask & LINE_TOP)) pushQuad(Border_T, col1 - overlap, row2, midW + overlap * 2.0f, ch, 50.0f);
    if (!(m_hideLineMask & LINE_BOT)) pushQuad(Border_B, col1 - overlap, row0, midW + overlap * 2.0f, ch, 50.0f);

    // Vertical borders
    if (!(m_hideLineMask & LINE_LEFT))  pushQuad(Border_L, col0, row1 - overlap, cw, midH + overlap * 2.0f, 50.0f);
    if (!(m_hideLineMask & LINE_RIGHT)) pushQuad(Border_R, col2, row1 - overlap, cw, midH + overlap * 2.0f, 50.0f);

    // if (m_hasBG)
    // pushQuad(BG, originX, originY, m_size.x , m_size.y, 10.0f);

    if (m_hasBG)
    {
        F_Sprite& spr = m_parts[BG].sprite;
        // float bgW = midW * m_bgScale;
        // float bgH = midH * m_bgScale;
        float bgW = m_size.x * m_bgScale;
        float bgH = m_size.y * m_bgScale;
        // glm::vec2 center(col1 + bgW * 0.5f, row1 + bgH * 0.5f);
        glm::vec2 center(m_pos.x, m_pos.y);
        // glm::vec2 center(m_pos.x, m_pos.y);
        if (m_angle != 0.0f)
        {
            center = rotateAround(center, m_pos, m_angle / 57.2957795f);
        }
        
        // m_bgQuad.destRect  = glm::vec4(center.x - bgW * 0.5f, center.y - bgH * 0.5f, bgW, bgH);
        // m_bgQuad.destRect = glm::vec4((m_pos.x - m_size.x * 0.5f) * m_bgScale, (m_pos.y - m_size.y * 0.5f) * m_bgScale, m_size.x * m_bgScale, m_size.y * m_bgScale);
        m_bgQuad.destRect = glm::vec4(
            m_pos.x - bgW * 0.5f,
            m_pos.y - bgH * 0.5f,
            bgW,
            bgH
        );
        m_bgQuad.uv        = spr.getUV();
        m_bgQuad.textureId = spr.getTexture().id;
        m_bgQuad.depth     = m_depth + (10.0f * 0.01f);
        m_hasBGQuad        = true;
    }

    for (const FrameLine& line : m_lineDefs)
    {
        pushLineQuad(line.offset, line.width, line.depth);
    }

    m_dirty = false;
}

void F_FrameObject::draw(SpriteBatch& spriteBatch)
{
    if (m_dirty)
    {
        recalculate();
    } 

    for (int i = 0; i < (int)m_cachedQuads.size(); i++)
    {
        spriteBatch.draw(m_cachedQuads[i].destRect, m_cachedQuads[i].uv, m_cachedQuads[i].textureId, m_cachedQuads[i].depth, m_color, m_angle / 57.2957795f);
    }

    if (m_hasBGQuad)
    spriteBatch.draw(m_bgQuad.destRect, m_bgQuad.uv, m_bgQuad.textureId, m_bgQuad.depth, m_bgColor, m_angle / 57.2957795f);

    for (int i = 0; i < (int)m_lines.size(); i++)
    {
        spriteBatch.draw(m_lines[i].destRect, m_lines[i].uv, m_lines[i].textureId, m_lines[i].depth, m_color, m_angle / 57.2957795f);
    }
}

void F_FrameObject::setColor(const Feintgine::Color& color)
{
    m_color = color;
}

void F_FrameObject::addLine(const glm::vec2& offset, float width, float depth)
{
    m_lineDefs.push_back({ offset, width, depth });
    m_dirty = true;
}
void F_FrameObject::pushLineQuad(const glm::vec2& offset, float width, float depth)
{
    F_Sprite& spr = m_parts[Border_T].sprite;   // reuse top border (loop texture)

    float h = spr.getDim().y * getScale();      // thickness comes from sprite height, scaled like the frame

    // offset is relative to frame center (m_pos), pre-rotation
    glm::vec2 center = m_pos + offset;
    if (m_angle != 0.0f)
    {
        center = rotateAround(center, m_pos, m_angle / 57.2957795f);
    }
        
    CachedQuad q;
    q.destRect  = glm::vec4(center.x - width * 0.5f, center.y - h * 0.5f, width, h);
    q.uv        = spr.getUV();
    q.textureId = spr.getTexture().id;
    q.depth     = m_depth + (depth * 0.01f);

    m_lines.push_back(q);
}


} // namespace Feintgine