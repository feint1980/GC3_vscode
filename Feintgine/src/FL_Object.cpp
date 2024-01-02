#include "fl_object.h"


namespace Feintgine
{
    FL_OBject::FL_OBject()
    {
        //ctor
    }

    FL_OBject::~FL_OBject()
    {
        //dtor
    }
    void FL_OBject::init(const Feintgine::F_Sprite & sprite ,const glm::vec2 & pos, const glm::vec2 & scale)
    {
        m_sprite = sprite;
        m_pos = pos;
        m_scale = scale;
        m_dim = sprite.getDim() * m_scale;
        m_isAnimated = false;
    }
    void FL_OBject::init(const Feintgine::F_AnimatedObject & animObj, const glm::vec2 & pos, const glm::vec2 & scale)
    {
        m_animation = animObj;
        m_pos = pos;
        m_scale = scale;
        m_dim = m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim() * m_scale;
        m_isAnimated = true;
    }

    void FL_OBject::draw(Feintgine::SpriteBatch & spriteBatch)
    {
        if(m_isAnimated)
        {
            m_animation.setPos(m_pos);
            m_animation.setScale(m_scale);
            m_animation.setAngle(m_angle);
            m_animation.setColor(m_color);
            m_animation.setDepth(m_depth);
            m_animation.draw(spriteBatch);
        }
        else
        {

            spriteBatch.draw(glm::vec4(m_pos.x,m_pos.y,m_dim.x,m_dim.y),m_sprite.getUV(),m_sprite.getTexture().id,m_depth,m_color,m_angle);
        }
    }

}