#include "ChargeParticle.h"
#include "feint_common.h"


class ChargingHandler
{
public:
    ChargingHandler();
    ~ChargingHandler();


    void registerTargetPos(glm::vec2 * t_targetPos);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void setCharging(const std::vector<Feintgine::F_Sprite> & t_chargingSprites, float t_chargeTime, float t_chargeRadius, int t_chargeMaxCount);

    void setPos(const glm::vec2 & pos);

    private:

    std::vector<ChargeParticle *> m_chargingParticles;
    float m_chargeTime;
    float m_chargeRadius;
    int m_chargeMaxCount;
    float m_chargeMoveSpeed;

    glm::vec2 m_pos;
    glm::vec2 * mp_targetPos;

};