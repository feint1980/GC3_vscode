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
        m_chargingParticles[i]->draw(spriteBatch);
    }

}

void ChargingHandler::update(float deltaTime)
{

    // if(t_chargeTime > 0)
    // {
    //     t_chargeTime -= deltaTime;
    // }

    for(int i = 0; i < m_chargingParticles.size(); i++) 
    {
        if(m_chargingParticles[i]->getLifeTime() > 0.0f)
        {
            m_chargingParticles[i]->update(deltaTime);
        }
        else
        {
            m_chargingParticles.erase(m_chargingParticles.begin() + i);
        }
        
    }   
    

}

void ChargingHandler::registerTargetPos(glm::vec2 * t_targetPos)
{
    //std::cout << "register Target Pos \n";
    //std::cout << t_targetPos << "\n";
    //std::cout << mp_targetPos << "\n";
    mp_targetPos = t_targetPos;
    
}

void ChargingHandler::setPos(const glm::vec2 & t_pos)
{
    m_pos = t_pos;
    mp_targetPos = &m_pos;
}
   

void ChargingHandler::setCharging(const std::vector<Feintgine::F_Sprite> & t_chargingSprites, float t_chargeTime, float t_chargeRadius, int t_chargeMaxCount)
{
    if(mp_targetPos)
    {

        //std::cout << "set charging pass 2 \n";
        m_chargeMaxCount = t_chargeMaxCount;
        int chargeSpritCount = t_chargingSprites.size();
        float calculateXPos = (*mp_targetPos).x - t_chargeRadius;
        float calculateYPos = (*mp_targetPos).y - t_chargeRadius;
       
        for(int i = 0; i < m_chargeMaxCount; i++)
        {
            int spriteIndex = feint_common::Instance()->radndomInt(0, chargeSpritCount - 1);
            float t_scale = feint_common::Instance()->getRandomNum(0.1f, 1.5f);
            ChargeParticle * chargeParticle  = new ChargeParticle(glm::vec2(
                feint_common::Instance()->getRandomNum(-calculateXPos, calculateXPos), feint_common::Instance()->getRandomNum(-calculateYPos - t_chargeRadius, (*mp_targetPos).y + t_chargeRadius)),
                t_chargingSprites[spriteIndex],
                feint_common::Instance()->getRandomNum(0,3.1415f),
                t_scale, t_scale * 0.05f , t_chargeTime);
            chargeParticle->setChargeMoveSpeed(feint_common::Instance()->getRandomNum(9.1f, 12.5f));
            chargeParticle->setTargetPos(mp_targetPos);
            chargeParticle->setAngle(feint_common::Instance()->getRandomNum(0, 3.1415f));
            m_chargingParticles.push_back( chargeParticle);
        }
        //std::cout << m_chargingParticles.size() << "\n";
    }
}