#include "F_FramePanel.h"

namespace Feintgine
{

void F_FramePanel::init(const std::string& packetname,
                        const glm::vec2&   pos,
                        const glm::vec2&   size,
                        float              depth,
                        const Color&       color,
                        float              scale)
{
    m_frame.init(packetname, pos, size, depth, color, scale);
    m_emblems.clear();
}

void F_FramePanel::addCornerEmblem(const std::string& spriteName,
                    int                placeMask,
                    int                hideMask,
                    const glm::vec2    &offset,
                    float              scale,
                    float              depth )
{
    F_FrameEmblem emb;
    emb.init(spriteName, EMBLEM_CORNER, placeMask, hideMask, offset, scale,depth);
    m_emblems.push_back(emb);
    rebuildHideMasks();
}

void F_FramePanel::addLineEmblem(const std::string& spriteName,
                                int                placeMask,
                                int                hideMask,
                                const glm::vec2    &offset,
                                float              scale,
                                float              depth)
{
    F_FrameEmblem emb;
    emb.init(spriteName, EMBLEM_LINE, placeMask, hideMask, offset,scale, depth);
    m_emblems.push_back(emb);
    rebuildHideMasks();
}

void F_FramePanel::rebuildHideMasks()
{
    // Accumulate hide masks from all emblems
    int hideCorner = 0;
    int hideLine   = 0;
    for (auto& e : m_emblems)
    {
        hideCorner |= e.getHideCornerMask();
        hideLine   |= e.getHideLineMask();
    }
    m_frame.setHideCornerMask(hideCorner);
    m_frame.setHideLineMask(hideLine);
}

void F_FramePanel::setPos(const glm::vec2& pos)
{
    m_frame.setPos(pos);
    markAllEmblemsDirty();
}

void F_FramePanel::setSize(const glm::vec2& size)
{
    m_frame.setSize(size);
    markAllEmblemsDirty();
}

void F_FramePanel::markAllEmblemsDirty()
{
    for (auto& e : m_emblems)
        e.markDirty();
}

void F_FramePanel::draw(SpriteBatch& spriteBatch)
{
    m_frame.draw(spriteBatch);

    // Feed frame's current layout data to each emblem
    glm::vec2 origin  = m_frame.getFrameOrigin();
    glm::vec2 size    = m_frame.getSize();
    float     cornerW = m_frame.getScaledCornerW();
    float     cornerH = m_frame.getScaledCornerH();

    for (auto& e : m_emblems)
    {
        if (e.isDirty())
            e.recalculate(origin, size, cornerW, cornerH);
        e.draw(spriteBatch);
    }
}

void F_FramePanel::setAngle(float angle)
{
    m_angle = angle;
    m_frame.setAngle(angle);
    for (auto& e : m_emblems)
    {
        e.setAngle(angle);
    }
}

void F_FramePanel::addLine(const glm::vec2& offset, float width, float depth)
{
    m_frame.addLine(offset, width, depth);
    markAllEmblemsDirty();
}

bool F_FramePanel::isMouseInPanel(const glm::vec2& mousePos)
{
    return m_frame.isMouseInside(mousePos);
}

} // namespace Feintgine