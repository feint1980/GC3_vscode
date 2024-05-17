#ifndef _CHARGEPARTICLE_H_
#define _CHARGEPARTICLE_H_

#include "F_Sprite.h"


#define DISTANCE_THRESHOLD 0.25f

class ChargeParticle
{
    
public:
    ChargeParticle();
    ~ChargeParticle();

    ChargeParticle(const glm::vec2 & t_pos, const Feintgine::F_Sprite & t_sprite, float t_angle, float t_scale, float t_scaleRate, float t_lifeTime);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void setTargetPos(glm::vec2 * t_targetPos);
    void init(const glm::vec2 & t_pos, const Feintgine::F_Sprite & t_sprite, float t_angle, float t_scale, float t_scaleRate, float t_lifeTime);

    void setChargeMoveSpeed(float t_speed){ m_chargeMoveSpeed = t_speed; }

private :
    glm::vec2 m_pos;
    Feintgine::F_Sprite m_sprite;
    float m_angle;
    float m_scale;
    float m_scaleRate;
    float m_lifeTime;
    glm::vec2 * mp_targetPos;

    float m_chargeMoveSpeed = 0.1f;


    Feintgine::Color m_color;
    float m_depth;
};


#endif