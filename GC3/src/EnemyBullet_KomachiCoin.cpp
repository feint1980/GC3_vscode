#include "EnemyBullet_KomachiCoin.h"

EnemyBullet_KomachiCoin::EnemyBullet_KomachiCoin()
{

}



EnemyBullet_KomachiCoin::~EnemyBullet_KomachiCoin()
{
    EnemyBulletBase::~EnemyBulletBase();

}

void EnemyBullet_KomachiCoin::update(float deltaTime)
{
    EnemyBulletBase::update(deltaTime);
    
    if(m_tier < m_tierSprites.size() -1)
    {
        float centerX = m_pos.x + m_sprite.getDim().x * m_scale.x / 2.0f;
        float centerY = m_pos.y + m_sprite.getDim().y * m_scale.y / 2.0f;
        if(m_lifeTime < 9.5f)
        {
        
            if(centerX > 320  || centerX < -400 ||
            centerY > 320 || centerY < -380)
            {
                    m_tier++;
                    m_sprite = m_tierSprites[m_tier];
                    if(abs(m_vel.x) > abs(m_vel.y))
                    {
                         m_vel.x = m_vel.x * -0.8f;
                         m_vel.y = m_vel.y * 0.8f;
                    }
                    else
                    {
                         m_vel.x = m_vel.x * 0.8f;
                         m_vel.y = m_vel.y * -0.8f;
                    }
                    
                    m_lifeTime = 10.0f;
            }
        }
    }
    

} 

void EnemyBullet_KomachiCoin::initTierSetting(const std::vector<std::string> & spriteDatas)
{

    for(int i = 0 ; i < spriteDatas.size() ;i++)
    {
        m_tierSprites.push_back(Feintgine::SpriteManager::Instance()->getSprite(spriteDatas[i]));
    }

}

void EnemyBullet_KomachiCoin::setTier(int val)
{
    m_tier = val;
    if(val < 0)
    {
        m_tier = 0;
    }
    if(val > m_tierSprites.size())
    {
        m_tier = m_tierSprites.size() -1;
    }
}





