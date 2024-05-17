#include "ChargingHandler.h"

ChargingHandler::ChargingHandler()
{

}


ChargingHandler::~ChargingHandler()
{

}


void ChargingHandler::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for(int i = 0; i < m_chargingParticles.size(); i++)
    {
        m_chargingParticles[i].draw(spriteBatch);
    }

}

void ChargingHandler::update(float deltaTime)
{

    for(int i = 0; i < m_chargingParticles.size(); i++) 
    {
        m_chargingParticles[i].update(deltaTime);
    }   

}

void ChargingHandler::registerTargetPos(glm::vec2 * t_targetPos)
{
    mp_targetPos = t_targetPos;
}

void ChargingHandler::setChargingSprites(const std::vector<Feintgine::F_Sprite> & t_chargingSprites, float t_chargeTime, float t_chargeRadius, int t_chargeMaxCount)
{
    if(mp_targetPos)
    {
        m_chargeMaxCount = t_chargeMaxCount;
        int chargeSpritCount = t_chargingSprites.size();
        float calculateXPos = (*mp_targetPos).x - t_chargeRadius;
        float calculateYPos = (*mp_targetPos).y - t_chargeRadius;
        int spriteIndex = feint_common::Instance()->radndomInt(0, chargeSpritCount - 1);
        for(int i = 0; i < chargeSpritCount; i++)
        {
            float t_scale = feint_common::Instance()->getRandomNum(0.1f, 1.5f);
            ChargeParticle chargeParticle(glm::vec2(
                feint_common::Instance()->getRandomNum(calculateXPos,- t_chargeRadius), feint_common::Instance()->getRandomNum(calculateYPos, -t_chargeRadius)),
                t_chargingSprites[i],
                feint_common::Instance()->getRandomNum(0,3.1415f),
                t_scale, t_scale * 0.05f , t_chargeTime);
            chargeParticle.setChargeMoveSpeed(feint_common::Instance()->getRandomNum(3.1f, 7.5f));
            chargeParticle.setTargetPos(mp_targetPos);
            m_chargingParticles.push_back(chargeParticle);
        }
    }
}