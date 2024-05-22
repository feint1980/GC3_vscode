#include "ChargeParticle.h"


ChargeParticle::ChargeParticle(const glm::vec2 & t_pos, const Feintgine::F_Sprite & t_sprite, float t_angle, float t_scale, float t_scaleRate, float t_lifeTime)
{
    init(t_pos, t_sprite, t_angle, t_scale, t_scaleRate, t_lifeTime);
    m_color = Feintgine::Color(255, 255, 255, 140);
}

ChargeParticle::ChargeParticle()
{

}


ChargeParticle::~ChargeParticle()
{

}

void ChargeParticle::draw(Feintgine::SpriteBatch & spriteBatch)
{
    glm::vec4 uvRect = m_sprite.getUV();
    glm::vec4 destRect(m_pos.x  -( m_scale * m_sprite.getDim().x * 0.5f), 
			m_pos.y - (m_scale * m_sprite.getDim().y * 0.5f), 
			m_scale * m_sprite.getDim().x
			, m_scale * m_sprite.getDim().y);
    spriteBatch.draw(destRect, uvRect, m_sprite.getTexture().id, m_depth, m_color, m_angle);
}

void ChargeParticle::setTargetPos(glm::vec2 * t_targetPos)
{
    //std::cout << "set target \n";
    //std::cout << t_targetPos << "\n";
  
    mp_targetPos = t_targetPos;
    //std::cout << mp_targetPos << "\n";
}

void ChargeParticle::update(float deltaTime)
{
    if(mp_targetPos)
    {
        //std::cout << "has target \n";
        if(m_lifeTime > 0)
        {
            m_lifeTime -= deltaTime;
            m_angle += deltaTime;
            m_direction = glm::normalize(*mp_targetPos - m_pos);
            //std::cout << "lifeTime " << m_lifeTime << "\n";
            //std::cout << "x " << mp_targetPos->x << " y " << mp_targetPos->y << "\n";
            m_lifeTime -= deltaTime;
            m_vel = m_direction * m_chargeMoveSpeed;
            float distance = glm::length(*mp_targetPos - m_pos);
            m_pos += m_vel * deltaTime;

            //std::cout << "distance " << distance << "\n";
            if(abs(distance) < DISTANCE_THRESHOLD)
            {
                m_lifeTime = 0.0f;
                m_pos = *mp_targetPos;
            }
            
            // {

            //     //m_pos = *mp_targetPos + glm::vec2(100); 
            //     m_pos += m_vel * deltaTime;
            // }
            // {
            //     m_pos = *mp_targetPos;
            //     m_lifeTime = 0.0f;
            // }

        }
    }
    

}


void ChargeParticle::init(const glm::vec2 & t_pos, const Feintgine::F_Sprite & t_sprite, float t_angle, float t_scale, float t_scaleRate, float t_lifeTime)
{
    m_pos = t_pos;
    m_sprite = t_sprite;
    m_angle = t_angle;
    m_scale = t_scale;
    m_scaleRate = t_scaleRate;
    m_lifeTime = t_lifeTime;
    m_color = Feintgine::Color(255, 255, 255, 255);
    m_depth = 20.1f;
}