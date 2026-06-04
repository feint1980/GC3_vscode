#ifndef _F_FRAMEPANEL_H_
#define _F_FRAMEPANEL_H_

#include "F_FrameObject.h"
#include "F_FrameEmblem.h"
#include <vector>

namespace Feintgine
{
    class F_FramePanel
    {
    public:
        F_FramePanel() = default;
        ~F_FramePanel() = default;

        void init(const std::string& packetname,
                    const glm::vec2&   pos,
                    const glm::vec2&   size,
                    float              depth = 0.5f,
                    const Color&       color = Color(255, 255, 255, 255),
                    float              scale = 1.0f);

        // void addCornerEmblem(const std::string& spriteName,
        //                         int                placeMask,
        //                         int                hideMask  = 0,
        //                         float              depth     = 60.0f);

        void addCornerEmblem(const std::string& spriteName,
                    int                placeMask,
                    int                hideMask  = 0,
                    const glm::vec2    &offset    = glm::vec2(0),
                    float              scale     = 1.0f,
                    float              depth     = 60.0f);


        void addLineEmblem  (const std::string& spriteName,
                                int                placeMask,
                                int                hideMask  = 0,
                                const glm::vec2    &offset    = glm::vec2(0.0f),
                                float              scale     = 1.0f,
                                float              depth     = 60.0f);

        void setPos  (const glm::vec2& pos);
        void setSize (const glm::vec2& size);
        void setDepth(float depth)          { m_frame.setDepth(depth); }
        void setColor(const Color& color)   { 
            
            m_frame.setColor(color);
            
            for (auto& emblem : m_emblems) 
            {
                emblem.setColor(color);
            }
        
        }
        void setScale(float scale)          
        { 
            m_scale = scale;
            m_frame.setScale(m_scale);
        }
        

        glm::vec2 getPos()  const { return m_frame.getPos();  }
        glm::vec2 getSize() const { return m_frame.getSize(); }

        void draw(SpriteBatch& spriteBatch);

        void hideBorderCorner(int mask) { 
            m_frame.setHideCornerMask(mask);
            rebuildHideMasks();
        }
        void hideBorderLine(int mask) {
            m_frame.setHideLineMask(mask);
            rebuildHideMasks();
        }


        void setAngle(float angle);
        float getAngle() const { return m_angle; }
    private:
        void rebuildHideMasks();
        void markAllEmblemsDirty();

        F_FrameObject              m_frame;
        std::vector<F_FrameEmblem> m_emblems;
        float                      m_scale = 1.0f;
        float                      m_angle = 0.0f;
    };
}

#endif