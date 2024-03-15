
#include "F_LuaObject.h"


namespace Feintgine
{
    F_LuaObject::F_LuaObject()
    {

    }

    F_LuaObject::~F_LuaObject()
    {

    }

    void F_LuaObject::init(const glm::vec2 & pos, const glm::vec2 & scale, const std::string & filePath, const std::string & name, int id, const glm::vec2 & vel)
    {
        m_pos = pos;
        m_scale = scale;
        m_animation.init(filePath);
        m_animation.playAnimation("idle");
        m_name = name;
        m_id = id;
        m_vel = vel;
    }
    void F_LuaObject::draw(Feintgine::SpriteBatch & spriteBatch)
    {
        m_animation.draw(spriteBatch);
    }

    void F_LuaObject::handleMoveToTargetPos(float deltaTime)
    {
        float dist = glm::distance(m_pos, m_targetPos);
        if (dist > 1.0f)
        {
            m_vel = glm::normalize(m_targetPos - m_pos) * 2.2f;
        }
        else
        {
            m_pos = m_targetPos;
            m_vel = glm::vec2(0, 0);
        }
    }

    void F_LuaObject::update(float deltaTime)
    {
        m_animation.update(deltaTime);
        
        m_pos += m_vel * deltaTime;
        m_animation.setPos(m_pos);
        m_animation.setScale(m_scale);
        m_animation.setAngle(0.0);
        handleMoveToTargetPos(deltaTime);

    }
    



}

