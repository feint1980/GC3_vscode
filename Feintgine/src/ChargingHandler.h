#include "F_Sprite.h"


struct ChargeParticle
{
    glm::vec2 pos;
    Feintgine::F_Sprite sprite;
    float m_angle;
    float m_scale;
    float m_scaleRate;
    float m_lifeTime;

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void init(const glm::vec2 & t_pos, const Feintgine::F_Sprite & t_sprite, float t_angle, float t_scale, float t_scaleRate, float t_lifeTime);
    
};


class ChargingHandler
{
public:
    ChargingHandler();
    ~ChargingHandler();


    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void setChargingSprites(const std::vector<Feintgine::F_Sprite> & t_chargingSprites, float t_chargeTime, float t_chargeRadius, int t_chargeMaxCount);


    private:
    // todo: put it in other class
    std::vector<ChargeParticle> m_chargingParticles;
    float m_chargeTime;
    float m_chargeRadius;
    int m_chargeMaxCount;
    float m_chargeMoveSpeed;

}