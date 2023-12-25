#include "F_BaseObject.h"

namespace Feintgine
{
    F_BaseObject::F_BaseObject()
    {
        m_pos = glm::vec2(0.0f);
        m_scale = glm::vec2(1.0f);
        m_color = Feintgine::Color(255, 255, 255, 255);
        m_vel = glm::vec2(0.0f);
        m_angle = 0.0f;
        m_depth = 0.0f;
        p_pos = &m_pos;
    }

    F_BaseObject::~F_BaseObject()
    {

    }


    void F_BaseObject::init(const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animation,
        const Feintgine::Color & color, const glm::vec2 & vel, const glm::vec2 & pos, float depth, int afterImageCount, float afterImageRate)
    {
        m_pos = pos;
        m_scale = scale;
        m_color = color;
        m_animation = animation;
        m_animation.setPos(m_pos);
        m_animation.playAnimation("idle");
        m_animation.setScale(m_scale);
        m_animation.setColor(m_color);
        m_vel = vel;
        p_pos = &m_pos;
        m_depth = depth;

        m_afterImagesParticle.init(p_pos, &m_animation, &m_animation.getColor(), afterImageRate, afterImageCount);
    }

    void F_BaseObject::init(const glm::vec2 & scale, const std::string & animationPath,
            const Feintgine::Color & color,const glm::vec2 & vel,const glm::vec2 & pos,float depth,int afterImageCount, float afterImageRate)
    {
        m_pos = pos;
        m_scale = scale;
        m_color = color;
        m_animation.init(animationPath);
        m_animation.setPos(m_pos);
        m_animation.playAnimation("idle");
        m_animation.setScale(m_scale);
        m_animation.setColor(m_color);
        m_vel = vel;
        p_pos = &m_pos;
        m_depth = depth;

        m_afterImagesParticle.init(p_pos, &m_animation, &m_animation.getColor(), afterImageRate, afterImageCount);
    }

    void F_BaseObject::update(float deltaTime)
    {
        m_pos += m_vel * deltaTime;
        m_animation.setPos(m_pos);
        m_animation.update(deltaTime);
        m_animation.setAngle(m_angle);
        //m_animation.setColor
        m_animation.setScale(m_scale);
        m_afterImagesParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(),m_angle);
    }
    void F_BaseObject::draw(Feintgine::SpriteBatch & spriteBatch)
    {
        m_animation.draw(spriteBatch);
        m_afterImagesParticle.draw(spriteBatch);
    }
}