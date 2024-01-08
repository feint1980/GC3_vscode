#include "fl_object.h"


namespace Feintgine
{
    FL_Object::FL_Object()
    {
        //ctor
        m_color = Feintgine::Color(255, 255, 255, 255);
    }

    FL_Object::~FL_Object()
    {
        //dtor
    }
    void FL_Object::init(const Feintgine::F_Sprite & sprite ,const glm::vec2 & pos, const glm::vec2 & scale)
    {
        m_sprite = sprite;
        m_pos = pos;
        m_scale = scale;
        m_dim = sprite.getDim() * m_scale;
        m_isAnimated = false;
    }
    void FL_Object::init(const Feintgine::F_AnimatedObject & animObj, const glm::vec2 & pos, const glm::vec2 & scale)
    {
        m_animation = animObj;
        m_animation.playAnimation("idle");
        m_pos = pos;
        m_scale = scale;
        m_dim = m_animation.getCurrentAnimation()->getCurrentAnim()->sprite.getDim() * m_scale;
        m_animation.setPos(m_pos);
        m_animation.setScale(m_scale);
        m_animation.setAngle(m_angle);
        m_animation.setColor(m_color);

        m_isAnimated = true;
    }

    void FL_Object::draw(Feintgine::SpriteBatch & spriteBatch)
    {
        if(m_isAnimated)
        {
            m_animation.setPos(m_pos);
            m_animation.setScale(m_scale);
            m_animation.setAngle(m_angle);
            m_animation.setColor(m_color);
            m_animation.setDepth(m_depth);
            m_animation.draw(spriteBatch);
           //std::cout << "draw" << std::endl;
        }
        else
        {

            spriteBatch.draw(glm::vec4(m_pos.x,m_pos.y,m_dim.x,m_dim.y),m_sprite.getUV(),m_sprite.getTexture().id,m_depth,m_color,m_angle);
        }
    }

    void FL_Object:: defaultUpdate(float deltaTime)
    {
        m_pos += m_vel * deltaTime;
        if(m_hasTarget)
        {
            if(!m_isReachDestination)
            {
                if(glm::distance(m_pos,m_destination) < 0.1f)
                {
                    m_isReachDestination = true;
                    m_hasTarget = false;
                }
                else
                {
                    m_vel = glm::normalize(m_destination - m_pos) * m_speed;
                }
            }
        }
    }

    void FL_Object::setManipulatedFunc(std::function<void(float)> func, float duration, float delayTime)
	{
		m_malipulatedFunc = func;
		m_manipulateDuration = duration;
		m_manipulateDelayTime = delayTime;
	}
	

    void FL_Object::update(float deltaTime)
    {
        if(m_malipulatedFunc)
        { 
            if(m_manipulateDelayTime > 0.0f)
            {
                m_manipulateDelayTime -= deltaTime;
            }
            else
            {
                if(m_manipulateDuration > 0.0f)
                {
                    m_manipulateDuration -= deltaTime;
                    m_malipulatedFunc(deltaTime);
                    return;
                }
                else
                {
                    m_malipulatedFunc = nullptr;
                    m_manipulateDuration = 0.0f;
                    m_manipulateDelayTime = 0.0f;
                }
            }
        }
        if(m_updateFunc)
        {
            m_updateFunc(deltaTime);
            return;
        }
        defaultUpdate(deltaTime);
        
    }

}